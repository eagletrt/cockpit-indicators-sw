#include "feedback.h"

// Don't know if dynamic allocation would be better here
static struct FeedbackHandler *feedback_handlers[MAX_FEEDBACK_HANDLERS] = { NULL }; // Array of pointers to feedback handlers
static size_t feedback_handler_count = 0;
static volatile bool feedback_enable_interrupts = true;

/*!
 * \brief Private helper function to validate the FeedbackHandler struct.
 * \param mhand The handler struct for feedback.
 * \return true if valid, false otherwise
 */
static bool prv_validate_handler(struct FeedbackHandler *mhand) {
    if (mhand == NULL || mhand->read_fb == NULL) {
        return false;
    }
    return true;
}

enum FeedbackReturnCode feedback_init(struct FeedbackHandler *mhand[], size_t handler_count) {

    if (mhand == NULL || handler_count == 0 || handler_count > MAX_FEEDBACK_HANDLERS) {
        return FEEDBACK_INVALID; // Invalid parameters
    }
    feedback_handler_count = handler_count;

    enum FeedbackReturnCode ret_code = FEEDBACK_NOT_PRESSED;

    // Check for valid handlers in the array and initialize their states
    for (size_t i = 0; i < handler_count; i++) {
        if (!prv_validate_handler(mhand[i])) {
            // Cleanup on error
            memset(feedback_handlers, 0, sizeof(feedback_handlers));
            feedback_handler_count = 0;

            return FEEDBACK_INVALID; // Invalid handler found
        }

        feedback_enable_interrupts = false;
        feedback_handlers[i] = mhand[i];
        feedback_enable_interrupts = true;

        // Initialize the feedback button states
        feedback_handlers[i]->fb_pressed = feedback_handlers[i]->read_fb();
        feedback_handlers[i]->changed_state = false;

        if (feedback_handlers[i]->fb_pressed) {
            // At least one button is pressed during initialization
            ret_code = FEEDBACK_PRESSED;
        }
    }

    return ret_code;
}

// Call the general event callback with edge information
void feedback_rising_edge_callback(struct FeedbackHandler *fb) {
    int_feedback_event_callback(fb, EDGE_TYPE_RISING_EDGE);
}
void feedback_falling_edge_callback(struct FeedbackHandler *fb) {
    int_feedback_event_callback(fb, EDGE_TYPE_FALLING_EDGE);
}

// TODO: Check if debouncing is needed
void int_feedback_event_callback(struct FeedbackHandler *fb, enum EdgeType edge) {
    // Return if rising edge as the reset logic is not handled here
    if (edge == EDGE_TYPE_RISING_EDGE) {
        return;
    }

    if (!prv_validate_handler(fb) || !feedback_enable_interrupts) {
        return; // Not initialized or interrupts disabled
    }

    // Always set the pressed state to true on falling edge
    // TODO: Discuss if it should be better to read the pin state instead to not risk misinputs
    fb->fb_pressed = true;
    fb->changed_state = true;
}

enum FeedbackReturnCode feedback_get_state() {
    if (feedback_handler_count == 0) {
        return FEEDBACK_ERROR; // No handlers initialized
    }
    for (size_t i = 0; i < feedback_handler_count; i++) {
        if (!prv_validate_handler(feedback_handlers[i])) {
            return FEEDBACK_ERROR; // Invalid handler found
        }
        if (feedback_handlers[i]->fb_pressed) {
            return FEEDBACK_PRESSED;
        }
    }
    return FEEDBACK_NOT_PRESSED;
}

void feedback_clear_changed_state_flag() {
    for (size_t i = 0; i < feedback_handler_count; i++) {
        if (prv_validate_handler(feedback_handlers[i])) {
            feedback_handlers[i]->changed_state = false;
        }
    }
}

void feedback_update_state() {
    for (size_t i = 0; i < feedback_handler_count; i++) {
        if (prv_validate_handler(feedback_handlers[i])) {
            feedback_handlers[i]->fb_pressed = feedback_handlers[i]->read_fb();
            feedback_handlers[i]->changed_state = false;
        }
    }
}