#ifndef FEEDBACK_API_H
#define FEEDBACK_API_H

#include "feedback.h"

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

#endif // FEEDBACK_API_H
