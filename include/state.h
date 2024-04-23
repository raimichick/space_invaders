#include <stdint.h>

typedef struct Conditions
{
    uint8_t zero : 1;      // aka Z
    uint8_t sign : 1;      // aka S
    uint8_t parity : 1;    // aka P
    uint8_t carry : 1;     // aka CY
    uint8_t aux_carry : 1; // aka AC
    uint8_t pad : 3;
} Conditions;

typedef struct State
{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    uint8_t *memory;
    Conditions conditions;
    uint8_t int_enable;
} State;

inline int state_compare(State *state, State *expected_state)
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
