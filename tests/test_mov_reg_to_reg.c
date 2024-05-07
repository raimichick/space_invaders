#include "../include/opcodes.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdlib.h>

int test_MOV_REG_REG(State *s, State *es, uint8_t opcode)
{
    // Use switch case to set addresses of to and from registers
    uint8_t *s_fr, *s_to, *es_fr, *es_to;

    // clang-format off
    switch (opcode)
    {
    case MOV_BB: s_fr = &s->b; s_to = &s->b; es_fr = &es->b; es_to = &es->b; break;
    case MOV_BC: s_fr = &s->c; s_to = &s->b; es_fr = &es->c; es_to = &es->b; break;
    case MOV_BD: s_fr = &s->d; s_to = &s->b; es_fr = &es->d; es_to = &es->b; break;
    case MOV_BE: s_fr = &s->e; s_to = &s->b; es_fr = &es->e; es_to = &es->b; break;
    case MOV_BH: s_fr = &s->h; s_to = &s->b; es_fr = &es->h; es_to = &es->b; break;
    case MOV_BL: s_fr = &s->l; s_to = &s->b; es_fr = &es->l; es_to = &es->b; break;
    case MOV_BA: s_fr = &s->a; s_to = &s->b; es_fr = &es->a; es_to = &es->b; break;
    case MOV_CB: s_fr = &s->b; s_to = &s->c; es_fr = &es->b; es_to = &es->c; break;
    case MOV_CC: s_fr = &s->c; s_to = &s->c; es_fr = &es->c; es_to = &es->c; break;
    case MOV_CD: s_fr = &s->d; s_to = &s->c; es_fr = &es->d; es_to = &es->c; break;
    case MOV_CE: s_fr = &s->e; s_to = &s->c; es_fr = &es->e; es_to = &es->c; break;
    case MOV_CH: s_fr = &s->h; s_to = &s->c; es_fr = &es->h; es_to = &es->c; break;
    case MOV_CL: s_fr = &s->l; s_to = &s->c; es_fr = &es->l; es_to = &es->c; break;
    case MOV_CA: s_fr = &s->a; s_to = &s->c; es_fr = &es->a; es_to = &es->c; break;
    case MOV_DB: s_fr = &s->b; s_to = &s->d; es_fr = &es->b; es_to = &es->d; break;
    case MOV_DC: s_fr = &s->c; s_to = &s->d; es_fr = &es->c; es_to = &es->d; break;
    case MOV_DD: s_fr = &s->d; s_to = &s->d; es_fr = &es->d; es_to = &es->d; break;
    case MOV_DE: s_fr = &s->e; s_to = &s->d; es_fr = &es->e; es_to = &es->d; break;
    case MOV_DH: s_fr = &s->h; s_to = &s->d; es_fr = &es->h; es_to = &es->d; break;
    case MOV_DL: s_fr = &s->l; s_to = &s->d; es_fr = &es->l; es_to = &es->d; break;
    case MOV_DA: s_fr = &s->a; s_to = &s->d; es_fr = &es->a; es_to = &es->d; break;
    case MOV_EB: s_fr = &s->b; s_to = &s->e; es_fr = &es->b; es_to = &es->e; break;
    case MOV_EC: s_fr = &s->c; s_to = &s->e; es_fr = &es->c; es_to = &es->e; break;
    case MOV_ED: s_fr = &s->d; s_to = &s->e; es_fr = &es->d; es_to = &es->e; break;
    case MOV_EE: s_fr = &s->e; s_to = &s->e; es_fr = &es->e; es_to = &es->e; break;
    case MOV_EH: s_fr = &s->h; s_to = &s->e; es_fr = &es->h; es_to = &es->e; break;
    case MOV_EL: s_fr = &s->l; s_to = &s->e; es_fr = &es->l; es_to = &es->e; break;
    case MOV_EA: s_fr = &s->a; s_to = &s->e; es_fr = &es->a; es_to = &es->e; break;
    case MOV_HB: s_fr = &s->b; s_to = &s->h; es_fr = &es->b; es_to = &es->h; break;
    case MOV_HC: s_fr = &s->c; s_to = &s->h; es_fr = &es->c; es_to = &es->h; break;
    case MOV_HD: s_fr = &s->d; s_to = &s->h; es_fr = &es->d; es_to = &es->h; break;
    case MOV_HE: s_fr = &s->e; s_to = &s->h; es_fr = &es->e; es_to = &es->h; break;
    case MOV_HH: s_fr = &s->h; s_to = &s->h; es_fr = &es->h; es_to = &es->h; break;
    case MOV_HL: s_fr = &s->l; s_to = &s->h; es_fr = &es->l; es_to = &es->h; break;
    case MOV_HA: s_fr = &s->a; s_to = &s->h; es_fr = &es->a; es_to = &es->h; break;
    case MOV_LB: s_fr = &s->b; s_to = &s->l; es_fr = &es->b; es_to = &es->l; break;
    case MOV_LC: s_fr = &s->c; s_to = &s->l; es_fr = &es->c; es_to = &es->l; break;
    case MOV_LD: s_fr = &s->d; s_to = &s->l; es_fr = &es->d; es_to = &es->l; break;
    case MOV_LE: s_fr = &s->e; s_to = &s->l; es_fr = &es->e; es_to = &es->l; break;
    case MOV_LH: s_fr = &s->h; s_to = &s->l; es_fr = &es->h; es_to = &es->l; break;
    case MOV_LL: s_fr = &s->l; s_to = &s->l; es_fr = &es->l; es_to = &es->l; break;
    case MOV_LA: s_fr = &s->a; s_to = &s->l; es_fr = &es->a; es_to = &es->l; break;
    case MOV_AB: s_fr = &s->b; s_to = &s->a; es_fr = &es->b; es_to = &es->a; break;
    case MOV_AC: s_fr = &s->c; s_to = &s->a; es_fr = &es->c; es_to = &es->a; break;
    case MOV_AD: s_fr = &s->d; s_to = &s->a; es_fr = &es->d; es_to = &es->a; break;
    case MOV_AE: s_fr = &s->e; s_to = &s->a; es_fr = &es->e; es_to = &es->a; break;
    case MOV_AH: s_fr = &s->h; s_to = &s->a; es_fr = &es->h; es_to = &es->a; break;
    case MOV_AL: s_fr = &s->l; s_to = &s->a; es_fr = &es->l; es_to = &es->a; break;
    case MOV_AA: s_fr = &s->a; s_to = &s->a; es_fr = &es->a; es_to = &es->a; break;
    default: return FAIL;
    }
    // clang-format on

    // Set state s and expected_state es
    s->memory[0] = opcode;
    *s_to = 0x11;
    *s_fr = 0xff;
    *es_to = 0xff;
    *es_fr = 0xff;
    es->pc = 1;

    // Run opcode
    emulate8080(s);

    // Validate output
    return state_compare(s, es);
}

