#include "feedback.h"

static MushroomPins *mushroom_pins = NULL;
static volatile MushroomState *mushroom_state = NULL;

bool Feedback_Init(MushroomPins *pins, MushroomState *state) {

    __disable_irq();
    mushroom_pins = pins;
    mushroom_state = state;
    __enable_irq();

    // Initialize the mushroom button states
    mushroom_state->M1_pressed = (HAL_GPIO_ReadPin(mushroom_pins->M1_port, mushroom_pins->M1_pin) == GPIO_PIN_RESET);
    mushroom_state->M2_pressed = (HAL_GPIO_ReadPin(mushroom_pins->M2_port, mushroom_pins->M2_pin) == GPIO_PIN_RESET);
    mushroom_state->changed_state = false;

    if (mushroom_state->M1_pressed || mushroom_state->M2_pressed) {
        // At least one button is pressed during initialization
        return false;
    }

    return true;
}

// Call the general EXTI callback with edge information
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin) {
    HAL_GPIO_EXTI_Callback(GPIO_Pin, 0);
}
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
    HAL_GPIO_EXTI_Callback(GPIO_Pin, 1);
}

// TODO: Check if debouncing is needed
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin, int edge) {

    // Return if rising edge as the reset logic is not handled here (???)
    if (edge == 0) {
        return;
    }

    if (mushroom_pins == NULL || mushroom_state == NULL) {
        return; // Not initialized
    }

    if (GPIO_Pin == mushroom_pins->M1_pin) {
        mushroom_state->M1_pressed = (HAL_GPIO_ReadPin(mushroom_pins->M1_port, mushroom_pins->M1_pin) == GPIO_PIN_RESET);
        mushroom_state->changed_state = true;
    } else if (GPIO_Pin == mushroom_pins->M2_pin) {
        mushroom_state->M2_pressed = (HAL_GPIO_ReadPin(mushroom_pins->M2_port, mushroom_pins->M2_pin) == GPIO_PIN_RESET);
        mushroom_state->changed_state = true;
    }
}

void relay_error(char *error_message, int message_length) {
    // Implementation to relay error message over CAN bus
    // This is a placeholder function and should be implemented as per the CAN bus protocol used
}

bool get_mushroom_state() {
    if (mushroom_state == NULL) {
        return false; // Not initialized
    }
    return mushroom_state->M1_pressed || mushroom_state->M2_pressed;
}

void clear_changed_state_flag() {
    if (mushroom_state != NULL) {
        mushroom_state->changed_state = false;
    }
}

void update_mushroom_state() {
    if (mushroom_state != NULL) {
        mushroom_state->M1_pressed = (HAL_GPIO_ReadPin(mushroom_pins->M1_port, mushroom_pins->M1_pin) == GPIO_PIN_RESET);
        mushroom_state->M2_pressed = (HAL_GPIO_ReadPin(mushroom_pins->M2_port, mushroom_pins->M2_pin) == GPIO_PIN_RESET);
        mushroom_state->changed_state = false;
    }
}