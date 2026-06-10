#ifndef COMUNICATION_API_H
#define COMUNICATION_API_H

// comunication module

#include "comunication.h"

#include "stdint.h"

// TODO? init function
enum ComunicationReturnCode comunication_api_init(void);

// TODO: receive and transmit with pal functions
enum ComunicationReturnCode comunication_api_read_from_queue(uint8_t *out_message, uint32_t size);
enum ComunicationReturnCode comunication_api_write_to_queue(uint8_t *in_message, uint32_t size);
enum ComunicationReturnCode comunication_api_process_rx_queue(void);
enum ComunicationReturnCode comunication_api_process_tx_queue(void);

enum ComunicationReturnCode comunication_api_deinit(void);

#endif // COMUNICATION_API_H
