#include "unity.h"
#include "fff.h"
#include "indicators.h"

extern struct IndicatorsHandler indicators_global_handler;

DEFINE_FFF_GLOBALS;
FAKE_VOID_FUNC(fake_set_indicator, enum IndicatorsName, uint8_t);

void setUp() { 
    RESET_FAKE(fake_set_indicator);
    FFF_RESET_HISTORY();
    indicators_init(fake_set_indicator);
}

void test_indicator_initialization_failure_double_init(void) {
    bool is_indicator_initialized = indicators_init(fake_set_indicator);

    TEST_ASSERT_FALSE_MESSAGE(
        is_indicator_initialized,
        "Double initialization should fail");
}

void test_indicator_initialization_state(void) {
    // After initialization, all indicators should be off
    for (int i = 0; i < INDICATORS_NAME_COUNT; i++) {
        TEST_ASSERT_FALSE_MESSAGE(
            indicators_global_handler.state[i],
            "Indicator should be off after init");
    }
}

void test_indicator_set_on_indicators_state(void) {
    indicators_set(true, INDICATORS_NAME_IMD);
    TEST_ASSERT_TRUE_MESSAGE(
    indicators_global_handler.state[INDICATORS_NAME_IMD],
    "IMD indicator should be ON");

    indicators_set(true, INDICATORS_NAME_AMS);
    TEST_ASSERT_TRUE_MESSAGE(
    indicators_global_handler.state[INDICATORS_NAME_AMS],
    "AMS indicator should be ON");

    indicators_set(true, INDICATORS_NAME_TS_OFF);
    TEST_ASSERT_TRUE_MESSAGE(
    indicators_global_handler.state[INDICATORS_NAME_TS_OFF],
    "TS_OFF indicator should be ON");

    indicators_set(true, INDICATORS_NAME_TSAL);
    TEST_ASSERT_TRUE_MESSAGE(
    indicators_global_handler.state[INDICATORS_NAME_TSAL],
    "TSAL indicator should be ON");
}

void test_indicator_luminosity_set(void) {
    // Test: Set valid luminosities
    indicators_set_luminosity(80);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(80, indicators_global_handler.luminosity, "Luminosity should be 80");
}

void test_indicator_luminosity_clamping(void) {
    // Test: Set luminosity above 100
    indicators_set_luminosity(150);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(100, indicators_global_handler.luminosity, "Luminosity should be clamped to 100");
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_indicator_initialization_failure_double_init);
    RUN_TEST(test_indicator_initialization_state);
    RUN_TEST(test_indicator_set_on_indicators_state);
    RUN_TEST(test_indicator_luminosity_set);
    RUN_TEST(test_indicator_luminosity_clamping);

    return UNITY_END();
}
