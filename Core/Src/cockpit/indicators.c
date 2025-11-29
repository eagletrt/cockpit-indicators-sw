#include "indicators.h"

static struct IndicatorsHandler indicators_global_handler;

bool indicators_init(indicator_set set_indicator_fct) {

    if (set_indicator_fct == NULL || set_indicator_fct == NULL || indicators_global_handler.initialized) {
        return false;
    }

    indicators_global_handler.set_indicator = set_indicator_fct;

    indicators_global_handler.ams_state_on = false;
    indicators_global_handler.imd_state_on = false;
    indicators_global_handler.ts_off_state_on = false;
    indicators_global_handler.tsal_state_on = false;

    indicators_global_handler.pwm_value = 0;

    indicators_update();

    indicators_global_handler.initialized = true;
    return true;
}

bool is_indicators_initialized(void) {
    return indicators_global_handler.initialized;
}

void indicators_update(void) {

    if (indicators_global_handler.ams_state_on)
        indicators_global_handler.set_indicator(INDICATOR_NAME_AMS, indicators_global_handler.pwm_value);
    else
        indicators_global_handler.set_indicator(INDICATOR_NAME_AMS, 0);

    if (indicators_global_handler.imd_state_on)
        indicators_global_handler.set_indicator(INDICATOR_NAME_IMD, indicators_global_handler.pwm_value);
    else
        indicators_global_handler.set_indicator(INDICATOR_NAME_IMD, 0);

    if (indicators_global_handler.ts_off_state_on)
        indicators_global_handler.set_indicator(INDICATOR_NAME_TS_OFF, indicators_global_handler.pwm_value);
    else
        indicators_global_handler.set_indicator(INDICATOR_NAME_TS_OFF, 0);
}

void indicators_set(bool state, enum IndicatorsName indicator) {
    switch (indicator) {
        case INDICATOR_NAME_AMS:
            indicators_global_handler.ams_state_on = state;
            break;
        case INDICATOR_NAME_IMD:
            indicators_global_handler.imd_state_on = state;
            break;
        case INDICATOR_NAME_TS_OFF:
            indicators_global_handler.ts_off_state_on = state;
            break;
        case INDICATOR_NAME_TSAL:
            indicators_global_handler.tsal_state_on = state;
            break;
        default:
            break;
    }
    indicators_update();
}

void indicators_set_pwm_value(uint8_t pwm_value) {
    if (pwm_value > 100) {
        pwm_value = 100;
    }
    indicators_global_handler.pwm_value = pwm_value;
    indicators_update();
}