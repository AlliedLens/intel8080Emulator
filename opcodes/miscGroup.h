#ifndef MISC_OPCODES_H
#define MISC_OPCODES_H

#include "../emulatorShell.h"
#include "../utils.h"

void HLT(){
    exit(1);
}

void EI(State8080* state){
    state->en = 1;
}

void DI(State8080* state){
    state->en = 0;
}

void IN(State8080* state){
    uint8_t* opcode = &state->memory[state->pc];
    printf("\n IN will be implemented later \n");
}

void OUT(State8080* state){
    uint8_t* opcode = &state->memory[state->pc];
    printf("\n OUT will be implemented later \n");
}

#endif
