/**
 ******************************************************************************
 * @file    moore_machine.c
 * @author  AW           Adrian.Wojcik@put.poznan.pl
 * @version 1.0
 * @date    23-Apr-2023
 * @brief   Moore machine C implementation example
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

/* Typedef -------------------------------------------------------------------*/
typedef enum { a, b, c, d, none } INPUT;                //! Input symbols type
typedef enum { alpha = 1, beta = 2, gamma = 4 } OUTPUT; //! Output symbols type
typedef enum { A, B, C, } STATE;                        //! State symbol type

/* Function prototypes -------------------------------------------------------*/

/**
 * @brief State machine state transition function: next state truth table.
 * @param[in] i - an input symbol
 * @param[in] s - a current state symbol
 * @return Next state symbol
 */
STATE STATE_MACHINE_StateTransition(INPUT i, STATE s);

/**
 * @brief State machine output function: output truth table.
 * @param[in] s - a current state symbol
 * @return Current output symbol
 */
OUTPUT STATE_MACHINE_GetOutput(STATE s);

/**
 * @brief Prints table row with names of input, output and state.
 * @param[in] i - Input symbol
 * @param[in] o - Output symbol
 * @param[in] s - State symbol
 */
void print_state_machine(INPUT i, OUTPUT o, STATE s);

/**
 * @brief Converts ASCII character to input symbol.
 * @param[in] c : ASCII character: 'a', 'b', 'c' or 'd'.
 * @return Input symbol  
 */
static inline INPUT ascii2input(char c);

/**
 * @brief Reads input sequence from C-string.
 * @param[in]  input_str : C-string with input sequence
 * @param[out] input_seq : Array of inputs symbols to be filled
 * @param[in]  input_seq_max_len : Length of array
 * @return User input sequence length. 
 */
int read_input(const char *input_str, INPUT *input_seq, int input_seq_max_len);

/* Entry point: main function ------------------------------------------------*/
int main(int argc, char* argv[])
{
    STATE state = A; // Initial state
    INPUT input[32] = {a, b, c, d};
    int input_len = 4;

    // Reading user input
    if(argc > 1)
    {
        input_len = read_input(argv[1], input, sizeof(input) / sizeof(input[0]));
    }
    else
    {
        puts("  [No user input]    "); 
        puts("-------------------- ");
    }

    if(input_len == 0)
    {
       puts("Invalid input sequence."); 
       puts("  Usage  : ./<executable> \"<text with input sequence>\"");
       puts("  Example: ./moore_machine \"a,d,b,a,c,b,b,c,c,b,d,c,a,d\"");

       return 1;
    }
    // Logging table header
    puts(" # | I |   O   | S | ");
    puts("-------------------- ");

    int i;
    for (i = 0; i < input_len; i++)
    {
        print_state_machine(input[i], STATE_MACHINE_GetOutput(state), state);
        state = STATE_MACHINE_StateTransition(input[i], state);
    }
    print_state_machine(none, STATE_MACHINE_GetOutput(state), state);

    return 0;
}

/* Function implementations ---------------------------------------------------*/

STATE STATE_MACHINE_StateTransition(INPUT i, STATE s)
{
    static const STATE lookUpTable[][4] = 
    {
        /*        a  b  c  d  */
        /* A: */ {A, B, C, A},
        /* B: */ {B, A, C, A},
        /* B: */ {C, B, A, A}
    };

    return lookUpTable[s][i];
}

OUTPUT STATE_MACHINE_GetOutput(STATE s)
{
    static const OUTPUT lookUpTable[] = 
    {
        /* A: */ alpha,
        /* B: */ beta,
        /* C: */ gamma
    };

    return lookUpTable[s];
}

void print_state_machine(INPUT i, OUTPUT o, STATE s)
{
    static const char *_input_names[] = {
      /*000  001  010  011  100 */
        "a", "b", "c", "d", "_"};

    static const char *_output_names[] = {
    /*  000      001      010      011      100 */
        "     ", "alpha", "beta ", "     ", "gamma"};

    static const char *_state_names[] = {
    /*  00   01   10 */
        "A", "B", "C"};

    static int cnt = 0;

    printf("%2d | %s | %s | %s | \n", ++cnt,
           _input_names[i], _output_names[o], _state_names[s]);
}

static inline INPUT ascii2input(char c)
{
    if (c >= 'a' && c <= 'd')
        return (c - 'a');
    if (c >= 'A' && c <= 'D')
        return (c - 'a');
    return none;
}

int read_input(const char *input_str, INPUT *input_seq, int input_seq_max_len)
{
    int k = 0;
    for(int i = 0; i < strlen(input_str); i++)
    {
        INPUT tmp = ascii2input(input_str[i]);
        if(tmp != none && k < input_seq_max_len) 
        {
            input_seq[k] = tmp;
            k++;
        }
    }
    return k;
}