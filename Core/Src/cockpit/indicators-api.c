#include "indicators.h"
#include "indicators-api.h"

#include "eagletrt.h"
#include "eagletrt-api.h"
#include <string.h>

EAGLETRT_STATIC struct IndicatorsHandler indicators_api_handler;

enum IndicatorsReturnCode indicators_api_init(indicators_api_get_tick_fn get_tick) {
    if (get_tick == NULL) {
        return INDICATORS_RC_ERROR;
    }

    memset(&indicators_api_handler, 0U, sizeof(indicators_api_handler));

    indicators_api_handler.get_tick = get_tick;

    return INDICATORS_RC_OK;
}

enum IndicatorsReturnCode indicators_api_set_indicator(const enum IndicatorsName indicator, bool state) {
    if (indicator >= INDICATORS_NAME_COUNT) {
        return INDICATORS_RC_ERROR;
    }

    indicators_api_handler.state[indicator] = state;
    return INDICATORS_RC_OK;
}

bool indicators_api_get_indicator(enum IndicatorsName indicator) {
    if (indicator >= INDICATORS_NAME_COUNT)
        return false;

    return indicators_api_handler.state[indicator];
}

void indicators_api_set_luminosity(float luminosity) {
    indicators_api_handler.luminosity = EAGLETRT_API_CLAMP(luminosity, 0.0F, 1.0F);
}

void indicators_api_update_timestamp(enum IndicatorsName indicator) {
    switch (indicator) {
        case INDICATORS_NAME_AMS:
            indicators_api_handler.ams_last_update = indicators_api_handler.get_tick();
            break;
        case INDICATORS_NAME_IMD:
            indicators_api_handler.imd_last_update = indicators_api_handler.get_tick();
            break;
        default:
            break;
    }
}

bool indicators_api_is_timestamp_expired(enum IndicatorsName indicator) {
    uint32_t milliseconds_elapsed = 0;
    milliseconds_elapsed = indicators_api_handler.get_tick();

    switch (indicator) {
        case INDICATORS_NAME_AMS:
            milliseconds_elapsed -= indicators_api_handler.ams_last_update;
            break;
        case INDICATORS_NAME_IMD:
            milliseconds_elapsed -= indicators_api_handler.imd_last_update;
            break;
        default:
            return false;
    }

    return (milliseconds_elapsed >= INDICATORS_EXPIRE_TIME);
}
