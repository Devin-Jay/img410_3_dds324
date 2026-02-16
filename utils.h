// header files
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <cstdint>
#include <cstring>

typedef struct {
    int width;
    int height;
    uint8_t *pixels;
} PPMImage;

// function declarations
void writeOutputPPMFile(char *filename, PPMImage* img);