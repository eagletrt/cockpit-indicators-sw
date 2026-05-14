#ifndef FEEDBACK_API_H
#define FEEDBACK_API_H

#include "feedback.h"

/*!
 * \brief  Initialize feedback-api module to `FEEDBACK_STATUS_ERROR`
 *
 * \retval FEEDBACK_RC_OK if successful
 * \retval FEEDBACK_RC_ERROR if fail
 */
enum FeedbackReturnCode feedback_api_init(void);

/*!
 * \brief  Get the current state of a feedback line
 *
 * \param feedback The feedback to query
 *
 * \retval enum FeedbackState of \p feedback
 * */
enum FeedbackState feedback_api_get_state(enum FeedbackName feedback);

/*!
 * \brief  Set the current state of a feedback line
 *
 * \param feedback The feedback to be set
 * \param state The state to set \p feedback to
 *
 * \retval FEEDBACK_RC_OK if successful
 * \retval FEEDBACK_RC_ERROR if \p feedback or \p state are out of bounds
 */
enum FeedbackReturnCode feedback_api_set_state(enum FeedbackName feedback, enum FeedbackState state);

#endif // FEEDBACK_API_H
