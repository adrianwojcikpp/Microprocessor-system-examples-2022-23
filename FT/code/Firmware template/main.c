/**
  ******************************************************************************
  * @file    main.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @author
  * @author
  * @version 2.0
  * @date	 02-Jun-2022
  * @brief	 Main file: simple test display_control library
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hal_gpio.h" 				//< HAL GPIO mock
#include "display_control.h"    	//< DISPLAY CONTROL LIBRARY
#include "display_control_config.h" //< DISPLAY CONTROL CONFIGURATION SETTINGS

/* Main function -------------------------------------------------------------*/
/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main(void)
{	
	timestamp_init();
	logfile_init("result.csv");
	
	/* USER CODE Begin */
	// TODO: add more test cases	
	DISP_printDecUInt(&hdisp1, 1234);
	/* USER CODE End */
	
	logfile_deinit();
	
	return 0;
}