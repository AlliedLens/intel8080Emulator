#ifndef MACHINEOPCODES_H
#define MACHINEOPCODES_H

// Include the State8080 definition
#include "../emulatorShell.h"

// Now State8080 is visible, and you can define functions that use it
void unimplementedInstruction(State8080* state){
    printf("Error: unimplemented Instruction\n");
    exit(1);
}

#endif
