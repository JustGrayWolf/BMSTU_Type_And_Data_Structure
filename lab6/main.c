#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
	setbuf(stdout, NULL);
	int ok = 0;
	FILE *f;
	int n;
	int val;
	char str[100];
	while (!ok)
	{
		printf("Введите имя файла: ");
		scanf("%s", str);
		f = fopen(str, "r");
		if (!f)
			printf("\nУказанного файла не существует.\n");
		else if ((n = nambers_in_file(f)) == -1)
			printf("\nНеверный формат файла.\n");
		else if (n == 0)
			printf("\nПустой файл\n");
		else if (n > MAX)
			printf("\nПревышено максимальное количество чисел.\n");
		//else if (check(str, n))
			//printf("\nПовторное число в файле\n");
		else
			ok = 1;
		fclose(f);
	}
	int max_shift;
	printf("\nВведите максимальное количество сравненеий в таблице: ");
	while (scanf("%d", &max_shift)!=1)
		getc(stdin);
	tree *t = NULL, *bal_t = NULL;
	hash_table *table = NULL;
	read_tree(&t, str);
	read_tree(&bal_t, str);
	balance(&bal_t, n);
	while (read_hash(&table, str, max_shift) == -1)
		free_hash(table);
	while (1)
		switch (menu())
		{
			case 0:
			return 0;
			break;
			case 1:
			print_tree(t, "ДДП");
			break;
			case 2:
			print_tree(bal_t, "Сбалансированное_дерево");
			break;
			case 3:
			print_hash(table);
			break;
			case 4:
			printf("\nВведите число которое нужно удалить: ");
			while (scanf("%d", &val)!=1)
				getc(stdin);
			if(t)
				comp(&t, &bal_t, table, str, val, &n);
			break;
		}
}