#pragma once
#include "state.h"
#include <stdint.h>

void emulate8080(struct State *state);

void push_register_pair_to_stack(struct State *state, uint8_t rh, uint8_t rl);
void pop_stack_to_register_pair(struct State *state, uint8_t *rh, uint8_t *rl);
void mov_reg_to_reg(struct State *state, uint8_t *to, uint8_t *from);
void mov_reg_to_mem(struct State *state, uint8_t *from);
void mov_mem_to_reg(struct State *state, uint8_t *to);
void ana_helper(struct State *state, uint8_t andwith_val);
void xra_helper(struct State *state, uint8_t xorwith_val);
void ora_helper(struct State *state, uint8_t orwith_val);
uint16_t combine_h_l_addr(struct State *state);
void jump_to_addr(struct State *state, uint8_t *code);
void call_helper(struct State *state, uint16_t call_address);
void call_helper_conditional(State *state, int conditional, uint16_t address);
void return_helper(struct State *state);
void return_helper_conditional(State *state, int conditional, int opbytes);
uint8_t subtract_8b(struct State *state, uint8_t minuend, uint8_t subtrahend);
uint8_t add_8b(struct State *state, uint8_t operand1, uint8_t operand2);
uint8_t add_with_carry_8b(struct State *state, uint8_t operand1, uint8_t operand2);
uint8_t increment_8b(struct State *state, uint8_t value_to_increment);
uint8_t decrement_8b(struct State *state, uint8_t value_to_decrement);
void wait_cycles(float clockCycles);
uint16_t combine_bytes_to_word(uint8_t hi_byte, uint8_t lo_byte);
void split_word_to_bytes(uint16_t word, uint8_t *hi_byte, uint8_t *lo_byte);
uint8_t get_sign_flag(uint8_t register_value);
uint8_t get_zero_flag(uint8_t register_value);
uint8_t get_parity_flag(uint8_t register_value);
uint8_t get_carry_flag_from_sum_8b(uint8_t val0, uint8_t val1);
uint8_t get_carry_flag_from_sum_16b(uint16_t val0, uint16_t val1);
uint8_t get_aux_carry_flag_from_sum(uint8_t val0, uint8_t val1);

void unimplementedInstr(uint8_t opcode);
