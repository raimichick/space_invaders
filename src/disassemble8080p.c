#include <stdio.h>

int disassemble8080p(unsigned char *codebuffer, int pc)
{
    /*
    tobedone: Base code copied from emulator 101 website: CHANGE THIS AROUND TO MAKE IT OUR OWN!
    tobedone: Add opcode-to-instruction cases.
    */
    unsigned char *code = &codebuffer[pc];
    int opbytes = 1;
    printf("%04x ", pc);
    switch (*code)
    {
        // clang-format off
        case 0x00: printf("NOP");  break;
        default: printf("NOT IMPLEMENTED NOT IMPLEMENTED NOT IMPLEMENTED NOT IMPLEMENTED");
        // clang-format on
    }
    printf("\n");
    return opbytes;
}
