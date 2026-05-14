#include "post.h"
#include "feedback-api.h"
#include "indicators-api.h"

#include <stdlib.h>

enum PostReturnCode post_run_power_on_tests(void) {
    // Indicators module initializzation
    if (indicators_api_init() == INDICATORS_RC_ERROR) {
        return POST_RC_UNINITIALIZED;
    }

    // Initialization functions
    if (feedback_api_init() == FEEDBACK_RC_ERROR) {
        return POST_RC_UNINITIALIZED;
    }

    return POST_RC_OK;
}
