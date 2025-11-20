#include "indicators.h"

/*!
 * \brief Private helper function to validate the IndicatorsHandler struct.
 * \param hindi The handler struct for indicators.
 * \return true if valid, false otherwise
 */
static bool prv_validate_handler(struct IndicatorsHandler *hindi) {
    if (hindi == NULL || hindi->ams == NULL || hindi->imd == NULL || hindi->ts_off == NULL || hindi->mission == NULL) {
        return false;
    }
    return true;
}

bool indicators_init(struct IndicatorsHandler *hindi) {

    // Initialize all indicator LEDs to OFF
    if (!prv_validate_handler(hindi)) {
        return false;
    }

    hindi->ams_state = false;
    hindi->imd_state = false;
    hindi->ts_off_state = false;
    hindi->mission_id = 0;
    hindi->changed_state = false;

    hindi->ams(false);
    hindi->imd(false);
    hindi->ts_off(false);

    for (int i = 0; i < MISSION_PINS; i++) {
        hindi->mission(false, i);
    }
    return true;
}

void update_indicators(struct IndicatorsHandler *hindi) {

    if (!prv_validate_handler(hindi)) {
        return;
    }

    hindi->ams(hindi->ams_state);
    hindi->imd(hindi->imd_state);
    hindi->ts_off(hindi->ts_off_state);
}

bool update_mission(struct IndicatorsHandler *hindi) {

    if (!prv_validate_handler(hindi)) {
        return false;
    }

    // The pins will be connected to a binary selector:
    // Mission 0 -> all off
    // Mission 1 -> LED 0 on
    // Mission 2 -> LED 1 on ecc...

    uint8_t mission = hindi->mission_id;

    if (mission > MAX_MISSION_LEDS) {
        return false;
    }

    for (int i = 0; i < MISSION_PINS; i++) {
        hindi->mission((mission >> i) & 0x01, i);
    }

    return true;
}