#include "unity.h"
#include "indicators.h"
#include <string.h>
#include <stdint.h>
#include "test_indicator.h"

extern struct IndicatorsHandler indicators_global_handler;

struct MockState {
    enum IndicatorsName last_indicator;
    uint8_t last_luminosity;
    int call_count;
};

static struct MockState mock_state;

// MOCKING FUNCTIONS

// The mock callback function to simulate hardware output
void indicator_mock_set_indicator(enum IndicatorsName indicator, uint8_t luminosity) {
    mock_state.last_indicator = indicator;
    mock_state.last_luminosity = luminosity;
    mock_state.call_count++;
}

// Helper to reset mock state
void indicator_reset_mock() {
    mock_state.last_indicator = INDICATORS_NAME_COUNT; // Invalid init value
    mock_state.last_luminosity = 0;
    mock_state.call_count = 0;
}

// Helper to forcefully reset the internal module state
void indicator_reset_module_state() {
    indicators_global_handler.initialized = false;
    memset(indicators_global_handler.state, 0, sizeof(indicators_global_handler.state));
    indicators_global_handler.luminosity = 0;
    indicators_global_handler.set_indicator = NULL;
}

void indicator_helper_initialize(void) {
    indicators_init(indicator_mock_set_indicator);
    indicator_reset_mock();
}

// TEST FUNCTIONS

void indicator_test_initialization_success(void) {
    bool result = indicators_init(indicator_mock_set_indicator);

    TEST_ASSERT_TRUE_MESSAGE(result, "Initialization should return true");

    // Initialization triggers an update, so mock should be called 4 times (once per indicator)
    TEST_ASSERT_EQUAL_INT_MESSAGE(4, mock_state.call_count, "Init should trigger update for all 4 indicators");
}

void indicator_test_initialization_check(void) {
    indicator_reset_module_state();
    indicators_init(indicator_mock_set_indicator);

    TEST_ASSERT_TRUE_MESSAGE(is_indicators_initialized(), "Module should be initialized after init call");
}

void indicator_test_initialization_failure_null_callback(void) {
    bool result = indicators_init(NULL);

    TEST_ASSERT_FALSE_MESSAGE(result, "Init should fail with NULL callback");
    TEST_ASSERT_FALSE_MESSAGE(is_indicators_initialized(), "Module should not be initialized");
}

void indicator_test_initialization_failure_double_init(void) {
    // First init
    indicators_init(indicator_mock_set_indicator);

    // Second init should fail
    bool result = indicators_init(indicator_mock_set_indicator);

    TEST_ASSERT_FALSE_MESSAGE(result, "Double initialization should fail");
}

void indicator_test_initialization_state(void) {
    indicator_helper_initialize();
    // After initialization, all indicators should be off
    for (int i = 0; i < INDICATORS_NAME_COUNT; i++) {
        TEST_ASSERT_FALSE_MESSAGE(indicators_global_handler.state[i], "Indicator should be off after init");
    }
}

void indicator_test_set_indicator_state(enum IndicatorsName indicator) {
    indicator_helper_initialize();
    // Test: Set AMS indicator ON
    indicators_set(true, indicator);

    TEST_ASSERT_TRUE_MESSAGE(indicators_global_handler.state[indicator], "Indicator should be ON");
}

// Specific tests for each indicator
void indicator_test_set_indicator_state_IMD(void) {
    indicator_test_set_indicator_state(INDICATORS_NAME_IMD);
}
void indicator_test_set_indicator_state_AMS(void) {
    indicator_test_set_indicator_state(INDICATORS_NAME_AMS);
}
void indicator_test_set_indicator_state_TS_OFF(void) {
    indicator_test_set_indicator_state(INDICATORS_NAME_TS_OFF);
}
void indicator_test_set_indicator_state_TSAL(void) {
    indicator_test_set_indicator_state(INDICATORS_NAME_TSAL);
}

void indicator_test_luminosity_set(void) {
    indicators_init(indicator_mock_set_indicator);
    indicator_reset_mock();

    // Test: Set valid luminosities
    indicators_set_luminosity(80);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(80, indicators_global_handler.luminosity, "Luminosity should be 80");
}

void indicator_test_luminosity_clamping(void) {
    indicators_init(indicator_mock_set_indicator);
    indicator_reset_mock();

    // Test: Set luminosity above 100
    indicators_set_luminosity(150);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(100, indicators_global_handler.luminosity, "Luminosity should be clamped to 100");
}