#include <stdio.h>
#define MAX 300

typedef struct hash_table
{
	int a, b, c;
	int size;
	int *arr;
	char *isfree;
	int maxshift;
}hash_table;

typedef struct tree
{
	int val;
	struct tree *left;
	struct tree *right;
} tree;

int check(char *s, int n);

int del_hash(int val, hash_table *table);

int tree_del(tree **t, int val);

int del_file(int val, char *fname);

int nambers_in_file(FILE *f);

void balance(tree **t, int size);

int read_hash(hash_table **table, char *fname, int m_shift);

int read_tree(tree **t, char *fname);

int print_tree(tree *t, char *s);

void free_hash(hash_table *table);

void print_hash(hash_table *table);

int menu();

void comp(tree **t, tree **bal_t, hash_table *table , char *str, int val, int *n);