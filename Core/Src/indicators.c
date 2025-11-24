#include "indicators.h"

static struct IndicatorsHandler indicators_global_handler;
static bool is_initialized = false;

bool indicators_init(struct IndicatorsFunctionSet *set_indicator_fct) {

    if (set_indicator_fct == NULL || set_indicator_fct->ams == NULL || set_indicator_fct->imd == NULL || set_indicator_fct->ts_off == NULL || set_indicator_fct->mission == NULL || is_initialized) {
        return false;
    }

    indicators_global_handler.ams = set_indicator_fct->ams;
    indicators_global_handler.imd = set_indicator_fct->imd;
    indicators_global_handler.ts_off = set_indicator_fct->ts_off;
    indicators_global_handler.mission = set_indicator_fct->mission;

    indicators_global_handler.ams_state_on = false;
    indicators_global_handler.imd_state_on = false;
    indicators_global_handler.ts_off_state_on = false;
    indicators_global_handler.mission_id = 0;
    indicators_global_handler.changed_state = false;
    indicators_global_handler.ams(false);
    indicators_global_handler.imd(false);
    indicators_global_handler.ts_off(false);

    for (int i = 0; i < MISSION_PINS; i++) {
        indicators_global_handler.mission(false, i);
    }
    is_initialized = true;
    return true;
}

void indicators_update() {

    indicators_global_handler.ams(indicators_global_handler.ams_state_on);
    indicators_global_handler.imd(indicators_global_handler.imd_state_on);
    indicators_global_handler.ts_off(indicators_global_handler.ts_off_state_on);
}

bool indicators_update_mission() {

    // The pins will be connected to a binary selector:
    // Mission 0 -> all off
    // Mission 1 -> LED 0 on
    // Mission 2 -> LED 1 on ecc...

    uint8_t mission = indicators_global_handler.mission_id;

    if (mission > MAX_MISSION_LEDS) {
        return false;
    }

    for (int i = 0; i < MISSION_PINS; i++) {
        indicators_global_handler.mission((mission >> i) & 0x01, i);
    }

    return true;
}