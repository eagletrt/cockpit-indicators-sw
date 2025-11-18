#ifndef INDICATORS_H
#define INDICATORS_H

#include <stdbool.h>
#include <main.h>

#define MISSION_PINS 3
#define MAX_MISSION_LEDS ((1 << MISSION_PINS) - 1)

typedef struct {
    bool AMS;           //!< Accumulator Management System indicator
    bool IMD;           //!< Insulation Monitoring Device indicator
    bool TS_OFF;        //!< Traction System Off indicator
    uint8_t mission_id; //!< Selected mission profile indicator (0-7)
    bool changed_state; //!< Flag to indicate if the state has changed
} LEDState;

typedef struct {
    GPIO_TypeDef *AMS_port; //!< GPIO port for the AMS indicators
    uint16_t AMS_pin;       //!< GPIO pin for AMS indicator

    GPIO_TypeDef *IMD_port; //!< GPIO port for the IMD indicators
    uint16_t IMD_pin;       //!< GPIO pin for IMD indicator

    GPIO_TypeDef *TS_OFF_port; //!< GPIO port for TS_OFF indicator
    uint16_t TS_OFF_pin;       //!< GPIO pin for TS_OFF indicator

    GPIO_TypeDef *MISSION_ports[MISSION_PINS]; //!< GPIO port for mission profile indicators
    uint16_t MISSION_pins[MISSION_PINS];       //!< GPIO pins for mission profile indicators
} LEDPins;

/*!
 * \brief Initialize the indicator LEDs to OFF state.
 * \param pins The struct containing the pins to the LED indicators.
 * 
 * \retval True if initialization is successful, else false
 */
bool Indicators_Init(const LEDPins *pins, LEDState *state);

/*!
 * \brief Update the indicator LEDs based on the current state.
 * \param state The struct containing the current state of the LED indicators.
 * \param pins The struct containing the pins to the LED indicators.
 */
void update_indicators(const LEDState *state, const LEDPins *pins);

/*! 
 * \brief Update the mission profile LEDs based on the selected profile.
 * \param state The struct containing the current state of the LED indicators.
 * \param pins The struct containing the pins to the LED indicators.
 * 
 * \return True if the mission value is valid, else false
 */
bool update_mission(const LEDState *state, const LEDPins *pins);

#endif // INDICATORS_H