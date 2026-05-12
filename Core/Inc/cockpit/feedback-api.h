#ifndef FEEDBACK_API_H
#define FEEDBACK_API_H

#include "feedback.h"

/*!
 * \brief  Initialize feedback-api module to `FEEDBACK_STATUS_ERROR`
 */
enum FeedbackReturnCode feedback_api_init(void);

/*!
 * \brief  Get the current state of a feedback line
 * \param  `enum FeedbackName feedback`
 * */
enum FeedbackState feedback_api_get_state(enum FeedbackName feedback);

/*!
 * \brief  Set the current state of a feedback line
 * \param  `enum FeedbackName feedback`
 * \param  `enum FeedbackState state`
 */
enum FeedbackReturnCode feedback_api_set_state(enum FeedbackName feedback, enum FeedbackState state);

#endif // FEEDBACK_API_H
