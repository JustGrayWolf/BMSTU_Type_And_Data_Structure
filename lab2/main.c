#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "functions.h"

int main(void)
{
	srand(time(0));
	setbuf(stdout, NULL);
	int action = 0, count = 0;
	int keys[ARR_LEN][2];
	struct performance array[ARR_LEN];
	printf("Программа предназначена для работы с базой данных репертуаров театров\n");
	printf("Её функционал: ввод, вывод, сортировка, поиск, удаление записей в базе данных,\n");
	printf(" а также сравнение различных способов сортировки\n");
	
	while (action != 1 && action != 2)
	{
		printf("\nВыберите, как задать базу данных репертуаров театра:\n1 - ввести вручную\n2 - заполнить из файла\n0 - выход\n");
		if (read_int(&action))
		{
			if (action == 1 || action == 2 || action == 0)
			{
				if (action == 1)				
					fill_manually(array, &count);
				if (action == 2)
					fill_file(array, &count); 
				if (action == 0)
					return 0;
			}
			else
				printf("\nНекорректный ввод, повторите\n");
		}
		else
		{
			action = 0;
			printf("\nНекорректный ввод, повторите\n");
		}
	}
	
	action = -1;
	while (action != 0) 
	{
		printf("\nВыберите действие:\n");
		printf("1 - вывести таблицу на экран\n");
		printf("2 - добавить запись\n");
		printf("3 - удалить запись по индексу\n");
		printf("4 - отсортировать ключи по меньшей цене билетов и вывести индексы\n");
		printf("5 - отсортировать таблицу по меньшей цене билетов и вывести записи\n");
		printf("6 - отсортировать ключи по меньшей цене билетов и вывести таблицу \n");
		printf("7 - сравнить сортировку по ключам и сортировку таблицы \n");
		printf("8 - сравнить быструю сортировку и сортировку пузырьком\n");
		printf("9 - найти записи по указанному возрастному ограничению и продолжительности\n");
		printf("0 - выход\n");
		if (read_int(&action))
		{
			if (action == 1 || action == 2 || action == 3 || action == 4 || \
			action == 5 || action == 6 || action == 7 || action == 8 || \
			action == 9 || action == 0)
			{
				if (action == 1)
				{
					if (count > 0)
						print(array, count);
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 2) 
				{
					if (count < ARR_LEN)
					{
						add_struct(array, count);
						count++;
					}
					else
						printf("\nДостигут максимум записей\n");
				}
				else if (action == 3) 
				{
					if (count > 0)
						remove_struct(array, &count);
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 4) 
				{
					if (count > 0)
					{
						fill_keys(keys, array, count);
						sort1 (keys, count);
						print_keys(keys, count);
					}
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 5)
				{
					if (count > 0)
					{
						sort_array_qs(array, 0, count - 1);
						fill_keys(keys, array, count);
						print(array, count);
					}
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 6)
				{
					if (count > 0)
					{
						fill_keys(keys, array, count);
						qs(keys, 0, count - 1);
						print_array_by_keys(array, keys, count);
					}
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 7)
				{
					if (count > 0)
						time_sort_array(array, keys, count);
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 8) 
				{
					if (count > 0)
						time_sort_keys(array, keys, count);
					else
						printf("\nВ таблице нет записей\n");
				}
				else if (action == 9)
				{
					if (count > 0)
						search(array, count);
					else
						printf("\nВ таблице нет записей\n");
				}
			}
			else
				printf("\nНекорректный ввод, повторите\n");
		}
		else
		{
			action = -1;
			printf("\nНекорректный ввод, повторите\n");
		}
	}
	return 0;
}