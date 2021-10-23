#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "struct.h"

void print_string(struct performance *array)
{
	printf("\nНазвание театра: ");
	printf("%s",array->theater);
	printf("\nНазвание спектакля: ");
	printf("%s",array->perf_name);
	printf("\nРежиссер: ");
	printf("%s",array->director);
	printf("\nДиапазон цен: ");
	printf("%d", array->low_prise);
	printf(" - ");
	printf("%d", array->high_prise);
	printf("\nТип спектакля: ");
	if (array->type_spc == 1)
		printf("Детский");
	else if (array->type_spc == 2)
		printf("Взрослый");
	else
		printf("Музыкальный");
	if (array->type_spc == 1)
	{
		printf("\nМинимальный возраст: ");
		printf("%d", array->spct.child.age);
		printf("\nТип детского спектакля: ");
		if (array->spct.child.type == 1)
			printf("Сказка");
		else if (array->spct.child.type == 2)
			printf("Пьеса");
		else
			printf("Музыкальный");
	}
	else if (array->type_spc == 2)
	{
		printf("\nТип взрослого спектакля: ");
		if (array->spct.adult.type == 1)
			printf("Пьеса");
		else if (array->spct.adult.type == 2)
			printf("Драма");
		else
			printf("Комедия");
	}
	else if (array->type_spc == 3)
	{
		printf("\nКомпозитор: ");
		printf("%s",array->spct.musical.composer);
		printf("\nСтрана: ");
		printf("%s",array->spct.musical.country);
		printf("\nМинимальный возраст: ");
		printf("%d", array->spct.musical.age);
		printf("\nПродолжительность: ");
		printf("%d", array->spct.musical.duration);
	}
}

void print(struct performance *array, int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("\n\nСтрока №%d\n", i + 1);
		print_string(&array[i]);

	}
	printf("\n");

}

void print_array_by_keys(struct performance *array, int keys[ARR_LEN][2], int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("\n\nСтрока №%d\n", keys[i][0]);
		print_string(&array[keys[i][0] - 1]);
	}
	printf("\n");
}

int read_line(char *s, int n)
{
    int ch, i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
	{
        if (i < n - 1) 
            s[i] = ch;
		i++;
	}
    s[i] = '\0';
    return i;
}

int read_int(int *a)
{
	int ch, i = 0, rc = 1;
	*a = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) 
	{
        if (ch >= '0' && ch <= '9') 
             *a = *a * 10 + ch - '0';
		else
			rc = 0;
		i++;
	}
	if (rc == 0)
		return rc;
    return i;
}

void fill_file(struct performance *array, int *count)
{
	char current;
	FILE *f = NULL;
	char str[21];
	while (f == NULL)
	{
		printf("\nВведите имя файла(не более 20 символов):\n");
	    if (fgets(str, 21, stdin) != NULL)
		{
			int i = 0;
			while (str[i])
				i++;
			if (i)
			    str[i - 1] = 0;
	        f = fopen(str, "r");
		    if (f == NULL)
			    printf("Невозможно открыть файл, повторите %s", str);
		}
		else
			printf("Некорректный ввод");
		
	}
	assert(f);
	int i = 0;
	int j = 0;
	while (i < 480 && !feof(f))
	{
		fgets(array[i].theater, NAME_LEN, f);
	    j = 0;
		while (array[i].theater[j])
			j++;
		if (j)
			array[i].theater[j - 1] = 0;
		fgets(array[i].perf_name, NAME_LEN, f);
		j = 0;
		while (array[i].perf_name[j])
			j++;
		if (j)
			array[i].perf_name[j - 1] = 0;
		fgets(array[i].director, NAME_LEN, f);
		j = 0;
		while (array[i].director[j])
			j++;
		if (j)
			array[i].director[j - 1] = 0;
		fscanf(f, "%d", &array[i].low_prise);
		fscanf(f, "%d", &array[i].high_prise);
		fscanf(f, "%d", &array[i].type_spc);
        fscanf(f, "%c", &current);
		if (array[i].type_spc == 1)
		{
			fscanf(f, "%d", &array[i].spct.child.age);
			fscanf(f, "%d", &array[i].spct.child.type);
            fscanf(f, "%c", &current);
		}
		else if (array[i].type_spc == 2)
        {
			fscanf(f, "%d", &array[i].spct.adult.type);
            fscanf(f, "%c", &current);
        }
		else if (array[i].type_spc == 3) 
		{
			fgets(array[i].spct.musical.composer, NAME_LEN, f);
			j = 0;
			while (array[i].spct.musical.composer[j])
				j++;
			if (j)
				array[i].spct.musical.composer[j - 1] = 0;
			fgets(array[i].spct.musical.country, THEATER, f);
			j = 0;
			while (array[i].spct.musical.country[j])
				j++;
			if (j)
				array[i].spct.musical.country[j - 1] = 0;
			fscanf(f, "%d", &array[i].spct.musical.age);
			fscanf(f, "%d", &array[i].spct.musical.duration);
            fscanf(f, "%c", &current);
		}
		i++;
	}
	*count = i;
	fclose(f);
}

