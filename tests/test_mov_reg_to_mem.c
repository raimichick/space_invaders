#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>

int test_MOV_REG_to_MEM(State *s, State *es, int8_t opcode)
{
    // Use switch case to set addresses of to registers
    uint8_t *s_fr, *es_fr;
    // clang-format off
    switch (opcode)
    {
    case MOV_MB: s_fr = &s->b; es_fr = &es->b; break;
    case MOV_MC: s_fr = &s->c; es_fr = &es->c; break;
    case MOV_MD: s_fr = &s->d; es_fr = &es->d; break;
    case MOV_ME: s_fr = &s->e; es_fr = &es->e; break;
    case MOV_MH: s_fr = &s->h; es_fr = &es->h; break;
    case MOV_ML: s_fr = &s->l; es_fr = &es->l; break;
    case MOV_MA: s_fr = &s->a; es_fr = &es->a; break;
    default: return FAIL;
    }
    // clang-format on

    // Set state s and expected_state es
    s->memory[0] = opcode;
    s->memory[0x0101] = 0;
    *s_fr = 2;
    s->h = 0x01;
    s->l = 0x01;
    *es_fr = 2;
    es->h = 0x01;
    es->l = 0x01;
    es->pc = 1;

    // Run opcode
    emulate8080(s);

    // Validate output
    if (opcode == MOV_ML || opcode == MOV_MH) // L and H cases will pass a different value
    {
        if (s->memory[0x0101] != 0x01)
        {
            return FAIL;
        }
    }
    else if (s->memory[0x0101] != 2)
        return FAIL;
    return state_compare(s, es);
}

/* Tests for moving a value from a register to memory
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
    case MOV_MB: result = test_MOV_REG_to_MEM(s, es, MOV_MB); break;
    case MOV_MC: result = test_MOV_REG_to_MEM(s, es, MOV_MC); break;
    case MOV_MD: result = test_MOV_REG_to_MEM(s, es, MOV_MD); break;
    case MOV_ME: result = test_MOV_REG_to_MEM(s, es, MOV_ME); break;
    case MOV_MH: result = test_MOV_REG_to_MEM(s, es, MOV_MH); break;
    case MOV_ML: result = test_MOV_REG_to_MEM(s, es, MOV_ML); break;
    case MOV_MA: result = test_MOV_REG_to_MEM(s, es, MOV_MA); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(s);
    Free8080(es);

    return result;
}
