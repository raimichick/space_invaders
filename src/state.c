#include "../include/state.h"

int state_compare(State *state, State *expected_state)
{
    // Compares each of the registers and conditions between the two states
    // If both states are the same, returns 0, else 1
    // Does not check memory

    if (state->a != expected_state->a) return 1;
    if (state->b != expected_state->b) return 1;
    if (state->c != expected_state->c) return 1;
    if (state->d != expected_state->d) return 1;
    if (state->e != expected_state->e) return 1;
    if (state->h != expected_state->h) return 1;
    if (state->l != expected_state->l) return 1;
    if (state->sp != expected_state->sp) return 1;
    if (state->pc != expected_state->pc) return 1;
    if (state->int_enable != expected_state->int_enable) return 1;

    if (state->conditions.zero != expected_state->conditions.zero) return 1;
    if (state->conditions.sign != expected_state->conditions.sign) return 1;
    if (state->conditions.parity != expected_state->conditions.parity) return 1;
    if (state->conditions.carry != expected_state->conditions.carry) return 1;
    if (state->conditions.aux_carry != expected_state->conditions.aux_carry)
        return 1;
    if (state->conditions.pad != expected_state->conditions.pad) return 1;

    return 0;
}