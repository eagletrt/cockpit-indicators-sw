#include "can-communications-router-api.h"
#include "can-networks-api.h"
#include "can-networks.h"
#include "can-primary.h"

#include "indicators-api.h"

#include "string.h"

enum CanCommunicationReturnCode can_communications_router_api_receive_primary(const struct CanCommunicationFrame *frame) {
    if (frame == NULL) {
        return CAN_COMMUNICATION_RC_NULL_POINTER;
    }

    struct CanCommunicationFrame buffer = {
        .id = frame->id,
        .length = frame->length,
    };

    memcpy(buffer.data, frame->data, frame->length);

    union CanNetworkMessage can_message;

    can_networks_api_deserialize(CAN_PRIMARY_NETWORK, buffer.id, buffer.data, &can_message);

    switch(buffer.id) {
        case CAN_PRIMARY_MESSAGE_INDEX_HV_BMS_IMD:
            indicators_api_set_indicator(INDICATORS_NAME_IMD, can_message.can_primary_message.hv_bms_imd.status);
            break;
        case CAN_PRIMARY_MESSAGE_INDEX_HV_BMS_STATUS:
            indicators_api_set_indicator(INDICATORS_NAME_AMS, (can_message.can_primary_message.hv_bms_status.name == CAN_PRIMARY_HV_BMS_STATUS_NAME_FATAL));
            break;
        case CAN_PRIMARY_MESSAGE_INDEX_HV_BMS_FEEDBACK_STATUS:
            indicators_api_set_indicator(INDICATORS_NAME_TS_OFF, can_message.can_primary_message.hv_bms_feedback_status.tsalgreen);
            break;
        default:
            break;
    }

    return CAN_COMMUNICATION_RC_OK;
}

enum CanCommunicationReturnCode can_communications_router_api_receive_secondary(const struct CanCommunicationFrame *frame) {
    if (frame == NULL) {
        return CAN_COMMUNICATION_RC_NULL_POINTER;
    }

    // TODO: add libcan deserialization and dispatch logic here

    return CAN_COMMUNICATION_RC_OK;
}
