#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "eagletrt.h"

/*!
 * \brief Possible return codes for feedback functions
 */
enum FeedbackState {
    FEEDBACK_STATUS_LOW,  //!< Feedback line is low
    FEEDBACK_STATUS_HIGH, //!< Feedback line is high
    FEEDBACK_STATUS_ERROR //!< Error in reading feedback button states
};

/*!
 * \brief Enum for identifying feedback lines, the names will be determined later when hardware is finalized
 */
enum FeedbackName {
    FEEDBACK_NAME_1,    //!< Feedback line 1
    FEEDBACK_NAME_2,    //!< Feedback line 2
    FEEDBACK_NAME_3,    //!< Feedback line 3
    FEEDBACK_NAME_COUNT //!< Total number of feedback lines
};

/*!
 * \brief Possible return codes for feedback initialization function
 */
enum FeedbackReturnCode {
    FEEDBACK_RC_OK,   //!< Initialization successful
    FEEDBACK_RC_ERROR //!< Error during initialization
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
    read_feedback read_fb;                                                   //!< Function to read feedback line state
    EAGLETRT_VOLATILE enum FeedbackState fb_line_state[FEEDBACK_NAME_COUNT]; //!< Feedback button state array
    EAGLETRT_VOLATILE bool initialized;                                      //!< Indicates if the feedback handler has been initialized
};

/*!
 * \brief  Initialize feedback module
 * \param  fb_read Function pointer to read feedback line state
 * 
 * \return FeedbackState indicating if any button is pressed during initialization (FEEDBACK_STATUS_HIGH, FEEDBACK_STATUS_LOW, FEEDBACK_STATUS_ERROR)
 */
enum FeedbackReturnCode feedback_init(read_feedback fb_read);

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