#ifndef COMUNICATION_API_H
#define COMUNICATION_API_H

// comunication module

#include "comunication.h"

#include "stdint.h"

enum ComunicationReturnCode comunication_api_init(
    pal_deserialize_callback pal_deserialize, pal_send_callback pal_send);
enum ComunicationReturnCode comunication_api_deinit(void);

// TODO: receive and transmit with pal functions
enum ComunicationReturnCode comunication_api_add_to_rx_queue(struct ComunicationFrame *frame);
enum ComunicationReturnCode comunication_api_process_rx_queue(void);
enum ComunicationReturnCode comunication_api_add_to_tx_queue(struct ComunicationFrame *frame);
enum ComunicationReturnCode comunication_api_process_tx_queue(void);

#endif // COMUNICATION_API_H
