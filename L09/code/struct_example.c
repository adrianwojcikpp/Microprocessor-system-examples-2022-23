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

//#pragma pack(2)

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

/* Typedef -------------------------------------------------------------------*/
typedef struct {
  char c1 __attribute__ ((aligned (16)));
  short int i1;
  double d1;
  char c2;
  short int i2;
  double d2;
  char c3;
} Structure1 /*__attribute__((packed))*/;

typedef struct {
  char c[2];
  short int i[2];
  double d[2];
} Structure2;

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief TODO
 * 
 * @param[in] s         :
 * @param[in] s_size    :
 * @param[in] alignment :
 */
void print_structure(void* s, int s_size, int alignment)
{
  printf("Size of structure: %d B\n", (int)s_size);
  char* s_bytes = (char*)s;
  for(int i = 0; i < s_size; i++)
  {
    if(i % alignment == 0)
      printf("\n");
    printf("%02hhX ", s_bytes[i]);
  }
}

/* Defines -------------------------------------------------------------------*/
#define PRINT_STRUCT(S) print_structure((void*)&(S), sizeof(S), __alignof__(S)); puts("\n")

/* Global variables ----------------------------------------------------------*/
Structure1 s1 = {'a', 1, 1.0, 'b', 2, 2.0 };
Structure2 s2 = { {'a', 'b'}, {1, 2}, {1.0, 2.0} };

/* Main function -------------------------------------------------------------*/
/**
  * @brief  The application entry point.
  * @retval 0 
  */
int main(void)
{
  { // Structure 1 Example
    Structure1 s = {'a', 1, 1.0, 'b', 2, 2.0 };
    //PRINT_STRUCT(s);
    PRINT_STRUCT(s1);
  }

    { // Structure 2 Example
    Structure2 s = { {'a', 'b'}, {1, 2}, {1.0, 2.0} };
    //PRINT_STRUCT(s);
    PRINT_STRUCT(s2);
  }

  return 0;
}