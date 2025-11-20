#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "main.h"
#include <stdbool.h>

/*!
 * \brief Function signature for reading feedback state
 * \return true if pressed, false otherwise
 */
typedef bool (*read_feedback_pin)(void);

/*!
 * \brief Struct that handles all relevant feedback information
 */
struct FeedbackHandler {

    read_feedback_pin read_m1; //<! Function to read first mushroom button state, must return true if pressed
    read_feedback_pin read_m2; //<! Function to read second mushroom button state, must return true if pressed

    volatile bool m1_pressed;    //<! First shutdown mushroom button state
    volatile bool m2_pressed;    //<! Second shutdown mushroom button state
    volatile bool changed_state; //<! Flag to indicate if the state has changed
};

/*!
 * \brief  Initialize feedback module
 * \param  mhand: Pointer to MushroomHandlers structure.
 * \warning The mushroom handlers struct must remain in scope for the entire runtime of the program.
 * 
 * \return true if initialization is successful, false if any button is pressed during initialization
 */
bool feedback_init(struct FeedbackHandler *mhand);

/*!
 * \brief  General event callback for mushroom button state changes
 * \param  fb: 0 - M1, 1 - M2 
 * \param  edge: 0 - rising edge, 1 - falling edge
 */
void general_event_callback(uint8_t fb, int edge);
// TODO: Should fb be an enum?

/*!
 * \brief  Function to be called on line rising edge detection
 * \param  fb: 0 - M1, 1 - M2
 */
void rising_mushroom_callback(uint8_t fb);

/*!
 * \brief  Function to be called on line falling edge detection
 * \param  fb: 0 - M1, 1 - M2
 */
void falling_mushroom_callback(uint8_t fb);

/*!
 * \brief  If this function is called while any of the mushroom buttons are pressed, 
 *         this function will relay an error on the CAN bus.
 */
void relay_error(char *error_message, int message_length);

/*!
 * \brief  Returns the current state of the mushroom buttons
 * \return true if any mushroom button is pressed, false otherwise
 */
bool get_mushroom_state();

/*!
 * \brief  Clears the changed_state flag in MushroomState
 */
void clear_changed_state_flag();

/*!
 * \brief  Force update of the mushroom button states from GPIO pins and reset changed_state flag
 *         useful if a reset can be triggered without power cycling the MCU
 */
void update_mushroom_state();

#endif // FEEDBACK_H