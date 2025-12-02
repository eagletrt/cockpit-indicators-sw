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

/* Test function prototypes */
void feedback_test_initialization_success(void);
void feedback_test_initialization_failure_null_callback(void);
void feedback_test_initialization_failure_double_init(void);
void feedback_test_update_and_get_state(void);
void feedback_test_state_persistence(void);

#endif /* TEST_TEST_FEEDBACK_H */

