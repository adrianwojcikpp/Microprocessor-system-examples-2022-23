/**
  ******************************************************************************
  * @file    mealy_machine_test.c
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    21-Apr-2021
  * @brief   Mealy machine C implementation example
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

/* Typedef -------------------------------------------------------------------*/
typedef enum { a, b, c, d } INPUT;                     				//! Input symbols type
typedef enum { alpha = 1, beta = 2, gamma = 4, delta = 8 } OUTPUT;  //! Output symbols type
typedef enum { A, B, C} STATE;                          			//! State symbol type

/* Function prototypes -------------------------------------------------------*/

/**
 * @brief State machine state transition function: next state truth table
 * @param[in] i - an input symbol
 * @param[in] s - a current state symbol
 * @return Next state symbol
 */
STATE STATE_MACHINE_StateTransition(INPUT i, STATE s);

/**
 * @brief State machine output function: output truth table
 * @param[in] i - an input symbol
 * @param[in] s - a current state symbol
 * @return Current output symbol
 */
OUTPUT STATE_MACHINE_GetOutput(INPUT i, STATE s);

/**
 * @brief Prints table row with names of input, output and state
 * @param[in] i - Input symbol 
 * @param[in] o - Output symbol 
 * @param[in] s - State symbol 
 */
void print_state_machine(INPUT i, OUTPUT o, STATE s);

/* Entry point: main function ------------------------------------------------*/
int main(void)
{
  STATE state = A; // Initial state
  INPUT input[] = { a, d, b, a, c, b, b, c, c, b, d, c, a, d };
  
  // Logging table header
  printf(" # | I |   O   | S | \n");
  printf("-------------------- \n");
  
  int i;
  for(i = 0; i < 14; i++)
  {
    print_state_machine(input[i], STATE_MACHINE_GetOutput(input[i], state), state);
    state = STATE_MACHINE_StateTransition(input[i], state);
  }
  print_state_machine(input[i-1], STATE_MACHINE_GetOutput(input[i-1], state), state);
  
  return 0;
}

/* Function implementations ---------------------------------------------------*/

STATE STATE_MACHINE_StateTransition(INPUT i, STATE s)
{
  STATE lookUpTable[][4] = {
    /*         a  b  c  d  */
    /* A: */ { A, B, C, A },
    /* B: */ { B, A, C, A },
    /* C: */ { C, B, A, A }      
  };
  
  return lookUpTable[s][i];
}

OUTPUT STATE_MACHINE_GetOutput(INPUT i, STATE s)
{
  OUTPUT lookUpTable[][4] = {
    /*           a      b      c      d  */
    /* A: */ { alpha,  beta, gamma, delta },
    /* B: */ {  beta,  beta, gamma, delta },
    /* C: */ { gamma,  beta, gamma, delta }      
  };
  
  return lookUpTable[s][i];
}

void print_state_machine(INPUT i, OUTPUT o, STATE s)
{
                                      
  static const char* _input_names[] = {
  /* 00   01   10   11 */
    "a", "b", "c", "d"
  };
  
  static const char* _output_names[] = {
  /* 0000     0001     0010     0011     0100     0101     0110     0111     1000  */
    "     ", "alpha", "beta ", "     ", "gamma", "     ", "     ", "     ", "delta"
  };
  
  static const char* _state_names[] = {
  /* 00   01   10 */ 
    "A", "B", "C"
  };
  
  static int cnt = 0;
  
  printf("%2d | %s | %s | %s | \n", ++cnt, 
    _input_names[i], _output_names[o], _state_names[s]);
}