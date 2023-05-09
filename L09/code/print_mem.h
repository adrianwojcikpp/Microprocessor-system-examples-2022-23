/**
  ******************************************************************************
  * @file    print_mem.h
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 2.0
  * @date    14-Mar-2022
  * @brief   Printing memory content
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>    
#include <stdint.h>
  
/* BEGIN RAW MEMORY -------------------------------------------- */
typedef uint8_t mem_t; //!< 8-bits (1 byte) memory location
/* END RAW MEMORY ---------------------------------------------- */

/* BEGIN INTEGER ----------------------------------------------- */
/**
 * @brief Printing integer variable or literal 
 *        as a numeric value and memory content.
 * @param number_text : Input integer variable name or literal as text
 * @param number : Input integer number
 */
void print_int64(const char* number_text, int64_t number);
void print_int32(const char* number_text, int32_t number);
void print_int16(const char* number_text, int16_t number);
void print_int8(const char* number_text, int8_t number);
/* END INTEGER ------------------------------------------------- */

/* BEGIN FLOATING-POINT -----------------------------------------*/
/**
 * @brief Printing single-precision floating point variable or literal 
 *        as a numeric value and memory content.
 * @param number_text : Input floating-point variable name or literal as text
 * @param number : Input floating-point number 
 */
void print_float(const char* number_text, float number);
void print_double(const char* number_text, double number);
void print_long_double(const char* number_text, long double number);
/* END FLOATING-POINT -------------------------------------------*/

/* BEGIN GENERIC ------------------------------------------------*/
#define PRINT_VAR(n) _Generic((n), \
  int64_t: print_int64, \
  int32_t: print_int32, \
  int16_t: print_int16, \
  int8_t: print_int8, \
  float: print_float, \
  double: print_double, \
  long double: print_long_double \
)(#n,n); puts("\n")
/* END GENERIC -------------------------------------------------*/