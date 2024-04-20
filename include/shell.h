#include <stdint.h>

struct State *Init8080(void);

void emulate8080(struct State *state);

void unimplementedInstr(uint8_t opcode);

uint8_t setParity(uint8_t register_value);