#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void free_hash(hash_table *table)
{
	free(table->arr);
	free(table->isfree);
	free(table);
}

hash_table *init(int size, int m_shift)
{
	hash_table *res = malloc(sizeof(hash_table));
	res->arr = malloc(sizeof(int) * size);
	res->size = size;
	res->maxshift = m_shift;
	res->isfree = calloc(size, sizeof(char));
	res->a = (rand() + 1) % 20;
	res->b = rand() % 100;
	res->c = rand() % 1000;
	return res;
}

int hash(int val, hash_table *table)
{
	int res = (table->a * val * (val + table->b) + table->c);
	res += res/ 100 + res/1000;
	return  res % table->size;
}

int add_hash(hash_table *table, int val)
{
	int id = hash(val, table);
	int s = 0;
	while (table->isfree[id])
	{
		//printf("%d\n", id);
	    s++;
		if (s > table->maxshift)
		{
			//printf("%d %d\n",s , table->maxshift);
			return -1;
		}
		id = (id + 1) % table->size;
	}
	table->arr[id] = val;
	table->isfree[id] = 1;
	return 0;
}

int search_hash(int val, int *id, hash_table *table)
{
	int res = 1;
	*id = hash(val, table);
	while (table->arr[*id] != val && table->isfree && res <= table->maxshift)
	{
		res++;
		(*id) = (*id + 1) % table->size;
	}
	if (!table->isfree || res > table->maxshift)
		return -1;
	return res;
}

int del_hash(int val, hash_table *table)
{
	int id;
	int res = search_hash(val, &id, table);
	if (res != -1)
		table->isfree[id] = 0;
	return res;
}

int read_hash(hash_table **table, char *fname, int m_shift)
{
	FILE *f = fopen(fname, "r");
	int n = nambers_in_file(f);
	int val;
	*table = init(MAX, m_shift);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &val);
		if (add_hash(*table, val) == -1)
		{
			fclose(f);
			return -1;
		}
	}
	fclose(f);
	return 0;
}

void print_hash(hash_table *table)
{
	printf(" Код  | Число|\n");
	printf("--------------\n");
	for (int i = 0; i < table->size; i++)
		if (table->isfree[i])
		{
			printf("%6d|%6d|\n", i, table->arr[i]);
		}
}