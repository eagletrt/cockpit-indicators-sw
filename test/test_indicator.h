/* Header for indicator unit tests
 * Provides mock helpers, externs and prototypes used by
 * `test/test_indicator.c`.
 */

#ifndef TEST_TEST_INDICATOR_H
#define TEST_TEST_INDICATOR_H

#include "unity.h"
#include "indicators.h"
#include <stdint.h>

extern struct IndicatorsHandler indicators_global_handler;

/* Mocking functions used by the tests */
void indicator_mock_set_indicator(enum IndicatorsName indicator, uint8_t luminosity);
void indicator_reset_mock(void);
void indicator_reset_module_state(void);
void indicator_test_init(void);

/* Test function prototypes */
void indicator_test_initialization_failure_double_init(void);
void indicator_test_initialization_state(void);
void indicator_test_set_indicator_state(enum IndicatorsName indicator);
void indicator_test_set_indicator_state_IMD(void);
void indicator_test_set_indicator_state_AMS(void);
void indicator_test_set_indicator_state_TS_OFF(void);
void indicator_test_set_indicator_state_TSAL(void);
void indicator_test_luminosity_set(void);
void indicator_test_luminosity_clamping(void);

#endif /* TEST_TEST_INDICATOR_H */
