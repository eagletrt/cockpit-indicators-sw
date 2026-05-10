#ifndef FEEDBACK_API_H
#define FEEDBACK_API_H

#include "feedback.h"

/*!
 * \brief  Initialize feedback-api module to `FEEDBACK_STATUS_ERROR`
 */
enum FeedbackReturnCode feedback_api_init();

/*!
 * \brief  Get the current state of a feedback line
 * \return state of the `feedback`
 * */
enum FeedbackState feedback_api_get_state(enum FeedbackName feedback);

/*!
 * \brief  Set the current state of a feedback line
 */
enum FeedbackReturnCode feedback_api_set_state(enum FeedbackName feedback, enum FeedbackState state);

#endif // FEEDBACK_API_H
