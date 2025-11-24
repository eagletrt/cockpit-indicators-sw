#include "feedback.h"

static struct FeedbackHandler feedback_handler;
static volatile bool feedback_enable_interrupts = true;
static bool initialized = false;

enum FeedbackLineState feedback_init(read_feedback fb_before, read_feedback fb_after, read_feedback fb_sw) {

    if (initialized || fb_before == NULL || fb_after == NULL || fb_sw == NULL) {
        return FEEDBACK_ERROR; // Invalid parameters
    }

    enum FeedbackLineState ret_code = FEEDBACK_LOW;

    feedback_handler.read_fb_before = fb_before;
    feedback_handler.read_fb_after = fb_after;
    feedback_handler.read_fb_sw = fb_sw;
    feedback_handler.fb_pressed_before = feedback_handler.read_fb_before();
    feedback_handler.fb_pressed_after = feedback_handler.read_fb_after();
    feedback_handler.fb_sw_pressed = feedback_handler.read_fb_sw();
    initialized = true;
    if (feedback_handler.fb_pressed_before == FEEDBACK_HIGH || feedback_handler.fb_pressed_after == FEEDBACK_HIGH || feedback_handler.fb_sw_pressed == FEEDBACK_HIGH) {
        ret_code = FEEDBACK_HIGH; // At least one button is pressed during initialization
    }

    return ret_code;
}

enum FeedbackLineState feedback_get_state_before() {
    if (initialized == false) {
        return FEEDBACK_ERROR; // No handlers initialized
    }

    return feedback_handler.fb_pressed_before;
}
enum FeedbackLineState feedback_get_state_after() {
    if (initialized == false) {
        return FEEDBACK_ERROR; // No handlers initialized
    }

    return feedback_handler.fb_pressed_after;
}
enum FeedbackLineState feedback_get_state_sw() {
    if (initialized == false) {
        return FEEDBACK_ERROR; // No handlers initialized
    }

    return feedback_handler.fb_sw_pressed;
}

void feedback_update_state() {
    if (initialized) {
        feedback_enable_interrupts = false;
        feedback_handler.fb_pressed_before = feedback_handler.read_fb_before();
        feedback_handler.fb_pressed_after = feedback_handler.read_fb_after();
        feedback_handler.fb_sw_pressed = feedback_handler.read_fb_sw();
        feedback_enable_interrupts = true;
    }
}