void fill_keys(int keys[ARR_LEN][2], struct performance *array, int count)
{
	for (int i = 0; i < count; i++)
	{
		keys[i][0] = i + 1;
		keys[i][1] = array[i].low_prise;
	}
}

void print_keys(int keys[ARR_LEN][2], int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("\nИндекс %d\n", keys[i][0]);
		printf("Наименьшая цена билета: %d\n", keys[i][1]);
	}
}

void add_struct(struct performance *array, int i)
{
	int count_let, low_prise_price, high_prise_price, action, age, durationation;
	count_let = 0;
	while (count_let == 0 || count_let > THEATER) 
	{
		printf("\nВведите название театра(до 35 символов)\n");
		count_let = read_line(array[i].theater, THEATER);
		if (count_let == 0 || count_let >= THEATER)
		{
			count_let = 0;
			printf("\nНекорректный ввод, повторите\n");
		}
	}
	
		count_let = 0;
	while (count_let == 0 || count_let > NAME_LEN)
	{
		printf("\nВведите название спектакля(до 40 символов)\n");
		count_let = read_line(array[i].perf_name, NAME_LEN);
		if (count_let == 0 || count_let >= NAME_LEN)
		{
			count_let = 0;
			printf("\nНекорректный ввод, повторите\n");
		}
	}
	
	count_let = 0;
	while (count_let == 0 || count_let > NAME_LEN)
	{
		printf("\nВведите режиссера(до 40 символов)\n");
		count_let = read_line(array[i].director, NAME_LEN);
		if (count_let == 0 || count_let >= NAME_LEN)
		{
			count_let = 0;
			printf("\nНекорректный ввод, повторите\n");
		}
	}
	
	low_prise_price = 0;
	while (low_prise_price <= 0) 
	{
		printf("\nВведите нижний предел цены билета:\n");
		if (read_int(&low_prise_price))
		{
			if (low_prise_price <= 0)
				printf("\nНекорректный ввод, повторите\n");
			else
				array[i].low_prise = low_prise_price;
		}
		else
		{
			low_prise_price = 0;
			printf("\nНекорректный ввод, повторите\n");
		}
		
	}
	
	high_prise_price = 0;
	while (high_prise_price <= 0 || high_prise_price < low_prise_price)
	{
		printf("\nВведите верхний предел цены билета(должен быть больше или равен нижнему):\n");
		if (read_int(&high_prise_price))
		{
			if (high_prise_price <= 0 || high_prise_price < low_prise_price)
				printf("\nНекорректный ввод, повторите\n");
			else
				array[i].high_prise = high_prise_price;
		}
		else
		{
			high_prise_price = 0;
			printf("\nНекорректный ввод, повторите\n");
		}
	}
	
	action = 0;
	while (action != 1 && action != 2 && action != 3)
	{
		printf("\nВыберите тип спектакля:\n1 - детский\n2 - взрослый\n3 - музыкальный\n");
		if (read_int(&action))
		{
			if (action != 1 && action != 2 && action != 3)
				printf("\nНекорректный ввод, повторите\n");
			else
				array[i].type_spc = action;
		}
		else
		{
			action = 0;
			printf("\nНекорректный ввод, повторите\n");
		}
	}
	
	if (action == 1) 
	{
		age = -1;
		while (age < 0 || age > 18)
		{
			printf("\nВведите возрастное ограничение(от 0 до 18):\n");
			if (read_int(&age))
			{
				if (age < 0 || age > 18 )
					printf("\nНекорректный ввод, повторите\n");
				else
					array[i].spct.child.age = age;
			}
			else
			{
				age = -1;
				printf("\nНекорректный ввод, повторите\n");
			}
			
		}
		
		action = 0;
		while (action != 1 && action != 2 && action != 3)
		{
			printf("\nВыберите тип детского спектакля:\n1 - сказка\n2 - пьеса\n3 - музыкальный\n");
			if (read_int(&action))
			{
				if (action != 1 && action != 2 && action != 3)
					printf("\nНекорректный ввод, повторите\n");
				else
					array[i].spct.child.type = action;
			}
			else
			{
				action = 0;
				printf("\nНекорректный ввод, повторите\n");
			}
		}
	}
	else if (action == 2) 
	{
		action = 0;
		while (action != 1 && action != 2 && action != 3)
		{
			printf("\nВыберите тип взрослого спектакля:\n1 - пьеса\n2 - драма\n3 - комедия\n");
			if (read_int(&action))
			{
				if (action != 1 && action != 2 && action != 3)
					printf("\nНекорректный ввод, повторите\n");
				else
					array[i].spct.adult.type = action;
			}
			else
			{
				action = 0;
				printf("\nНекорректный ввод, повторите\n");
			}
		}
	}
	else if (action == 3) 
	{
		count_let = 0;
		while (count_let == 0 || count_let > NAME_LEN)
		{
			printf("\nВведите композитора(до 40 символов)\n");
			count_let = read_line(array[i].spct.musical.composer, NAME_LEN);
			if (count_let == 0 || count_let >= NAME_LEN)
			{
				count_let = 0;
				printf("\nНекорректный ввод, повторите\n");
			}
		}
		
		count_let = 0;
		while (count_let == 0 || count_let > THEATER)
		{
			printf("\nВведите страну(до 35 символов)\n");
			count_let = read_line(array[i].spct.musical.country, THEATER);
			if (count_let == 0 || count_let >= THEATER)
			{
				count_let = 0;
				printf("\nНекорректный ввод, повторите\n");
			}
		}
			
		age = -1;
		while (age < 0 || age > 18)
		{
			printf("\nВведите возрастное ограничение(от 0 до 18):\n");
			if (read_int(&age))
			{
				if (age < 0 || age > 18 )
					printf("\nНекорректный ввод, повторите\n");
				else
					array[i].spct.musical.age = age;
			}
			else
			{
				age = -1;
				printf("\nНекорректный ввод, повторите\n");
			}
		}
		durationation = 0;
		while (durationation <= 0)
		{
			printf("\nВведите продолжительность(в минутах):\n");
			if (read_int(&durationation))
			{
				if (durationation <= 0)
					printf("\nНекорректный ввод, повторите\n");
				else
					array[i].spct.musical.duration = durationation;
			}
			else
			{
				durationation = 0;
				printf("\nНекорректный ввод, повторите\n");
			}
		}
	}
}

void fill_manually(struct performance *array, int *count)
{
	int i = 0;
	*count = 0;
	while (*count <= 0 || *count > ARR_LEN)
	{
		printf("\nВведите число строк таблицы(от 1 до 45):\n");
		if (read_int(count))
		{
			if (*count <= 0 || *count > ARR_LEN)
				printf("\nНекорректный ввод, повторите\n");
		}
		else
		{
			*count = 0;
			printf("\nНекорректный ввод, повторите\n");
		}
	}

	while (i < *count) 
	{
		printf("\n\nЗапись №%d", i+1);
		add_struct(array, i);
		i++;
	}
}

void remove_struct(struct performance *array, int *count)
{
	int index = 0;
	while (index <= 0 || index > *count)
	{
		printf("\nВведите индекс удаляемой строки(от 1 до %d):\n", *count);
		if (read_int(&index))
		{
			if (index <= 0 || index > *count)
				printf("\nНекорректный ввод, повторите\n");
		}
		else
		{
			*count = 0;
			printf("\nНекорректный ввод, повторите\n");
		}
	}
	index--;
	for (int i = index; i < *count - 1; i++) 
		array[i] = array[i + 1];
	*count -= 1;
}