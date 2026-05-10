#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "eagletrt.h"

#include <stdbool.h>

/*!
 * \brief Possible return codes for feedback status functions
 */
enum FeedbackState {
    FEEDBACK_STATE_LOW,   //!< Feedback line is low
    FEEDBACK_STATE_HIGH,  //!< Feedback line is high
    FEEDBACK_STATE_ERROR, //!< Error in reading feedback button states
    FEEDBACK_STATE_COUNT  //!< Total number of feedback statuses
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
 * \brief Struct that handles all relevant feedback information
 */
struct FeedbackHandler {
    EAGLETRT_VOLATILE enum FeedbackState feedback_line_state[FEEDBACK_NAME_COUNT]; //!< Feedback button state array
};

#endif // FEEDBACK_H
