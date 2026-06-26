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

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : USER_LED_Pin */
    GPIO_InitStruct.Pin = USER_LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(USER_LED_GPIO_Port, &GPIO_InitStruct);
}

/* USER CODE BEGIN 2 */

/*
static GPIO_TypeDef *prv_gpio_get_port_from_feedback_name(enum FeedbackName feedback) {
    switch (feedback) {
        case FEEDBACK_NAME_STEERING_WHEEL:
            return SHUTDOWN_LINE_STEERING_WHEEL_GPIO_Port;
        case FEEDBACK_NAME_MUSHROOM_BEFORE:
            return SHUTDOWN_LINE_BEFORE_GPIO_Port;
        case FEEDBACK_NAME_MUSHROOM_AFTER:
            return SHUTDOWN_LINE_AFTER_GPIO_Port;
        default:
            return NULL;
    };
}

static int16_t prv_gpio_get_pin_from_feedback_name(enum FeedbackName feedback) {
    switch (feedback) {
        case FEEDBACK_NAME_STEERING_WHEEL:
            return SHUTDOWN_LINE_STEERING_WHEEL_Pin;
        case FEEDBACK_NAME_MUSHROOM_BEFORE:
            return SHUTDOWN_LINE_BEFORE_Pin;
        case FEEDBACK_NAME_MUSHROOM_AFTER:
            return SHUTDOWN_LINE_AFTER_Pin;
        default:
            return -1;
    };
}

// TODO: call from the main.c
enum FeedbackState gpio_feedback_read(enum FeedbackName feedback) {
    GPIO_TypeDef *port = prv_gpio_get_port_from_feedback_name(feedback);
    int16_t pin = prv_gpio_get_pin_from_feedback_name(feedback);
    if (port == NULL || pin < 0) {
        return FEEDBACK_STATE_ERROR;
    }
    switch (HAL_GPIO_ReadPin(port, pin)) {
        case GPIO_PIN_SET:
            return FEEDBACK_STATE_HIGH;
        case GPIO_PIN_RESET:
            return FEEDBACK_STATE_LOW;
        default:
            return FEEDBACK_STATE_ERROR;
    };
}
*/

/* USER CODE END 2 */
