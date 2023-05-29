/**
  ******************************************************************************
  * @file    display_control_config.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date	 02-Jun-2022
  * @brief	 Display control configuration header file
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "display_control.h"

/* Public variables ----------------------------------------------------------*/
DISP_HandleTypeDef hdisp1 = { 
	.Port = GPIOA,
	.CLOCK_Pin = GPIO_PIN_0,
	.DATA1_Pin = GPIO_PIN_1,
	.DATA2_Pin = GPIO_PIN_2,
	.DATA3_Pin = GPIO_PIN_3,
	.DATA4_Pin = GPIO_PIN_4,
	.ClockPeriod = 500       // [ms]
};
