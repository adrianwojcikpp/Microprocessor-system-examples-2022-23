/**
  ******************************************************************************
  * @file    disp.h
  * @author  AW
  * @version V1.0
  * @date    4-Nov-2020
  * @brief   Simple 4 x 8 segment LED display driver library.
  *
  ******************************************************************************
  */
#ifndef INC_DISP_H_
#define INC_DISP_H_

/* Config --------------------------------------------------------------------*/
#define DISP_SEG_NO 7  //! Without decimal point segment
#define DISP_DIG_NO 4

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Typedef -------------------------------------------------------------------*/
#define DISP_PortType GPIO_TypeDef*
#define DISP_PinType uint16_t
#define DISP_TimerType TIM_HandleTypeDef*

typedef enum {
  DISP_DP_1 = 0, DISP_DP_2, DISP_DP_3, DISP_DP_4, DISP_NONE
} DISP_DP_TypeDef;

typedef struct {
  // Display GPIO ports and pins
  DISP_PortType Digit_Ports[DISP_DIG_NO];
  DISP_PinType  Digit_Pins[DISP_DIG_NO];
  DISP_PortType Segment_Ports[DISP_SEG_NO];
  DISP_PinType  Segment_Pins[DISP_SEG_NO];
  DISP_PortType DecimalPoint_Port;
  DISP_PinType  DecimalPoint_Pin;
  DISP_TimerType Timer;
  // Display data
  uint8_t DataArray[DISP_DIG_NO];
  DISP_DP_TypeDef  DecimalPoint;
} DISP_HandleTypeDef;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Seven-segment display initialization.
 * @param[in/out] hdisp : Display handle
 * @retval None
 * @remark Starts display timer.
 */
void DISP_Init(DISP_HandleTypeDef* hdisp);

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
void DISP_EnableDecimalPoint(DISP_HandleTypeDef* hdisp, DISP_DP_TypeDef dp);

/**
 * @brief Seven-segment display decimal unsigned integer printing.
 * @param[in/out] hdisp : Display handle
 * @param[in]     dec   : Decimal number in range <0, 9999>
 * @retval None
 */
void DISP_printDecUInt(DISP_HandleTypeDef* hdisp, uint16_t dec);

/**
 * @brief Seven-segment display control routine
 * @param[in/out] hdisp : Display handle
 * @retval None
 * @remark This should be called in display timer callback.
 */
void DISP_ROUTINE(DISP_HandleTypeDef* hdisp);


#endif /* INC_DISP_H_ */
