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
        case 0x01: printf("LXI B,D16, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x02: printf("STAX B"); break;
        case 0x03: printf("INX B"); break;
        case 0x04: printf("INR B"); break;
        case 0x05: printf("DCR B"); break;
        case 0x06: printf("MVI B, D8, $%02x", code[1]); opbytes = 2; break;
        case 0x07: printf("RLC"); break;
        case 0x08: printf("-"); break;
        case 0x09: printf("DAD B"); break;
        case 0x0a: printf("LDAX B"); break;
        case 0x0b: printf("DCX B"); break;
        case 0x0c: printf("INR C"); break;
        case 0x0d: printf("DCR C"); break;
        case 0x0e: printf("MVI C,D8, $%02x", code[1]); opbytes = 2; break;
        case 0x0f: printf("RRC"); break;
        case 0x10: printf("-"); break;
        case 0x11: printf("LXI D,D16, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x12: printf("STAX D"); break;
        case 0x13: printf("INX D"); break;
        case 0x14: printf("INR D"); break;
        case 0x15: printf("DCR D"); break;
        case 0x16: printf("MVI D, D8, $%02x", code[1]); opbytes = 2; break;
        case 0x17: printf("RAL"); break;
        case 0x18: printf("-"); break;
        case 0x19: printf("DAD D"); break;
        case 0x1a: printf("LDAX D"); break;
        case 0x1b: printf("DCX D"); break;
        case 0x1c: printf("INR E"); break;
        case 0x1d: printf("DCR E"); break;
        case 0x1e: printf("MVI E,D8, $%02x", code[1]); opbytes = 2; break;
        case 0x1f: printf("RAR"); break;
        case 0x20: printf("RIM"); break;
        case 0x21: printf("LXI H,D16, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x22: printf("SHLD adr, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x23: printf("INX H"); break;
        case 0x24: printf("INR H"); break;
        case 0x25: printf("DCR H"); break;
        case 0x26: printf("MVI H,D8, $%02x", code[1]); opbytes = 2; break;
        case 0x27: printf("DAA"); break;
        case 0x28: printf("-"); break;
        case 0x29: printf("DAD H"); break;
        case 0x2a: printf("LHLD adr, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x2b: printf("DCX H"); break;
        case 0x2c: printf("INR L"); break;
        case 0x2d: printf("DCR L"); break;
        case 0x2e: printf("MVI L, D8, $%02x", code[1]); opbytes = 2; break;
        case 0x2f: printf("CMA"); break;
        case 0x30: printf("SIM"); break;
        case 0x31: printf("LXI SP, D16, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x32: printf("STA adr, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x33: printf("INX SP"); break;
        case 0x34: printf("INR M"); break;
        case 0x35: printf("DCR M"); break;
        case 0x36: printf("MVI M,D8, $%02x", code[1]); opbytes = 2; break;
        case 0x37: printf("STC"); break;
        case 0x38: printf("-"); break;
        case 0x39: printf("DAD SP"); break;
        case 0x3a: printf("LDA adr, $%02x%02x", code[2], code[1]); opbytes = 3; break;
        case 0x3b: printf("DCX SP"); break;
        case 0x3c: printf("INR A"); break;
        case 0x3d: printf("DCR A"); break;
        case 0x3e: printf("MVI A,D8, $%02x", code[1]); opbytes = 2; break;
        case 0x3f: printf("CMC"); break;
        case 0x40: printf("MOV B,B"); break;
        case 0x81: printf("ADD C"); break;
        case 0x82: printf("ADD D"); break;
        case 0x83: printf("ADD E"); break;
        case 0x84: printf("ADD H"); break;
        case 0x85: printf("ADD L"); break;
        case 0x86: printf("ADD M"); break;
        case 0x87: printf("ADD A"); break;
        case 0x88: printf("ADC B"); break;
        case 0x89: printf("ADC C"); break;
        case 0x8a: printf("ADC D"); break;
        case 0x8b: printf("ADC E"); break;
        case 0x8c: printf("ADC H"); break;
        case 0x8d: printf("ADC L"); break;
        case 0x8e: printf("ADC M"); break;
        case 0x8f: printf("ADC A"); break;
        case 0x90: printf("SUB B"); break;
        case 0x91: printf("SUB C"); break;
        case 0x92: printf("SUB D"); break;
        case 0x93: printf("SUB E"); break;
        case 0x94: printf("SUB H"); break;
        case 0x95: printf("SUB L"); break;
        case 0x96: printf("SUB M"); break;
        case 0x97: printf("SUB A"); break;
        case 0x98: printf("SBB B"); break;
        case 0x99: printf("SBB C"); break;
        case 0x9a: printf("SBB D"); break;
        case 0x9b: printf("SBB E"); break;
        case 0x9c: printf("SBB H"); break;
        case 0x9d: printf("SBB L"); break;
        case 0x9e: printf("SBB M"); break;
        case 0x9f: printf("SBB A"); break;
        case 0xa0: printf("ANA B"); break;
        case 0xa1: printf("ANA C"); break;
        case 0xa2: printf("ANA D"); break;
        case 0xa3: printf("ANA E"); break;
        case 0xa4: printf("ANA H"); break;
        case 0xa5: printf("ANA L"); break;
        case 0xa6: printf("ANA M"); break;
        case 0xa7: printf("ANA A"); break;
        case 0xa8: printf("XRA B"); break;
        case 0xa9: printf("XRA C"); break;
        case 0xaa: printf("XRA D"); break;
        case 0xab: printf("XRA E"); break;
        case 0xac: printf("XRA H"); break;
        case 0xad: printf("XRA L"); break;
        case 0xae: printf("XRA M"); break;
        case 0xaf: printf("XRA A"); break;
        case 0xb0: printf("ORA B"); break;
        case 0xb1: printf("ORA C"); break;
        case 0xb2: printf("ORA D"); break;
        case 0xb3: printf("ORA E"); break;
        case 0xb4: printf("ORA H"); break;
        case 0xb5: printf("ORA L"); break;
        case 0xb6: printf("ORA M"); break;
        case 0xb7: printf("ORA A"); break;
        case 0xb8: printf("CMP B"); break;
        case 0xb9: printf("CMP C"); break;
        case 0xba: printf("CMP D"); break;
        case 0xbb: printf("CMP E"); break;
        case 0xbc: printf("CMP H"); break;
        case 0xbd: printf("CMP L"); break;
        case 0xbe: printf("CMP M"); break;
        case 0xbf: printf("CMP A"); break;
        case 0xc0: printf("RNZ"); break;
        default: printf("NOT IMPLEMENTED NOT IMPLEMENTED NOT IMPLEMENTED NOT IMPLEMENTED");
    }
    // clang-format on
    printf("\n");
    return opbytes;
}
