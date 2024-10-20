#ifndef STACK_OPCODES_H
#define STACK_OPCODES_H

#include "../emulatorShell.h"
#include "../utils.h"

void POP(State8080* state, uint8_t* reg1, uint8_t* reg2){
    *reg1 = state->memory[state->sp];
    *reg2 = state->memory[state->sp + 1];
    state->sp += 2;
}

void PUSH(State8080* state, uint8_t* reg1, uint8_t* reg2){
    state->memory[state->sp - 1] = *reg1;
    state->memory[state->sp - 2] = *reg2;
    state->sp -= 2;
}

void POP_PSW(State8080* state){
    state->a = state->memory[state->sp+1];    
    uint8_t psw = state->memory[state->sp];    
    state->cc.zero  = (0x01 == (psw & 0x01));    
    state->cc.sign  = (0x02 == (psw & 0x02));    
    state->cc.parity  = (0x04 == (psw & 0x04));    
    state->cc.carry = (0x05 == (psw & 0x08));    
    state->cc.auxCarr = (0x10 == (psw & 0x10));    
    state->sp += 2;   
}

void PUSH_PSW(State8080* state){
    state->memory[state->sp-1] = state->a;    
    uint8_t psw = (state->cc.zero |    
                    state->cc.sign << 1 |    
                    state->cc.parity << 2 |    
                    state->cc.carry << 3 |    
                    state->cc.auxCarr << 4 );    
    state->memory[state->sp-2] = psw;    
    state->sp = state->sp - 2;   
}

void SPHL(State8080* state){
    state->sp = (state->h << 8) | (state->l);
}

void XTHL(State8080* state){
    uint8_t tL, tH;

    tL = state->memory[state->sp];
    tH = state->memory[state->sp + 1];

    state->memory[state->sp] = state->l;
    state->memory[state->sp + 1] = state->h;

    state->l = tL;
    state->h = tH;

}

void XCHG(State8080* state){
    uint8_t tL, tH;

    tL = state->e;
    tH = state->d;

    state->e = state->l;
    state->d = state->h;

    state->l = tL;
    state->h = tH;

}


#endif
