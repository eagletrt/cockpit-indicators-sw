#include "feedback.h"

static volatile struct FeedbackHandler *feedback_handler = NULL;
volatile bool feedback_enable_interrupts = true;

/*!
 * \brief Private helper function to validate the IndicatorsHandler struct.
 * \param mhand The handler struct for indicators.
 * \return true if valid, false otherwise
 */
static bool prv_validate_handler(struct FeedbackHandler *mhand) {
    if (mhand == NULL || mhand->read_m1 == NULL || mhand->read_m2 == NULL) {
        return false;
    }
    return true;
}

bool feedback_init(struct FeedbackHandler *mhand) {

    feedback_enable_interrupts = false;
    feedback_handler = mhand;
    feedback_enable_interrupts = true;

    // Initialize the mushroom button states
    feedback_handler->m1_pressed = feedback_handler->read_m1();
    feedback_handler->m2_pressed = feedback_handler->read_m2();
    feedback_handler->changed_state = false;

    if (feedback_handler->m1_pressed || feedback_handler->m2_pressed) {
        // At least one button is pressed during initialization
        return false;
    }

    return true;
}

// Call the general EXTI callback with edge information
void rising_mushroom_callback(uint8_t fb) {
    general_event_callback(fb, 0);
}
void falling_mushroom_callback(uint8_t fb) {
    general_event_callback(fb, 1);
}

// TODO: Check if debouncing is needed
void general_event_callback(uint8_t fb, int edge) {

    // Return if rising edge as the reset logic is not handled here (???)
    if (edge == 0) {
        return;
    }

    if (!prv_validate_handler(feedback_handler) || !feedback_enable_interrupts) {
        return; // Not initialized
    }

    // Always set the pressed state to true on falling edge
    // TODO: Discuss if it should be better to read the pin state instead to not risk misinputs
    if (fb == 0) {
        feedback_handler->m1_pressed = true;
        feedback_handler->changed_state = true;
    } else if (fb == 1) {
        feedback_handler->m2_pressed = true;
        feedback_handler->changed_state = true;
    }
}

void relay_error(char *error_message, int message_length) {
    // Implementation to relay error message over CAN bus
    // This is a placeholder function and should be implemented as per the CAN bus protocol used
}

bool get_mushroom_state() {
    if (!prv_validate_handler(feedback_handler)) {
        return false; // Not initialized
    }
    return feedback_handler->m1_pressed || feedback_handler->m2_pressed;
}

void clear_changed_state_flag() {
    if (prv_validate_handler(feedback_handler)) {
        feedback_handler->changed_state = false;
    }
}

void update_mushroom_state() {
    if (prv_validate_handler(feedback_handler)) {
        feedback_handler->m1_pressed = feedback_handler->read_m1();
        feedback_handler->m2_pressed = feedback_handler->read_m2();
        feedback_handler->changed_state = false;
    }
}