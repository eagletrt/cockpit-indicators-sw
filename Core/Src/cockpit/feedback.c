#include "feedback.h"

static struct FeedbackHandler feedback_handler;
static bool initialized = false;

enum FeedbackLineState feedback_init(read_feedback fb_before, read_feedback fb_after, read_feedback fb_sw) {

    if (initialized || fb_before == NULL || fb_after == NULL || fb_sw == NULL) {
        return FEEDBACK_ERROR; // Invalid parameters
    }

    enum FeedbackLineState ret_code = FEEDBACK_HIGH;

    feedback_handler.read_fb_before = fb_before;
    feedback_handler.read_fb_after = fb_after;
    feedback_handler.read_fb_sw = fb_sw;
    feedback_handler.fb_pressed_before = (feedback_handler.read_fb_before() ? FEEDBACK_HIGH : FEEDBACK_LOW);
    feedback_handler.fb_pressed_after = (feedback_handler.read_fb_after() ? FEEDBACK_HIGH : FEEDBACK_LOW);
    feedback_handler.fb_sw_pressed = (feedback_handler.read_fb_sw() ? FEEDBACK_HIGH : FEEDBACK_LOW);
    initialized = true;

    if (feedback_handler.fb_pressed_before == FEEDBACK_LOW || feedback_handler.fb_pressed_after == FEEDBACK_LOW || feedback_handler.fb_sw_pressed == FEEDBACK_LOW) {
        ret_code = FEEDBACK_LOW; // At least one button is pressed during initialization
    }

    return ret_code;
}

enum FeedbackLineState feedback_get_state(void) {
    if (initialized == false) {
        return FEEDBACK_ERROR; // No handlers initialized
    }

    if (feedback_handler.fb_pressed_before == FEEDBACK_LOW || feedback_handler.fb_pressed_after == FEEDBACK_LOW || feedback_handler.fb_sw_pressed == FEEDBACK_LOW) {
        return FEEDBACK_LOW; // At least one button is pressed
    }

    return FEEDBACK_HIGH; // No buttons are pressed
}

enum FeedbackLineState feedback_get_state_before(void) {
    if (initialized == false) {
        return FEEDBACK_ERROR; // No handlers initialized
    }

    return feedback_handler.fb_pressed_before;
}
enum FeedbackLineState feedback_get_state_after(void) {
    if (initialized == false) {
        return FEEDBACK_ERROR; // No handlers initialized
    }

    return feedback_handler.fb_pressed_after;
}
enum FeedbackLineState feedback_get_state_sw(void) {
    if (initialized == false) {
        return FEEDBACK_ERROR; // No handlers initialized
    }

    return feedback_handler.fb_sw_pressed;
}

void feedback_update_state(void) {
    if (initialized) {
        feedback_handler.fb_pressed_before = (feedback_handler.read_fb_before() ? FEEDBACK_HIGH : FEEDBACK_LOW);
        feedback_handler.fb_pressed_after = (feedback_handler.read_fb_after() ? FEEDBACK_HIGH : FEEDBACK_LOW);
        feedback_handler.fb_sw_pressed = (feedback_handler.read_fb_sw() ? FEEDBACK_HIGH : FEEDBACK_LOW);
    }
}