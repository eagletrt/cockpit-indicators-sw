#ifndef POST_H
#define POST_H

#include <stdint.h>
#include "feedback.h"
#include "indicators.h"
#include "fsm.h"

/*!
 * \brief Possible return codes for POST functions
 */
enum PostReturnCode {
    POST_RC_OK,
    POST_RC_UNINITIALIZED,
    POST_RC_SETUP_ERROR,
    POST_RC_INVALID_POINTER
};

/*!
 * \brief Function signature for TIM module POST check
 */
typedef bool (*tim_post)(void);

/*!
 * \brief Struct containing initialization data for POST functions.
 */
struct PostInitData {
    indicator_set indicator_set; //!< Function pointer to set indicator luminosity

    read_feedback fb_read; //!< Function pointer to read feedback state

    tim_post tim_post_function; //!< Function pointer for the timer module POST check
};

/*!
 * \brief Run power-on self tests.
 * \param init_data Pointer to PostInitData struct containing initialization data.
 * 
 * \retval POST_RC_OK if all tests pass
 * \retval POST_RC_UNINITIALIZED if a module is uninitialized
 * \retval POST_RC_SETUP_ERROR if a setup error is detected
 * \retval POST_RC_INVALID_POINTER if a null pointer is provided
 */
enum PostReturnCode post_run_power_on_tests(struct PostInitData *init_data);

/*!
 * \brief Run power-on initialization tests.
 * 
 * \retval POST_RC_OK if all tests pass
 * \retval POST_RC_UNINITIALIZED if a module is uninitialized
 * \retval POST_RC_SETUP_ERROR if a setup error is detected
 * \retval POST_RC_INVALID_POINTER if a null pointer is provided
 */
enum PostReturnCode post_run_power_on_init_tests();

#endif // POST_H