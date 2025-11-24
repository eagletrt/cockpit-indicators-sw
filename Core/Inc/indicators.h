#ifndef INDICATORS_H
#define INDICATORS_H

#include <stdbool.h>
#include <main.h>

#define MISSION_PINS (3)
#define MAX_MISSION_LEDS ((1 << MISSION_PINS) - 1)

/*!
 * \brief Function signature for setting indicators
 * 
 * \param state true to turn on, false to turn off
 * 
 */
typedef void (*indicator_set)(bool state);

/*!
 * \brief Function signature for setting mission profile indicators
 * 
 * \param state true to turn on, false to turn off
 * \param pin specifies which mission indicator binary selector pin to set
 */
typedef void (*mission_set)(bool state, uint8_t pin);

/*!
 * \brief Struct that handles all relevant indicator information
 */
struct IndicatorsHandler {
    indicator_set ams;    //!< Function to set AMS indicator
    indicator_set imd;    //!< Function to set IMD indicator
    indicator_set ts_off; //!< Function to set TS_OFF indicator

    mission_set mission; //!< Function to set mission profile indicators

    bool ams_state_on;    //!< Accumulator Management System indicator
    bool imd_state_on;    //!< Insulation Monitoring Device indicator
    bool ts_off_state_on; //!< Traction System Off indicator
    uint8_t mission_id;   //!< Selected mission profile indicator (0-7)
    bool changed_state;   //!< Flag to indicate if the state has changed
};

/*!
 * \brief Struct containing all function pointers for indicators
 */
struct IndicatorsFunctionSet {
    indicator_set ams;    //!< Function to set AMS indicator
    indicator_set imd;    //!< Function to set IMD indicator
    indicator_set ts_off; //!< Function to set TS_OFF indicator
    mission_set mission;  //!< Function to set mission profile indicators
};

/*!
 * \brief Initialize the indicators to OFF state.
 * \param indicator_handler The handler struct for the indicators functions.
 * 
 * \retval True if initialization is successful, else false
 */
bool indicators_init(struct IndicatorsFunctionSet *indicator_handler);

/*!
 * \brief Update the indicators based on the current state.
 */
void indicators_update();

/*! 
 * \brief Update the mission profile indicators based on the selected profile.
 * 
 * \return True if the mission value is valid, else false
 */
bool indicators_update_mission();

#endif // INDICATORS_H