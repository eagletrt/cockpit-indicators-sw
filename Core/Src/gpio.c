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
#include "feedback.h"
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

    /*Configure GPIO pin : SHUTDOWN_LINE_STEERING_WHEEL_Pin */
    GPIO_InitStruct.Pin = SHUTDOWN_LINE_STEERING_WHEEL_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SHUTDOWN_LINE_STEERING_WHEEL_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : SHUTDOWN_LINE_BEFORE_Pin SHUTDOWN_LINE_AFTER_Pin */
    GPIO_InitStruct.Pin = SHUTDOWN_LINE_BEFORE_Pin | SHUTDOWN_LINE_AFTER_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* USER CODE BEGIN 2 */

static GPIO_TypeDef *prv_gpio_get_port_from_feedback_name(enum FeedbackName feedback) {
    switch (feedback) {
        case FEEDBACK_STEERING_WHEEL:
            return SHUTDOWN_LINE_STEERING_WHEEL_GPIO_Port;
        case FEEDBACK_MUSHROOM_BEFORE:
            return SHUTDOWN_LINE_BEFORE_GPIO_Port;
        case FEEDBACK_MUSHROOM_AFTER:
            return SHUTDOWN_LINE_AFTER_GPIO_Port;
        default:
            return NULL;
    };
}

static int16_t prv_gpio_get_pin_from_feedback_name(enum FeedbackName feedback) {
    switch (feedback) {
        case FEEDBACK_STEERING_WHEEL:
            return SHUTDOWN_LINE_STEERING_WHEEL_Pin;
        case FEEDBACK_MUSHROOM_BEFORE:
            return SHUTDOWN_LINE_BEFORE_Pin;
        case FEEDBACK_MUSHROOM_AFTER:
            return SHUTDOWN_LINE_AFTER_Pin;
        default:
            return -1;
    };
}

enum FeedbackState gpio_feedback_read(enum FeedbackName feedback) {
    GPIO_TypeDef *port = prv_gpio_get_port_from_feedback_name(feedback);
    int16_t pin = prv_gpio_get_pin_from_feedback_name(feedback);
    if (port == NULL || pin < 0) {
        return FEEDBACK_STATUS_ERROR;
    }
    switch (HAL_GPIO_ReadPin(port, pin)) {
        case GPIO_PIN_SET:
            return FEEDBACK_STATUS_HIGH;
        case GPIO_PIN_RESET:
            return FEEDBACK_STATUS_LOW;
        default:
            return FEEDBACK_STATUS_ERROR;
    };
}

/* USER CODE END 2 */
