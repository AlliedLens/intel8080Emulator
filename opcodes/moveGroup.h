#include <stdint.h>

#ifndef MOVE_OPCODES_H
#define MOVE_OPCODES_H

#include "../emulatorShell.h"
#include "../utils.h"

void MOV(State8080* state, uint8_t* reg1, uint8_t* reg2){
    *reg1 = *reg2;
}

void MVI(State8080* state, uint8_t* reg1){
    uint8_t* opcode = &state->memory[state->pc];
    *reg1 = opcode[1];
}

void STAX(State8080* state, uint8_t* reg1, uint8_t* reg2){
    uint16_t addr = ((*reg1) << 8)  | (*reg2);
    state->memory[addr] = state->a;
}

void LXI(State8080* state, uint8_t* reg1, uint8_t* reg2){
    uint8_t* opcode = &state->memory[state->pc];
    *reg1 = opcode[2];
    *reg2 = opcode[1];
}

void SHLD(State8080* state, uint8_t* reg1, uint8_t* reg2){
    uint8_t* opcode = &state->memory[state->pc];
    uint16_t addr = (opcode[2] << 8 ) | opcode[1];

    state->memory[addr] = state->l;
    state->memory[addr+1] = state->h;
}

void LHLD(State8080* state, uint8_t* reg1, uint8_t* reg2){
    uint8_t* opcode = &state->memory[state->pc];
    uint16_t addr = (opcode[2] << 8 ) | opcode[1];

    state->l = state->memory[addr];
    state->h = state->memory[addr+1];
}

#endif