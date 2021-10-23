#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int nambers_in_file(FILE *f)
{
	int i, res = 0;
	while (!feof(f))
	{
		res++;
		if (fscanf(f, "%d", &i) != 1)
			return -1;
	}
	rewind(f);
	return res;
}

int check(char *s, int n)
{
	FILE *f = fopen(s, "r");
	int *arr = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		fscanf(f, "%d", arr + i);
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (arr[i] == arr[j])
				return 1;
	return 0;
}

int del_file(int val, char *fname)
{
	int n;
	FILE *f = fopen(fname, "r");
	if (!f || (n = nambers_in_file(f)) == -1)
		return -1;
	int *arr = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		fscanf(f, "%d", arr + i);
	fclose(f);
	f = fopen(fname, "w");
	for (int i = 0; i< n; i++)
		if (arr[i] != val)
			fprintf(f ," %d", arr[i]);
	free(arr);
	fclose(f);
	return n;
}