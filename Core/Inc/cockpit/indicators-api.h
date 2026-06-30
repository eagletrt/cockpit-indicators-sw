#ifndef INDICATORS_API_H
#define INDICATORS_API_H

#include "indicators.h"

/*!
 * \brief Initialize the indicator module and sets them to OFF state.
 * \param set_indicator_fct Function pointer to set an indicator's PWM value.
 *
 * \retval True if initialization is successful, else false
 */
enum IndicatorsReturnCode indicators_api_init(void);

/*!
 * \brief Change the specified indicator state and updates all indicators.
 * \param indicator The indicator to change
 * \param state true to turn on, false to turn off
 */
enum IndicatorsReturnCode indicators_api_set_indicator(enum IndicatorsName indicator, bool state);

/*!
 * \brief Get the specified indicator state
 * \param indicator The indicator to query
 */
bool indicators_api_get_indicator(enum IndicatorsName indicator);

/*!
 * \brief Change pwm value of all indicators
 * \param luminosity The PWM value to set for all indicators (0f-1f).
*/
void indicators_api_set_luminosity(float luminosity);

// TODO: make documentation
void indicators_api_update_timestamp(enum IndicatorsName indicator);

bool indicators_api_is_timestamp_expired(enum IndicatorsName indicator);

#endif // INDICATORS_API_H
