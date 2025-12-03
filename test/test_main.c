#include "eagletrt.h"
#include "test_feedback.h"
#include "test_indicator.h"

void setUp(void) {
    indicator_reset_mock();
    indicator_reset_module_state();
    feedback_reset_mock();
    feedback_reset_module_state();
}

void tearDown(void) {
    // Nothing to clean up after each test
}

int main() {

    UNITY_BEGIN();

    RUN_TEST(indicator_test_initialization_success);
    RUN_TEST(indicator_test_initialization_failure_null_callback);
    RUN_TEST(indicator_test_initialization_failure_double_init);
    RUN_TEST(indicator_test_set_indicator_state);
    RUN_TEST(indicator_test_luminosity_clamping);

    RUN_TEST(feedback_test_initialization_success);
    RUN_TEST(feedback_test_initialization_failure_null_callback);
    RUN_TEST(feedback_test_initialization_failure_double_init);
    RUN_TEST(feedback_test_update_and_get_state);
    RUN_TEST(feedback_test_state_persistence);

    return UNITY_END();
}
