#include "comunication.h"
#include "comunication-api.h"

#include "pal.h"
#include "eagletrt.h"
// #include "eagletrt-api.h"
#include "arena-allocator.h"
#include "arena-allocator-api.h"

EAGLETRT_STATIC struct PalHandler pal_handler;
EAGLETRT_STATIC struct ArenaAllocatorHandler arena;

// TODO: Manage errors
enum ComunicationReturnCode comunication_api_init(void) {
    arena_allocator_api_init(&arena);

    if (pal_api_init(
            &pal_handler,
            10U,
            10U,
            64U,
            NULL,
            NULL,
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