/* Tests for moving a value from one register to another
 * Select a test by passing the opcode value as the first argument
 */
int main(int argc, char *argv[])
{
    // Set up a states to test with
    State *s = Init8080();  // state
    State *es = Init8080(); // expected_state

    int result;

    switch (strtol(argv[1], NULL, 16))
    {
    case MOV_BB: result = test_MOV_REG_REG(s, es, MOV_BB); break;
    case MOV_BC: result = test_MOV_REG_REG(s, es, MOV_BC); break;
    case MOV_BD: result = test_MOV_REG_REG(s, es, MOV_BD); break;
    case MOV_BE: result = test_MOV_REG_REG(s, es, MOV_BE); break;
    case MOV_BH: result = test_MOV_REG_REG(s, es, MOV_BH); break;
    case MOV_BL: result = test_MOV_REG_REG(s, es, MOV_BL); break;
    case MOV_BA: result = test_MOV_REG_REG(s, es, MOV_BA); break;
    case MOV_CB: result = test_MOV_REG_REG(s, es, MOV_CB); break;
    case MOV_CC: result = test_MOV_REG_REG(s, es, MOV_CC); break;
    case MOV_CD: result = test_MOV_REG_REG(s, es, MOV_CD); break;
    case MOV_CE: result = test_MOV_REG_REG(s, es, MOV_CE); break;
    case MOV_CH: result = test_MOV_REG_REG(s, es, MOV_CH); break;
    case MOV_CL: result = test_MOV_REG_REG(s, es, MOV_CL); break;
    case MOV_CA: result = test_MOV_REG_REG(s, es, MOV_CA); break;
    case MOV_DB: result = test_MOV_REG_REG(s, es, MOV_DB); break;
    case MOV_DC: result = test_MOV_REG_REG(s, es, MOV_DC); break;
    case MOV_DD: result = test_MOV_REG_REG(s, es, MOV_DD); break;
    case MOV_DE: result = test_MOV_REG_REG(s, es, MOV_DE); break;
    case MOV_DH: result = test_MOV_REG_REG(s, es, MOV_DH); break;
    case MOV_DL: result = test_MOV_REG_REG(s, es, MOV_DL); break;
    case MOV_DA: result = test_MOV_REG_REG(s, es, MOV_DA); break;
    case MOV_EB: result = test_MOV_REG_REG(s, es, MOV_EB); break;
    case MOV_EC: result = test_MOV_REG_REG(s, es, MOV_EC); break;
    case MOV_ED: result = test_MOV_REG_REG(s, es, MOV_ED); break;
    case MOV_EE: result = test_MOV_REG_REG(s, es, MOV_EE); break;
    case MOV_EH: result = test_MOV_REG_REG(s, es, MOV_EH); break;
    case MOV_EL: result = test_MOV_REG_REG(s, es, MOV_EL); break;
    case MOV_EA: result = test_MOV_REG_REG(s, es, MOV_EA); break;
    case MOV_HB: result = test_MOV_REG_REG(s, es, MOV_HB); break;
    case MOV_HC: result = test_MOV_REG_REG(s, es, MOV_HC); break;
    case MOV_HD: result = test_MOV_REG_REG(s, es, MOV_HD); break;
    case MOV_HE: result = test_MOV_REG_REG(s, es, MOV_HE); break;
    case MOV_HH: result = test_MOV_REG_REG(s, es, MOV_HH); break;
    case MOV_HL: result = test_MOV_REG_REG(s, es, MOV_HL); break;
    case MOV_HA: result = test_MOV_REG_REG(s, es, MOV_HA); break;
    case MOV_LB: result = test_MOV_REG_REG(s, es, MOV_LB); break;
    case MOV_LC: result = test_MOV_REG_REG(s, es, MOV_LC); break;
    case MOV_LD: result = test_MOV_REG_REG(s, es, MOV_LD); break;
    case MOV_LE: result = test_MOV_REG_REG(s, es, MOV_LE); break;
    case MOV_LH: result = test_MOV_REG_REG(s, es, MOV_LH); break;
    case MOV_LL: result = test_MOV_REG_REG(s, es, MOV_LL); break;
    case MOV_LA: result = test_MOV_REG_REG(s, es, MOV_LA); break;
    case MOV_AB: result = test_MOV_REG_REG(s, es, MOV_AB); break;
    case MOV_AC: result = test_MOV_REG_REG(s, es, MOV_AC); break;
    case MOV_AD: result = test_MOV_REG_REG(s, es, MOV_AD); break;
    case MOV_AE: result = test_MOV_REG_REG(s, es, MOV_AE); break;
    case MOV_AH: result = test_MOV_REG_REG(s, es, MOV_AH); break;
    case MOV_AL: result = test_MOV_REG_REG(s, es, MOV_AL); break;
    case MOV_AA: result = test_MOV_REG_REG(s, es, MOV_AA); break;
    default: result = FAIL; // Test failed due to incorrect test parameter
    }

    // Clean up the state memory
    Free8080(s);
    Free8080(es);

    return result;
}