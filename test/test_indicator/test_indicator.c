#include "unity.h"
#include "indicators.h"

#include <string.h>

extern struct IndicatorsHandler indicators_handler;

void setUp() {
    indicators_init();
}

/*!
 * \defgroup test_indicators_init
 * \{
 */

void test_indicators_initialization(void) {
    struct IndicatorsHandler expected_result = {
        .state = { false },
        .luminosity = 0,
    };

    // reset `indicators_handler`
    memset(&indicators_handler, 0U, sizeof(indicators_handler));

    enum IndicatorsReturnCode indicators_init_rc = indicators_init();

    TEST_ASSERT_EQUAL_INT8_MESSAGE(
        INDICATORS_RC_OK,
        indicators_init_rc,
        "Inizializzation should never fail");

    TEST_ASSERT_EQUAL_MEMORY_MESSAGE(
        &expected_result,
        &indicators_handler,
        sizeof(indicators_handler),
        "Struct must be initialized with all data at 0");
}

/*! \} */

/*!
 * \defgroup test_indicators_set
 * \{
 */

void test_indicators_set_on_indicators_valid_state(void) {
    enum IndicatorsReturnCode indicators_set_rc = indicators_set_indicator(INDICATORS_NAME_IMD, true);

    TEST_ASSERT_EQUAL_INT8_MESSAGE(
        INDICATORS_RC_OK,
        indicators_set_rc,
        "Return code should be INDICATORS_RC_OK");

    TEST_ASSERT_TRUE_MESSAGE(
        indicators_handler.state[INDICATORS_NAME_IMD],
        "Indicator should be ON");
}

void test_indicators_set_on_indicators_invalid_state(void) {
    enum IndicatorsReturnCode indicators_set_rc = indicators_set_indicator(INDICATORS_NAME_COUNT, true);

    TEST_ASSERT_EQUAL_INT8_MESSAGE(
        INDICATORS_RC_ERROR,
        indicators_set_rc,
        "Return code should be INDICATORS_RC_ERROR");
}

/*! \} */

/*!
 * \defgroup test_indicators_set_luminosity
 * \{
 */

void test_indicators_set_luminosity_in_range_value(void) {
    indicators_set_luminosity(0.8);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        0.8,
        indicators_handler.luminosity,
        "Luminosity should be 80%");
}

void test_indicators_set_luminosity_out_of_range_value_high(void) {
    indicators_set_luminosity(816.80085);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        1.0,
        indicators_handler.luminosity,
        "Luminosity should be 100%");
}

void test_indicators_set_luminosity_out_of_range_value_low(void) {
    indicators_set_luminosity(-816.80085);
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(
        0.0,
        indicators_handler.luminosity,
        "Luminosity should be 0%");
}

/*! \} */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_indicators_initialization);
    RUN_TEST(test_indicators_set_on_indicators_valid_state);
    RUN_TEST(test_indicators_set_on_indicators_invalid_state);
    RUN_TEST(test_indicators_set_luminosity_in_range_value);
    RUN_TEST(test_indicators_set_luminosity_out_of_range_value_high);
    RUN_TEST(test_indicators_set_luminosity_out_of_range_value_low);

    return UNITY_END();
}
