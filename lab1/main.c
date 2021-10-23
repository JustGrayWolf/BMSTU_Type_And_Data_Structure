#include "functions.h"
#include "struct.h"

int main()
{
    setbuf(stdout, NULL);
    printf("Программа деления целого числа на вещественное.\n");
    int zn;
    struct my_float ch1;
    for (int i = 0; i < 32; i++)
        ch1.digit[i] = 10;
    char *delitel = ch1.digit + 2;
    char ch2[96];
    for (int i = 0; i < 96; i++)
        ch2[i] = 10;
    char *delimoe = ch2 + 1;
    struct my_float result;
    if (!input_int(ch2, &zn) && !input_float(ch1.digit, &ch1.e))
    {
        if (!*delitel)
        {
            printf("Попытка деления на 0!");
            return DIV_BY_ZERO;
        }
        else if (!*delimoe)
            printf("Результат деления: 0");
        else
        {
            result.e = zn - ch1.e;
            division(&delimoe, &delitel, result.digit, &result.e);
            correct_result(result.digit, ch2, ch1.digit, &result.e);
            if ((-100000 < result.e) && (result.e < 100000))
                print_result(result.digit, result.e);
            else
            {
                printf("Переполнение");
                return OVERFLOW;
            }
        }
    }
    else
    {
        printf("Ввод не соответствует формату");
        return INCORRECT_INPUT;
    }
    return OK;
}