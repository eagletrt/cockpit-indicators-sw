#ifndef POST_H
#define POST_H

#include <stdint.h>

#include "feedback.h"
#include "can-communications.h"

/*!
 * \brief Possible return codes for POST functions
 */
enum PostReturnCode {
    POST_RC_OK,             //!< All tests passed
    POST_RC_UNINITIALIZED,  //!< A module is uninitialized
    POST_RC_SETUP_ERROR,    //!< A setup error is detected
    POST_RC_INVALID_POINTER //!< A null pointer is provided
};

struct PostInit {
    bool fdcan_return_code;
    bool adc_return_code;
    struct CanCommunicationsNetworkConfig config;
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
enum PostReturnCode post_init(struct PostInit *Init);

#endif // POST_H
