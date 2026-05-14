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
            FEEDBACK_STATE_ERROR,
            FEEDBACK_STATE_ERROR,
            FEEDBACK_STATE_ERROR,
        }
    };

    // reset `indicators_handler`
    memset(&feedback_api_handler, 0U, sizeof(feedback_api_handler));

    enum FeedbackReturnCode feedback_api_init_rc = feedback_api_init();

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
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

/*!
 * \defgroup test_feedback_api_get_state
 * \{
 */

void test_feedback_api_get_state_valid_feedback(void) {
    feedback_api_handler.feedback_line_state[FEEDBACK_NAME_MUSHROOM_AFTER] = FEEDBACK_STATE_LOW;

    enum FeedbackState state = feedback_api_get_state(FEEDBACK_NAME_MUSHROOM_AFTER);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_STATE_LOW,
        state,
        "State should be FEEDBACK_STATUS_LOW");
}

void test_feedback_api_get_state_invalid_feedback(void) {
    enum FeedbackState state = feedback_api_get_state(FEEDBACK_NAME_COUNT);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_STATE_ERROR,
        state,
        "State should be FEEDBACK_STATUS_ERROR");
}

/*! \} */

/*!
 * \defgroup test_feedback_api_set_state
 * \{
 */

void test_feedback_api_set_state_valid_feedback_and_valid_state(void) {
    enum FeedbackReturnCode feedback_api_set_rc =
        feedback_api_set_state(FEEDBACK_NAME_STEERING_WHEEL, FEEDBACK_STATE_HIGH);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_OK,
        feedback_api_set_rc,
        "Return code should be FEEDBACK_RC_OK");

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        feedback_api_handler.feedback_line_state[FEEDBACK_NAME_STEERING_WHEEL],
        FEEDBACK_STATE_HIGH,
        "After function call feedback line state should be FEEDBACK_STATE_HIGH");
}

void test_feedback_api_set_state_invalid_feedback_and_valid_state(void) {
    enum FeedbackReturnCode feedback_api_set_rc =
        feedback_api_set_state(FEEDBACK_NAME_COUNT, FEEDBACK_STATE_HIGH);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_ERROR,
        feedback_api_set_rc,
        "Return code should be FEEDBACK_RC_ERROR");
}

void test_feedback_api_set_state_valid_feedback_and_invalid_state(void) {
    feedback_api_handler.feedback_line_state[FEEDBACK_NAME_STEERING_WHEEL] =
        FEEDBACK_STATE_ERROR;

    enum FeedbackReturnCode feedback_api_set_rc =
        feedback_api_set_state(FEEDBACK_NAME_STEERING_WHEEL, FEEDBACK_STATE_COUNT);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_ERROR,
        feedback_api_set_rc,
        "Return code should be FEEDBACK_RC_ERROR");

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        feedback_api_handler.feedback_line_state[FEEDBACK_NAME_STEERING_WHEEL],
        FEEDBACK_STATE_ERROR,
        "After function call feedback line state should not be changed");
}

void test_feedback_api_set_state_invalid_feedback_and_invalid_state(void) {
    enum FeedbackReturnCode feedback_api_set_rc =
        feedback_api_set_state(FEEDBACK_NAME_COUNT, FEEDBACK_STATE_COUNT);

    TEST_ASSERT_EQUAL_UINT8_MESSAGE(
        FEEDBACK_RC_ERROR,
        feedback_api_set_rc,
        "Return code should be FEEDBACK_RC_ERROR");
}

/*! \} */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_feedback_api_initialization);
    RUN_TEST(test_feedback_api_get_state_valid_feedback);
    RUN_TEST(test_feedback_api_get_state_invalid_feedback);
    RUN_TEST(test_feedback_api_set_state_valid_feedback_and_valid_state);
    RUN_TEST(test_feedback_api_set_state_invalid_feedback_and_valid_state);
    RUN_TEST(test_feedback_api_set_state_valid_feedback_and_invalid_state);
    RUN_TEST(test_feedback_api_set_state_invalid_feedback_and_invalid_state);

    return UNITY_END();
}
