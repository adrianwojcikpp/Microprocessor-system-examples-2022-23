/**
  ******************************************************************************
  * @file    hal_gpio.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date	 02-Jun-2022
  * @brief	 HAL GPIO mock header file
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "hal_gpio.h"
#include <sys/timeb.h> 

/* Public variables ----------------------------------------------------------*/
/**
  * @brief Start of program execution timestamp
  */
struct timeb TIMESTAP_Start;

/* Public constants ----------------------------------------------------------*/
/** @defgroup GPIO_ports GPIO ports
  * @{
  */
GPIO_TypeDef MOCK_GPIOA;
GPIO_TypeDef MOCK_GPIOB;
GPIO_TypeDef MOCK_GPIOC;
GPIO_TypeDef MOCK_GPIOD;
GPIO_TypeDef MOCK_GPIOE;
GPIO_TypeDef MOCK_GPIOF;
GPIO_TypeDef MOCK_GPIOG;
GPIO_TypeDef MOCK_GPIOH;
/**
  * @}
  */

/* Initialization and printing / logging functions ****************************/

/* Delay function *************************************************************/
/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @param Delay  specifies the delay time length, in milliseconds.
  * @retval None
  */
void HAL_Delay(uint32_t Delay)
{
	struct timeb start, end;
    unsigned int diff;
    ftime(&start);	
	do {
		ftime(&end);
		diff =  (unsigned int)(1000 * (end.time - start.time) + (end.millitm - start.millitm));
	}
	while(diff < Delay);
}

/* IO operation functions *****************************************************/
/**
  * @brief  Read the specified input port pin.
  * @param  GPIOx: where x can be (A..H) to select the GPIO peripheral for STM32xxx family
  * @param  GPIO_Pin: specifies the port bit to read.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval The input port pin value.
  */
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	return ((*GPIOx) & GPIO_Pin) ? GPIO_PIN_SET : GPIO_PIN_RESET;
}

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
void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
	if(PinState)
		*GPIOx |= GPIO_Pin; 
	else
		*GPIOx &=~GPIO_Pin; 
}

/**
  * @brief  Toggle the specified GPIO pin.
  * @param  GPIOx where x can be (A..H) to select the GPIO peripheral for STM32xxx family
  * @param  GPIO_Pin specifies the pin to be toggled.
  * @retval None
  */
void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	*GPIOx ^= GPIO_Pin; 
}