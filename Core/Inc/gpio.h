/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/*
 * \brief  Wrapper function for Mushroom line before pin
 * \return true if pressed, false otherwise
 */
bool GPIO_read_line_before_pin(void);

/*
 * \brief  Wrapper function for Mushroom line after pin
 * \return true if pressed, false otherwise
 */
bool GPIO_read_line_after_pin(void);

/*
 * \brief  Wrapper function for Steering Wheel shutdown pin
 * \return true if pressed, false otherwise
 */
bool GPIO_read_steering_wheel_pin(void);

/*
 * \brief  Wrapper function for AMS indicator
 * \param  state true to turn on, false to turn off
 */
void GPIO_set_ams_indicator(bool state);

/*
 * \brief  Wrapper function for IMD indicator
 * \param  state true to turn on, false to turn off
 */
void GPIO_set_imd_indicator(bool state);

/*
 * \brief  Wrapper function for TS_OFF indicator
 * \param  state true to turn on, false to turn off
 */
void GPIO_set_ts_off_indicator(bool state);

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

struct GPIO_functions

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */
