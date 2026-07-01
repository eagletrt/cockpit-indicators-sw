#include "can-communications-router-api.h"
#include "can-communications.h"
#include "can-primary-api.h"
#include "indicators-api.h"

enum CanCommunicationReturnCode can_communications_router_api_receive_primary(const struct CanCommunicationFrame *frame) {
    if (frame == NULL) {
        return CAN_COMMUNICATION_RC_NULL_POINTER;
    }

    union CanPrimaryMessages message = { 0 };

    if (!can_primary_api_id_is_valid(frame->id)) {
        return CAN_COMMUNICATION_RC_ERROR;
    }

    if (can_primary_api_deserialize_from_id(frame->id, (uint8_t *)frame->data, &message) != 0) {
        return CAN_COMMUNICATION_RC_ERROR;
    }

    switch (frame->id) {
        case CAN_PRIMARY_MESSAGE_FRAME_ID_HV_BMS_IMD:
            indicators_api_set_indicator(INDICATORS_NAME_IMD, message.hv_bms_imd.fault_bool);
            break;
        case CAN_PRIMARY_MESSAGE_FRAME_ID_HV_BMS_STATUS:
            indicators_api_set_indicator(INDICATORS_NAME_AMS, (message.hv_bms_status.name == CAN_PRIMARY_HV_BMS_STATUS_NAME_FATAL));
            break;
        case CAN_PRIMARY_MESSAGE_FRAME_ID_HV_BMS_FEEDBACK_STATUS:
            indicators_api_set_indicator(INDICATORS_NAME_TS_OFF, message.hv_bms_feedback_status.tsalgreen);
            break;
        default:
            break;
    }

    return CAN_COMMUNICATION_RC_OK;
}
