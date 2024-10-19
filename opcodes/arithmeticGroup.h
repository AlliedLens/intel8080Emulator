#include <stdint.h>

#ifndef ARITHMETIC_OPCODES_H
#define ARITHMETIC_OPCODES_H

#include "../emulatorShell.h"
#include "../utils.h"

void incrementRegister(uint8_t* reg){
    *reg += 1;
    printf("Error: unimplemented Instruction\n");
}

void setFlags(State8080* state, int ans){
    state->cc.zero = ((ans&0xFF) == 0);
    state->cc.sign = ((ans&0x80) == 0);
    state->cc.carry = (ans > 0xFF);
    state->cc.parity = checkParity(ans);
}

void INR(State8080* state, uint8_t* reg1){
    uint16_t ans = (uint16_t)(*reg1) + 1;
    setFlags(state, ans);
}

void DCR(State8080* state, uint8_t* reg1){
    uint16_t ans = (uint16_t)(*reg1) - 1;
    setFlags(state, ans);
}

void INX(State8080* state, uint8_t* reg1, uint8_t* reg2){
    uint16_t combined = *reg1 << 8 | *reg2;
    uint16_t ans = combined + 1;

    *reg1 = (ans & 0xFF00) >> 8;
    *reg2 = (ans & 0x00FF);
}

void DCX(State8080* state, uint8_t* reg1, uint8_t* reg2){
    uint16_t combined = *reg1 << 8 | *reg2;
    uint16_t ans = combined - 1;

    *reg1 = (ans & 0xFF00) >> 8;
    *reg2 = (ans & 0x00FF);
}

void RLC(State8080* state, uint8_t* reg1){
    uint8_t prevBit7 = (*reg1 >> 7) & 1;
    *reg1 = (*reg1 << 1) | prevBit7;
    state->cc.carry = prevBit7;
}

void RRC(State8080* state, uint8_t* reg1){
    uint8_t prevBit0 = (*reg1) & 0x01;

    *reg1 = (*reg1 >> 1) | (prevBit0<<8);
    state->cc.carry = prevBit0;
}

void RAL(State8080* state, uint8_t* reg1){
    uint8_t prevCarry = state->cc.carry;
    uint8_t prevBit7 = (*reg1 >> 7) & 1;
    
    *reg1 = (*reg1 << 1) | (prevCarry);
    state->cc.carry = prevBit7;
}

void RAR(State8080* state, uint8_t* reg1){
    uint8_t prevCarry = state->cc.carry;
    uint8_t prevBit7 = (*reg1 >> 7) & 1;
    uint8_t prevBit0 = (*reg1) & 0x01;

    *reg1 = (*reg1 >> 1) | (prevBit7<<8);
    state->cc.carry = prevBit0;
}

void DAD(State8080* state, uint8_t* reg1, uint8_t* reg2){
    uint16_t HL = (state->h << 8 ) | (state->l);
    uint16_t combined = (*reg1 << 8) | (*reg2);

    uint32_t ans = HL + combined;

    state->cc.carry = (ans & 0x0000)>>16;

    state->h = (ans & 0xFF00) >> 8;
    state->l = (ans & 0x00FF);

}


#endif
