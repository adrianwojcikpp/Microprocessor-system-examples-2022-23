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
typedef uint32_t mem_t; //!< 32-bits (4 bytes) memory location

/**
 * @brief Printing content of 32-bit memory location
 *        as unsigned integer in decimal, hexadecimal and binary.
 * @param mem : Input memory address
 */
void print_mem(mem_t* mem);
/* END RAW MEMORY ---------------------------------------------- */

/* BEGIN INTEGER ----------------------------------------------- */

/// @brief Naming convention: binary string buffer name postfix
#define __binstr(name) name##_binstr

/// @brief Defines buffer of <size> for <name> variable
#define __binstr_buf(name, size) \
  char __binstr(name)[size] = {0,};\
  uint32_to_binstr(name, __binstr(name))
  
/**
 * @brief Printing integer variable or literal 
 *        as a numeric value and memory content.
 * @param number_text : Input integer number as text
 * @param number : Input integer number as 'int32_t'
 */
void print_int32(const char* number_text, int32_t number);

/**
 * @brief Integer printing macro with stringize operator
 * @param n : Input integer variable or literal
 */
#define PRINT_INT32(n) print_int32(#n,n); puts("\n")
/* END INTEGER ------------------------------------------------- */

/* BEGIN FIXED-POINT ------------------------------------------- */
/**
 * @brief Custom fixed-point data type
 * @ref https://en.wikipedia.org/wiki/Q_(number_format)
 */
typedef int32_t q31_t; 

#define DOUBLE_TO_Q31(n) (q31_t)(n * (1LL << 31))  //!< 
#define Q31_TO_DOUBLE(n) (double)n / (1LL << 31)   //!< 

/**
 * @brief Printing fixed-point variable or literal 
 *        from <-1.0, 1.0) range as a numeric value and memory content.
 * @param number_text : Input fixed-point fractional number as text
 * @param number : Input fixed-point fractional number as 'q31_t'
 */
void print_q31(const char* number_text, q31_t number);

/**
 * @brief Fixed-point number printing macro with stringize operator
 * @param n : Input >>floating-point<< variable or literal
 */
#define PRINT_Q31(n) print_q31(#n,DOUBLE_TO_Q31(n)); puts("\n")
/* END FIXED-POINT --------------------------------------------- */

/* BEGIN FLOATING-POINT -----------------------------------------*/
/**
 * @brief Printing single-precision floating point variable or literal 
 *        as a numeric value and memory content.
 * @param number_text : Input floating-point fractional number as text
 * @param number : Input floating-point fractional number as 'float'
 */
void print_float(const char* number_text, float number);

/**
 * @brief Floating-point number printing macro with stringize operator
 * @param n : Input single precision floating-point variable or literal
 */
#define PRINT_FLOAT(n) print_float(#n,n); puts("\n")
/* END FLOATING-POINT -------------------------------------------*/