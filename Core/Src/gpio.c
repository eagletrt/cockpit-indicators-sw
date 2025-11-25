/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void) {

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin : SW_SD_Pin */
    GPIO_InitStruct.Pin = SW_SD_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SW_SD_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : SHUTD_1_Pin SHTD_2_Pin */
    GPIO_InitStruct.Pin = SHUTD_1_Pin | SHTD_2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* USER CODE BEGIN 2 */

/* Wrapper function for Mushroom line before pin */
bool GPIO_read_line_before_pin(void) {
    return (HAL_GPIO_ReadPin(SHUTD_1_GPIO_Port, SHUTD_1_Pin) == GPIO_PIN_RESET);
}

/* Wrapper function for Mushroom line after pin */
bool GPIO_read_line_after_pin(void) {
    return (HAL_GPIO_ReadPin(SHTD_2_GPIO_Port, SHTD_2_Pin) == GPIO_PIN_RESET);
}

/* Wrapper function for steering wheel shutdown line */
bool GPIO_read_steering_wheel_pin(void) {
    return (HAL_GPIO_ReadPin(SW_SD_GPIO_Port, SW_SD_Pin) == GPIO_PIN_RESET);
}

/*Wrapper function for AMS led*/
void GPIO_set_ams_indicator(bool state) {
    HAL_GPIO_WritePin(AMS_GPIO_Port, AMS_Pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/*Wrapper function for IMD led*/
void GPIO_set_imd_indicator(bool state) {
    HAL_GPIO_WritePin(IMD_GPIO_Port, IMD_Pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/*Wrapper function for TS_OFF led*/
void GPIO_set_ts_off_indicator(bool state) {
    HAL_GPIO_WritePin(TS_OFF_GPIO_Port, TS_OFF_Pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/* USER CODE END 2 */
