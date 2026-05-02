#include "unity.h"
#include "feedback.h"
#include "feedback-api.h"

#include <string.h>

extern struct FeedbackHandler feedback_api_handler;

void setUp() {
    feedback_api_init();
}

/*!
 * \defgroup test_feedback_api_init
 * \{
 */

void test_feedback_api_initialization(void) {
    struct FeedbackHandler expected_result = {
        .feedback_line_state = {
            FEEDBACK_STATUS_ERROR,
            FEEDBACK_STATUS_ERROR,
            FEEDBACK_STATUS_ERROR,
        }
    };

    // reset `indicators_handler`
    memset(&feedback_api_handler, 0U, sizeof(feedback_api_handler));

    enum FeedbackReturnCode feedback_api_init_rc = feedback_api_init();

    TEST_ASSERT_EQUAL_INT8_MESSAGE(
        FEEDBACK_RC_OK,
        feedback_api_init_rc,
        "Inizializzation should never fail");

    TEST_ASSERT_EQUAL_MEMORY_MESSAGE(
        &expected_result,
        &feedback_api_handler,
        sizeof(feedback_api_handler),
        "Struct must be initialized at error status");
}

/*! \} */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_feedback_api_initialization);

    return UNITY_END();
}
