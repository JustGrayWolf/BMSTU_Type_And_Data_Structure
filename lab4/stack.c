#define MAX_SIZE 5
#define MENU 7
#define ERROR 1
#define OK 1
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

typedef struct list
{
    int val;
	struct list *next;
}list;

typedef struct array
{
    int n;
	int elements[MAX_SIZE * 2 + 1];
}array;

void free_stdin()
{
	//char c = 0;
	//while(!feof(stdin) && (c = getc(stdin)) != EOF && c != '\n' && c != 0);
	fflush(stdin);
}

void push_list(list **l, int val)
{
    list *res = malloc(sizeof(list));
	if (res)
	{
	    (*res).next = *l;
	    (*res).val = val;
	    *l = res;
	}
	else
		errno = ERROR;
}

int pop_list(list **l)
{
	int res = (**l).val;
    list *buf = *l;
    *l = (**l).next;
    free(buf);
	
	return res;
}

void push_array(array *arr, int val)
{
	int *buf;
	//if ((*arr).n)
	//    buf = realloc((*arr).elements, ((*arr).n + 1) * sizeof(int));
	//else
	//	buf = malloc(sizeof(int));
    //if (buf)
	//{
        //(*arr).elements = buf;
		(*arr).elements[(*arr).n] = val;
		(*arr).n++;
	//}
	//else
	//{
	//	printf("err");
	//	errno = ERROR;
	//}
}

int pop_array(array *arr)
{
    int res = (*arr).elements[(*arr).n - 1];
	//if ((*arr).n == 1)
	//{
	//	free((*arr).elements);
	//	(*arr).n = 0;
	//}
	//else
	//{
		//int *buf = realloc((*arr).elements, ((*arr).n - 1) * sizeof(int));
		//if (buf)
		//{
			//(*arr).elements = buf;
			(*arr).n--;
	    //}
	//}
	return res;
}

void input_list_stack(list **l)
{
	*l = NULL;
	int n = 0;
	while (n < 1 || n > MAX_SIZE)
	{
		free_stdin();
		printf("\nВведите количество элементов в стеке(целое число>0 и <=%d): ", MAX_SIZE);
		if (!scanf("%d", &n))
			n = 0;
		if (n < 1)
			printf("\nНекорректный ввод, повторите.\n");
		if (n > MAX_SIZE)
			printf("\nЧисло элементов больше максимального, повторите.\n");
	}
	printf("\nВведите по строкам элеметы стека(целые числа):\n");
	int val;
	for (int i = 0; i < n;)
	{
		free_stdin();
		printf("%d:", i + 1);
		if (scanf("%d", &val))
		{
			push_list(l, val);
			i++;
		}
		else
			printf("\nЭлемент %d введён некорректно, повторите ввод элемента.\n", i + 1);
	}
}

void input_array_stack(array *arr)
{
	(*arr).n = 0;
		int n = 0;
	while (n < 1 || n > MAX_SIZE)
	{
		free_stdin();
		printf("\nВведите количество элементов в стеке(целое число>0 и <=%d): ", MAX_SIZE);
		if (!scanf("%d", &n))
			n = 0;
		if (n < 1)
			printf("\nНекорректный ввод, повторите.\n");
		if (n > MAX_SIZE)
			printf("\nЧисло элементов больше максимального, повторите.\n");
	}
	printf("\nВведите по строкам элеметы стека(целые числа):\n");
	int val;
	for (int i = 0; i < n;)
	{
		free_stdin();
		printf("%d:", i + 1);
		if (scanf("%d", &val))
		{
			push_array(arr, val);
			i++;
		}
		else
			printf("\nЭлемент %d введён некорректно, повторите ввод элемента.\n", i + 1);
	}
}

void from_list_to_array(list **l, array *arr)
{
	(*arr).n = 0;
	while (*l)
		push_array(arr, pop_list(l));
}

void from_array_to_list(list **l, array *arr)
{
	*l = NULL;
	while ((*arr).n)
		push_list(l, pop_array(arr));
}

void print_list_stack(list *l)
{
	printf("\n");
	for (;l; l = (*l).next)
		printf("%d ",(*l).val);
	printf("\n");
}

void print_array_stack(array arr)
{
	printf("\n");
	for (int i = 0; i < arr.n; i++)
		printf("%d ", arr.elements[i]);
	printf("\n");
}

void print_addres(list *l, list *del)
{
	printf("\nАдреса элементов списка:\n");
	for (;l; l = (*l).next)
		printf("%d ", (long long)l);
	printf("\nАдреса удалёных элементов:\n");
	print_list_stack(del);
}

unsigned long long tick(void)
{
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc": "=A" (d));
	return d;
}

list *sort_list(list **l1, list **l2)
{
	list *l3 = NULL;
	int val;
	while (*l1 || *l2)
	{
		if ((*l1 && *l2 && (**l1).val > (**l2).val) || (*l1 && !*l2))
			val = pop_list(l1);
		else
			val = pop_list(l2);
		while (l3 && val > (*l3).val)
		    push_list(l1, pop_list(&l3));
		push_list(&l3, val);
	}
	return l3;
}

