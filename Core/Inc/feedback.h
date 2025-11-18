#ifndef FEEDBACK_H
#define FEEDBACK_H

#include "main.h"
#include <stdbool.h>

typedef struct {

    volatile bool M1_pressed;    //<! First shutdown mushroom button state
    volatile bool M2_pressed;    //<! Second shutdown mushroom button state
    volatile bool changed_state; //<! Flag to indicate if the state has changed

} MushroomState;

typedef struct {

    GPIO_TypeDef *M1_port; //<! GPIO port for first shutdown mushroom button
    uint16_t M1_pin;       //<! GPIO pin for first shutdown mushroom button

    GPIO_TypeDef *M2_port; //<! GPIO port for second shutdown mushroom button
    uint16_t M2_pin;       //<! GPIO pin for second shutdown mushroom button

} MushroomPins;

/*!
 * \brief  Initialize feedback module
 * \param  pins: Pointer to MushroomPins structure with GPIO configuration
 * \param  state: Pointer to MushroomState structure to hold button states
 * 
 * \return true if initialization is successful, false if any button is pressed during initialization
 */
bool Feedback_Init(MushroomPins *pins, MushroomState *state);

/*!
 * \brief  EXTI line detection callbacks
 * \param  GPIO_Pin: Specifies the pins connected EXTI line
 * \param  edge: 0 - rising edge, 1 - falling edge
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin, int edge);

/*!
 * \brief  EXTI line rising edge detection callback
 */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin);

/*!
 * \brief  EXTI line falling edge detection callback
 */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin);

/*!
 * \brief  If this function is called while any of the mushroom buttons are pressed, 
 *         this function will relay an error on the CAN bus.
 */
void relay_error(char *error_message, int message_length);

/*!
 * \brief  Returns the current state of the mushroom buttons
 * \return true if any mushroom button is pressed, false otherwise
 */
bool get_mushroom_state();

/*!
 * \brief  Clears the changed_state flag in MushroomState
 */
void clear_changed_state_flag();

/*!
 * \brief  Force update of the mushroom button states from GPIO pins and reset changed_state flag
 *         useful if a reset can be triggered without power cycling the MCU
 */
void update_mushroom_state();

#endif // FEEDBACK_H