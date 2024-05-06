/**
  ******************************************************************************
  * @file    array_example.c
  * @author  AW		adrian.wojcik@put.poznan.pl
  * @version 3.0
  * @date    09-May-2022
  * @brief   Arrays in C
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

/* Defines -------------------------------------------------------------------*/
#define array_size(x) sizeof( x ) / sizeof( x[0] )

/* Global variables ----------------------------------------------------------*/
uint16_t x[10];

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main(void)
{
  uint16_t y[10]; //= { 0 };
  
  printf("First element of array 'x' sizeof(): %llu\n", sizeof(x[0])); // %I64u instead of %llu for Microsoft Visual Studio
  printf("Array 'x' sizeof(): %llu\n", sizeof(x));
  printf("Array 'x' number of elements: %llu\n", array_size(x));
  
  puts("\nGlobal variable 'x'");
  for(int i = 0; i < (sizeof(x)/sizeof(x[0])); i++)
    printf("%d,", x[i]);
    
  puts("\nLocal variable 'y'");
  for(int i = 0; i < (sizeof(y)/sizeof(y[0])); i++)
    printf("%d,", y[i]);
  
  return 0;
}