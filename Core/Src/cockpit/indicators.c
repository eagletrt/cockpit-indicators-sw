#include "indicators.h"

static struct IndicatorsHandler indicators_global_handler;

bool indicators_init(indicator_set set_indicator_fct) {

    if (set_indicator_fct == NULL || set_indicator_fct == NULL || indicators_global_handler.initialized) {
        return false;
    }

    indicators_global_handler.set_indicator = set_indicator_fct;

    for (int i = 0; i < INDICATOR_NAME_COUNT; i++) {
        indicators_global_handler.state[i] = false;
    }

    indicators_global_handler.luminosity = 0;

    indicators_update();

    indicators_global_handler.initialized = true;
    return true;
}

bool is_indicators_initialized(void) {
    return indicators_global_handler.initialized;
}

void indicators_update(void) {

    if (indicators_global_handler.state[INDICATOR_NAME_AMS])
        indicators_global_handler.set_indicator(INDICATOR_NAME_AMS, indicators_global_handler.luminosity);
    else
        indicators_global_handler.set_indicator(INDICATOR_NAME_AMS, 0);

    if (indicators_global_handler.state[INDICATOR_NAME_IMD])
        indicators_global_handler.set_indicator(INDICATOR_NAME_IMD, indicators_global_handler.luminosity);
    else
        indicators_global_handler.set_indicator(INDICATOR_NAME_IMD, 0);

    if (indicators_global_handler.state[INDICATOR_NAME_TS_OFF])
        indicators_global_handler.set_indicator(INDICATOR_NAME_TS_OFF, indicators_global_handler.luminosity);
    else
        indicators_global_handler.set_indicator(INDICATOR_NAME_TS_OFF, 0);
}

void indicators_set(bool state, enum IndicatorsName indicator) {
    indicators_global_handler.state[indicator] = state;
    indicators_update();
}

void indicators_set_luminosity(uint8_t luminosity) {
    if (luminosity > 100) {
        luminosity = 100;
    }
    indicators_global_handler.luminosity = luminosity;
    indicators_update();
}