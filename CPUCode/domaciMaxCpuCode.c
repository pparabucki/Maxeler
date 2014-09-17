#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

int main(void) {
	FILE* file = fopen("input.txt", "r");
	FILE* out = fopen("output.txt", "w");
	int m;
	int n;
	int iteracija = 0;

	printf("\nRunning on DFE...\n");

	while (1) {

		if (fscanf(file, "%d", &m) != 1)
			break;
		if (fscanf(file, "%d", &n) != 1)
			break;

		//printf("\nm = %d\n", m);
		//printf("n = %d\n", n);

		double *nizX, *nizC, *data_out;

		int size = 0;

		//if(m>=n) size = m; else size = n;

		size = m * n;
		if (size % 2 != 0)
			size++;
		nizX = calloc(size, sizeof(double));
		nizC = calloc(size, sizeof(double));
		data_out = calloc(size, sizeof(double));

		//nizC
		for (int i = 0; i < m; i++) {
			double pom;
			fscanf(file, "%lf", &pom);
			for (int j = 0; j < n; j++) {
				nizC[m*j+i] = pom;


			}
		}

		//nizX
		for (int i = 0; i < n; i++) {
			double pom;
			fscanf(file, "%lf", &pom);
			for (int j = 0; j < m; j++) {
				nizX[i*m + j] = pom;
				//if(j==0) nizX[i*m] = 1;	// postavlja za X0 = 1
			}
		}

		/*printf("NIZC: ");
		for (int i = 0; i < size; i++)
			printf("%lf ", nizC[i]);
		printf("\nNIZX: ");
		for (int i = 0; i < size; i++)
			printf("%lf ", nizX[i]);
		 */
	//	printf("\nRunning on DFE.\n");

		domaciMax(size, m , n, nizC, nizX, data_out);

		fprintf(out, "ITERACIJA %3d za m = %d , n = %d\n", iteracija, m, n);
		for (int i = 0; i < n; i++) {
			if (i == 0)
				fprintf(out, "\t");
			fprintf(out, "Y(X(%3d))=%lf ", i, data_out[m*i+m-1]);
			if (i < n - 1)
				fprintf(out, ",");
			else
				fprintf(out, ";");
			if (i % 50 == 0)
				fprintf(out, "\n\t");
		}
		fprintf(out, "\n-----------------------------------------------\n");
		iteracija++;
		free(nizX);
		free(nizC);
		free(data_out);
	}

	fclose(file);
	fclose(out);
	printf("\nDone.\n");

	return 0;
}
