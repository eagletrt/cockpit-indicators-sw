#include "post.h"
#include "feedback-api.h"
#include "indicators-api.h"
#include "can-communications-api.h"

#include <stdlib.h>

enum PostReturnCode post_init(struct PostInit *init) {
    // Indicators module initializzation
    if (indicators_api_init() == INDICATORS_RC_ERROR) {
        return POST_RC_UNINITIALIZED;
    }

    // Initialization functions
    if (feedback_api_init() == FEEDBACK_RC_ERROR) {
        return POST_RC_UNINITIALIZED;
    }

    if (can_communications_api_init(init->config) != CAN_COMMUNICATION_RC_OK) {
        return POST_RC_UNINITIALIZED;
    }

    if (!(init->adc_return_code && init->fdcan_return_code)) {
        return POST_RC_UNINITIALIZED;
    }

    return POST_RC_OK;
}
