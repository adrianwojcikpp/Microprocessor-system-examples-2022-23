/**
  ******************************************************************************
  * @file    union_example.c
  * @author  AW		adrian.wojcik@put.poznan.pl
  * @version 3.0
  * @date    09-May-2022
  * @brief   Unions in C
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "print_mem.h"

/* Typedef -------------------------------------------------------------------*/
typedef union {
  int8_t number;
  char   character;
} int8_to_char;

typedef union {
  uint8_t raw[sizeof(float)];
  float  fp;
} uint8_to_float;

typedef union {
  uint8_t raw[sizeof(double)];
  double  fp;
} uint8_to_double;

typedef union {
  uint8_t raw[sizeof(long double)];
  long double fp;
} uint8_to_longdouble;

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main(void)
{
  { // Union example: ASCII character as number
    int8_to_char varA = { .number = 0x61 };
    int8_to_char varB = { .character = 'a' };
    printf("varA.character: %c\n", varA.character);
    printf("varB.number: 0x%hhx\n\n", varB.number);
  }

  { // Single precision floating point 
    uint8_to_float var = { .raw = {0xC3, 0xF5, 0x48, 0x40} };
    PRINT_VAR( var.fp );
  }

  { // Double precision floating point 
    uint8_to_double var = { .raw = {0x1F, 0x85, 0xEB, 0x51, 0xB8, 0x1E, 0x09, 0x40} };
    PRINT_VAR( var.fp );
  }

  { // Extended double precision floating point
    uint8_to_longdouble varA = { .raw = {0x00, 0xF8, 0x28, 0x5C, 0x8F, 0xC2, 0xF5, 0xC8,
									                       0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} };
    PRINT_VAR( varA.fp );
    uint8_to_longdouble varB = { .raw = {0x00, 0xF8, 0x28, 0x5C, 0x8F, 0xC2, 0xF5, 0xC8,
									                       0x00, 0x40, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC} };
    PRINT_VAR( varB.fp );
  }

  return 0;
}