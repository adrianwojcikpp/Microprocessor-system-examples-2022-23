/**
  ******************************************************************************
  * @file    display_control.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date	 02-Jun-2022
  * @brief	 Display control library
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_CONTROL_H
#define __DISPLAY_CONTROL_H
  
/* Includes ------------------------------------------------------------------*/
#include "hal_gpio.h"
#include <sys/timeb.h> 
#include <stdio.h>
#include <stdlib.h>

/* Exported variables --------------------------------------------------------*/
/**
  * @brief Start of program execution timestamp
  */
extern struct timeb timestamp_start;

/**
  * @brief Log file handler
  */
extern FILE* logfile;

/* Typedef -------------------------------------------------------------------*/
typedef struct {
	GPIO_TypeDef* Port;
	uint16_t CLOCK_Pin;
	uint16_t DATA1_Pin;
	uint16_t DATA2_Pin;
	uint16_t DATA3_Pin;
	uint16_t DATA4_Pin;
	uint32_t ClockPeriod; 
} DISP_HandleTypeDef;

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Seven-segment display decimal unsigned integer printing.
 * @param[in/out] hdisp : Display handle
 * @param[in]     dec   : Decimal number in range <0, 9999>
 * @retval None
 */
void DISP_printDecUInt(DISP_HandleTypeDef* hdisp, unsigned int dec);

/**
 * @brief Initialization of time measurement. 
 * @retval None
 */
void timestamp_init(void);  

/**
 * @brief Opening log file for writing.
 * @param[in] filename : Name of log file 
 * @retval None
 */
void logfile_init(char* filename);  

/**
 * @brief Closing of log file.
 * @retval None
 */
void logfile_deinit();  

#endif // __DISPLAY_CONTROL_H