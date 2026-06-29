#ifndef COMUNICATION_H
#define COMUNICATION_H

#include "pal.h"
#include "arena-allocator.h"

#define RX_CAPACITY (8 * 64U)
#define TX_CAPACITY (8 * 64U)
#define MAX_MSG_SIZE (8U)

enum ComunicationReturnCode {
    COMUNICATION_RC_OK = 0,
    COMUNICATION_RC_NULL_POINTER,
    COMUNICATION_RC_ERROR,
};

struct ComunicationHandler {
    struct PalHandler pal_handler;
    struct ArenaAllocatorHandler arena;
    void *tmp_rx_buffer; // TODO: maybe use callback?
};

struct [[gnu::packed]] ComunicationFrame {
    uint32_t id;                /*!< CAN identifier (Standard 11-bit or Extended 29-bit) */
    uint8_t length;             /*!< Count of valid data bytes within the array (0..8) */
    uint8_t data[MAX_MSG_SIZE]; /*!< Raw payload byte buffer */
};

#endif // COMUNICATION_H
