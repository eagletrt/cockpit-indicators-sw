#include "comunication.h"
#include "comunication-api.h"

#include "pal.h"
#include "pal-api.h"
#include "eagletrt.h"
#include "arena-allocator.h"
#include "arena-allocator-api.h"

#include <string.h>

EAGLETRT_STATIC struct ComunicationHandler comunication_api_handler;

// TODO: Manage errors more decently
enum ComunicationReturnCode comunication_api_init(pal_deserialize_callback pal_deserialize, pal_send_callback pal_send) {
    struct PalHandler pal_handler;
    struct ArenaAllocatorHandler arena;

    arena_allocator_api_init(&arena);

    comunication_api_handler.arena = arena;

    if (pal_api_init(
            &pal_handler,
            RX_CAPACITY,
            TX_CAPACITY,
            MAX_MSG_SIZE,
            pal_deserialize,
            pal_send, // TODO: pass callback with HAL_FDCAN_AddMessageToTxFifoQ()
            NULL,
            NULL,
            &arena) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }

    comunication_api_handler.pal_handler = pal_handler;

    return COMUNICATION_RC_OK;
}

enum ComunicationReturnCode comunication_api_deinit(void) {
    arena_allocator_api_free(&comunication_api_handler.arena);
    memset((void *)&comunication_api_handler, 0U, sizeof(comunication_api_handler));
    return COMUNICATION_RC_OK;
}

// To use inside the receive can callback, use HAL_FDCAN_GetRxMessage to query message
enum ComunicationReturnCode comunication_api_add_to_rx_queue(struct ComunicationFrame *frame) {
    if (frame == NULL) {
        return COMUNICATION_RC_NULL_POINTER;
    }

    struct ComunicationFrame buffer = *frame;
    if (pal_api_add_to_rx_queue(&comunication_api_handler.pal_handler, (uint8_t *)&buffer, (uint32_t)sizeof(buffer)) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }
    return COMUNICATION_RC_OK;
}

enum ComunicationReturnCode comunication_api_add_to_tx_queue(struct ComunicationFrame *frame) {
    if (frame == NULL) {
        return COMUNICATION_RC_NULL_POINTER;
    }

    struct ComunicationFrame buffer = *frame;
    if (pal_api_add_to_tx_queue(&comunication_api_handler.pal_handler, (uint8_t *)&buffer, (uint32_t)sizeof(buffer)) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }

    return COMUNICATION_RC_OK;
}

enum ComunicationReturnCode comunication_api_process_rx_queue(void) {
    enum PalReturnCode return_code;

    do {
        return_code = pal_api_process_rx(&comunication_api_handler.pal_handler, comunication_api_handler.tmp_rx_buffer);
    } while(return_code != PAL_RC_OK);

    if(return_code != PAL_RC_OK && return_code != PAL_RC_QUEUE_EMPTY) {
        return COMUNICATION_RC_ERROR;
    }

    return COMUNICATION_RC_OK;
}

// call HAL_FDCAN_AddMessageToTxFifoQ
enum ComunicationReturnCode comunication_api_process_tx_queue(void) {
    enum PalReturnCode return_code;

    do {
        return_code = pal_api_process_tx(&comunication_api_handler.pal_handler);
    } while(return_code == PAL_RC_OK);

    if(return_code != PAL_RC_OK && return_code != PAL_RC_QUEUE_EMPTY) {
        return COMUNICATION_RC_ERROR;
    }

    return COMUNICATION_RC_OK;
}
