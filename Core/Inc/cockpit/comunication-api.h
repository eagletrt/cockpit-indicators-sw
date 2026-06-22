#ifndef COMUNICATION_API_H
#define COMUNICATION_API_H

// comunication module

#include "comunication.h"

#include "stdint.h"

// TODO? init function
enum ComunicationReturnCode comunication_api_init(void);

// TODO: receive and transmit with pal functions
enum ComunicationReturnCode comunication_api_add_to_rx_queue(uint8_t *out_message, uint32_t size);
enum ComunicationReturnCode comunication_api_add_to_tx_queue(uint8_t *in_message, uint32_t size);
enum ComunicationReturnCode comunication_api_process_rx_queue(void);
enum ComunicationReturnCode comunication_api_process_tx_queue(void);

enum ComunicationReturnCode comunication_api_deinit(void);

#endif // COMUNICATION_API_H
