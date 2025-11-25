#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*!
 * \brief Function signature for reading feedback state
 * \return true if pressed, false otherwise
 */
typedef bool (*read_feedback)(void);

/*!
 * \brief Possible return codes for feedback functions
 */
enum FeedbackLineState {
    FEEDBACK_HIGH, //!< Feedback line is high
    FEEDBACK_LOW,  //!< Feedback line is low
    FEEDBACK_ERROR //!< Error in reading feedback button states
};

/*!
 * \brief Struct that handles all relevant feedback information
 */
struct FeedbackHandler {

    read_feedback read_fb_before;                      //!< Function to read feedback button state, must return true if pressed
    read_feedback read_fb_after;                       //!< Function to read feedback button state, must return true if pressed
    read_feedback read_fb_sw;                          //!< Function to read steering wheel feedback button state, must return true if pressed
    volatile enum FeedbackLineState fb_pressed_before; //!< Feedback button state before
    volatile enum FeedbackLineState fb_pressed_after;  //!< Feedback button state after
    volatile enum FeedbackLineState fb_sw_pressed;     //!< Steering wheel feedback button state
    volatile bool changed_state;                       //!< Flag to indicate if the state has changed
};

/*!
 * \brief  Initialize feedback module
 * \param  fb_before Function pointer to read feedback button before
 * \param  fb_after Function pointer to read feedback button after
 * \param  fb_sw Function pointer to read steering wheel feedback button
 * 
 * \return FeedbackLineState indicating if any button is pressed during initialization (FEEDBACK_HIGH, FEEDBACK_LOW, FEEDBACK_ERROR)
 */
enum FeedbackLineState feedback_init(read_feedback fb_before, read_feedback fb_after, read_feedback fb_sw);

/*!
 * \brief  Returns the current overall state of the feedback lines
 * \return FeedbackLineState indicating the overall state (FEEDBACK_HIGH, FEEDBACK_LOW, FEEDBACK_ERROR)
 */
enum FeedbackLineState feedback_get_state(void);

/*!
 * \brief  Returns the current state of the feedback line before
 * \return FeedbackLineState indicating the state of the feedback line (FEEDBACK_HIGH, FEEDBACK_LOW, FEEDBACK_ERROR)
 */
enum FeedbackLineState feedback_get_state_before(void);

/*!
 * \brief  Returns the current state of the feedback line after
 * \return FeedbackLineState indicating the state of the feedback line (FEEDBACK_HIGH, FEEDBACK_LOW, FEEDBACK_ERROR)
 */
enum FeedbackLineState feedback_get_state_after(void);

/*!
 * \brief  Returns the current state of the steering wheel feedback line
 * \return FeedbackLineState indicating the state of the feedback line (FEEDBACK_HIGH, FEEDBACK_LOW, FEEDBACK_ERROR)
 */
enum FeedbackLineState feedback_get_state_sw(void);

/*!
 * \brief  Update the state of all feedback lines
 */
void feedback_update_state(void);

#endif // FEEDBACK_H