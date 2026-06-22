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

static void *tmp_rx_buffer; // TODO: use can stuff when available
// static void *tmp_tx_buffer; // TODO: use can stuff when available

EAGLETRT_STATIC struct PalHandler pal_handler;
EAGLETRT_STATIC struct ArenaAllocatorHandler arena;

// TODO: Manage errors
enum ComunicationReturnCode comunication_api_init(void) {
    arena_allocator_api_init(&arena);

    if (pal_api_init(
            &pal_handler,
            RX_CAPACITY,
            TX_CAPACITY,
            MAX_MSG_SIZE,
            NULL, // TODO: put callback
            NULL, // TODO: put callback
            NULL,
            NULL,
            &arena) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }

    return COMUNICATION_RC_OK;
}

enum ComunicationReturnCode comunication_api_deinit(void) {
    arena_allocator_api_free(&arena);
    return COMUNICATION_RC_OK;
}

// To use inside the receive can callback
enum ComunicationReturnCode comunication_api_add_to_rx_queue(uint8_t *out_message, uint32_t size) {
    if (pal_api_add_to_rx_queue(&pal_handler, out_message, size) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }
    return COMUNICATION_RC_OK;
}

enum ComunicationReturnCode comunication_api_process_rx_queue(void) {
    if (pal_api_process_rx(&pal_handler, tmp_rx_buffer) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }
    return COMUNICATION_RC_OK;
}

enum ComunicationReturnCode comunication_api_add_to_tx_queue(uint8_t *in_message, uint32_t size) {
    if (pal_api_add_to_tx_queue(&pal_handler, in_message, size) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }
    return COMUNICATION_RC_OK;
}

enum ComunicationReturnCode comunication_api_process_tx_queue(void) {
    if (pal_api_process_tx(&pal_handler) != PAL_RC_OK) {
        return COMUNICATION_RC_ERROR;
    }
    return COMUNICATION_RC_OK;
}
