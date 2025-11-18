#include "indicators.h"

bool Indicators_Init(const LEDPins *pins, LEDState *state) {

    // Initialize all indicator LEDs to OFF
    if (pins == NULL || state == NULL) {
        return false;
    }

    HAL_GPIO_WritePin(pins->AMS_port, pins->AMS_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(pins->IMD_port, pins->IMD_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(pins->TS_OFF_port, pins->TS_OFF_pin, GPIO_PIN_RESET);

    for (int i = 0; i < MISSION_PINS; i++) {
        HAL_GPIO_WritePin(pins->MISSION_ports[i], pins->MISSION_pins[i], GPIO_PIN_RESET);
    }
    return true;
}

void update_indicators(const LEDState *state, const LEDPins *pins) {

    if (state == NULL || pins == NULL) {
        return;
    }

    HAL_GPIO_WritePin(pins->AMS_port, pins->AMS_pin, state->AMS ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(pins->IMD_port, pins->IMD_pin, state->IMD ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(pins->TS_OFF_port, pins->TS_OFF_pin, state->TS_OFF ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

bool update_mission(const LEDState *state, const LEDPins *pins) {

    if (state == NULL || pins == NULL) {
        return false;
    }

    // The pins will be connected to a binary selector:
    // Mission 0 -> all off
    // Mission 1 -> LED 0 on
    // Mission 2 -> LED 1 on ecc...

    uint8_t mission = state->mission_id;

    if (mission > MAX_MISSION_LEDS) {
        return false;
    }

    for (int i = 0; i < MISSION_PINS; i++) {
        HAL_GPIO_WritePin(pins->MISSION_ports[i], pins->MISSION_pins[i], (mission >> i) & 0x01 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    return true;
}