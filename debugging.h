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


void printProgram(unsigned char* buff, int size){
    printf("\n======================Program-Code========================\n");
    for (int i = 0; i < 0x100; i++){
        for (int j = 0; j < 8; j++){
            printf(" 0x%x ", buff[i*8 + j]);
        }

        printf("\n");
    }
    printf("\n==========================================================\n");
}