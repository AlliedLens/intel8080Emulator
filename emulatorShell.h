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


// INR  Reg = Reg + 1
// DCR  Reg = Reg - 1
// INX  Reg<<8|Adjacent Reg = Reg<<8|Adjacent Reg + 1  
// RLC Reg = Reg << 1 bit 0 = prev bit 7; CY = prev bit 7
// DAD HL = HL + Reg<<8|Adjacent Reg

void emulateCycle(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    uint16_t HL = state->h << 8;

    switch(*opcode){
        case 0x00: noOperation(state); break; // NOP
        case 0x01: unimplementedInstruction(state); break; // LXI B, D16
        case 0x02: unimplementedInstruction(state); break; 
        case 0x03: INX(state, &state->b, &state->c); break; // INX B
        case 0x04: INR(state, &state->b); break;  // INR B
        case 0x05: DCR(state, &state->b); break; // DCR B
        case 0x06: unimplementedInstruction(state); break;
        case 0x07: RLC(state, &state->a); break;
        case 0x08: noOperation(state); break;
        case 0x09: DAD(state, &state->b, &state->c); break;
        case 0x0A: unimplementedInstruction(state); break;
        case 0x0B: DCX(state); break;
        case 0x0C: unimplementedInstruction(state); break;
        case 0x0D: unimplementedInstruction(state); break;
        case 0x0E: unimplementedInstruction(state); break;
        case 0x0F: unimplementedInstruction(state); break;

        case 0x10: noOperation(state); break;
        case 0x11: unimplementedInstruction(state); break;
        case 0x12: unimplementedInstruction(state); break;
        case 0x13: unimplementedInstruction(state); break;
        case 0x14: INR(state, &state->d);  break;
        case 0x15: unimplementedInstruction(state); break;
        case 0x16: unimplementedInstruction(state); break;
        case 0x17: unimplementedInstruction(state); break;
        case 0x18: noOperation(state); break;
        case 0x19: unimplementedInstruction(state); break;
        case 0x1A: unimplementedInstruction(state); break;
        case 0x1B: unimplementedInstruction(state); break;
        case 0x1C: unimplementedInstruction(state); break;
        case 0x1D: unimplementedInstruction(state); break;
        case 0x1E: unimplementedInstruction(state); break;
        case 0x1F: unimplementedInstruction(state); break;

        case 0x20: noOperation(state); break;
        case 0x21: unimplementedInstruction(state); break;
        case 0x22: unimplementedInstruction(state); break;
        case 0x23: unimplementedInstruction(state); break;
        case 0x24: INR(state, &state->h); break;
        case 0x25: unimplementedInstruction(state); break;
        case 0x26: unimplementedInstruction(state); break;
        case 0x27: unimplementedInstruction(state); break;
        case 0x28: noOperation(state); break;
        case 0x29: unimplementedInstruction(state); break;
        case 0x2A: unimplementedInstruction(state); break;
        case 0x2B: unimplementedInstruction(state); break;
        case 0x2C: unimplementedInstruction(state); break;
        case 0x2D: unimplementedInstruction(state); break;
        case 0x2E: unimplementedInstruction(state); break;
        case 0x2F: unimplementedInstruction(state); break;

        case 0x30: noOperation(state); break;
        case 0x31: unimplementedInstruction(state); break;
        case 0x32: unimplementedInstruction(state); break;
        case 0x33: unimplementedInstruction(state); break;
        case 0x34: unimplementedInstruction(state); break;
        case 0x35: unimplementedInstruction(state); break;
        case 0x36: unimplementedInstruction(state); break;
        case 0x37: unimplementedInstruction(state); break;
        case 0x38: noOperation(state); break;
        case 0x39: unimplementedInstruction(state); break;
        case 0x3A: unimplementedInstruction(state); break;
        case 0x3B: unimplementedInstruction(state); break;
        case 0x3C: unimplementedInstruction(state); break;
        case 0x3D: unimplementedInstruction(state); break;
        case 0x3E: unimplementedInstruction(state); break;
        case 0x3F: unimplementedInstruction(state); break;

        case 0x40: unimplementedInstruction(state); break;
        case 0x41: unimplementedInstruction(state); break;
        case 0x42: unimplementedInstruction(state); break;
        case 0x43: unimplementedInstruction(state); break;
        case 0x44: unimplementedInstruction(state); break;
        case 0x45: unimplementedInstruction(state); break;
        case 0x46: unimplementedInstruction(state); break;
        case 0x47: unimplementedInstruction(state); break;
        case 0x48: unimplementedInstruction(state); break;
        case 0x49: unimplementedInstruction(state); break;
        case 0x4A: unimplementedInstruction(state); break;
        case 0x4B: unimplementedInstruction(state); break;
        case 0x4C: unimplementedInstruction(state); break;
        case 0x4D: unimplementedInstruction(state); break;
        case 0x4E: unimplementedInstruction(state); break;
        case 0x4F: unimplementedInstruction(state); break;

        case 0x50: unimplementedInstruction(state); break;
        case 0x51: unimplementedInstruction(state); break;
        case 0x52: unimplementedInstruction(state); break;
        case 0x53: unimplementedInstruction(state); break;
        case 0x54: unimplementedInstruction(state); break;
        case 0x55: unimplementedInstruction(state); break;
        case 0x56: unimplementedInstruction(state); break;
        case 0x57: unimplementedInstruction(state); break;
        case 0x58: unimplementedInstruction(state); break;
        case 0x59: unimplementedInstruction(state); break;
        case 0x5A: unimplementedInstruction(state); break;
        case 0x5B: unimplementedInstruction(state); break;
        case 0x5C: unimplementedInstruction(state); break;
        case 0x5D: unimplementedInstruction(state); break;
        case 0x5E: unimplementedInstruction(state); break;
        case 0x5F: unimplementedInstruction(state); break;

        case 0x60: unimplementedInstruction(state); break;
        case 0x61: unimplementedInstruction(state); break;
        case 0x62: unimplementedInstruction(state); break;
        case 0x63: unimplementedInstruction(state); break;
        case 0x64: unimplementedInstruction(state); break;
        case 0x65: unimplementedInstruction(state); break;
        case 0x66: unimplementedInstruction(state); break;
        case 0x67: unimplementedInstruction(state); break;
        case 0x68: unimplementedInstruction(state); break;
        case 0x69: unimplementedInstruction(state); break;
        case 0x6A: unimplementedInstruction(state); break;
        case 0x6B: unimplementedInstruction(state); break;
        case 0x6C: unimplementedInstruction(state); break;
        case 0x6D: unimplementedInstruction(state); break;
        case 0x6E: unimplementedInstruction(state); break;
        case 0x6F: unimplementedInstruction(state); break;

        case 0x70: unimplementedInstruction(state); break;
        case 0x71: unimplementedInstruction(state); break;
        case 0x72: unimplementedInstruction(state); break;
        case 0x73: unimplementedInstruction(state); break;
        case 0x74: unimplementedInstruction(state); break;
        case 0x75: unimplementedInstruction(state); break;
        case 0x76: unimplementedInstruction(state); break;
        case 0x77: unimplementedInstruction(state); break;
        case 0x78: unimplementedInstruction(state); break;
        case 0x79: unimplementedInstruction(state); break;
        case 0x7A: unimplementedInstruction(state); break;
        case 0x7B: unimplementedInstruction(state); break;
        case 0x7C: unimplementedInstruction(state); break;
        case 0x7D: unimplementedInstruction(state); break;
        case 0x7E: unimplementedInstruction(state); break;
        case 0x7F: unimplementedInstruction(state); break;

        case 0x80: unimplementedInstruction(state); break;
        case 0x81: unimplementedInstruction(state); break;
        case 0x82: unimplementedInstruction(state); break;
        case 0x83: unimplementedInstruction(state); break;
        case 0x84: unimplementedInstruction(state); break;
        case 0x85: unimplementedInstruction(state); break;
        case 0x86: unimplementedInstruction(state); break;
        case 0x87: unimplementedInstruction(state); break;
        case 0x88: unimplementedInstruction(state); break;
        case 0x89: unimplementedInstruction(state); break;
        case 0x8A: unimplementedInstruction(state); break;
        case 0x8B: unimplementedInstruction(state); break;
        case 0x8C: unimplementedInstruction(state); break;
        case 0x8D: unimplementedInstruction(state); break;
        case 0x8E: unimplementedInstruction(state); break;
        case 0x8F: unimplementedInstruction(state); break;

        case 0x90: unimplementedInstruction(state); break;
        case 0x91: unimplementedInstruction(state); break;
        case 0x92: unimplementedInstruction(state); break;
        case 0x93: unimplementedInstruction(state); break;
        case 0x94: unimplementedInstruction(state); break;
        case 0x95: unimplementedInstruction(state); break;
        case 0x96: unimplementedInstruction(state); break;
        case 0x97: unimplementedInstruction(state); break;
        case 0x98: unimplementedInstruction(state); break;
        case 0x99: unimplementedInstruction(state); break;
        case 0x9A: unimplementedInstruction(state); break;
        case 0x9B: unimplementedInstruction(state); break;
        case 0x9C: unimplementedInstruction(state); break;
        case 0x9D: unimplementedInstruction(state); break;
        case 0x9E: unimplementedInstruction(state); break;
        case 0x9F: unimplementedInstruction(state); break;

        case 0xA0: unimplementedInstruction(state); break;
        case 0xA1: unimplementedInstruction(state); break;
        case 0xA2: unimplementedInstruction(state); break;
        case 0xA3: unimplementedInstruction(state); break;
        case 0xA4: unimplementedInstruction(state); break;
        case 0xA5: unimplementedInstruction(state); break;
        case 0xA6: unimplementedInstruction(state); break;
        case 0xA7: unimplementedInstruction(state); break;
        case 0xA8: unimplementedInstruction(state); break;
        case 0xA9: unimplementedInstruction(state); break;
        case 0xAA: unimplementedInstruction(state); break;
        case 0xAB: unimplementedInstruction(state); break;
        case 0xAC: unimplementedInstruction(state); break;
        case 0xAD: unimplementedInstruction(state); break;
        case 0xAE: unimplementedInstruction(state); break;
        case 0xAF: unimplementedInstruction(state); break;

        case 0xB0: unimplementedInstruction(state); break;
        case 0xB1: unimplementedInstruction(state); break;
        case 0xB2: unimplementedInstruction(state); break;
        case 0xB3: unimplementedInstruction(state); break;
        case 0xB4: unimplementedInstruction(state); break;
        case 0xB5: unimplementedInstruction(state); break;
        case 0xB6: unimplementedInstruction(state); break;
        case 0xB7: unimplementedInstruction(state); break;
        case 0xB8: unimplementedInstruction(state); break;
        case 0xB9: unimplementedInstruction(state); break;
        case 0xBA: unimplementedInstruction(state); break;
        case 0xBB: unimplementedInstruction(state); break;
        case 0xBC: unimplementedInstruction(state); break;
        case 0xBD: unimplementedInstruction(state); break;
        case 0xBE: unimplementedInstruction(state); break;
        case 0xBF: unimplementedInstruction(state); break;

        case 0xC0: unimplementedInstruction(state); break;
        case 0xC1: unimplementedInstruction(state); break;
        case 0xC2: unimplementedInstruction(state); break;
        case 0xC3: unimplementedInstruction(state); break;
        case 0xC4: unimplementedInstruction(state); break;
        case 0xC5: unimplementedInstruction(state); break;
        case 0xC6: unimplementedInstruction(state); break;
        case 0xC7: unimplementedInstruction(state); break;
        case 0xC8: unimplementedInstruction(state); break;
        case 0xC9: unimplementedInstruction(state); break;
        case 0xCA: unimplementedInstruction(state); break;
        case 0xCB: unimplementedInstruction(state); break;
        case 0xCC: unimplementedInstruction(state); break;
        case 0xCD: unimplementedInstruction(state); break;
        case 0xCE: unimplementedInstruction(state); break;
        case 0xCF: unimplementedInstruction(state); break;

        case 0xD0: unimplementedInstruction(state); break;
        case 0xD1: unimplementedInstruction(state); break;
        case 0xD2: unimplementedInstruction(state); break;
        case 0xD3: unimplementedInstruction(state); break;
        case 0xD4: unimplementedInstruction(state); break;
        case 0xD5: unimplementedInstruction(state); break;
        case 0xD6: unimplementedInstruction(state); break;
        case 0xD7: unimplementedInstruction(state); break;
        case 0xD8: unimplementedInstruction(state); break;
        case 0xD9: unimplementedInstruction(state); break;
        case 0xDA: unimplementedInstruction(state); break;
        case 0xDB: unimplementedInstruction(state); break;
        case 0xDC: unimplementedInstruction(state); break;
        case 0xDD: unimplementedInstruction(state); break;
        case 0xDE: unimplementedInstruction(state); break;
        case 0xDF: unimplementedInstruction(state); break;

        case 0xE0: unimplementedInstruction(state); break;
        case 0xE1: unimplementedInstruction(state); break;
        case 0xE2: unimplementedInstruction(state); break;
        case 0xE3: unimplementedInstruction(state); break;
        case 0xE4: unimplementedInstruction(state); break;
        case 0xE5: unimplementedInstruction(state); break;
        case 0xE6: unimplementedInstruction(state); break;
        case 0xE7: unimplementedInstruction(state); break;
        case 0xE8: unimplementedInstruction(state); break;
        case 0xE9: unimplementedInstruction(state); break;
        case 0xEA: unimplementedInstruction(state); break;
        case 0xEB: unimplementedInstruction(state); break;
        case 0xEC: unimplementedInstruction(state); break;
        case 0xED: unimplementedInstruction(state); break;
        case 0xEE: unimplementedInstruction(state); break;
        case 0xEF: unimplementedInstruction(state); break;

        case 0xF0: unimplementedInstruction(state); break;
        case 0xF1: unimplementedInstruction(state); break;
        case 0xF2: unimplementedInstruction(state); break;
        case 0xF3: unimplementedInstruction(state); break;
        case 0xF4: unimplementedInstruction(state); break;
        case 0xF5: unimplementedInstruction(state); break;
        case 0xF6: unimplementedInstruction(state); break;
        case 0xF7: unimplementedInstruction(state); break;
        case 0xF8: unimplementedInstruction(state); break;
        case 0xF9: unimplementedInstruction(state); break;
        case 0xFA: unimplementedInstruction(state); break;
        case 0xFB: unimplementedInstruction(state); break;
        case 0xFC: unimplementedInstruction(state); break;
        case 0xFD: unimplementedInstruction(state); break;
        case 0xFE: unimplementedInstruction(state); break;
        case 0xFF: unimplementedInstruction(state); break;


    }
}

#endif