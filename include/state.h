#pragma once
#include <stdint.h>

#include "disassemble8080p.h"

#define PASS 0
#define FAIL 1

#define MEM_SIZE 0x10000

extern float cycles_elapsed;

typedef struct Conditions
{
    uint8_t sign : 1; // aka S
    uint8_t zero : 1; // aka Z
    uint8_t pad5 : 1;
    uint8_t aux_carry : 1; // aka AC
    uint8_t pad3 : 1;
    uint8_t parity : 1; // aka P
    uint8_t pad1 : 1;
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
    uint8_t ports[8];
} State;

int state_compare(State *state, State *expected_state);

int state_compare_to_js_site(State *state, State *expected_state);

State *Init8080(void);

void Free8080(State *state);

void set_conditions(State *state, uint8_t byte_val);

uint8_t get_conditions_byte(const State *state);

void set_reg_pair(State *state, const char *reg_pair, uint16_t bit16_val);

void print_next_x_operations(const State *state, int num_ops, int cur_op_num);
