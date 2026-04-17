#include "unity.h"
#include "fff.h"
#include "feedback.h"

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(enum FeedbackState, fake_read_feedback, enum FeedbackName);

void setUp() {
    RESET_FAKE(fake_read_feedback);
    FFF_RESET_HISTORY();

    static enum FeedbackState feedback_states[FEEDBACK_NAME_COUNT];
    feedback_states[FEEDBACK_NAME_STEERING_WHEEL] = FEEDBACK_STATUS_HIGH;
    feedback_states[FEEDBACK_NAME_MUSHROOM_BEFORE] = FEEDBACK_STATUS_LOW;
    feedback_states[FEEDBACK_NAME_MUSHROOM_AFTER] = FEEDBACK_STATUS_ERROR;

    SET_RETURN_SEQ(fake_read_feedback, feedback_states, FEEDBACK_NAME_COUNT)

    feedback_init(fake_read_feedback);
}

/*!
 * \defgroup feedback Test cases for feedback module functions
 * \{
 */

void test_feedback_get_state_call_count(void) {
    // Run the update cycle
    feedback_update_state();

    // Verify mock was called correct number of times (once per indicator)
    TEST_ASSERT_EQUAL_INT_MESSAGE(
        FEEDBACK_NAME_COUNT,
        fake_read_feedback_fake.call_count,
        "Update should poll all sensors");
}

void test_feedback_get_state(void) {
    // Run the update cycle
    feedback_update_state();

    // Verify States via getter
    TEST_ASSERT_EQUAL_INT_MESSAGE(
        FEEDBACK_STATUS_HIGH,
        feedback_get_state(FEEDBACK_NAME_STEERING_WHEEL),
        "State should be HIGH after update");

    TEST_ASSERT_EQUAL_INT_MESSAGE(
        FEEDBACK_STATUS_LOW,
        feedback_get_state(FEEDBACK_NAME_MUSHROOM_BEFORE),
        "State should be LOW after update");
    
    TEST_ASSERT_EQUAL_INT_MESSAGE(
        FEEDBACK_STATUS_ERROR,
        feedback_get_state(FEEDBACK_NAME_MUSHROOM_AFTER),
        "State should be ERROR after update");
}

/*! \} */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_feedback_get_state_call_count);
    RUN_TEST(test_feedback_get_state);

    return UNITY_END();
}
