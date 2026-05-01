#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "eagletrt.h"

#include <stdbool.h>

/*!
 * \brief Possible return codes for feedback status functions
 */
enum FeedbackState {
    FEEDBACK_STATUS_LOW,  //!< Feedback line is low
    FEEDBACK_STATUS_HIGH, //!< Feedback line is high
    FEEDBACK_STATUS_ERROR //!< Error in reading feedback button states
};

/*!
 * \brief Enum for identifying feedback lines
 */
enum FeedbackName {
    FEEDBACK_NAME_STEERING_WHEEL,  //!< Feedback mushroom for the steering wheel
    FEEDBACK_NAME_MUSHROOM_BEFORE, //!< Feedback mushroom before line
    FEEDBACK_NAME_MUSHROOM_AFTER,  //!< Feedback mushroom after line
    FEEDBACK_NAME_COUNT            //!< Total number of feedback lines
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
 * \return FeedbackState indicating the state of the feedback line
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

#endif // FEEDBACK_H
