// #ifndef MACHINE_OPCODES_H
// #define MACHINE_OPCODES_H


// // Now State8080 is visible, and you can define functions that use it
// void unimplementedInstruction(State8080* state){
//     printf("Error: unimplemented Instruction\n");
//     exit(1);
// }

// #endif


#ifndef CONTROL_OPCODES_H
#define CONTROL_OPCODES_H

#include "../emulatorShell.h"

void unimplementedInstruction(State8080* state){
    printf("Error: unimplemented Instruction\n");
    exit(1);
}

void noOperation(State8080* state){
    printf("No operation");
}

#endif