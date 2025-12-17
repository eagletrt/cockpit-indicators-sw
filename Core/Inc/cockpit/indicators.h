#ifndef INDICATORS_H
#define INDICATORS_H

#include <stdbool.h>
#include <stdio.h>

#include <stdint.h> // Fixes: unknown type name 'uint8_t' in testing environment
#include "eagletrt.h"

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
 * \brief Function signature for setting indicators
 * 
 * \param indicator Enum indicating which indicator to set
 * \param luminosity PWM value to set (0-100)
 * 
 */
typedef void (*indicator_set)(enum IndicatorsName indicator, uint8_t luminosity);

/*!
 * \brief Struct that handles all relevant indicator information
 */
struct IndicatorsHandler {
    indicator_set set_indicator;       //!< Function to set indicators
    uint8_t luminosity;                //!< PWM value for all indicators (0-100)
    bool state[INDICATORS_NAME_COUNT]; //!< State of each indicator (on/off)
    bool initialized;                  //!< Indicates if the indicators handler has been initialized
};

/*!
 * \brief Initialize the indicator module and sets them to OFF state.
 * \param set_indicator_fct Function pointer to set an indicator's PWM value.
 * 
 * \retval True if initialization is successful, else false
 */
bool indicators_init(indicator_set set_indicator_fct);

/*!
 * \brief Check if indicators module is initialized.
 * \retval True if initialized, else false
 */
bool is_indicators_initialized(void);

/*!
 * \brief Update the indicators based on the current state.
 */
void indicators_update(void);

/*!
 * \brief Change the specified indicator state and updates all indicators.
 * \param state true to turn on, false to turn off
 * \param indicator The indicator to change
 */
void indicators_set(bool state, enum IndicatorsName indicator);

/*!
 * \brief Change pwm value of all indicators and updates all indicators.
 * \param luminosity The PWM value to set for all indicators (0-100).
*/
void indicators_set_luminosity(uint8_t luminosity);

#endif // INDICATORS_H
