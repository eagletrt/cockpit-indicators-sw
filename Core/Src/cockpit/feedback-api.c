#include "feedback-api.h"

#include "eagletrt.h"
#include <stdlib.h>
#include <stdint.h>

EAGLETRT_STATIC struct FeedbackHandler feedback_api_handler;

enum FeedbackReturnCode feedback_api_init() {
    // Initialize feedback states to ERROR to indicate uninitialized state
    for (int i = 0; i < FEEDBACK_NAME_COUNT; i++) {
        feedback_api_handler.feedback_line_state[i] = FEEDBACK_STATUS_ERROR;
    }

    return FEEDBACK_RC_OK;
}

enum FeedbackState feedback_api_get_state(enum FeedbackName feedback) {
    if (feedback >= FEEDBACK_NAME_COUNT) {
        return false;
    }

    return feedback_api_handler.feedback_line_state[feedback];
}

void feedback_update_state(void) {
    // TODO: decide feedback update logic
    // for (int i = 0; i < FEEDBACK_NAME_COUNT; i++) {
    //     feedback_handler.fb_line_state[i] =
    //         feedback_handler.read_fb((enum FeedbackName)i);
    // }
}
