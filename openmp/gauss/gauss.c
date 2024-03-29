#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//#define DEBUG

#define MAX 4000
long double a[MAX][MAX];
long double x[MAX];
long double b[MAX];
long double swap[MAX];

int main(int argc, char **argv) {
    clock_t before = clock();

	int r, c, n;
	int i, j, k;
	long double m;
	int msec;
	FILE *file;

	if(argc < 2){
		perror("Arg error!");
		exit(1);
	}


	if ((file = fopen(argv[1], "r")) == NULL) {
		perror("gauss.in");
		exit(1);
	}

	fscanf(file, "%d", &n);

	for (r = 0; r < n; r++) {
		for (c = 0; c < n; c++) {
			fscanf(file, "%Lf", &a[r][c]);
		}
	}
	for (r = 0; r < n; r++)
		fscanf(file, "%Lf", &b[r]);

	fclose(file);
    printf("n %d\n", n);
    for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (fabs(a[i][i]) < fabs(a[j][i])) {
				memcpy(swap, a[i], n * sizeof(long double));
				memcpy(a[i], a[j], n * sizeof(long double));
				memcpy(a[j], swap, n * sizeof(long double));
				m = b[i];
				b[i] = b[j];
				b[j] = m;
			}
		}
		for (j = i + 1; j < n; j++) {
            m = a[j][i] / a[i][i];
			for (k = i; k < n; k++) {
				a[j][k] = a[j][k] - a[i][k] * m;
			}
			b[j] = b[j] - b[i] * m;
		}
	}

	x[i] = b[i] / a[i][i];
	for (i--; i >= 0; i--) {
        printf("i %d\n", i);
		m = 0;
		for (j = i; j < n; j++)
			m = m + a[i][j] * x[j];
		x[i] = (b[i] - m) / a[i][i];
	}

#ifdef DEBUG
	for (r = 0; r < n; r++) {
		for (c = 0; c < n; c++) {
			fprintf(stdout, "%Lf ", a[r][c]);
		}
		fprintf(stdout, "\n");
	}
	for (r = 0; r < n; r++)
	fprintf(stdout, "%Lf ", b[r]);
	fprintf(stdout, "\n");
#endif

	if ((file = fopen("gauss.out", "w")) == NULL) {
		perror("gauss.out");
		exit(1);
	}

	for (r = 0; r < n; r++)
		fprintf(file, "%2.2Lf ", x[r]);
	fprintf(file, "\n");
	fflush(file);

	fclose(file);

    clock_t difference = clock() - before;
    msec = difference * 1000 / CLOCKS_PER_SEC;
    printf("Tempo: %d segundos %d mili\n", msec/1000, msec%1000);
	return EXIT_SUCCESS;
}