#ifndef COMUNICATION_H
#define COMUNICATION_H

#include "pal.h"
#include "arena-allocator.h"

enum ComunicationReturnCode {
    COMUNICATION_RC_OK = 0,
    COMUNICATION_RC_ERROR,
};

struct ComunicationHandler {
    struct PalHandler pal_handler;
    struct ArenaAllocatorHandler arena;
    void *tmp_rx_buffer; // TODO: use can stuff when available
};

#endif // COMUNICATION_H
