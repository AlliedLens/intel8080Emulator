#ifndef CONTROL_OPCODES_H
#define CONTROL_OPCODES_H

#include "../emulatorShell.h"

void XXX(State8080* state){
    printf("Error: unimplemented Instruction\n");
    exit(1);
}

void NOP(State8080* state){
    printf("No operation");
}

// Jump

void JMP(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    state->pc = (opcode[2] << 8) | (opcode[1]);
}

void JNC(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    if (state->cc.carry == 0){
        state->pc = (opcode[2] << 8) | (opcode[1]);
    }
}

void JNZ(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    if (state->cc.zero == 0){
        state->pc = (opcode[2] << 8) | (opcode[1]);
    }
}

void JPO(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    if (state->cc.parity == 0){
        state->pc = (opcode[2] << 8) | (opcode[1]);
    }
}

void JP(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    if (state->cc.sign == 0){
        state->pc = (opcode[2] << 8) | (opcode[1]);
    }
}


void JC(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    if (state->cc.carry == 1){
        state->pc = (opcode[2] << 8) | (opcode[1]);
    }
}

void JZ(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    if (state->cc.zero == 1){
        state->pc = (opcode[2] << 8) | (opcode[1]);
    }
}

void JPE(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    if (state->cc.parity == 1){
        state->pc = (opcode[2] << 8) | (opcode[1]);
    }
}

void JM(State8080* state){
    unsigned char* opcode = &state->memory[state->pc];
    if (state->cc.sign == 0){
        state->pc = (opcode[2] << 8) | (opcode[1]);
    }
}

// Call

void CALL(State8080* state){
    uint16_t ret = state->pc + 2;
    
    state->memory[state->sp - 1] = (ret >> 8) & 0xFF;
    state->memory[state->sp - 2] = (ret & 0xFF);

    state->sp = state->sp - 2;
    unsigned char* opcode = &state->memory[state->pc];

    state->pc = (opcode[2] << 8) | opcode[1];
}

void CZ(State8080* state){
    if (state->cc.zero == 1){
        CALL(state);
    }
}

void CNZ(State8080* state){
    if (state->cc.zero == 0){
        CALL(state);
    }
}

void CC(State8080* state){
    if (state->cc.carry == 1){
        CALL(state);
    }
}

void CNC(State8080* state){
    if (state->cc.carry == 0){
        CALL(state);
    }
}

void CPO(State8080* state){
    if (state->cc.parity == 1){
        CALL(state);
    }
}

void CPE(State8080* state){
    if (state->cc.parity == 0){
        CALL(state);
    }
}

// Return

void RET(State8080* state){
    state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
    state->sp += 2;
}


void RZ(State8080* state){
    if (state->cc.zero == 1){
        RET(state);
    }
}

void RNZ(State8080* state){
    if (state->cc.zero == 0){
        RET(state);
    }
}

void RC(State8080* state){
    if (state->cc.carry == 1){
        RET(state);
    }
}

void RNC(State8080* state){
    if (state->cc.parity == 0){
        RET(state);
    }
}
void RPO(State8080* state){
    if (state->cc.parity == 1){
        RET(state);
    }
}

void RPE(State8080* state){
    if (state->cc.parity == 0){
        RET(state);
    }
}

void RST(State8080* state, uint8_t rstNum){
    uint16_t ret = state->pc;
    unsigned char* opcode = &state->memory[state->pc];


    state->memory[state->sp - 1] = (ret >> 8) & 0xFF;
    state->memory[state->sp - 2] = (ret & 0xFF);
    state->sp = state->sp - 2;

    switch(rstNum){
        case 0: state->pc = 0x00; break;
        case 1: state->pc = 0x08; break;
        case 2: state->pc = 0x10; break;
        case 3: state->pc = 0x18; break;
        case 4: state->pc = 0x20; break;
        case 5: state->pc = 0x28; break;
        case 6: state->pc = 0x30; break;
        case 7: state->pc = 0x38; break;
    }
}

void PCHL(State8080* state){
    state->pc = (state->h << 8) | (state->l);
}

#endif