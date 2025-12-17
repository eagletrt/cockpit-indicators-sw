#include "post.h"

enum PostReturnCode post_run_power_on_tests(struct PostInitData *init_data) {

    // Validate input pointers
    if (init_data == NULL || init_data->tim_post_function == NULL || init_data->indicator_set == NULL || init_data->fb_read == NULL) {
        return POST_RC_INVALID_POINTER;
    }

    // Check if TIM module is initialized
    if (!init_data->tim_post_function()) {
        return POST_RC_UNINITIALIZED;
    }

    // Initialization functions
    if (feedback_init(init_data->fb_read) == FEEDBACK_RC_ERROR) {
        return POST_RC_UNINITIALIZED;
    }

    if (!indicators_init(init_data->indicator_set)) {
        return POST_RC_UNINITIALIZED;
    }

    // Update feedback states
    feedback_update_state();

    // Check if feedback module is not updating properly
    if (feedback_get_state(FEEDBACK_NAME_MUSHROOM_AFTER) == FEEDBACK_STATUS_ERROR || feedback_get_state(FEEDBACK_NAME_MUSHROOM_BEFORE) == FEEDBACK_STATUS_ERROR || feedback_get_state(FEEDBACK_NAME_STEERING_WHEEL) == FEEDBACK_STATUS_ERROR) {
        return POST_RC_SETUP_ERROR;
    }

    return POST_RC_OK;
}