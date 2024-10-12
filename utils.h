#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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

int checkParity(uint8_t num){
    int count = 0;

    while (num){
        count += num & 1;
        num >>= 1;
    }

    return (count % 2 == 0) ? 1 : 0;
}

#endif