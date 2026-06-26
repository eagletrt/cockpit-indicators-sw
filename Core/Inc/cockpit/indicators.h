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

#endif // INDICATORS_H
