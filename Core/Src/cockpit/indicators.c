#include "indicators.h"

EAGLETRT_STATIC struct IndicatorsHandler indicators_global_handler; // Private in production

bool indicators_init(indicator_set set_indicator_fct) {

    if (set_indicator_fct == NULL || set_indicator_fct == NULL || indicators_global_handler.initialized) {
        return false;
    }

    indicators_global_handler.set_indicator = set_indicator_fct;

    for (int i = 0; i < INDICATORS_NAME_COUNT; i++) {
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
    for (enum IndicatorsName i = 0; i < INDICATORS_NAME_COUNT; ++i) {
        const uint8_t luminosity = indicators_global_handler.state[i] ? indicators_global_handler.luminosity : 0U;
        indicators_global_handler.set_indicator(i, luminosity);
    }
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