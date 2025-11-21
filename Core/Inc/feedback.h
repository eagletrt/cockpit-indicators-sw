#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <main.h>
#include <string.h>
#include <stdbool.h>

/*!
 * \brief Function signature for reading feedback state
 * \return true if pressed, false otherwise
 */
typedef bool (*read_feedback)(void);

/*!
 * \brief Struct that handles all relevant feedback information
 */
struct FeedbackHandler {

    read_feedback read_fb;       //!< Function to read feedback button state, must return true if pressed
    char fb_name[20];            //!< Name of the feedback button
    volatile bool fb_pressed;    //!< Feedback button state
    volatile bool changed_state; //!< Flag to indicate if the state has changed
};

#define FEEDBACK_MAX_HANDLERS 3

/*!
 * \brief Possible return codes for feedback functions
 */
enum FeedbackReturnCode {
    FEEDBACK_PRESSED,     //!< At least one feedback button is pressed
    FEEDBACK_NOT_PRESSED, //!< No feedback buttons are pressed
    FEEDBACK_ERROR,       //!< Error in reading feedback button states
    FEEDBACK_INVALID      //!< Invalid feedback handler
};
// This technically breaks the embedded convention but FEEDBACK_RETURN_CODE_FEEDBACK_PRESSED is too long

/*!
 * \brief Edge types for feedback events
 */
enum EdgeType {
    EDGE_TYPE_RISING_EDGE,
    EDGE_TYPE_FALLING_EDGE
};

/*!
 * \brief  Initialize feedback module
 * \param  mhand: Pointer to FeedbackHandler array containing all feedback handlers pointers.
 * \param  handler_count: Number of feedback handlers in the array.
 * \warning All feedback handler structs must remain in scope for the entire runtime of the program.
 * 
 * \return true if initialization is successful, false if any button is pressed during initialization or an invalid handler is found.
 */
enum FeedbackReturnCode feedback_init(struct FeedbackHandler *mhand[], size_t handler_count);

/*!
 * \brief  Internal general event callback for feedback button state changes
 * \param  fb The FeedbackHandler pointer for which the event was detected
 * \param  edge The type of edge detected (RISING_EDGE or FALLING_EDGE)
 */
void int_feedback_event_callback(struct FeedbackHandler *fb, enum EdgeType edge);

/*!
 * \brief  Function to be called on line rising edge detection
 * \param  fb The FeedbackHandler pointer for which the rising edge was detected
 */
void feedback_rising_edge_callback(struct FeedbackHandler *fb);

/*!
 * \brief  Function to be called on line falling edge detection
 * \param  fb The FeedbackHandler pointer for which the falling edge was detected
 */
void feedback_falling_edge_callback(struct FeedbackHandler *fb);

/*!
 * \brief  Returns the current state of the feedback buttons
 * \return FeedbackReturnCode indicating the state of the feedback buttons (FEEDBACK_PRESSED, FEEDBACK_NOT_PRESSED, FEEDBACK_ERROR)
 */
enum FeedbackReturnCode feedback_get_state();

/*!
 * \brief  Fills the provided array with the names of currently pressed feedback buttons
 * \param  names A 2D char array to hold the names of pressed feedback buttons
 * \warning The array must be at least of size FEEDBACK_MAX_HANDLERS else the function will ALWAYS return 0
 * \return The number of pressed feedback buttons whose names were written to the array
 */
size_t feedback_get_pressed(char *names[], size_t max_names);

/*!
 * \brief  Clears the changed_state flag in FeedbackHandler
 */
void feedback_clear_changed_state_flag();

/*!
 * \brief  Force update of the feedback button states from GPIO pins and reset changed_state flag
 *         useful if a reset can be triggered without power cycling the MCU
 */
void feedback_update_state();

#endif // FEEDBACK_H