#ifndef INDICATORS_H
#define INDICATORS_H

#include <stdbool.h>
#include <stdint.h>

#define INDICATORS_EXPIRE_TIME (1000U)

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

typedef uint32_t (*indicators_api_get_tick_fn)(void);

/*!
 * \brief Struct that handles all relevant indicator information
 */
struct IndicatorsHandler {
    float luminosity; //!< PWM value for all indicators (0f-1f)
    uint32_t ams_last_update;
    uint32_t imd_last_update;
    indicators_api_get_tick_fn get_tick;
    bool state[INDICATORS_NAME_COUNT]; //!< State of each indicator (on/off)
};

#endif // INDICATORS_H
