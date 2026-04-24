#include "indicators.h"

#include "eagletrt-api.h"
#include <string.h>

EAGLETRT_STATIC struct IndicatorsHandler indicators_handler;

enum IndicatorsReturnCode indicators_init(void) {
    memset(&indicators_handler, 0U, sizeof(indicators_handler));

    // Initialize all indicators to OFF state
    for (int i = 0; i < INDICATORS_NAME_COUNT; i++) {
        indicators_handler.state[i] = false;
    }

    indicators_handler.luminosity = 0.0;

    return INDICATORS_RC_OK;
}

enum IndicatorsReturnCode indicators_set(enum IndicatorsName indicator, bool state) {
    if (indicator < 0 || indicator >= INDICATORS_NAME_COUNT) 
        return INDICATORS_RC_ERROR;

    indicators_handler.state[indicator] = state;
    return INDICATORS_RC_OK;
}

bool indicators_get(enum IndicatorsName indicator) {
    return indicators_handler.state[indicator];
}

void indicators_set_luminosity(float luminosity) {
    indicators_handler.luminosity = EAGLETRT_API_CLAMP(luminosity, 0.0f, 1.0f);
}
