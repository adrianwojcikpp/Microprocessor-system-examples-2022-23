/**
  ******************************************************************************
  * @file    hal_gpio.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date	 02-Jun-2022
  * @brief	 HAL GPIO mock header file
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOCK_HAL_GPIO_H
#define __MOCK_HAL_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
}GPIO_PinState;

/**
  * @brief General Purpose I/O
  */
typedef uint16_t GPIO_TypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIO_ports GPIO ports
  * @{
  */
extern GPIO_TypeDef MOCK_GPIOA;
#define GPIOA 					  (&MOCK_GPIOA)        /* GPIO A selected */
extern GPIO_TypeDef MOCK_GPIOB;
#define GPIOB 					  (&MOCK_GPIOB)        /* GPIO B selected */
extern GPIO_TypeDef MOCK_GPIOC;
#define GPIOC 					  (&MOCK_GPIOC)        /* GPIO C selected */
extern GPIO_TypeDef MOCK_GPIOD;
#define GPIOD 					  (&MOCK_GPIOD)        /* GPIO D selected */
extern GPIO_TypeDef MOCK_GPIOE;
#define GPIOE 					  (&MOCK_GPIOE)        /* GPIO E selected */
extern GPIO_TypeDef MOCK_GPIOF;
#define GPIOF 					  (&MOCK_GPIOF)        /* GPIO F selected */
extern GPIO_TypeDef MOCK_GPIOG;
#define GPIOG 					  (&MOCK_GPIOG)        /* GPIO G selected */
extern GPIO_TypeDef MOCK_GPIOH;
#define GPIOH 					  (&MOCK_GPIOH)        /* GPIO H selected */
/**
  * @}
  */

/** @defgroup GPIO_pins GPIO pins
  * @{
  */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */
/**
  * @}
  */

/* Initialization and printing / logging functions ****************************/
void MX_GPIO_Init(void);   			   //< MOCK
 
/* Delay function *************************************************************/
/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @param Delay  specifies the delay time length, in milliseconds.
  * @retval None
  */
void HAL_Delay(uint32_t Delay);

/* IO operation functions *****************************************************/
/**
  * @brief  Read the specified input port pin.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral for STM32xxx family
  * @param  GPIO_Pin: specifies the port bit to read.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval The input port pin value.
  */
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/**
  * @brief  Set or clear the selected data port bit.
  *
  * @note   This function uses GPIOx_BSRR and GPIOx_BRR registers to allow atomic read/modify
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  *
  * @param  GPIOx where x can be (A..H) to select the GPIO peripheral for STM32xxx family
  * @param  GPIO_Pin specifies the port bit to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @param  PinState specifies the value to be written to the selected bit.
  *         This parameter can be one of the GPIO_PinState enum values:
  *            @arg GPIO_PIN_RESET: to clear the port pin
  *            @arg GPIO_PIN_SET: to set the port pin
  * @retval None
  */
void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

/**
  * @brief  Toggle the specified GPIO pin.
  * @param  GPIOx where x can be (A..H) to select the GPIO peripheral for STM32xxx family
  * @param  GPIO_Pin specifies the pin to be toggled.
  * @retval None
  */
void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif /* __MOCK_HAL_GPIO_H */
