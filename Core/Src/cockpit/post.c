#include "post.h"

enum PostReturnCode post_run_power_on_tests(struct PostInitData *init_data) {

    if (init_data == NULL || init_data->tim_post_function == NULL) {
        return POST_RC_INVALID_POINTER;
    }
    if (init_data->fb_read == NULL) {
        return POST_RC_INVALID_POINTER;
    }
    if (init_data->indicator_set == NULL) {
        return POST_RC_INVALID_POINTER;
    }

    // Check if TIM module is initialized
    if (!init_data->tim_post_function()) {
        return POST_RC_UNINITIALIZED;
    }

    // Additional power-on tests can be added here

    return POST_RC_OK;
}

enum PostReturnCode post_run_power_on_init_tests(void) {

    // Update feedback states
    feedback_update_state();

    // Check if feedback module is initialized
    if (feedback_get_state(FEEDBACK_NAME_MUSHROOM_AFTER) == FEEDBACK_STATUS_ERROR || feedback_get_state(FEEDBACK_NAME_MUSHROOM_BEFORE) == FEEDBACK_STATUS_ERROR || feedback_get_state(FEEDBACK_NAME_STEERING_WHEEL) == FEEDBACK_STATUS_ERROR) {
        return POST_RC_UNINITIALIZED;
    }
    if (feedback_get_state(FEEDBACK_NAME_MUSHROOM_AFTER) == FEEDBACK_STATUS_LOW || feedback_get_state(FEEDBACK_NAME_MUSHROOM_BEFORE) == FEEDBACK_STATUS_LOW || feedback_get_state(FEEDBACK_NAME_STEERING_WHEEL) == FEEDBACK_STATUS_LOW) {
        // At least one mushroom button is pressed during initialization
        return POST_RC_SETUP_ERROR;
    }
    // Check if indicators module is initialized
    if (!is_indicators_initialized()) {
        return POST_RC_UNINITIALIZED;
    }
    return POST_RC_OK;
};