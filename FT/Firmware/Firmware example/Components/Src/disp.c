/**
  ******************************************************************************
  * @file    disp.c
  * @author  AW
  * @version V1.0
  * @date    4-Nov-2020
  * @brief   Simple 4 x 8 segment LED display driver library.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "disp.h"
#include <stdio.h>
#include <ctype.h>

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/
#define DISP_EMPTY_CHAR   10
#define DISP_DECIMALS_NO  10

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
const uint8_t DISP_COMMON_ANODE_DECIMALS[] = {
  0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF
};

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void disp_write_data(DISP_HandleTypeDef* hdisp, uint8_t byte);
void disp_disable_all_digits(DISP_HandleTypeDef* hdisp);
void disp_enable_digit(DISP_HandleTypeDef* hdisp, uint8_t dig);
void disp_enable_decimal_point(DISP_HandleTypeDef* hdisp);
void disp_disable_decimal_point(DISP_HandleTypeDef* hdisp);

/* Private function ----------------------------------------------------------*/
inline void disp_write_data(DISP_HandleTypeDef* hdisp, uint8_t data)
{
  for(uint8_t i = 0; i < DISP_SEG_NO; i++)
    HAL_GPIO_WritePin(hdisp->Segment_Ports[i], hdisp->Segment_Pins[i], (data >> i) & 0x01);
}

inline void disp_disable_all_digits(DISP_HandleTypeDef* hdisp)
{
  for(uint8_t i = 0; i < DISP_DIG_NO; i++)
    HAL_GPIO_WritePin(hdisp->Digit_Ports[i], hdisp->Digit_Pins[i], GPIO_PIN_RESET);
}

inline void disp_enable_digit(DISP_HandleTypeDef* hdisp, uint8_t dig)
{
  if(dig < DISP_DIG_NO)
   HAL_GPIO_WritePin(hdisp->Digit_Ports[dig], hdisp->Digit_Pins[dig], GPIO_PIN_SET);
}

inline void disp_enable_decimal_point(DISP_HandleTypeDef* hdisp)
{
  HAL_GPIO_WritePin(hdisp->DecimalPoint_Port, hdisp->DecimalPoint_Pin, GPIO_PIN_RESET);
}

inline void disp_disable_decimal_point(DISP_HandleTypeDef* hdisp)
{
  HAL_GPIO_WritePin(hdisp->DecimalPoint_Port, hdisp->DecimalPoint_Pin, GPIO_PIN_SET);
}

/* Public function -----------------------------------------------------------*/

/**
 * @brief Seven-segment display initialization.
 * @param[in/out] hdisp : Display handle
 * @retval None
 * @remark Starts display timer.
 */
void DISP_Init(DISP_HandleTypeDef* hdisp)
{
  HAL_TIM_Base_Start_IT(hdisp->Timer);
}

/**
 * @brief Seven-segment display decimal point control.
 * @param[in/out] hdisp : Display handle
 * @param[in]     dp    : Decimal point
 *   This parameter can be one of the following values:
 *     @arg DISP_DP_1    : First (most significant) digit decimal point is enabled
 *     @arg DISP_DP_2    : Second digit decimal point is enabled
 *     @arg DISP_DP_3    : Third digit decimal point is enabled
 *     @arg DISP_DP_4    : Fourth (least significant) digit decimal point is enabled
 *     @arg DISP_DP_NONE : Decimal point is disabled
 * @retval None
 */
void DISP_EnableDecimalPoint(DISP_HandleTypeDef* hdisp, DISP_DP_TypeDef dp)
{
  hdisp->DecimalPoint = dp;
}

/**
 * @brief Seven-segment display decimal unsigned integer printing.
 * @param[in/out] hdisp : Display handle
 * @param[in]     dec   : Decimal number in range <0, 9999>
 * @retval None
 */
void DISP_printDecUInt(DISP_HandleTypeDef* hdisp, uint16_t dec)
{
  char dec_str[5] = { 0, };
  int n = sprintf(dec_str, "%4u", dec);
  if(n == DISP_DIG_NO)
  {
    for(int i = 0; i < DISP_DIG_NO; i++)
	{
	  if(isdigit((int)dec_str[i]))
	    hdisp->DataArray[i] = dec_str[i] - '0';
     else
        hdisp->DataArray[i] = DISP_EMPTY_CHAR;
    }
  }
}

/**
 * @brief Seven-segment display control routine
 * @param[in/out] hdisp : Display handle
 * @retval None
 * @remark This should be called in display timer callback.
 */
void DISP_ROUTINE(DISP_HandleTypeDef* hdisp)
{
  static uint8_t dig = 0;  // active digit selector

  // Disable all segments
  disp_disable_all_digits(hdisp);

  // Enable single segment
  disp_enable_digit(hdisp, dig);

  // Write to selected segment
  uint8_t idx = hdisp->DataArray[dig];
  
  /* DECIMAL POSITIVE NUMBERS: 0000-9999 */
  if(idx < DISP_DECIMALS_NO)
    disp_write_data(hdisp, DISP_COMMON_ANODE_DECIMALS[idx]);
  
  //else if(...) 
  /* text handling, 
     hex number handling, 
     negative decimal number handling 
     etc */
     
  /* EMPTY CHARACTER (BLANK) */
  else
    disp_write_data(hdisp, DISP_COMMON_ANODE_DECIMALS[DISP_EMPTY_CHAR]);

  // Decimal point control
  if(hdisp->DecimalPoint == dig)
    disp_enable_decimal_point(hdisp);
  else
    disp_disable_decimal_point(hdisp);

  // Select next segment
  dig = (dig < DISP_DIG_NO-1) ? (dig+1) : (0);
}
