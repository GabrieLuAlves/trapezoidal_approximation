#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OUTPUT_PRECISION    17

double trapezoid_rule(const double a, const double b, double const *y, const int n) {

    double total = 0;
    double dx = (b - a) / (n - 1);
    int x = n - 2;

    total = y[0] / 2.0 + y[n - 1] / 2.0;
    while(x > 0) total += (double)y[x--];
    total *= dx;

    return total;

}

void read(FILE *file, double *expectedArea, double *a, double *b, double *array, int n) {
    fread(expectedArea, 1, sizeof(double), file);
    fread(a, 1, sizeof(double), file);
    fread(b, 1, sizeof(double), file);
    fread(array, 500, sizeof(double), file);
}

/*
void displayArray(const double *array, int n, const int columns) {
    int i = 0;
    int c = 0;

    while (i < n) {
        while (i < n && c--) {
            printf("%+.*f ", OUTPUT_PRECISION , array[i++]);
        }
        printf("\n");
        c = columns;
    }
}
*/

int main(int argc, char** argv) {
	unsigned i = 0;
	double buffer[504];
    double a, b, *y, pickedToolApproximation, calculatedArea, preciseArea;
	FILE *file = fopen("input.bin", "rb");

    fread(&i, sizeof(unsigned), 1, file);

    printf("+----------------------------+----------------------------------+----------------------------------+\n");
    printf("|      Calculated Area       |      Wolfram Absolute error      |  Calculated Area Absolute error  |\n");
    printf("+----------------------------+----------------------------------+----------------------------------+\n");
	while (i--) {
		fread(buffer, sizeof(double), 504, file);

        preciseArea = buffer[0];
		pickedToolApproximation = buffer[1];
		a = buffer[2];
		b = buffer[3];
		y = buffer + 4;

		calculatedArea = trapezoid_rule(a, b, y, 500);

		printf("|  %+24.16f  |  %+.23e  |  %+.23e  |\n", calculatedArea, fabs(preciseArea - pickedToolApproximation), fabs(preciseArea - calculatedArea));
	}
    printf("+----------------------------+----------------------------------+----------------------------------+\n");
	
    fclose(file);

    return 0;
}
