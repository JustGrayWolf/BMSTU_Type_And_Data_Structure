#include <stdio.h>
#include <stdlib.h>
#include "input_output.h"
#include "matrix.h"
#include "menu.h"
#define OK 0
#define ERROR 1

int main(void)
{
int s[4] = {10, 100, 500, 1000};
int c[5] = {1, 5, 20, 50, 60};
    setbuf(stdout, NULL);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 5; j++)
		{
			printf("\n\n%d %d\n\n", s[i], c[j]);
    int error = OK;
    int ** matrix;
    int size_rows = s[i], size_cols = s[i], count = c[j];
    matrix = rand_matrix(&size_cols, &size_rows, &count);
    error = (matrix == NULL) ? ERROR : OK;
	
    int *A = malloc((count) * sizeof(int));
	int *IA = malloc((count) * sizeof(int));
	struct ja JA;
    error = (A == NULL) ? ERROR : OK;
    error = (IA == NULL) ? ERROR : OK;
    int *ARRJ = malloc((size_cols + 1) * sizeof(int));
	error = (ARRJ == NULL) ? ERROR : OK; 
    if (count!= 0)
        input_matrix(matrix, size_rows, size_cols, count, A, IA, ARRJ);

        statistic(matrix, size_rows, size_cols, A, IA, ARRJ, count);
		}
    return 0;
}
