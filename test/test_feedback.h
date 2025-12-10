/* Header for feedback unit tests
 * Provides mock helpers, externs and prototypes used by
 * `test/test_feedback.c`.
 */

#ifndef TEST_TEST_FEEDBACK_H
#define TEST_TEST_FEEDBACK_H

#include "unity.h"
#include "feedback.h"

/* Mocking functions used by the tests */
enum FeedbackState mock_read_feedback(enum FeedbackName feedback);
void feedback_reset_mock(void);
void feedback_reset_module_state(void);
void feedback_test_init(void);

/* Test function prototypes */
void feedback_test_get_state_call_count(void);
void feedback_test_get_state(void);

#endif /* TEST_TEST_FEEDBACK_H */
