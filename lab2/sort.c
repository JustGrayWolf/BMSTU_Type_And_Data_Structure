#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "functions.h"

void sort1 (int keys[ARR_LEN][2], int count)
{
	int tmp;
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count ; j++)
		{
			if (keys[i][1] > keys[j][1]) 
			{
 tmp = keys[j][1];
 keys[j][1] = keys[i][1];
 keys[i][1] = tmp;
 tmp = keys[j][0];
				keys[j][0] = keys[i][0];
				keys[i][0] = tmp;
			}
		}
	}
}

void qs(int keys[ARR_LEN][2], int first, int last)
{
	int tmp;
    if (first < last) 
    {
        int left = first, right = last, middle = keys[(left + right) / 2][1];
        do 
        {
            while (keys[left][1] < middle) left++; 
            while (keys[right][1] > middle) right--; 
            if (left <= right)
            {
				tmp = keys[left][1]; 
                keys[left][1] = keys[right][1];
                keys[right][1] = tmp;
				tmp = keys[left][0];
                keys[left][0] = keys[right][0];
                keys[right][0] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        qs(keys, first, right);
        qs(keys, left, last);
    }
}

void sort_array_qs(struct performance *array, int first, int last)
{
	struct performance tmp;
	if (first < last) 
    {
        int left = first, right = last, middle = array[(left + right) / 2].low_prise;
        do 
        {
            while (array[left].low_prise < middle) left++;
            while (array[right].low_prise > middle) right--; 
            if (left <= right) 
            {
				tmp = array[left];
                array[left] = array[right];
                array[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        sort_array_qs(array, first, right); 
        sort_array_qs(array, left, last);
    }
}

void sort_array_sort1 (struct performance *array, int count)
{
	struct performance tmp;
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count ; j++)
		{
			if (array[i].low_prise > array[j].low_prise) 
			{
 tmp = array[j];
 array[j] = array[i];
 array[i] = tmp;
			}
		}
	}
}

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc": "=A" (d));
	return d;
}

void time_sort_array(struct performance *array, int keys[ARR_LEN][2], int count)
{
	unsigned long long tb, te, all_k = 0, all_t = 0;
	struct performance array_test[count];
	float result;
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < count; j++) 
 array_test[j] = array[j];
		fill_keys(keys, array, count); 
 tb = tick(); 
		qs(keys, 0, count - 1);
 te = tick();
		all_k += te - tb; 
		tb = tick(); 
		sort_array_qs(array_test, 0, count - 1);
		te = tick();
		all_t += te - tb; 
	}
	printf("\nСортировка по ключам: %d\n", (int)all_k/10);
	printf("\nСортировка таблицы: %d\n", (int)all_t/10);
	if (all_t >= all_k)
	{
		result = (all_t - all_k)/(float)all_t * 100; 
		printf("\nСортировка по ключам быстрее сортировки таблицы на %.3f %%", result);
	}
	else if (all_t < all_k)
	{
		result = (all_k - all_t)/(float)all_k * 100;
		printf("\nСортировка таблицы быстрее сортировки по ключам на %.3f %%", result);
	}
	result = (sizeof(keys[0][0]) * 2 * ARR_LEN) / (float)(sizeof(array[0]) * ARR_LEN) * 100;
	printf("\nМатрица для индексов использует дополнительные %.3f%% памяти относительно массива структур\n", result);
}

void time_sort_keys(struct performance *array, int keys[ARR_LEN][2], int count)
{
	float result;
	unsigned long long tb, te, all_k1 = 0, all_k2 = 0;
	for (int i = 0; i < 10; i++) 
	{
		fill_keys(keys, array, count); 
		tb = tick();
		sort1 (keys, count);
		te = tick();
		all_k1 += te - tb; 
		fill_keys(keys, array, count); 
		tb = tick(); 
		qs(keys, 0, count - 1); 
		te = tick();
		all_k2 += te - tb; 
	}
	printf("\nБыстрая сортировка: %d\n", (int)all_k2/10);
	printf("\nСортировка пузырьком: %d\n", (int)all_k1/10);
	if (all_k1 >= all_k2)
	{
		result = (all_k1 - all_k2)/(float)all_k1 * 100; 
		printf("\nБыстрая сортировка быстрее сортировки пузырьком на %.3f %%\n", result);
	}
	else if (all_k1 < all_k2)
	{
		result = (all_k2 - all_k1)/(float)all_k2 * 100;
		printf("\nСортировка пузырьком быстрее быстрой сортировки на %.3f%%\n", result);
	}
}

void search(struct performance *array, int count)
{
	int age = -1, durationation = 0, count_s = 0;
	while (age < 0 || age > 18)
	{
		printf("\nВведите возраст ребенка(от 0 до 18):\n");
		if (read_int(&age))
		{
			if (age < 0 || age > 18 )
				printf("\nНеверный ввод, введите еще раз\n");
		}
		else
		{
			age = -1;
			printf("\nНеверный ввод, введите еще раз\n");
		}	
	}
	while (durationation <= 0)
	{
		printf("\nВведите максимальную продолжительность спектакля(в минутах):\n");
		if (read_int(&durationation))
		{
			if (durationation <= 0)
				printf("\nНеверный ввод, введите еще раз\n");
		}
		else
		{
 durationation = 0;
			printf("\nНеверный ввод, введите еще раз\n");
		}
	}
	for (int i = 0; i < count; i++)
	{
		if (array[i].type_spc == 3)
		{
			if (array[i].spct.musical.age <= age)
			{
				if (array[i].spct.musical.duration <= durationation)
				{
					printf("\n\nСтрока №%d\n", i + 1);
					print_string(&array[i]);
 count_s++;
				}
			}
		}
	}
	if (count_s == 0)
		printf("\nМузыкальных спектаклей по указанным параметрам не найдено\n");
	else
		printf("\n");
}