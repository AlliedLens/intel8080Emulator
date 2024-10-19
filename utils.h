
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "emulatorShell.h"

#ifndef UTILS_H
#define UTILS_H

int openRom(unsigned char** buff, char* filename){
    FILE* f = fopen(filename, "rb");

    if ( f == NULL){
        printf("error: couldnt open %s \n", filename);
        exit(1);
    }

    fseek(f, 0, SEEK_END); // fseek moves the file pointer, 0 is the offset added after the pointer reaches the third parameter
    int filesize = ftell(f); // tells position of the pointer, since this is the last pointer, we get the filesize;
    fseek(f, 0, SEEK_SET);

    *buff = (unsigned char*)malloc(filesize);

    fread(*buff, filesize, 1, f);
    fclose(f);

    return filesize;
}

int checkParity(uint8_t num){ // returns 1 if even number of 1s else 0
    int count = 0;

    while (num){
        count += num & 1;
        num >>= 1;
    }

    return (count % 2 == 0) ? 1 : 0;
}

void setFlags(State8080* state, int ans){
    state->cc.zero = ((ans&0xFF) == 0);
    state->cc.sign = ((ans&0x80) == 0);
    state->cc.carry = (ans > 0xFF);
    state->cc.parity = checkParity(ans);
}

// void auxiliary_carry_flag(uint8_t a, unsigned char b, unsigned char carry_in) {
//     // Isolate the lower 4 bits (nibble) of both a and b
//     unsigned char lower_nibble_a = a & 0x0F;
//     unsigned char lower_nibble_b = b & 0x0F;

//     // Add the lower nibbles along with carry in (if any)
//     unsigned char lower_sum = lower_nibble_a + lower_nibble_b + carry_in;

//     // Check if there was a carry from bit 3 to bit 4
//     if (lower_sum > 0x0F) {
//         return 1; // Auxiliary carry occurred
//     } else {
//         return 0; // No auxiliary carry
//     }
// }


#endif