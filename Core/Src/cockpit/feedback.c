#include "feedback.h"

static struct FeedbackHandler feedback_handler;

enum FeedbackRC feedback_init(read_feedback fb_read) {

    if (feedback_handler.initialized || fb_read == NULL) {
        return FEEDBACK_RC_ERROR; // Invalid parameters
    }

    feedback_handler.read_fb = fb_read;
    // Initialize feedback states to ERROR to indicate uninitialized state
    feedback_handler.fb_pressed_before = FEEDBACK_STATUS_ERROR;
    feedback_handler.fb_pressed_after = FEEDBACK_STATUS_ERROR;
    feedback_handler.fb_sw_pressed = FEEDBACK_STATUS_ERROR;
    feedback_handler.initialized = true;

    return FEEDBACK_RC_OK;
}
enum FeedbackState feedback_get_state(enum FeedbackName feedback) {
    switch (feedback) {
        case FEEDBACK_NAME_STEERING_WHEEL:
            return feedback_handler.fb_sw_pressed;
        case FEEDBACK_NAME_MUSHROOM_BEFORE:
            return feedback_handler.fb_pressed_before;
        case FEEDBACK_NAME_MUSHROOM_AFTER:
            return feedback_handler.fb_pressed_after;
        default:
            return FEEDBACK_STATUS_ERROR;
    }
}

void feedback_update_state(void) {
    feedback_handler.fb_pressed_before = feedback_handler.read_fb(FEEDBACK_NAME_MUSHROOM_BEFORE);
    feedback_handler.fb_pressed_after = feedback_handler.read_fb(FEEDBACK_NAME_MUSHROOM_AFTER);
    feedback_handler.fb_sw_pressed = feedback_handler.read_fb(FEEDBACK_NAME_STEERING_WHEEL);
}