#ifndef INDICATORS_H
#define INDICATORS_H

#include <stdbool.h>
#include <main.h>

#define MISSION_PINS 3
#define MAX_MISSION_LEDS ((1 << MISSION_PINS) - 1)

/*!
 * \brief Function signature for setting indicators
 * 
 * \param bool true to turn on, false to turn off
 * 
 */
typedef void (*indicator_set)(bool);

/*!
 * \brief Function signature for setting mission profile indicators
 * 
 * \param bool true to turn on, false to turn off
 * \param uint8_t specifies which mission indicator binary selector pin to set (0-2)
 */
typedef void (*mission_set)(bool, uint8_t);

/*!
 * \brief Struct that handles all relevant indicator information
 */
struct IndicatorsHandler {
    indicator_set ams;    //<! Function to set AMS indicator
    indicator_set imd;    //<! Function to set IMD indicator
    indicator_set ts_off; //<! Function to set TS_OFF indicator

    mission_set mission; //<! Function to set mission profile indicators

    bool ams_state;     //!< Accumulator Management System indicator
    bool imd_state;     //!< Insulation Monitoring Device indicator
    bool ts_off_state;  //!< Traction System Off indicator
    uint8_t mission_id; //!< Selected mission profile indicator (0-7)
    bool changed_state; //!< Flag to indicate if the state has changed
};

/*!
 * \brief Initialize the indicators to OFF state.
 * \param hindi The handler struct for indicators.
 * 
 * \retval True if initialization is successful, else false
 */
bool indicators_init(struct IndicatorsHandler *hindi);

/*!
 * \brief Update the indicators based on the current state.
 * \param hindi The handler struct for indicators.
 */
void update_indicators(struct IndicatorsHandler *hindi);

/*! 
 * \brief Update the mission profile indicators based on the selected profile.
 * \param hindi The handler struct for indicators.
 * 
 * \return True if the mission value is valid, else false
 */
bool update_mission(struct IndicatorsHandler *hindi);

#endif // INDICATORS_H