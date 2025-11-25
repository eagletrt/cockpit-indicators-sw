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

struct PostInitData {
    indicator_set ams_indicator_set;
    indicator_set imd_indicator_set;
    indicator_set ts_off_indicator_set;

    read_feedback fb_before;
    read_feedback fb_after;
    read_feedback fb_steering_wheel;
};

#endif // POST_H