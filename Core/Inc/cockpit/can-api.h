#ifndef CAN_API_H
#define CAN_API_H

#include "can.h"

#include "pal-api.h"

// TODO? init function
enum CanReturnCode can_api_init(void);

// TODO: receive and transmit with pal functions
enum CanReturnCode can_api_read_from_queue(struct PalMessage *out_message);
enum CanReturnCode can_api_write_to_queue(struct PalMessage *in_message);
enum CanReturnCode can_api_process_rx_queue(void);
enum CanReturnCode can_api_process_tx_queue(void);

#endif // CAN_API_H
