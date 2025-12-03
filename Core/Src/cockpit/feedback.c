#include "feedback.h"

EAGLETRT_STATIC struct FeedbackHandler feedback_handler; // Private in production

enum FeedbackReturnCode feedback_init(read_feedback fb_read) {

    if (feedback_handler.initialized || fb_read == NULL) {
        return FEEDBACK_RC_ERROR; // Invalid parameters
    }

    feedback_handler.read_fb = fb_read;
    // Initialize feedback states to ERROR to indicate uninitialized state
    for (int i = 0; i < FEEDBACK_NAME_COUNT; i++) {
        feedback_handler.fb_line_state[i] = FEEDBACK_STATUS_ERROR;
    }
    feedback_handler.initialized = true;

    return FEEDBACK_RC_OK;
}
enum FeedbackState feedback_get_state(enum FeedbackName feedback) {

    return feedback_handler.fb_line_state[feedback];
}

void feedback_update_state(void) {
    for (int i = 0; i < FEEDBACK_NAME_COUNT; i++) {
        feedback_handler.fb_line_state[i] = feedback_handler.read_fb((enum FeedbackName)i);
    }
}