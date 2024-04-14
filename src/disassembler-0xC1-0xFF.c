//
// Created by J Web on 4/14/2024.
//
#include <stdio.h>

int disassemble8080p(unsigned char *codebuffer, int pc)
{
    unsigned char *code = &codebuffer[pc];
    int opbytes = 1;
    printf("%04x ", pc);
    // clang-format off
    switch (*code)
    {
        case 0xc1: printf("POP B"); break;
        case 0xc2: printf("JNZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xc3: printf("JMP, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xc4: printf("CNZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xc5: printf("PUSH B"); break;
        case 0xc6: printf("ADI D8, $%02x", code[1]); opbytes = 2; break;
        case 0xc7: printf("RST 0"); break;
        case 0xc8: printf("RZ"); break;
        case 0xc9: printf("RET"); break;
        case 0xca: printf("JZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xcb: printf("-"); break;
        case 0xcc: printf("CZ, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xcd: printf("CALL, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xce: printf("ACI D8, $%02x", code[1]); opbytes = 2; break;
        case 0xcf: printf("RST 1"); break;
        case 0xd0: printf("RNC"); break;
        case 0xd1: printf("POP D"); break;
        case 0xd2: printf("JNC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xd3: printf("OUT,D8, $%02x", code[1]); opbytes = 2; break;
        case 0xd4: printf("CNC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xd5: printf("PUSH D"); break;
        case 0xd6: printf("SUI D8, $%02x", code[1]); opbytes = 2; break;
        case 0xd7: printf("RST 2"); break;
        case 0xd8: printf("RC 1"); break;
        case 0xd9: printf("-"); break;
        case 0xda: printf("JC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xdb: printf("IN D8, $%02x", code[1]); opbytes = 2; break;
        case 0xdc: printf("CC, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xdd: printf("-"); break;
        case 0xde: printf("SBI D8, $%02x", code[1]); opbytes = 2; break;
        case 0xdf: printf("RST 3"); break;
        case 0xe0: printf("RPO"); break;
        case 0xe1: printf("POP H"); break;
        case 0xe2: printf("JPO, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xe3: printf("XTHL"); break;
        case 0xe4: printf("CPO, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xe5: printf("PUSH H"); break;
        case 0xe6: printf("ANI D8, $%02x", code[1]); break;
        case 0xe7: printf("RST 4"); break;
        case 0xe8: printf("RPE"); break;
        case 0xe9: printf("PCHL"); break;
        case 0xea: printf("JPE, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xeb: printf("XCHG"); break;
        case 0xec: printf("CPE, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xed: printf("-"); break;
        case 0xee: printf("XRI D8, $%02x", code[1]); opbytes = 2; break;
        case 0xef: printf("RST 5"); break;
        case 0xf0: printf("RP"); break;
        case 0xf1: printf("POP PSW"); break;
        case 0xf2: printf("JP, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xf3: printf("DI"); break;
        case 0xf4: printf("CP, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xf5: printf("PUSH PSW"); break;
        case 0xf6: printf("ORI D8, $%02x", code[1]); opbytes = 2; break;
        case 0xf7: printf("RST 6"); break;
        case 0xf8: printf("RM"); break;
        case 0xf9: printf("SPHL"); break;
        case 0xfa: printf("JM, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xfb: printf("EI"); break;
        case 0xfc: printf("CM, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0xfd: printf("-"); break;
        case 0xfe: printf("CPI, $%02x", code[1]); opbytes = 2; break;
        case 0xff: printf("RST 7"); break;
        default: printf("NOT IMPLEMENTED NOT IMPLEMENTED NOT IMPLEMENTED NOT IMPLEMENTED");
    }
    // clang-format on
    printf("\n");
    return opbytes;
}