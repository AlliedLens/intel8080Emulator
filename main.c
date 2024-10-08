#include "disassembler.h"
#include "debugging.h"
#include "utils.h"

void main(int argc, char** argv){
    // printf("%s\n", argv[1]);
    unsigned char* invaderE;
    openRom(&invaderE, argv[1]);

    int pc = 0;
    while (pc < 50){
        pc += disassemble8080(invaderE, pc);
    }

}