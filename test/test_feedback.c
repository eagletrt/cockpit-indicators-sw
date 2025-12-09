#include "unity.h"
#include "feedback.h"
#include <string.h>
#include <stdio.h>
#include "test_feedback.h"

extern struct FeedbackHandler feedback_handler;

// MOCKING FUNCTIONS

// Array to control what the mock returns for each sensor
static enum FeedbackState mock_input_values[FEEDBACK_NAME_COUNT];
static int mock_call_count;

// The mock callback function to simulate reading hardware
enum FeedbackState mock_read_feedback(enum FeedbackName feedback) {
    mock_call_count++;
    if (feedback < FEEDBACK_NAME_COUNT) {
        return mock_input_values[feedback];
    }
    return FEEDBACK_STATUS_ERROR;
}

// Helper to reset mock state
void feedback_reset_mock() {
    mock_call_count = 0;
    for (int i = 0; i < FEEDBACK_NAME_COUNT; i++) {
        mock_input_values[i] = FEEDBACK_STATUS_LOW; // Default safe state
    }
}

// Helper to forcefully reset the internal module state
void feedback_reset_module_state() {
    feedback_handler.initialized = false;
    feedback_handler.read_fb = NULL;
    // Clear state array
    memset((void *)feedback_handler.fb_line_state, 0, sizeof(feedback_handler.fb_line_state));
}

void feedback_helper_initialize_with_mock_states(void) {
    feedback_init(mock_read_feedback);

    // Setup Mock Inputs:
    // 1. Steering Wheel -> HIGH
    // 2. Mushroom Before -> LOW
    // 3. Mushroom After -> ERROR (simulate fault)

    feedback_reset_mock(); // Reset mock struct

    mock_input_values[FEEDBACK_NAME_1] = FEEDBACK_STATUS_HIGH;
    mock_input_values[FEEDBACK_NAME_2] = FEEDBACK_STATUS_LOW;
    mock_input_values[FEEDBACK_NAME_3] = FEEDBACK_STATUS_ERROR;
}

// TEST FUNCTIONS

void feedback_test_initialization_success(void) {
    enum FeedbackReturnCode result = feedback_init(mock_read_feedback);

    TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_RC_OK, result, "Initialization should return OK");
    TEST_ASSERT_TRUE_MESSAGE(feedback_handler.initialized, "Module should be marked initialized");
}

void feedback_test_initialization_state(void) {
    feedback_init(mock_read_feedback);

    // Check that all feedback states are initialized to ERROR
    for (int i = 0; i < FEEDBACK_NAME_COUNT; i++) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_STATUS_ERROR, feedback_handler.fb_line_state[i], "Feedback state should be initialized to ERROR");
    }
}

void feedback_test_initialization_failure_null_callback(void) {
    enum FeedbackReturnCode result = feedback_init(NULL);

    TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_RC_ERROR, result, "Init should fail with NULL callback");
    TEST_ASSERT_FALSE_MESSAGE(feedback_handler.initialized, "Module should not be initialized");
}

void feedback_test_initialization_failure_double_init(void) {
    // First init
    feedback_init(mock_read_feedback);
    // Second init should fail
    enum FeedbackReturnCode result = feedback_init(mock_read_feedback);

    TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_RC_ERROR, result, "Double initialization should return ERROR");
}

void feedback_test_get_state_call_count(void) {

    feedback_helper_initialize_with_mock_states();

    // Run the update cycle
    feedback_update_state();

    // Verify mock was called correct number of times (once per indicator)
    TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_NAME_COUNT, mock_call_count, "Update should poll all sensors");

    // Verify States via getter
    TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_STATUS_HIGH, feedback_get_state(FEEDBACK_NAME_1), "State should be HIGH after update");
    TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_STATUS_LOW, feedback_get_state(FEEDBACK_NAME_2), "State should be LOW after update");
    TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_STATUS_ERROR, feedback_get_state(FEEDBACK_NAME_3), "State should be ERROR after update");
}

void feedback_test_get_state(void) {

    feedback_helper_initialize_with_mock_states();

    // Run the update cycle
    feedback_update_state();

    // Verify States via getter
    TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_STATUS_HIGH, feedback_get_state(FEEDBACK_NAME_1), "State should be HIGH after update");
    TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_STATUS_LOW, feedback_get_state(FEEDBACK_NAME_2), "State should be LOW after update");
    TEST_ASSERT_EQUAL_INT_MESSAGE(FEEDBACK_STATUS_ERROR, feedback_get_state(FEEDBACK_NAME_3), "State should be ERROR after update");
}
