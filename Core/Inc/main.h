/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADDRESS_LED_Pin GPIO_PIN_0
#define ADDRESS_LED_GPIO_Port GPIOA
#define AMS_Pin GPIO_PIN_1
#define AMS_GPIO_Port GPIOA
#define FEEDBACK_1_Pin GPIO_PIN_2
#define FEEDBACK_1_GPIO_Port GPIOA
#define FEEDBACK_2_Pin GPIO_PIN_3
#define FEEDBACK_2_GPIO_Port GPIOA
#define TSAL_RED_INPUT_Pin GPIO_PIN_4
#define TSAL_RED_INPUT_GPIO_Port GPIOA
#define IMD_Pin GPIO_PIN_5
#define IMD_GPIO_Port GPIOA
#define TSAL_RED_Pin GPIO_PIN_6
#define TSAL_RED_GPIO_Port GPIOA
#define TS_OFF_Pin GPIO_PIN_7
#define TS_OFF_GPIO_Port GPIOA
#define USER_LED_Pin GPIO_PIN_12
#define USER_LED_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
