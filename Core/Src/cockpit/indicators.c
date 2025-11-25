#include "indicators.h"

static struct IndicatorsHandler indicators_global_handler;
static bool is_initialized = false;

bool indicators_init(struct IndicatorsFunctionSet *set_indicator_fct) {

    if (set_indicator_fct == NULL || set_indicator_fct->ams == NULL || set_indicator_fct->imd == NULL || set_indicator_fct->ts_off == NULL || set_indicator_fct->tsal == NULL || is_initialized) {
        return false;
    }

    indicators_global_handler.ams = set_indicator_fct->ams;
    indicators_global_handler.imd = set_indicator_fct->imd;
    indicators_global_handler.ts_off = set_indicator_fct->ts_off;
    indicators_global_handler.tsal = set_indicator_fct->tsal;

    indicators_global_handler.ams_state_on = false;
    indicators_global_handler.imd_state_on = false;
    indicators_global_handler.ts_off_state_on = false;
    indicators_global_handler.tsal_state_on = false;

    indicators_global_handler.pwm_value = 0;

    indicators_global_handler.ams(0);
    indicators_global_handler.imd(0);
    indicators_global_handler.ts_off(0);
    indicators_global_handler.tsal(0);

    is_initialized = true;
    return true;
}

bool is_indicators_initialized(void) {
    return is_initialized;
}

void indicators_update(void) {

    if (indicators_global_handler.ams_state_on)
        indicators_global_handler.ams(indicators_global_handler.pwm_value);
    else
        indicators_global_handler.ams(0);

    if (indicators_global_handler.imd_state_on)
        indicators_global_handler.imd(indicators_global_handler.pwm_value);
    else
        indicators_global_handler.imd(0);

    if (indicators_global_handler.ts_off_state_on)
        indicators_global_handler.ts_off(indicators_global_handler.pwm_value);
    else
        indicators_global_handler.ts_off(0);
}

void indicators_change_ams(bool state) {
    indicators_global_handler.ams_state_on = state;
    indicators_update();
}

void indicators_change_imd(bool state) {
    indicators_global_handler.imd_state_on = state;
    indicators_update();
}

void indicators_change_ts_off(bool state) {
    indicators_global_handler.ts_off_state_on = state;
    indicators_update();
}

void indicators_change_tsal(bool state) {
    indicators_global_handler.tsal_state_on = state;
    indicators_update();
}

void indicators_set_pwm_value(uint8_t pwm_value) {
    if (pwm_value > 100) {
        pwm_value = 100;
    }
    indicators_global_handler.pwm_value = pwm_value;
    indicators_update();
}