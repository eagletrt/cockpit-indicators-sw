#include "feedback-api.h"

#include "eagletrt.h"
#include <stdlib.h>
#include <stdint.h>

EAGLETRT_STATIC struct FeedbackHandler feedback_api_handler;

enum FeedbackReturnCode feedback_api_init() {
    // Initialize feedback states to ERROR to indicate uninitialized state
    for (int i = 0; i < FEEDBACK_NAME_COUNT; i++) {
        feedback_api_handler.feedback_line_state[i] = FEEDBACK_STATE_ERROR;
    }

    return FEEDBACK_RC_OK;
}

enum FeedbackState feedback_api_get_state(enum FeedbackName feedback) {
    if (feedback >= FEEDBACK_NAME_COUNT) {
        return FEEDBACK_STATE_ERROR;
    }

    return feedback_api_handler.feedback_line_state[feedback];
}

enum FeedbackReturnCode feedback_api_set_state(enum FeedbackName feedback, enum FeedbackState state) {
    if (feedback >= FEEDBACK_NAME_COUNT
            || state >= FEEDBACK_STATE_COUNT) {
        return FEEDBACK_RC_ERROR;
    }

    feedback_api_handler.feedback_line_state[feedback] = state;

    return FEEDBACK_RC_OK;
}
