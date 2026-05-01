#include "feedback-api.h"

#include "eagletrt.h"
#include <stdlib.h>
#include <stdint.h>

EAGLETRT_STATIC struct FeedbackHandler feedback_handler;

enum FeedbackReturnCode feedback_init() {
    if (feedback_handler.initialized) {
        return FEEDBACK_RC_ERROR;
    }

    // Initialize feedback states to ERROR to indicate uninitialized state
    for (int i = 0; i < FEEDBACK_NAME_COUNT; i++) {
        feedback_handler.fb_line_state[i] = FEEDBACK_STATUS_ERROR;
    }

    feedback_handler.initialized = true;

    return FEEDBACK_RC_OK;
}

enum FeedbackState feedback_get_state(enum FeedbackName feedback) {
    if (feedback < 0 || feedback >= FEEDBACK_NAME_COUNT)
        return false;

    return feedback_handler.fb_line_state[feedback];
}

void feedback_update_state(void) {
    // TODO: decide feedback update logic
    // for (int i = 0; i < FEEDBACK_NAME_COUNT; i++) {
    //     feedback_handler.fb_line_state[i] =
    //         feedback_handler.read_fb((enum FeedbackName)i);
    // }
}
