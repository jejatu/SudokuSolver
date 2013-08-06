#include "file.h"
#include <stdio.h>

void read_matrix_from_file(char* filename, int matrix[HEIGHT][WIDTH]) {
    FILE* file;
    file = fopen(filename, "r");
    if (file != NULL) {
        int c;
        int i = 0;
        while ((c = fgetc(file)) != EOF && i < WIDTH * HEIGHT) {
            if (c >= '0' && c <= '9') {
                matrix[(int)(i / HEIGHT)][i % WIDTH] = c - '0';
                ++i;
            }
            else if (c == '.') {
                matrix[(int)(i / HEIGHT)][i % WIDTH] = 0;
                ++i;
            }
        }
        fclose(file);
    }
}