#include <stdint.h>

struct State *Init8080(void);

void emulate8080(struct State *state);

void unimplementedInstr(uint8_t opcode);

void push_program_counter_to_stack(struct State *state);
void push_register_pair_to_stack(struct State *state, uint8_t rh, uint8_t rl);
void pop_stack_to_program_counter(struct State *state);
void pop_stack_to_register_pair(struct State *state, uint8_t *rh, uint8_t *rl);
void mov_reg_to_reg(struct State *state, uint8_t *to, uint8_t *from);
void subtract_instruction(struct State *state, uint8_t minuend,
                          uint8_t subtrahend);
void wait_cycles(int clockCycles);
uint16_t combine_registers(uint8_t reg1, uint8_t reg2);
uint8_t get_sign_flag(uint8_t register_value);
uint8_t get_zero_flag(uint8_t register_value);
uint8_t get_parity_flag(uint8_t register_value);
uint8_t get_carry_flag_from_sum(uint8_t val0, uint8_t val1);
uint8_t get_carry_flag_from_sum_16b(uint16_t val0, uint16_t val1);
uint8_t get_aux_carry_flag_from_sum(uint8_t val0, uint8_t val1);
