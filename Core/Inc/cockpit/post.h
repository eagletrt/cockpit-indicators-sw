#ifndef POST_H
#define POST_H

#include <stdint.h>
#include <feedback.h>
#include <indicators.h>
#include <fsm.h>

enum PostReturnCode {
    POST_OK,
    POST_UNINITIALIZED,
    POST_SETUP_ERROR,
    POST_NULL_POINTER
};

typedef bool (*tim_post)(void);

struct PostInitData {
    indicator_set ams_indicator_set;
    indicator_set imd_indicator_set;
    indicator_set ts_off_indicator_set;
    indicator_set tsal_indicator_set;

    read_feedback fb_before;
    read_feedback fb_after;
    read_feedback fb_steering_wheel;

    tim_post tim_post_function;
};

/*!
 * \brief Run power-on self tests.
 * \param init_data Pointer to PostInitData struct containing initialization data.
 * 
 * \retval POST_OK if all tests pass
 * \retval POST_UNINITIALIZED if a module is uninitialized
 * \retval POST_SETUP_ERROR if a setup error is detected
 * \retval POST_NULL_POINTER if a null pointer is provided
 */
enum PostReturnCode post_run_power_on_tests(struct PostInitData *init_data);

/*!
 * \brief Run power-on initialization tests.
 * 
 * \retval POST_OK if all tests pass
 * \retval POST_UNINITIALIZED if a module is uninitialized
 * \retval POST_SETUP_ERROR if a setup error is detected
 * \retval POST_NULL_POINTER if a null pointer is provided
 */
enum PostReturnCode post_run_power_on_init_tests();

#endif // POST_H