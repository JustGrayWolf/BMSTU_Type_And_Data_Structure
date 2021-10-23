#include "functions.h"
#include <stdio.h>

int menu()
{
	int chose = -1;
	while (chose < 0 || chose > 4)
	{
		printf("\n1)Вывести дерево\n2)Вывести сбалансированное дерево\n3)Вывести хеш таблицу\n4)Удалить элемент и сравнить эффективность разных типов\n0)Выход\nВыбор: ");
		scanf("%d", &chose);
		if (chose < 0 || chose > 4)
			printf("\nНекорректный ввод. Повторите.\n");
	}
	return chose;
}

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc": "=A" (d));
	return d;
}

int getFileSize(const char* file_name){
	int _file_size = 0;
	FILE* fd = fopen(file_name, "rb");
	if(fd == NULL){
		_file_size = -1;
	}
	else{
		while(getc(fd) != EOF)
			_file_size++;
		fclose(fd);
	}
	return _file_size;
}

void comp(tree **t, tree **bal_t, hash_table *table , char *str, int val, int *n)
{
	if (!*t || !*bal_t)
	{
		printf("\nЭлементов в структурах.\n");
		return ;
	}
	long long t_start = tick();
	int res1 = tree_del(t, val);
	long long time1 = tick() - t_start;
	t_start = tick();
	int res2 = tree_del(bal_t, val);
	if (*n > 2)
		balance(bal_t, *n);
	long long time2 = tick() - t_start;
	t_start = tick();
	int res3 = del_hash(val, table);
	long long time3 = tick() - t_start;
	int mem1 = getFileSize(str);
	t_start = tick();
	int res4 = del_file(val, str);
	long long time4 = tick() - t_start;
	int mem2 = getFileSize(str);
	if (res1 == -1)
	{
		printf("\nУказанного элемента не существует.\n");
	}
	else
	{
		(*n)--;
		printf("\nДДП:\nСравнений: %d\nВремя: %ld\nПамять до: %d\nПамять после: %d\n\n", res1, time1, ((*n) + 1) * sizeof(tree), (*n) * sizeof(tree));
		printf("\nСбалансированое дерево:\nСравнений: %d\nВремя: %ld\nПамять до: %d\nПамять после: %d\n\n", res2, time2, ((*n) + 1) * sizeof(tree), (*n) * sizeof(tree));
		printf("\nХеш таблица:\nСравнений: %d\nВремя: %ld\nПамять до: %d\nПамять после: %d\n\n", res3, time3, (MAX) * (sizeof(int) + sizeof(char)) + sizeof(hash_table), (MAX) * (sizeof(int) + sizeof(char)) + sizeof(hash_table));
		printf("\nФайл:\nСравнений: %d\nВремя: %ld\nПамять до: %d\nПамять после: %d\n\n", res4, time4, mem1, mem2);
	}
}