#ifndef INDICATORS_H
#define INDICATORS_H

#include <stdbool.h>
#include <stdio.h>

/*!
 * \brief Function signature for setting indicators
 * 
 * \param state true to turn on, false to turn off
 * 
 */
typedef void (*indicator_set)(uint8_t pwm_value);

/*!
 * \brief Struct that handles all relevant indicator information
 */
struct IndicatorsHandler {
    indicator_set ams;    //!< Function to set AMS indicator
    indicator_set imd;    //!< Function to set IMD indicator
    indicator_set ts_off; //!< Function to set TS_OFF indicator
    indicator_set tsal;   //!< Function to set TSAL indicator

    uint8_t pwm_value; //!< PWM value for all indicators (0-100)

    bool ams_state_on;    //!< Accumulator Management System indicator
    bool imd_state_on;    //!< Insulation Monitoring Device indicator
    bool ts_off_state_on; //!< Traction System Off indicator
    bool tsal_state_on;   //!< TSAL indicator
};

/*!
 * \brief Struct containing all function pointers for indicators
 */
struct IndicatorsFunctionSet {
    indicator_set ams;    //!< Function to set AMS indicator
    indicator_set imd;    //!< Function to set IMD indicator
    indicator_set ts_off; //!< Function to set TS_OFF indicator
    indicator_set tsal;   //!< Function to set TSAL indicator
};

/*!
 * \brief Initialize the indicators to OFF state.
 * \param indicator_handler The handler struct for the indicators functions.
 * 
 * \retval True if initialization is successful, else false
 */
bool indicators_init(struct IndicatorsFunctionSet *indicator_handler);

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
 * \brief Change the AMS indicator state.
 * \param state true to turn on, false to turn off
 */
void indicators_change_ams(bool state);

/*!
 * \brief Change the IMD indicator state.
 * \param state true to turn on, false to turn off
 */
void indicators_change_imd(bool state);

/*!
 * \brief Change the TS_OFF indicator state.
 * \param state true to turn on, false to turn off
 */
void indicators_change_ts_off(bool state);

/*!
 * \brief Change the TSAL indicator state.
 * \param state true to turn on, false to turn off
 */
void indicators_change_tsal(bool state);

/*!
 * \brief Change pwm value of all indicators.
 * \param pwm_value The PWM value to set for all indicators (0-100).
*/
void indicators_set_pwm_value(uint8_t pwm_value);

#endif // INDICATORS_H