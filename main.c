#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_POINTS    500

float trapezoid_rule(const float a, const float b, float const *y, const int n) {

    float total = 0;
    float dx = (b - a) / (n - 1);
    int x = n - 2;

    total = y[0] / 2.0 + y[n - 1] / 2.0;
    while(x > 0) total += (float)y[x--];
    total *= dx;

    return total;
}

void read(FILE *file, float *a, float *b, float *array, int n) {
    fread(a, 1, sizeof(float), file);
    fread(b, 1, sizeof(float), file);
    fread(array, 500, sizeof(float), file);
}

int main(int argc, char** argv) {
    FILE *file;
    char *inputFile = "input.bin";
    char *outputFile = "output.bin";
    float a, b, y[500], calculatedArea;

    file = fopen(inputFile, "rb");
    read(file, &a, &b, y, N_POINTS);
    fclose(file);

    calculatedArea = trapezoid_rule(a, b, y, N_POINTS);

    file = fopen(outputFile, "wb");
    fwrite(&calculatedArea, sizeof(float), 1, file);
    fclose(file);

    return 0;
}