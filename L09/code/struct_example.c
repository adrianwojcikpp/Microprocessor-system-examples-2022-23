/**
  ******************************************************************************
  * @file    struct_example.c
  * @author  AW		adrian.wojcik@put.poznan.pl
  * @version 3.0
  * @date    09-May-2022
  * @brief   Structures in C
  *
  ******************************************************************************
  */

//#pragma pack(1)

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

/* Typedef -------------------------------------------------------------------*/
typedef struct {
  char c1;
  double d1;
  char c2;
  double d2;
  char c3;
  double d3;
  char c4;
  double d4;
} Structure1;

typedef struct {
  char c[4];
  double d[4];
} Structure2;

/* Main function -------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main(void)
{
  Structure1 a;
  Structure2 b;
  printf("Size of 'Structure1': %d\n", (int)sizeof(a));
  printf("Size of 'Structure2': %d\n", (int)sizeof(b));
  return 0;
}