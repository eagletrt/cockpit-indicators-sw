/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

extern TIM_HandleTypeDef htim1;

extern TIM_HandleTypeDef htim3;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_TIM1_Init(void);
void MX_TIM3_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN Prototypes */

/* Wrapper function to set AMS PWM value (0-100%) */
void tim_ams_set_pwm(uint8_t pwm_value);

/* Wrapper function to set IMD PWM value (0-100%) */
void tim_imd_set_pwm(uint8_t pwm_value);

/* Wrapper function to set TS_OFF PWM value (0-100%) */
void tim_ts_off_set_pwm(uint8_t pwm_value);

/* Wrapper function to set TS_OFF PWM value (0-100%) */
void tim_tsal_set_pwm(uint8_t pwm_value);

/* Wrapper function to set TS_OFF PWM value (0-100%) */
void tim_addressable_set_pwm(uint8_t pwm_value);

/*!
 * \brief Check if TIM module is initialized.
 * \retval True if initialized, else false
 */
bool tim_test_timers_initialized(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */
