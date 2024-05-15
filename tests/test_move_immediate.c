#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>
#include <string.h>

int test_MOV_IMM(State *s, State *es, int8_t opcode)
{
    // Use switch case to set addresses of to registers
    uint8_t *s_to, *es_to;
    // clang-format off
    switch (opcode)
    {
    case MVI_B: s_to = &s->b; es_to = &es->b; break;
    case MVI_C: s_to = &s->c; es_to = &es->c; break;
    case MVI_D: s_to = &s->d; es_to = &es->d; break;
    case MVI_E: s_to = &s->e; es_to = &es->e; break;
    case MVI_H: s_to = &s->h; es_to = &es->h; break;
    case MVI_L: s_to = &s->l; es_to = &es->l; break;
    case MVI_A: s_to = &s->a; es_to = &es->a; break;
    case MVI_M: break;
    default: return FAIL;
    }
    // clang-format on

    // Set state s and expected_state es
    s->memory[0] = opcode;
    s->memory[1] = 0xff;
    s->memory[0x3399] = 0;
    s->h = 0x33;
    s->l = 0x99;
    es->h = 0x33;
    es->l = 0x99;
    if (opcode == MVI_M)
        es->memory[combine_bytes_to_word(es->h, es->l)] = 0xff;
    else
        *es_to = 0xff;
    es->pc = 2;

    // Run opcode
    emulate8080(s);

    // Validate opcode
    if (opcode == MVI_M && es->memory[0x3399] != 0xff) return FAIL;
    return state_compare(s, es);
}

/* Tests for various add instructions
 * Select a test by passing the opcode value as the first argument
 *
 */
int main(int argc, char *argv[])
{
    // Set up a states to test with
    State *s = Init8080();
    State *es = Init8080();

    int result;

    switch (strtol(argv[1], NULL, 16))
    {
    case MVI_B: result = test_MOV_IMM(s, es, MVI_B); break;
    case MVI_C: result = test_MOV_IMM(s, es, MVI_C); break;
    case MVI_D: result = test_MOV_IMM(s, es, MVI_D); break;
    case MVI_E: result = test_MOV_IMM(s, es, MVI_E); break;
    case MVI_H: result = test_MOV_IMM(s, es, MVI_H); break;
    case MVI_L: result = test_MOV_IMM(s, es, MVI_L); break;
    case MVI_M: result = test_MOV_IMM(s, es, MVI_M); break;
    case MVI_A: result = test_MOV_IMM(s, es, MVI_A); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(s);
    Free8080(es);

    return result;
}