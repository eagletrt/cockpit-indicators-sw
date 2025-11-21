#include "indicators.h"

/*!
 * \brief Private helper function to validate the IndicatorsHandler struct.
 * \param indicator_handler The handler struct for indicators.
 * \return true if valid, false otherwise
 */
static bool prv_validate_handler(const struct IndicatorsHandler *indicator_handler) {
    if (indicator_handler == NULL || indicator_handler->ams == NULL || indicator_handler->imd == NULL || indicator_handler->ts_off == NULL || indicator_handler->mission == NULL) {
        return false;
    }
    return true;
}

bool indicators_init(struct IndicatorsHandler *indicator_handler) {

    // Initialize all indicator LEDs to OFF
    if (!prv_validate_handler(indicator_handler)) {
        return false;
    }

    indicator_handler->ams_state = false;
    indicator_handler->imd_state = false;
    indicator_handler->ts_off_state = false;
    indicator_handler->mission_id = 0;
    indicator_handler->changed_state = false;

    indicator_handler->ams(false);
    indicator_handler->imd(false);
    indicator_handler->ts_off(false);

    for (int i = 0; i < MISSION_PINS; i++) {
        indicator_handler->mission(false, i);
    }
    return true;
}

void indicators_update(const struct IndicatorsHandler *indicator_handler) {

    if (!prv_validate_handler(indicator_handler)) {
        return;
    }

    indicator_handler->ams(indicator_handler->ams_state);
    indicator_handler->imd(indicator_handler->imd_state);
    indicator_handler->ts_off(indicator_handler->ts_off_state);
}

bool indicators_update_mission(const struct IndicatorsHandler *indicator_handler) {

    if (!prv_validate_handler(indicator_handler)) {
        return false;
    }

    // The pins will be connected to a binary selector:
    // Mission 0 -> all off
    // Mission 1 -> LED 0 on
    // Mission 2 -> LED 1 on ecc...

    uint8_t mission = indicator_handler->mission_id;

    if (mission > MAX_MISSION_LEDS) {
        return false;
    }

    for (int i = 0; i < MISSION_PINS; i++) {
        indicator_handler->mission((mission >> i) & 0x01, i);
    }

    return true;
}