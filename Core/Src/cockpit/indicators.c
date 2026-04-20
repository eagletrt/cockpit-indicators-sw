#include "indicators.h"

#include "eagletrt-api.h"

EAGLETRT_STATIC struct IndicatorsHandler indicators_global_handler;

enum IndicatorsReturnCode indicators_init(indicator_set set_indicator_fct) {
    if (set_indicator_fct == NULL) {
        return false;
    }

    indicators_global_handler.set_indicator = set_indicator_fct;

    // Initialize all indicators to OFF state
    for (int i = 0; i < INDICATORS_NAME_COUNT; i++) {
        indicators_global_handler.state[i] = false;
    }

    indicators_global_handler.luminosity = 0;

    indicators_update();

    return true;
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

void indicators_set_luminosity(double luminosity) {
    indicators_global_handler.luminosity = EAGLETRT_API_CLAMP(luminosity, 0.0, 1.0);
}
