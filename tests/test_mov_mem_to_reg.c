#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>

int test_MOV_MEM_to_REG(State *s, State *es, uint8_t opcode)
{
    // Use switch case to set addresses of to registers
    uint8_t *s_to, *es_to;
    // clang-format off
    switch (opcode)
    {
    case MOV_BM: s_to = &s->b; es_to = &es->b; break;
    case MOV_CM: s_to = &s->c; es_to = &es->c; break;
    case MOV_DM: s_to = &s->d; es_to = &es->d; break;
    case MOV_EM: s_to = &s->e; es_to = &es->e; break;
    case MOV_HM: s_to = &s->h; es_to = &es->h; break;
    case MOV_LM: s_to = &s->l; es_to = &es->l; break;
    case MOV_AM: s_to = &s->a; es_to = &es->a; break;
    default: return FAIL;
    }
    // clang-format on

    // Set state s and expected_state es
    s->memory[0] = opcode;
    s->memory[1] = 1;
    s->memory[2] = 5;
    *s_to = 2;
    s->h = 0;
    s->l = 2;
    es->h = 0;
    es->l = 2;
    es->pc = 1;
    *es_to = 5;

    // Run opcode
    emulate8080(s);

    // Validate output
    return state_compare(s, es);
}

/* Tests for moving a value from memory to a register
 * Select a test by passing the opcode value as the first argument
 *
 */
int main(int argc, char *argv[])
{
    // Set up states to test with
    State *s = Init8080();
    State *es = Init8080();

    int result;

    switch (strtol(argv[1], NULL, 16))
    {
    case MOV_BM: result = test_MOV_MEM_to_REG(s, es, MOV_BM); break;
    case MOV_CM: result = test_MOV_MEM_to_REG(s, es, MOV_CM); break;
    case MOV_DM: result = test_MOV_MEM_to_REG(s, es, MOV_DM); break;
    case MOV_EM: result = test_MOV_MEM_to_REG(s, es, MOV_EM); break;
    case MOV_HM: result = test_MOV_MEM_to_REG(s, es, MOV_HM); break;
    case MOV_LM: result = test_MOV_MEM_to_REG(s, es, MOV_LM); break;
    case MOV_AM: result = test_MOV_MEM_to_REG(s, es, MOV_AM); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(s);
    Free8080(es);

    return result;
}
