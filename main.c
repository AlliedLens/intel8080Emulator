#include "debugging.h"
#include "utils.h"
#include "emulatorShell.h"

void main(int argc, char** argv){
    // printf("%s\n", argv[1]);
    unsigned char* program;
    int filesize = openRom(&program, argv[1]);

    // printProgram(program, filesize);
    // disassembleProgram(program, filesize);


    int i = 0;
    State8080* intel8080;
    intel8080 = (State8080*)malloc(sizeof(State8080));
    initializeEmulator(intel8080);

    // while (intel8080->pc < 50){
    //     disassemble8080(program, intel8080->pc);
    //     intel8080->pc = intel8080->pc + emulateCycle(intel8080);
    // }
    stepByStepDebugger(intel8080, program);
}
