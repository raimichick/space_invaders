#include "../include/disassemble8080p.h"
#include "../include/shell.h"
#include "../include/state.h"

#include <stdio.h>
#include <stdlib.h>

const int DEBUG = 0;
int _emulate_count = 0;

int main()
{
    // FILE *game_file = fopen("../include/invaders_combined", "rb");
    FILE *file = fopen(ROOT_DIR "/tests/diagnostics_asm", "rb");
    if (file == NULL)
    {
        file = fopen("../diagnostics_asm", "rb");
        if (file == NULL)
        {
            perror("Error: Could not open diagnostics_asm");
            exit(1);
        }
    }

    State *state = Init8080();

    // Allocate space for the game data
    fseek(file, 0L, SEEK_END);
    const int size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    fread(&state->memory[0x0100], size, 1, file);
    fclose(file);

    // Fix the first instruction to be JMP 0x100
    state->memory[0] = 0xc3;
    state->memory[1] = 0;
    state->memory[2] = 0x01;

    // Fix the stack pointer from 0x6ad to 0x7ad
    //  this 0x06 byte 112 in the code, which is
    //  byte 112 + 0x100 = 368 in memory
    state->memory[429] = 0x7;

    // Skip DAA test
    state->memory[0x59c] = 0xc3; // JMP
    state->memory[0x59d] = 0xc2;
    state->memory[0x59e] = 0x05;

    // run diagnostics asm
    uint16_t CPUER = 0x0689;
    uint16_t CPUOK = 0x069B;
    while (state->halt != 1 && state->pc < 0x06b0 && state->pc != CPUER && state->pc != CPUOK)
    {
        // print next 10 operations for debugging
        if (DEBUG)
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n%d\n", _emulate_count);
            // // TODO print registers to match javascript site
            int opbytes = 0;
            for (int _ = 0; _ < 10; _++)
                opbytes += disassemble8080p(state->memory, state->pc + opbytes);
        }

        emulate8080(state);
        _emulate_count += 1;
    }
    printf("\n\n\n\n");
    int result = FAIL;
    if (state->halt == 1)
    {
        printf("STOPPED DUE TO HALT");
        result = FAIL;
    }
    if (state->pc == CPUER)
    {
        printf("CPU ERRORED OUT!");
        result = FAIL;
    }
    if (state->pc == CPUOK)
    {
        printf("CPU IS OK!");
        result = PASS;
    }

    Free8080(state);
    return result;
}
