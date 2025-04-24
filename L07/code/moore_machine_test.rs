
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(non_upper_case_globals)]

/**
  ******************************************************************************
  * @file    moore_machine_test.rs
  * @author  AW           Adrian.Wojcik@put.poznan.pl
  * @version 1.1
  * @date    24-Apr-2025
  * @brief   Moore machine Rust implementation example
  *
  ******************************************************************************
  */

/* Enums ---------------------------------------------------------------------*/
#[derive(Copy, Clone)]
enum INPUT { a, b, c, d, none, } // Input symbols type

#[derive(Copy, Clone)]
enum OUTPUT { alpha = 1, beta = 2, gamma = 4, } // Output symbols type

#[derive(Copy, Clone)]
enum STATE { A, B, C, } // State symbol type

/* Function implementations ---------------------------------------------------*/
/**
 * @brief State machine state transition function: next state truth table.
 * @param[in] i : an input symbol
 * @param[in] s : a current state symbol
 * @return Next state symbol
 */
fn STATE_MACHINE_StateTransition(input: INPUT, state: STATE) -> STATE {
    let lookup_table = [
    //   INPUT::A  INPUT::B  INPUT::C  INPUT::D
        [STATE::A, STATE::B, STATE::C, STATE::A], // STATE A
        [STATE::B, STATE::A, STATE::C, STATE::A], // STATE B
        [STATE::C, STATE::B, STATE::A, STATE::A], // STATE C
    ];

    let i = match input {
        INPUT::a => 0,
        INPUT::b => 1,
        INPUT::c => 2,
        INPUT::d => 3,
        INPUT::none => 3, // Fallback safe default
    };

    let s = match state {
        STATE::A => 0,
        STATE::B => 1,
        STATE::C => 2,
    };

    lookup_table[s][i]
}

/**
 * @brief State machine output function: output truth table.
 * @param[in] s : a current state symbol
 * @return Current output symbol
 */
fn STATE_MACHINE_GetOutput(state: STATE) -> OUTPUT {
    match state {
        STATE::A => OUTPUT::alpha,
        STATE::B => OUTPUT::beta,
        STATE::C => OUTPUT::gamma,
    }
}

/**
 * @brief Prints table row with names of input, output and state.
 * @param[in] i : Input symbol 
 * @param[in] o : Output symbol 
 * @param[in] s : State symbol 
 */
fn print_state_machine(input: INPUT, output: OUTPUT, state: STATE, count: usize) {
    let input_names = ["a", "b", "c", "d", "_"];
    let output_names = ["     ", "alpha", "beta ", "     ", "gamma"];
    let state_names = ["A", "B", "C"];

    let i = match input {
        INPUT::a => 0,
        INPUT::b => 1,
        INPUT::c => 2,
        INPUT::d => 3,
        INPUT::none => 4,
    };

    let o = match output {
        OUTPUT::alpha => 1,
        OUTPUT::beta => 2,
        OUTPUT::gamma => 4,
    };

    let s = match state {
        STATE::A => 0,
        STATE::B => 1,
        STATE::C => 2,
    };

    println!("{:2} | {} | {} | {} |", count, input_names[i], output_names[o], state_names[s]);
}

// Entry point
fn main() {
    let input = [
        INPUT::a, INPUT::d, INPUT::b, INPUT::a, INPUT::d,
        INPUT::b, INPUT::b, INPUT::c, INPUT::c, INPUT::b,
        INPUT::d, INPUT::c, INPUT::a, INPUT::d,
    ];

    let mut state = STATE::A; // Initial state

    println!(" # | I |   O   | S |");
    println!("--------------------");

    for (count, &i) in input.iter().enumerate() {
        print_state_machine(i, STATE_MACHINE_GetOutput(state), state, count + 1);
        state = STATE_MACHINE_StateTransition(i, state);
    }

    print_state_machine(INPUT::none, STATE_MACHINE_GetOutput(state), state, input.len() + 1);
}
