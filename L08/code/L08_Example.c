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
  PRINT_FLOAT(0.5);
  
  return 0;
}