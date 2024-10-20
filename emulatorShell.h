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
        case 0x00: NOP(state); break; // NOP
        case 0x01: XXX(state); break; // LXI B, D16
        case 0x02: XXX(state); break; 
        case 0x03: INX(state, &state->b, &state->c); break; // INX B
        case 0x04: INR(state, &state->b); break;  // INR B
        case 0x05: DCR(state, &state->b); break; // DCR B
        case 0x06: XXX(state); break;
        case 0x07: RLC(state, &state->a); break;
        case 0x08: NOP(state); break;
        case 0x09: DAD(state, &state->b, &state->c); break;
        case 0x0A: XXX(state); break;
        case 0x0B: DCX(state, &state->b, &state->c); break;
        case 0x0C: INR(state, &state->c); break;
        case 0x0D: DCR(state, &state->c); break;
        case 0x0E: XXX(state); break;
        case 0x0F: RRC(state, &state->a); break;

        case 0x10: NOP(state); break;
        case 0x11: XXX(state); break;
        case 0x12: XXX(state); break;
        case 0x13: INX(state, &state->d, &state->e); break;
        case 0x14: INR(state, &state->d);  break;
        case 0x15: DCR(state, &state->d); break;
        case 0x16: XXX(state); break;
        case 0x17: RAL(state, &state->a); break;
        case 0x18: NOP(state); break;
        case 0x19: DAD(state, &state->d, &state->e); break;
        case 0x1A: XXX(state); break;
        case 0x1B: DCX(state, &state->d, &state->e); break;
        case 0x1C: INR(state, &state->e); break;
        case 0x1D: DCR(state, &state->e); break;
        case 0x1E: XXX(state); break;
        case 0x1F: RAR(state, &state->a); break;

        case 0x20: NOP(state); break;
        case 0x21: XXX(state); break;
        case 0x22: XXX(state); break;
        case 0x23: XXX(state); break;
        case 0x24: INR(state, &state->h); break;
        case 0x25: XXX(state); break;
        case 0x26: XXX(state); break;
        case 0x27: XXX(state); break;
        case 0x28: NOP(state); break;
        case 0x29: XXX(state); break;
        case 0x2A: XXX(state); break;
        case 0x2B: XXX(state); break;
        case 0x2C: XXX(state); break;
        case 0x2D: XXX(state); break;
        case 0x2E: XXX(state); break;
        case 0x2F: XXX(state); break;

        case 0x30: NOP(state); break;
        case 0x31: XXX(state); break;
        case 0x32: XXX(state); break;
        case 0x33: XXX(state); break;
        case 0x34: XXX(state); break;
        case 0x35: XXX(state); break;
        case 0x36: XXX(state); break;
        case 0x37: XXX(state); break;
        case 0x38: NOP(state); break;
        case 0x39: XXX(state); break;
        case 0x3A: XXX(state); break;
        case 0x3B: XXX(state); break;
        case 0x3C: XXX(state); break;
        case 0x3D: XXX(state); break;
        case 0x3E: XXX(state); break;
        case 0x3F: XXX(state); break;

        case 0x40: XXX(state); break;
        case 0x41: XXX(state); break;
        case 0x42: XXX(state); break;
        case 0x43: XXX(state); break;
        case 0x44: XXX(state); break;
        case 0x45: XXX(state); break;
        case 0x46: XXX(state); break;
        case 0x47: XXX(state); break;
        case 0x48: XXX(state); break;
        case 0x49: XXX(state); break;
        case 0x4A: XXX(state); break;
        case 0x4B: XXX(state); break;
        case 0x4C: XXX(state); break;
        case 0x4D: XXX(state); break;
        case 0x4E: XXX(state); break;
        case 0x4F: XXX(state); break;

        case 0x50: XXX(state); break;
        case 0x51: XXX(state); break;
        case 0x52: XXX(state); break;
        case 0x53: XXX(state); break;
        case 0x54: XXX(state); break;
        case 0x55: XXX(state); break;
        case 0x56: XXX(state); break;
        case 0x57: XXX(state); break;
        case 0x58: XXX(state); break;
        case 0x59: XXX(state); break;
        case 0x5A: XXX(state); break;
        case 0x5B: XXX(state); break;
        case 0x5C: XXX(state); break;
        case 0x5D: XXX(state); break;
        case 0x5E: XXX(state); break;
        case 0x5F: XXX(state); break;

        case 0x60: XXX(state); break;
        case 0x61: XXX(state); break;
        case 0x62: XXX(state); break;
        case 0x63: XXX(state); break;
        case 0x64: XXX(state); break;
        case 0x65: XXX(state); break;
        case 0x66: XXX(state); break;
        case 0x67: XXX(state); break;
        case 0x68: XXX(state); break;
        case 0x69: XXX(state); break;
        case 0x6A: XXX(state); break;
        case 0x6B: XXX(state); break;
        case 0x6C: XXX(state); break;
        case 0x6D: XXX(state); break;
        case 0x6E: XXX(state); break;
        case 0x6F: XXX(state); break;

        case 0x70: XXX(state); break;
        case 0x71: XXX(state); break;
        case 0x72: XXX(state); break;
        case 0x73: XXX(state); break;
        case 0x74: XXX(state); break;
        case 0x75: XXX(state); break;
        case 0x76: XXX(state); break;
        case 0x77: XXX(state); break;
        case 0x78: XXX(state); break;
        case 0x79: XXX(state); break;
        case 0x7A: XXX(state); break;
        case 0x7B: XXX(state); break;
        case 0x7C: XXX(state); break;
        case 0x7D: XXX(state); break;
        case 0x7E: XXX(state); break;
        case 0x7F: XXX(state); break;

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

        case 0xA0: XXX(state); break;
        case 0xA1: XXX(state); break;
        case 0xA2: XXX(state); break;
        case 0xA3: XXX(state); break;
        case 0xA4: XXX(state); break;
        case 0xA5: XXX(state); break;
        case 0xA6: XXX(state); break;
        case 0xA7: XXX(state); break;
        case 0xA8: XXX(state); break;
        case 0xA9: XXX(state); break;
        case 0xAA: XXX(state); break;
        case 0xAB: XXX(state); break;
        case 0xAC: XXX(state); break;
        case 0xAD: XXX(state); break;
        case 0xAE: XXX(state); break;
        case 0xAF: XXX(state); break;

        case 0xB0: XXX(state); break;
        case 0xB1: XXX(state); break;
        case 0xB2: XXX(state); break;
        case 0xB3: XXX(state); break;
        case 0xB4: XXX(state); break;
        case 0xB5: XXX(state); break;
        case 0xB6: XXX(state); break;
        case 0xB7: XXX(state); break;
        case 0xB8: XXX(state); break;
        case 0xB9: XXX(state); break;
        case 0xBA: XXX(state); break;
        case 0xBB: XXX(state); break;
        case 0xBC: XXX(state); break;
        case 0xBD: XXX(state); break;
        case 0xBE: XXX(state); break;
        case 0xBF: XXX(state); break;

        case 0xC0: XXX(state); break;
        case 0xC1: XXX(state); break;
        case 0xC2: XXX(state); break;
        case 0xC3: XXX(state); break;
        case 0xC4: XXX(state); break;
        case 0xC5: XXX(state); break;
        case 0xC6: XXX(state); break;
        case 0xC7: XXX(state); break;
        case 0xC8: XXX(state); break;
        case 0xC9: XXX(state); break;
        case 0xCA: XXX(state); break;
        case 0xCB: XXX(state); break;
        case 0xCC: XXX(state); break;
        case 0xCD: XXX(state); break;
        case 0xCE: XXX(state); break;
        case 0xCF: XXX(state); break;

        case 0xD0: XXX(state); break;
        case 0xD1: XXX(state); break;
        case 0xD2: XXX(state); break;
        case 0xD3: XXX(state); break;
        case 0xD4: XXX(state); break;
        case 0xD5: XXX(state); break;
        case 0xD6: XXX(state); break;
        case 0xD7: XXX(state); break;
        case 0xD8: XXX(state); break;
        case 0xD9: XXX(state); break;
        case 0xDA: XXX(state); break;
        case 0xDB: XXX(state); break;
        case 0xDC: XXX(state); break;
        case 0xDD: XXX(state); break;
        case 0xDE: XXX(state); break;
        case 0xDF: XXX(state); break;

        case 0xE0: XXX(state); break;
        case 0xE1: XXX(state); break;
        case 0xE2: XXX(state); break;
        case 0xE3: XXX(state); break;
        case 0xE4: XXX(state); break;
        case 0xE5: XXX(state); break;
        case 0xE6: XXX(state); break;
        case 0xE7: XXX(state); break;
        case 0xE8: XXX(state); break;
        case 0xE9: XXX(state); break;
        case 0xEA: XXX(state); break;
        case 0xEB: XXX(state); break;
        case 0xEC: XXX(state); break;
        case 0xED: XXX(state); break;
        case 0xEE: XXX(state); break;
        case 0xEF: XXX(state); break;

        case 0xF0: XXX(state); break;
        case 0xF1: XXX(state); break;
        case 0xF2: XXX(state); break;
        case 0xF3: XXX(state); break;
        case 0xF4: XXX(state); break;
        case 0xF5: XXX(state); break;
        case 0xF6: XXX(state); break;
        case 0xF7: XXX(state); break;
        case 0xF8: XXX(state); break;
        case 0xF9: XXX(state); break;
        case 0xFA: XXX(state); break;
        case 0xFB: XXX(state); break;
        case 0xFC: XXX(state); break;
        case 0xFD: XXX(state); break;
        case 0xFE: XXX(state); break;
        case 0xFF: XXX(state); break;

    }

    return opbytes;
}

#endif