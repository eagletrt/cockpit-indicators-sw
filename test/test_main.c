#include "eagletrt.h"
#include "test_feedback.h"
#include "test_indicator.h"

void setUp(void) {
    indicator_test_init();
    feedback_test_init();
}

void tearDown(void) {
    // Nothing to clean up after each test
}

int main() {

    UNITY_BEGIN();

    RUN_TEST(indicator_test_initialization_failure_double_init);
    RUN_TEST(indicator_test_set_indicator_state_IMD);
    RUN_TEST(indicator_test_set_indicator_state_AMS);
    RUN_TEST(indicator_test_set_indicator_state_TS_OFF);
    RUN_TEST(indicator_test_set_indicator_state_TSAL);
    RUN_TEST(indicator_test_luminosity_set);
    RUN_TEST(indicator_test_luminosity_clamping);

    RUN_TEST(feedback_test_get_state);
    RUN_TEST(feedback_test_get_state_call_count);

    return UNITY_END();
}
