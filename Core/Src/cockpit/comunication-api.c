#include "comunication.h"
#include "comunication-api.h"

#include "pal.h"
#include "pal-api.h"
#include "eagletrt.h"
// #include "eagletrt-api.h"
#include "arena-allocator.h"
#include "arena-allocator-api.h"

#define RX_CAPACITY (8 * 64U)
#define TX_CAPACITY (8 * 64U)
#define MAX_MSG_SIZE (8U)

EAGLETRT_STATIC struct ComunicationHandler comunication_api_handler;

// TODO: Manage errors more decently
enum ComunicationReturnCode comunication_api_init(void) {
    struct PalHandler pal_handler;
    struct ArenaAllocatorHandler arena;

    arena_allocator_api_init(&arena);

    comunication_api_handler.arena = arena;

    if (pal_api_init(
            &pal_handler,
            RX_CAPACITY,
            TX_CAPACITY,
            MAX_MSG_SIZE,
            NULL, // TODO: put callback to deserialize
            NULL, // TODO: put callback with HAL_FDCAN_AddMessageToTxFifoQ()
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
    return COMUNICATION_RC_OK;
}

// To use inside the receive can callback, use HAL_FDCAN_GetRxMessage to query message
enum ComunicationReturnCode comunication_api_add_to_rx_queue(uint8_t *out_message, uint32_t size) {
    if (pal_api_add_to_rx_queue(&comunication_api_handler.pal_handler, out_message, size) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }
    return COMUNICATION_RC_OK;
}

enum ComunicationReturnCode comunication_api_process_rx_queue(void) {
    if (pal_api_process_rx(&comunication_api_handler.pal_handler, comunication_api_handler.tmp_rx_buffer) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }
    return COMUNICATION_RC_OK;
}

enum ComunicationReturnCode comunication_api_add_to_tx_queue(uint8_t *in_message, uint32_t size) {
    if (pal_api_add_to_tx_queue(&comunication_api_handler.pal_handler, in_message, size) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }
    return COMUNICATION_RC_OK;
}

// call HAL_FDCAN_AddMessageToTxFifoQ
enum ComunicationReturnCode comunication_api_process_tx_queue(void) {
    if (pal_api_process_tx(&comunication_api_handler.pal_handler) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }
    return COMUNICATION_RC_OK;
}
