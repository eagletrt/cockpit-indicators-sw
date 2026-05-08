#ifndef FEEDBACK_API_H
#define FEEDBACK_API_H

#include "feedback.h"

/*!
 * \brief  Initialize feedback module
 */
enum FeedbackReturnCode feedback_api_init();

/*!
 * \brief  Get the current state of a feedback line
 * \param  feedback Enum indicating which feedback line to read
 * \return FeedbackState indicating if any button is pressed (FEEDBACK_STATUS_HIGH, FEEDBACK_STATUS_LOW, FEEDBACK_STATUS_ERROR)
 */
enum FeedbackState feedback_api_get_state(enum FeedbackName feedback);

/*!
 * \brief  Set the current state of a feedback line
 */
enum FeedbackReturnCode feedback_api_set_state(enum FeedbackName feedback, enum FeedbackState state);

#endif // FEEDBACK_API_H
