#include "indicators.h"

#include "eagletrt-api.h"
#include <string.h>

EAGLETRT_STATIC struct IndicatorsHandler indicators_global_handler;

enum IndicatorsReturnCode indicators_init(indicator_set set_indicator_fct) {
    memset(&indicators_global_handler, 0U, sizeof(indicators_global_handler));

    if (set_indicator_fct == NULL) {
        return INDICATORS_RC_ERROR;
    }

    indicators_global_handler.set_indicator = set_indicator_fct;

    // Initialize all indicators to OFF state
    for (int i = 0; i < INDICATORS_NAME_COUNT; i++) {
        indicators_global_handler.state[i] = false;
    }

    indicators_global_handler.luminosity = 0;

    return INDICATORS_RC_OK;
}

enum IndicatorsReturnCode indicators_set(enum IndicatorsName indicator, bool state) {
    if(indicator < 0 || indicator >= INDICATORS_NAME_COUNT)
        return INDICATORS_RC_ERROR;

    indicators_global_handler.state[indicator] = state;
    return INDICATORS_RC_OK;
}

void indicators_set_luminosity(double luminosity) {
    indicators_global_handler.luminosity = EAGLETRT_API_CLAMP(luminosity, 0.0, 1.0);
}
