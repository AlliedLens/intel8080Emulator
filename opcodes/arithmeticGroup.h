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

// reg1 <- reg1 + reg2

// 0x87, 0x81,82,83,84, 85, 86
void addRegister(State8080* state, uint8_t* reg1){
    uint16_t ans = (uint16_t)(state->a) + (uint16_t)(*reg1);
    
    setFlags(state, ans);
    state->a = ans & 0xFF;
}

void addRegisterWithCarry(State8080* state, uint8_t* reg1, int carry){
    uint16_t ans = (uint16_t)(state->a) + (uint16_t)(*reg1) + carry;
    
    setFlags(state, ans);
    state->a = ans & 0xFF;
}

// C6, CE, D8, DE
void addImmediate(State8080* state,  int d8, int carry){
    uint16_t ans = (uint16_t)(state->a) +  d8 + carry;
    
    setFlags(state, ans);
    state->a = ans & 0xFF;
}

void subRegister(State8080* state, uint8_t* reg1){
    uint16_t ans = (uint16_t)(state->a) - (uint16_t)(*reg1);
    
    setFlags(state, ans);
    state->a = ans & 0xFF;
}

void subRegisterWithCarry(State8080* state, uint8_t* reg1, int carry){
    uint16_t ans = (uint16_t)(state->a) - (uint16_t)(*reg1) - carry;
    
    setFlags(state, ans);
    state->a = ans & 0xFF;
}

void subImmediate(State8080* state,  int d8, int carry){
    uint16_t ans = (uint16_t)(state->a) +  d8 + carry;
    
    setFlags(state, ans);
    state->a = ans & 0xFF;
}

void incrementReg(State8080* state, uint8_t* reg1){
    uint16_t ans = (uint16_t)(*reg1) + 1;
    setFlags(state, ans);
}

void decrementReg(State8080* state, uint8_t* reg1){
    uint16_t ans = (uint16_t)(*reg1) - 1;
    setFlags(state, ans);
}


#endif
