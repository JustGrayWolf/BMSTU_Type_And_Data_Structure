//#include "graphics.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void free_tree(tree *t)
{
	if (t)
	{
		free_tree(t->right);
		free_tree(t->left);
		free(t);
	}
}

tree *new_node(int val)
{
	tree *res = malloc(sizeof(tree));
	res->right = NULL;
	res->left = NULL;
	res->val = val;
	return res;
}

void tree_add(tree *t, tree *val)
{
	if (t->val > val->val)
		if (t->right)
			tree_add(t->right, val);
		else
			t->right = val;
	else
		if (t->left)
			tree_add(t->left, val);
		else
			t->left = val;
}

int tree_search(tree *t, int val, tree **p, tree **prev)
{
	int res = 1;
	if (!t)
		return -1;
	if (t->val == val)
		*p = t;
	else if (t->val > val)
	{
		*prev = t;
		res = tree_search(t->right, val, p, prev) + 1;
		if (!res)
			return -1;
	}
	else
	{
		*prev = t;
		res = tree_search(t->left, val, p, prev) + 1;
		if (!res)
			return -1;
	}
	return res;
}

int tree_del(tree **t, int val)
{
	tree *delel = NULL, *prevel = NULL;
	int res = tree_search(*t, val, &delel, &prevel);
	if (res == -1)
		return -1;
	if (!prevel)
	{
		if ((*t)->right)
		{
			(*t) = (*t)->right;
			if (delel->left)
				tree_add(*t, delel->left);
		}
		else 
			(*t) = (*t)->left;
	}
	else 
	{
		if (prevel->right && prevel->right->val == val)
			prevel->right = NULL;
		else
			prevel->left = NULL;
		if (delel->right)
			tree_add(*t, delel->right);
		if (delel->left)
			tree_add(*t, delel->left);
	}
	//free(delel);
	printf("ok ");
	return res;
}

void read_in_arr(tree *t, int *arr, int *i)
{
	if (t->right)
		read_in_arr(t->right, arr, i);
	arr[*i] = t->val;
	(*i)++;
	if (t->left)
		read_in_arr(t->left, arr, i);
}

void add_balance(int *arr, tree **t, int left, int right)
{
	//printf("lr %d %d\n", left, right);
	int i = (left + right) / 2;
	tree *n = new_node(arr[i - 1]);
	if (!(*t))
		*t = n;
	else
		tree_add(*t, n);
	if (right - left > 1)
	{
		if (right - i > 1 )
			add_balance(arr, t, i, right);
		if (i - left > 1 )
			add_balance(arr, t, left, i);
	}
	
}

void balance(tree **t, int size)
{
	//print_tree(*t, "---");
	int *arr = malloc(size * sizeof(int));
	int i = 0;
	read_in_arr(*t, arr, &i);
	for (int j = 0; j < size; j++)
		//printf("%d ", arr[j]);
	//free_tree(*t);
	*t = NULL;
	add_balance(arr, t, 0, size + 1);
	free(arr);
}

int read_tree(tree **t, char *fname)
{
	FILE *f = fopen(fname, "r");
	int n = nambers_in_file(f);
	int val;
	*t = NULL;
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &val);
		tree *node = new_node(val);
		if (!*t)
			*t = node;
		else
			tree_add(*t, node);
	}
	fclose(f);
	return 0;
}

void to_dot(tree *t, FILE *f)
{

    if (t->left)
    {
            fprintf(f, "\"%d \" -> \"%d \";\n", t->val, t->left->val);
    }

    if (t->right)
    {            fprintf(f, "\"%d \" -> \"%d \";\n", t->val, t->right->val);
    }
}

void apply_pre(tree *t, FILE *f)
{
    if (t == NULL)
    {
        return;
    }
    to_dot(t, f);
    apply_pre(t->left, f);
    apply_pre(t->right, f);
}

void export_to_dot(FILE *f, const char *tree_name, tree *t)
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply_pre(t, f);

    fprintf(f, "}\n");
    
    fclose(f);
    
    system("dot -Tpng ./output.gv -oGRAPH.png");
    system("C:/Windows/System32/mspaint.exe GRAPH.png");
    system("rm output.gv");
}

int print_tree(tree *t, char *s)
{
	FILE *f = fopen("output.gv", "w");
	export_to_dot(f, s, t);
}