array sort_array(array *arr1, array *arr2)
{
	array arr3;
	arr3.n = 0;
	int val;
	while ((*arr1).n || (*arr2).n)
	{
		if (((*arr1).n && (*arr2).n && 
		(*arr1).elements[(*arr1).n - 1] > (*arr2).elements[(*arr2).n - 1]) 
		|| ((*arr1).n && !(*arr2).n))
			val = pop_array(arr1);
		else
			val = pop_array(arr2);
		while (arr3.n && val > arr3.elements[arr3.n - 1])
		    push_array(arr1, pop_array(&arr3));
		push_array(&arr3, val);
	}
	return arr3;
}

void add_list(list **l)
{
	int n = 0;
	for (list *bl = (*l); bl; bl = (*bl).next)
		n++;
	if (n >= MAX_SIZE * 2)
		printf("В стеке максимальное количество элементов, добавление невозможно.");
	else
	{
		int val;
		printf("Введите число, добавляемое в стек:");
		free_stdin();
		while (!scanf("%d", &val))
		{
		    printf("Некорректный ввод.\nВедите число, добавляемое в стек:");
			free_stdin();
		}
		unsigned long long ts = tick();
		push_list(l, val);
		unsigned long long tf = tick();
		printf("\nВремя добавления %I64d тактов\n", tf - ts);
	}
}

void add_array(array *arr)	
{
    if ((*arr).n >= MAX_SIZE * 2)
		printf("В стеке максимальное количество элементов, добавление невозможно.");
	else
	{
		int val;
		printf("Введите число, добавляемое в стек:");
		free_stdin();
		while (!scanf("%d", &val))
		{
		    printf("Некорректный ввод.\nВедите число, добавляемое в стек:");
			free_stdin();
		}
		unsigned long long ts = tick();
		push_array(arr, val);
		unsigned long long tf = tick();
		printf("\nВремя добавления %I64d тактов\n", tf - ts);
	}
}

int menu()
{
	int c = -1;
	while (c < 0 || c > MENU)
	{
	    printf("\n1-Ввести и отсортировать стек в виде списка\n2-Ввести и отсортировать стек в виде массива\n3-Добавит в стек элемент\n4-Удалить последний элемент из стека\n5-Вывести стек\n6-Вывести адреса\n7-Изменить реализацию стека\n0-Выход");
	    printf("\nВыбор: ");
		free_stdin();
		if (!scanf("%d", &c))
	    {
		    printf("\nНекорректный ввод. Повторите.\n");
			c = -1;
	    }
        if (c > MENU || c < 0)
		    printf("\nНет такого пункта меню. Повторите.\n");
	}
	return c;
}

int main()
{
	setbuf(stdout, NULL);
	int c;
	unsigned long long ts, tf;
	list *l;
	list *del = NULL;
	array arr;
	int type = 0;
	free_stdin();
	while ((c = menu()))
	{
	free_stdin();
	switch (c)
	{
	    case 1:
		type = 1;
		printf("\nВведиет 1 стек\n");
		list *l1;
		input_list_stack(&l1);
		printf("\nВведиет 2 стек\n");
		list *l2;
		input_list_stack(&l2);
		ts = tick();
		l = sort_list(&l1, &l2);
		tf = tick();
		printf("\nОтсортированный стек:\n");
		print_list_stack(l);
		printf("\nВремя сортировки %I64d тактов\n", tf - ts);
	    break;
	    case 2:
		type = 2;
		printf("\nВведиет 1 стек\n");
		array arr1;
		input_array_stack(&arr1);
		printf("\nВведиет 2 стек\n");
		array arr2;
		input_array_stack(&arr2);
		ts = tick();
		arr = sort_array(&arr1, &arr2);
		tf = tick();
		printf("\nОтсортированный стек:\n");
		print_array_stack(arr);
		printf("\nВремя сортировки %I64d тактов\n", tf - ts);
	    break;
		case 3:
		if (type == 1)
			add_list(&l);
		else if (type == 2)
			add_array(&arr);
		else
			printf("\nСтек не инициализирован\n");
	    break;
		case 4:
		if (type == 1)
		{
			if (l)
			{
				push_list(&del, (long long) l);
				ts = tick();
			    pop_list(&l);
				tf = tick();
				printf("\nВремя удаления %I64d тактов\n", tf - ts);
			}
			else
				printf("\nСтек пуст.\n");
		}
		else if (type == 2)
		{
			if (arr.n)
			{
				ts = tick();
			    pop_array(&arr);
				tf = tick();
				printf("\nВремя удаления %I64d тактов\n", tf - ts);
			}
			else
				printf("\nСтек пуст.\n");
		}
		else
			printf("\nСтек не инициализирован\n");
	    break;
		case 5:
		if (type == 1)
		{
			if (l)
			    print_list_stack(l);
			else
				printf("\nСтек пуст.\n");
		}
		else if (type == 2)
		{
			if (arr.n)
			    print_array_stack(arr);
			else
				printf("\nСтек пуст.\n");
		}
		else
			printf("\nСтек не инициализирован\n");
	    break;
		case 6:
		if (type == 1)
			print_addres(l, del);
		else if (type == 2)
			printf("\nДля данного представления стека действее недоступно.\n");
		else
			printf("\nСтек не инициализирован\n");
	    break;
		case 7:
		if (type == 1)
		{
			from_list_to_array(&l, &arr);
			type = 2;
			del = NULL;
			printf("\nТеперь стек представлен в виде масива.\n");
		}
		else if (type == 2)
		{
			from_array_to_list(&l, &arr);
			type = 1;
			printf("\nТеперь стек представлен в виде списка.\n");
		}
		else
			printf("\nСтек не инициализирован\n");
	    break;
	}
	}
}