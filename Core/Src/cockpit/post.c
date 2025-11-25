#include "post.h"

enum PostReturnCode post_run_power_on_tests(struct PostInitData *init_data) {

    if (init_data == NULL || init_data->tim_post_function == NULL) {
        return POST_NULL_POINTER;
    }
    if (init_data->fb_before == NULL || init_data->fb_after == NULL || init_data->fb_steering_wheel == NULL) {
        return POST_NULL_POINTER;
    }
    if (init_data->ams_indicator_set == NULL || init_data->imd_indicator_set == NULL || init_data->ts_off_indicator_set == NULL || init_data->tsal_indicator_set == NULL) {
        return POST_NULL_POINTER;
    }

    // Check if TIM module is initialized
    if (!init_data->tim_post_function()) {
        return POST_UNINITIALIZED;
    }

    // Additional power-on tests can be added here

    return POST_OK;
}

enum PostReturnCode post_run_power_on_init_tests(void) {
    // Check if feedback module is initialized
    if (feedback_get_state() == FEEDBACK_ERROR) {
        return POST_UNINITIALIZED;
    }
    if (feedback_get_state() == FEEDBACK_LOW) {
        // At least one mushroom button is pressed during initialization
        return POST_SETUP_ERROR;
    }
    // Check if indicators module is initialized
    if (!is_indicators_initialized()) {
        return POST_UNINITIALIZED;
    }
    return POST_OK;
};