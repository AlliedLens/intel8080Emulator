#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/*
Intel 8080 Register Layout
one register is 8 bits
------------------------------------------------
| S   Z   -  AC   -  P   -   C | Flag Register
------------------------------------------------
|   A (Accumulator)    |
-----------------------
|     B   |     C      |
-----------------------
|     D   |     E      |
-----------------------
|     H   |     L      |
-----------------------
|  SP (Stack Pointer)  |
-----------------------
|  PC (Program Counter)|
-----------------------


*/

typedef struct ConditionCodes{
    // : specifies the number of bits
    uint8_t sign: 1;
    uint8_t zero: 1;
    uint8_t auxCarr: 1;
    uint8_t parity: 1;
    uint8_t carry: 1;
    uint8_t padding: 3;
}ConditionCodes;

typedef struct State8080{
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    
    uint16_t sp;
    uint16_t pc;

    ConditionCodes cc;
    
    uint8_t* memory;

    uint8_t en;

}State8080;


#include "opcodes/controlGroup.h"
#include "opcodes/arithmeticGroup.h"
#include "opcodes/logicalGroup.h"
#include "opcodes/miscGroup.h"
#include "opcodes/stackGroup.h"
#include "opcodes/moveGroup.h"

int emulateCycle(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    uint16_t HL = state->h << 8;
    int opbytes = 1;

    switch(*opcode){
        case 0x00: NOP(state); break; 
        case 0x01: LXI(state, &state->b, &state->c); opbytes=3; break; 
        case 0x02: STAX(state, &state->b, &state->c); break; 
        case 0x03: INX(state, &state->b, &state->c); break; 
        case 0x04: INR(state, &state->b); break;  
        case 0x05: DCR(state, &state->b); break; 
        case 0x06: MVI(state, &state->b); opbytes=2; break;
        case 0x07: RLC(state, &state->a); break;
        case 0x08: NOP(state); break;
        case 0x09: DAD(state, &state->b, &state->c); break;
        case 0x0A: LDAX(state, &state->b, &state->c); break;
        case 0x0B: DCX(state, &state->b, &state->c); break;
        case 0x0C: INR(state, &state->c); break;
        case 0x0D: DCR(state, &state->c); break;
        case 0x0E: MVI(state, &state->c); opbytes=2; break;
        case 0x0F: RRC(state, &state->a); break;

        case 0x10: NOP(state); break; 
        case 0x11: LXI(state, &state->d, &state->e); opbytes=3; break; 
        case 0x12: STAX(state, &state->d, &state->e); break; 
        case 0x13: INX(state, &state->d, &state->e); break; 
        case 0x14: INR(state, &state->d); break;  
        case 0x15: DCR(state, &state->d); break; 
        case 0x16: MVI(state, &state->d); opbytes=2; break;
        case 0x17: RAL(state, &state->a); break;
        case 0x18: NOP(state); break;
        case 0x19: DAD(state, &state->d, &state->e); break;
        case 0x1A: LDAX(state, &state->d, &state->e); break;
        case 0x1B: DCX(state, &state->d, &state->e); break;
        case 0x1C: INR(state, &state->e); break;
        case 0x1D: DCR(state, &state->e); break;
        case 0x1E: MVI(state, &state->e); opbytes=2; break;
        case 0x1F: RAR(state, &state->a); break;

        case 0x20: NOP(state); break; 
        case 0x21: LXI(state, &state->h, &state->l); opbytes=3; break; 
        case 0x22: STAX(state, &state->h, &state->l); opbytes=3; break; 
        case 0x23: INX(state, &state->h, &state->l); break; 
        case 0x24: INR(state, &state->h); break;  
        case 0x25: DCR(state, &state->h); break; 
        case 0x26: MVI(state, &state->h); opbytes=2; break;
        case 0x27: RAL(state, &state->a); break;
        case 0x28: NOP(state); break;
        case 0x29: DAD(state, &state->h, &state->l); break;
        case 0x2A: LDAX(state, &state->h, &state->l); break;
        case 0x2B: DCX(state, &state->h, &state->l); break;
        case 0x2C: INR(state, &state->l); break;
        case 0x2D: DCR(state, &state->l); break;
        case 0x2E: MVI(state, &state->l); opbytes=2; break;
        case 0x2F: RAR(state, &state->a); break;

        case 0x30: NOP(state); break;
        case 0x31: LXI_SP(state); opbytes=3; break;
        case 0x32: STA(state); opbytes=3; break;
        case 0x33: INX_SP(state); break;
        case 0x34: INR(state, &state->memory[(state->h<<8) | state->l] ) ; break;
        case 0x35: DCR(state, &state->memory[(state->h<<8) | state->l] ); break;
        case 0x36: MVI(state, &state->memory[(state->h<<8) | state->l]); opbytes=2; break;
        case 0x37: STC(state); break;
        case 0x38: NOP(state); break;
        case 0x39: DAD_SP(state); break;
        case 0x3A: LDA(state); break;
        case 0x3B: DCX_SP(state); break;
        case 0x3C: INR(state, &state->a); break;
        case 0x3D: DCR(state, &state->a); break;
        case 0x3E: MVI(state, &state->a); break;
        case 0x3F: CMC(state); break;

        case 0x40: MOV(state, &state->b, &state->b); break;
        case 0x41: MOV(state, &state->b, &state->c); break;
        case 0x42: MOV(state, &state->b, &state->d); break;
        case 0x43: MOV(state, &state->b, &state->e); break;
        case 0x44: MOV(state, &state->b, &state->h); break;
        case 0x45: MOV(state, &state->b, &state->l); break;
        case 0x46: MOV(state, &state->b, &state->memory[(state->h<<8) | state->l]); break;
        case 0x47: MOV(state, &state->b, &state->a); break;
        case 0x48: MOV(state, &state->c, &state->b); break;
        case 0x49: MOV(state, &state->c, &state->c); break;
        case 0x4A: MOV(state, &state->c, &state->d); break;
        case 0x4B: MOV(state, &state->c, &state->e); break;
        case 0x4C: MOV(state, &state->c, &state->h); break;
        case 0x4D: MOV(state, &state->c, &state->l); break;
        case 0x4E: MOV(state, &state->c, &state->memory[(state->h<<8) | state->l]); break;
        case 0x4F: MOV(state, &state->c, &state->a); break;

        case 0x50: MOV(state, &state->d, &state->b); break;
        case 0x51: MOV(state, &state->d, &state->c); break;
        case 0x52: MOV(state, &state->d, &state->d); break;
        case 0x53: MOV(state, &state->d, &state->e); break;
        case 0x54: MOV(state, &state->d, &state->h); break;
        case 0x55: MOV(state, &state->d, &state->l); break;
        case 0x56: MOV(state, &state->d, &state->memory[(state->h<<8) | state->l]); break;
        case 0x57: MOV(state, &state->d, &state->a); break;
        case 0x58: MOV(state, &state->e, &state->b); break;
        case 0x59: MOV(state, &state->e, &state->c); break;
        case 0x5A: MOV(state, &state->e, &state->d); break;
        case 0x5B: MOV(state, &state->e, &state->e); break;
        case 0x5C: MOV(state, &state->e, &state->h); break;
        case 0x5D: MOV(state, &state->e, &state->l); break;
        case 0x5E: MOV(state, &state->e, &state->memory[(state->h<<8) | state->l]); break;
        case 0x5F: MOV(state, &state->e, &state->a); break;

        case 0x60: MOV(state, &state->h, &state->b); break;
        case 0x61: MOV(state, &state->h, &state->c); break;
        case 0x62: MOV(state, &state->h, &state->d); break;
        case 0x63: MOV(state, &state->h, &state->e); break;
        case 0x64: MOV(state, &state->h, &state->h); break;
        case 0x65: MOV(state, &state->h, &state->l); break;
        case 0x66: MOV(state, &state->h, &state->memory[(state->h<<8) | state->l]); break;
        case 0x67: MOV(state, &state->h, &state->a); break;
        case 0x68: MOV(state, &state->l, &state->b); break;
        case 0x69: MOV(state, &state->l, &state->c); break;
        case 0x6A: MOV(state, &state->l, &state->d); break;
        case 0x6B: MOV(state, &state->l, &state->e); break;
        case 0x6C: MOV(state, &state->l, &state->h); break;
        case 0x6D: MOV(state, &state->l, &state->l); break;
        case 0x6E: MOV(state, &state->l, &state->memory[(state->h<<8) | state->l]); break;
        case 0x6F: MOV(state, &state->l, &state->a); break;

        case 0x70: MOV(state, &state->memory[(state->h<<8) | state->l], &state->b); break;
        case 0x71: MOV(state, &state->memory[(state->h<<8) | state->l], &state->c); break;
        case 0x72: MOV(state, &state->memory[(state->h<<8) | state->l], &state->d); break;
        case 0x73: MOV(state, &state->memory[(state->h<<8) | state->l], &state->e); break;
        case 0x74: MOV(state, &state->memory[(state->h<<8) | state->l], &state->h); break;
        case 0x75: MOV(state, &state->memory[(state->h<<8) | state->l], &state->l); break;
        case 0x76: HLT(); break;
        case 0x77: MOV(state, &state->memory[(state->h<<8) | state->l], &state->a); break;
        case 0x78: MOV(state, &state->a, &state->b); break;
        case 0x79: MOV(state, &state->a, &state->c); break;
        case 0x7A: MOV(state, &state->a, &state->d); break;
        case 0x7B: MOV(state, &state->a, &state->e); break;
        case 0x7C: MOV(state, &state->a, &state->h); break;
        case 0x7D: MOV(state, &state->a, &state->l); break;
        case 0x7E: MOV(state, &state->a, &state->memory[(state->h<<8) | state->l]); break;
        case 0x7F: MOV(state, &state->a, &state->a); break;

        case 0x80: ADD(state, &state->b); break;
        case 0x81: ADD(state, &state->c); break;
        case 0x82: ADD(state, &state->d); break;
        case 0x83: ADD(state, &state->e); break;
        case 0x84: ADD(state, &state->h); break;
        case 0x85: ADD(state, &state->l); break;
        case 0x86: ADDM(state); break;
        case 0x87: ADD(state, &state->a); break;
        case 0x88: ADC(state, &state->b); break;
        case 0x89: ADC(state, &state->c); break;
        case 0x8A: ADC(state, &state->d); break;
        case 0x8B: ADC(state, &state->e); break;
        case 0x8C: ADC(state, &state->h); break;
        case 0x8D: ADC(state, &state->l); break;
        case 0x8E: ADCM(state); break;
        case 0x8F: ADC(state, &state->a);

        case 0x90: SUB(state, &state->b); break;
        case 0x91: SUB(state, &state->c); break;
        case 0x92: SUB(state, &state->d); break;
        case 0x93: SUB(state, &state->e); break;
        case 0x94: SUB(state, &state->h); break;
        case 0x95: SUB(state, &state->l); break;
        case 0x96: SUBM(state); break;
        case 0x97: SUB(state, &state->a); break;
        case 0x98: SBB(state, &state->b); break;
        case 0x99: SBB(state, &state->c); break;
        case 0x9A: SBB(state, &state->d); break;
        case 0x9B: SBB(state, &state->e); break;
        case 0x9C: SBB(state, &state->h); break;
        case 0x9D: SBB(state, &state->l); break;
        case 0x9E: SBBM(state); break;
        case 0x9F: SBB(state, &state->a); break;

        case 0xA0: ANA(state, &state->b); break;
        case 0xA1: ANA(state, &state->c); break;
        case 0xA2: ANA(state, &state->d); break;
        case 0xA3: ANA(state, &state->e); break;
        case 0xA4: ANA(state, &state->h); break;
        case 0xA5: ANA(state, &state->l); break;
        case 0xA6: ANA(state, &state->memory[(state->h<<8) | state->l]); break;
        case 0xA7: ANA(state, &state->a); break;
        case 0xA8: XRA(state, &state->b); break;
        case 0xA9: XRA(state, &state->c); break;
        case 0xAA: XRA(state, &state->d); break;
        case 0xAB: XRA(state, &state->e); break;
        case 0xAC: XRA(state, &state->h); break;
        case 0xAD: XRA(state, &state->l); break;
        case 0xAE: XRA(state, &state->memory[(state->h<<8) | state->l]); break;
        case 0xAF: XRA(state, &state->a); break;

        case 0xB0: ORA(state, &state->b); break;
        case 0xB1: ORA(state, &state->c); break;
        case 0xB2: ORA(state, &state->d); break;
        case 0xB3: ORA(state, &state->e); break;
        case 0xB4: ORA(state, &state->h); break;
        case 0xB5: ORA(state, &state->l); break;
        case 0xB6: ORA(state, &state->memory[(state->h<<8) | state->l]); break;
        case 0xB7: ORA(state, &state->a); break;
        case 0xB8: CMP(state, &state->b); break;
        case 0xB9: CMP(state, &state->c); break;
        case 0xBA: CMP(state, &state->d); break;
        case 0xBB: CMP(state, &state->e); break;
        case 0xBC: CMP(state, &state->h); break;
        case 0xBD: CMP(state, &state->l); break;
        case 0xBE: CMP(state, &state->memory[(state->h<<8) | state->l]); break;
        case 0xBF: CMP(state, &state->a); break;

        case 0xC0: RNZ(state); break;
        case 0xC1: POP(state, &state->b, &state->c); break;
        case 0xC2: JNZ(state); opbytes=3; break;
        case 0xC3: JMP(state); opbytes=3; break;
        case 0xC4: CNZ(state); opbytes=3; break;
        case 0xC5: PUSH(state, &state->b, &state->c); break;
        case 0xC6: ADI(state); opbytes=2; break;
        case 0xC7: RST(state, 0); break;
        case 0xC8: RZ(state); break;
        case 0xC9: RET(state); break;
        case 0xCA: JZ(state); opbytes=3; break;
        case 0xCB: JMP(state); opbytes=3; break;
        case 0xCC: CZ(state); opbytes=3; break;
        case 0xCD: CALL(state); opbytes=3; break;
        case 0xCE: ACI(state); opbytes=2; break;
        case 0xCF: RST(state, 1); break;

        case 0xD0: RNC(state); break;
        case 0xD1: POP(state, &state->d, &state->e); break;
        case 0xD2: JNC(state); opbytes=3; break;
        case 0xD3: OUT(state); opbytes=2; break;
        case 0xD4: CNC(state); opbytes=3; break;
        case 0xD5: PUSH(state, &state->d, &state->e); break;
        case 0xD6: SUI(state); opbytes=2; break;
        case 0xD7: RST(state, 2); break;
        case 0xD8: RC(state); break;
        case 0xD9: RET(state); break;
        case 0xDA: JC(state); opbytes=3; break;
        case 0xDB: IN(state); opbytes=2; break;
        case 0xDC: CC(state); opbytes=3; break;
        case 0xDD: CALL(state); opbytes=3; break;
        case 0xDE: SBI(state); opbytes=2; break;
        case 0xDF: RST(state, 3); break;

        case 0xE0: RPO(state); break;
        case 0xE1: POP(state, &state->h, &state->l); break;
        case 0xE2: JPO(state); opbytes=3; break;
        case 0xE3: XTHL(state); break;
        case 0xE4: CPO(state); opbytes=3; break;
        case 0xE5: PUSH(state, &state->h, &state->l); break;
        case 0xE6: ANI(state); opbytes=2; break;
        case 0xE7: RST(state, 4); break;
        case 0xE8: RPE(state); break;
        case 0xE9: PCHL(state); break;
        case 0xEA: JPE(state); opbytes=3; break;
        case 0xEB: XCHG(state); break;
        case 0xEC: CPE(state); opbytes=3; break;
        case 0xED: CALL(state); opbytes=3; break;
        case 0xEE: XRI(state); opbytes=2; break;
        case 0xEF: RST(state, 5); break;

        case 0xF0: RP(state); break;
        case 0xF1: POP_PSW(state); break;
        case 0xF2: JP(state); opbytes=3; break;
        case 0xF3: DI(state); break;
        case 0xF4: CP(state); opbytes=3; break;
        case 0xF5: PUSH_PSW(state); break;
        case 0xF6: ANI(state); opbytes=2; break;
        case 0xF7: RST(state, 6); break;
        case 0xF8: RM(state); break;
        case 0xF9: SPHL(state); break;
        case 0xFA: JM(state); opbytes=3; break;
        case 0xFB: EI(state); break;
        case 0xFC: CM(state); opbytes=3; break;
        case 0xFD: CALL(state); opbytes=3; break;
        case 0xFE: CPI(state); opbytes=2; break;
        case 0xFF: RST(state, 7); break;

    }

    return opbytes;
}

#endif