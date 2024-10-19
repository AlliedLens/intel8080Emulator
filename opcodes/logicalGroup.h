#ifndef LOGICAL_OPCODES_H
#define LOGICAL_OPCODES_H

#include "../emulatorShell.h"


// void setFlags(State8080* state, int ans){
//     state->cc.zero = ((ans&0xFF) == 0);
//     state->cc.sign = ((ans&0x80) == 0);
//     state->cc.carry = (ans > 0xFF);
//     state->cc.parity = checkParity(ans);
// }

void CMA(State8080* state, uint8_t* reg1){
    *reg1 = ~(*reg1);
}

void ANA(State8080* state, uint8_t* reg1){
    uint16_t ans = state->a & (*reg1);
    setFlags(state, ans);
    state->a = ans;
}

void XRA(State8080* state, uint8_t* reg1){
    uint16_t ans = state->a ^ (*reg1);
    setFlags(state, ans);
    state->a = ans;
}

void ORA(State8080* state, uint8_t* reg1){
    uint16_t ans = state->a | (*reg1);
    setFlags(state, ans);
    state->a = ans;
}

void CMP(State8080* state, uint8_t* reg1){
    uint16_t ans = state->a - (*reg1);
    setFlags(state, ans);
}

void CMC(State8080* state){
    state->cc.carry = !state->cc.carry;
}

void STD(State8080* state){
    state->cc.carry = 1;
}

//immediate

void CPI(State8080* state){
    uint8_t* opcode = &state->memory[state->pc];
    uint16_t ans = state->a - opcode[1];
    setFlags(state, ans);
}

void ANI(State8080* state){
    uint8_t* opcode = &state->memory[state->pc];
    uint16_t ans = state->a & opcode[1];
    setFlags(state, ans);
    state->a = ans;
}

void ORI(State8080* state){
    uint8_t* opcode = &state->memory[state->pc];
    uint16_t ans = state->a | opcode[1];
    setFlags(state, ans);
    state->a = ans;
}

void XRI(State8080* state){
    uint8_t* opcode = &state->memory[state->pc];
    uint16_t ans = state->a ^ opcode[1];
    setFlags(state, ans);
    state->a = ans;
}

#endif
