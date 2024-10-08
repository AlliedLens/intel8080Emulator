#ifndef DEBUGGING_H
#define DEBUGGING_H

// void printProgram(unsigned char* buff)

/*
   Space Invaders, (C) Taito 1978, Midway 1979    

   CPU: Intel 8080 @ 2MHz (CPU similar to the (newer) Zilog Z80)    

   Interrupts: $cf (RST 8) at the start of vblank, $d7 (RST $10) at the end of vblank.    

   Video: 256(x)*224(y) @ 60Hz, vertical monitor. Colours are simulated with a    
   plastic transparent overlay and a background picture.    
   Video hardware is very simple: 7168 bytes 1bpp bitmap (32 bytes per scanline).    

   Sound: SN76477 and samples.    

   Memory map:    
    ROM    
    $0000-$07ff:    invaders.h    
    $0800-$0fff:    invaders.g    
    $1000-$17ff:    invaders.f    
    $1800-$1fff:    invaders.e    

    RAM    
    $2000-$23ff:    work RAM    
    $2400-$3fff:    video RAM    

    $4000-:     RAM mirror   

    Invaders.h is the start of the space invaders program
     
*/

#include <stdio.h>
#include "disassembler.h"


void printProgram(unsigned char* buff, int size){
    printf("\n============================================================================Program--Machine--Code=================================================================================\n");
    for (int i = 0; i < size; i++){
            printf(" 0x%02x ", buff[i]);
            if (i % 32 == 0) printf(": 0x%04x \n", i);
    }
    printf("\n==============================================================================================================================================================================\n");
}

void disassembleProgram(unsigned char* buff, int size){
    printf("\n==========================================================================Program-Dissasembled===================================================================================================\n");
    int pc = 0;
    while (pc < size){
        pc += disassemble8080(buff, pc);
    }    
    printf("\n==============================================================================================================================================================================\n");

}

#endif