#include "indicators.h"

static struct IndicatorsHandler indicators_global_handler;
static bool is_initialized = false;

bool indicators_init(struct IndicatorsFunctionSet *set_indicator_fct) {

    if (set_indicator_fct == NULL || set_indicator_fct->ams == NULL || set_indicator_fct->imd == NULL || set_indicator_fct->ts_off == NULL || is_initialized) {
        return false;
    }

    indicators_global_handler.ams = set_indicator_fct->ams;
    indicators_global_handler.imd = set_indicator_fct->imd;
    indicators_global_handler.ts_off = set_indicator_fct->ts_off;

    indicators_global_handler.ams_state_on = false;
    indicators_global_handler.imd_state_on = false;
    indicators_global_handler.ts_off_state_on = false;

    indicators_global_handler.ams(false);
    indicators_global_handler.imd(false);
    indicators_global_handler.ts_off(false);

    is_initialized = true;
    return true;
}

void indicators_update() {

    indicators_global_handler.ams(indicators_global_handler.ams_state_on);
    indicators_global_handler.imd(indicators_global_handler.imd_state_on);
    indicators_global_handler.ts_off(indicators_global_handler.ts_off_state_on);
}

void indicators_change_ams(bool state) {
    indicators_global_handler.ams_state_on = state;
}

void indicators_change_imd(bool state) {
    indicators_global_handler.imd_state_on = state;
}

void indicators_change_ts_off(bool state) {
    indicators_global_handler.ts_off_state_on = state;
}