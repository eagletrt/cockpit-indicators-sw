#include "indicators-api.h"

#include "eagletrt.h"
#include "eagletrt-api.h"
#include <string.h>

EAGLETRT_STATIC struct IndicatorsHandler indicators_api_handler;

enum IndicatorsReturnCode indicators_api_init(void) {
    // reset `indicators_api_handler`
    memset(&indicators_api_handler, 0U, sizeof(indicators_api_handler));

    return INDICATORS_RC_OK;
}

enum IndicatorsReturnCode indicators_api_set_indicator(enum IndicatorsName indicator, bool state) {
    if (indicator < 0 || indicator >= INDICATORS_NAME_COUNT)
        return INDICATORS_RC_ERROR;

    indicators_api_handler.state[indicator] = state;
    return INDICATORS_RC_OK;
}

bool indicators_api_get_indicator(enum IndicatorsName indicator) {
    if (indicator < 0 || indicator >= INDICATORS_NAME_COUNT)
        return false;

    return indicators_api_handler.state[indicator];
}

void indicators_api_set_luminosity(float luminosity) {
    indicators_api_handler.luminosity = EAGLETRT_API_CLAMP(luminosity, 0.0f, 1.0f);
}
