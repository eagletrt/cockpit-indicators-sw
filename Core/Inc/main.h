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
#define TSAL_R_Pin GPIO_PIN_0
#define TSAL_R_GPIO_Port GPIOA
#define TSAL_G_Pin GPIO_PIN_1
#define TSAL_G_GPIO_Port GPIOA
#define TSAL_B_Pin GPIO_PIN_2
#define TSAL_B_GPIO_Port GPIOA
#define IMD_LED_Pin GPIO_PIN_5
#define IMD_LED_GPIO_Port GPIOA
#define AMS_LED_Pin GPIO_PIN_6
#define AMS_LED_GPIO_Port GPIOA
#define TS_OFF_LED_Pin GPIO_PIN_7
#define TS_OFF_LED_GPIO_Port GPIOA
#define EXTRA_LED_2_Pin GPIO_PIN_5
#define EXTRA_LED_2_GPIO_Port GPIOC
#define USER_LED_Pin GPIO_PIN_0
#define USER_LED_GPIO_Port GPIOB
#define EXTRA_LED_1_Pin GPIO_PIN_10
#define EXTRA_LED_1_GPIO_Port GPIOB
#define LED_CHAIN_DATA_Pin GPIO_PIN_0
#define LED_CHAIN_DATA_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
