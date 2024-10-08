#include "disassembler.h"
#include "debugging.h"
#include "utils.h"

void main(int argc, char** argv){
    // printf("%s\n", argv[1]);
    unsigned char* program;
    int filesize = openRom(&program, argv[1]);

    // printProgram(program, filesize);
    // disassembleProgram(program, filesize);
}
