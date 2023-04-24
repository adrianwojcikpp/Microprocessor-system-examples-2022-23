/**
  ******************************************************************************
  * @file    L08_example.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    14-Mar-2022
  * @brief   Instruction #08 numeric data types in C
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <float.h>  // FLT constants
#include <stdint.h> // uint32_t
#include <limits.h> // INT_MAX etc.

#include "print_mem.h" 

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main(void)
{
  PRINT_INT32(INT32_MIN);
  PRINT_INT32(INT32_MAX);
  PRINT_INT32(2147483828);
 
  PRINT_Q31(0.32);
  PRINT_Q31(-1);
  PRINT_Q31(2.1);

  PRINT_FLOAT(1900.8099);
  PRINT_FLOAT(-1901.1901);
  PRINT_FLOAT(FLT_MAX);

  return 0;
}