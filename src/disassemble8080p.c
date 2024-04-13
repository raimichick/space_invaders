#include <stdio.h>

int disassemble8080p(unsigned char *codebuffer, int pc)
{
    /*
    TODO: Base code copied from emulator 101 website: CHANGE THIS AROUND TO MAKE
    IT OUR OWN!
    TODO: Add opcode-to-instruction cases.
    */
    unsigned char *code = &codebuffer[pc];
    int opbytes = 1;
    printf("%04x ", pc);
    // clang-format off
    switch (*code)
    {
        case 0x00: printf("NOP");  break;
        default: printf("NOT IMPLEMENTED NOT IMPLEMENTED NOT IMPLEMENTED NOT IMPLEMENTED");
    }
    // clang-format on
    printf("\n");
    return opbytes;
}
