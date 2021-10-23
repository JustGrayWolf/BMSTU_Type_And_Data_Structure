#include <stdio.h>
#include "defines.h"
#include "func.h"

int main(void)
{
	setbuf(stdout, NULL);
    int ifrom, ito;
    FILE *f = fopen(FILENAME, "r");
    if (!f)
    {
        printf("Файл не найден!\n");
        return 0;
    }
    unsigned long long t1, t2;

    int menu = 0, flag = 1;
    int k_mat = 0;

    matrix_t *graph = read_matrix(f);
    if (graph == NULL)
    {
        return 0;
    }

    int ver[graph->size];

    while (flag)
    {
        printf(" МЕНЮ: \n");
        printf(" 1) Показать граф\n");
        printf(" 2) Показать входные данные\n");
        printf(" 3) Найти путь с минимальным S+P\n");
        printf(" 0) Выйти\n");
        printf(" Выбор: ");

        menu = scan_choise();
        switch (menu)
        {
            case 1:
                output_graph_to_png(graph);
                break;
            case 2:
                print_matrix(stdout, graph);
                break;
            case 3:
                printf("Введите начальную и конечную точки через пробел: ");
                scanf("%d%d", &ifrom, &ito);
                if (ifrom < 0 || ito < 0 || ifrom > graph->size - 1 || ito > graph->size - 1)
                {
                    printf("Неверный ввод.\n");
                }
				t1 = tick();
				int res = deiksrt(graph, ifrom, ito, ver, &k_mat);
                t2 = tick();
                printf("Время: %d тактов\n", (int) (t2 - t1));
                printf("Память: %lu Байт\n\n", sizeof(int) * graph->size * graph->size * 2 + sizeof(unsigned int));
				if (res == 0)
                    output_got_to_png(graph, ver, k_mat, ito);
				break;
            case 0:
                flag = 0;
                break;
            default:
                printf("\nНеверный пункт меню!\n\n");
                break;
        }
    }

    free_matrix(graph);
    //free_matrix(best);
    fclose(f);
    return 0;
}
