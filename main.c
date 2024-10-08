#include "disassembler.h"
#include "debugging.h"
#include "utils.h"

void main(int argc, char** argv){
    // printf("%s\n", argv[1]);
    unsigned char* invaderE;
    openRom(&invaderE, argv[1]);

    // printProgram(invaderE, 0x800);\

    disassemble8080(invaderE, 0);

    int pc = 0;
    while (pc < 100){
        pc += disassemble8080(invaderE, pc);
    }

}