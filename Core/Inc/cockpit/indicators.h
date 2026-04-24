#ifndef INDICATORS_H
#define INDICATORS_H

#include <stdbool.h>
#include <stdint.h>

/*!
 * \brief Enum for identifying indicators
 */
enum IndicatorsName {
    INDICATORS_NAME_AMS,    //!< AMS Indicator
    INDICATORS_NAME_IMD,    //!< IMD Indicator
    INDICATORS_NAME_TS_OFF, //!< TS_OFF Indicator
    INDICATORS_NAME_TSAL,   //!< TSAL Indicator
    INDICATORS_NAME_COUNT   //!< Total number of indicators
};

/*!
 * \brief Enum with possible return codes for indicators module
 */
enum IndicatorsReturnCode {
    INDICATORS_RC_OK = 0,
    INDICATORS_RC_ERROR,
};

/*!
 * \brief Struct that handles all relevant indicator information
 */
struct IndicatorsHandler {
    float luminosity;                  //!< PWM value for all indicators (0f-1f)
    bool state[INDICATORS_NAME_COUNT]; //!< State of each indicator (on/off)
};

/*!
 * \brief Initialize the indicator module and sets them to OFF state.
 * \param set_indicator_fct Function pointer to set an indicator's PWM value.
 * 
 * \retval True if initialization is successful, else false
 */
enum IndicatorsReturnCode indicators_init(void);

/*!
 * \brief Change the specified indicator state and updates all indicators.
 * \param indicator The indicator to change
 * \param state true to turn on, false to turn off
 */
enum IndicatorsReturnCode indicators_set_indicator(enum IndicatorsName indicator, bool state);

/*!
 * \brief Get the specified indicator state
 * \param indicator The indicator to query
 */
bool indicators_get_indicator(enum IndicatorsName indicator);

/*!
 * \brief Change pwm value of all indicators
 * \param luminosity The PWM value to set for all indicators (0f-1f).
*/
void indicators_set_luminosity(float luminosity);

#endif // INDICATORS_H
