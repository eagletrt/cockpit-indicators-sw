#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*!
 * \brief Possible return codes for feedback functions
 */
enum FeedbackState {
    FEEDBACK_STATUS_HIGH, //!< Feedback line is high
    FEEDBACK_STATUS_LOW,  //!< Feedback line is low
    FEEDBACK_STATUS_ERROR //!< Error in reading feedback button states
};

/*!
 * \brief Enum for identifying feedback lines
 */
enum FeedbackName {
    FEEDBACK_NAME_STEERING_WHEEL,
    FEEDBACK_NAME_MUSHROOM_BEFORE,
    FEEDBACK_NAME_MUSHROOM_AFTER,
    FEEDBACK_NAME_COUNT
};

/*!
 * \brief Possible return codes for feedback initialization function
 */
enum FeedbackRC {
    FEEDBACK_RC_ERROR,
    FEEDBACK_RC_OK
};

/*!
 * \brief Function signature for reading feedback state
 * \param feedback Enum indicating which feedback line to read
 * \return true if pressed, false otherwise
 */
typedef enum FeedbackState (*read_feedback)(enum FeedbackName feedback);

/*!
 * \brief Struct that handles all relevant feedback information
 */
struct FeedbackHandler {

    read_feedback read_fb;                             //!< Function to read feedback line state
    volatile enum FeedbackState fb_pressed_before; //!< Feedback button state before
    volatile enum FeedbackState fb_pressed_after;  //!< Feedback button state after
    volatile enum FeedbackState fb_sw_pressed;     //!< Steering wheel feedback button state
    volatile bool initialized;                         //!< Indicates if the feedback handler has been initialized
};

/*!
 * \brief  Initialize feedback module
 * \param  fb_read Function pointer to read feedback line state
 * 
 * \return FeedbackState indicating if any button is pressed during initialization (FEEDBACK_STATUS_HIGH, FEEDBACK_STATUS_LOW, FEEDBACK_STATUS_ERROR)
 */
enum FeedbackRC feedback_init(read_feedback fb_read);

/*!
 * \brief  Get the current state of a feedback line
 * \param  feedback Enum indicating which feedback line to read
 * \return FeedbackState indicating if any button is pressed (FEEDBACK_STATUS_HIGH, FEEDBACK_STATUS_LOW, FEEDBACK_STATUS_ERROR)
 */
enum FeedbackState feedback_get_state(enum FeedbackName feedback);

/*!
 * \brief  Update the state of all feedback lines
 */
void feedback_update_state(void);

#endif // FEEDBACK_H