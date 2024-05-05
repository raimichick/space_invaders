#pragma once
#include <stdint.h>

#define PASS 0
#define FAIL 1

typedef struct Conditions
{
    uint8_t sign : 1; // aka S
    uint8_t zero : 1; // aka Z
    uint8_t pad0 : 1;
    uint8_t aux_carry : 1; // aka AC
    uint8_t pad1 : 1;
    uint8_t parity : 1; // aka P
    uint8_t pad2 : 1;
    uint8_t carry : 1; // aka CY
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
    uint8_t interrupt_enabled;
    uint8_t halt;
    uint8_t *read_ports[8];
    uint8_t *write_ports[8];
} State;

int state_compare(State *state, State *expected_state);

State *Init8080(void);

void Free8080(State *state);

void set_conditions(State *state, uint8_t hex_val);
