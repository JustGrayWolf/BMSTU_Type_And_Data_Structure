#include "struct.h"

int compere(char *ch1, char *ch2)
{
    int res = 0;
    int i = 0;
    while (ch1[i] != 10 && ch2[i] != 10)
    {
        if (ch1[i] > ch2[i])
        {
            res = 1;
            break;
        }
        else if (ch1[i] < ch2[i])
        {
            break;
        }
    i++;
    }
    if (ch2[i] == 10)
        res = 1;
    else if (ch1[i] == 10 && (i > 0)) 
    {
        res = 1;
        while (ch2[i] != 10)
        {
            if (!ch2[i])
                res = 0;
            i++;
        }
    }
    
    return res;
}

void minus(char *ch1, char *ch2)
{
    int i = 0;
    while (ch2[i] != 10 && i < 31)
    {
        if ((ch2[i] > ch1[i] || ch1[i] == 10) && ch2[i])
        {
            int j = i - 1;
            while (ch1[j] == 0)
                j--;
            ch1[j] -= 1;
            j++;
            while (j != i)
            {
                ch1[j] = 9;
                j++;
            }
            ch1[i] = ch1[i] == 10 ? 10 - ch2[i] : ch1[i] + 10 - ch2[i];
        }
        else
            ch1[i] -= ch2[i];
        i++;
    }
}

int shift(char **ch1, char **ch2)
{
    if (**ch1 == 0)
    {
        *ch1 += 1;
        if (**ch2 == 0)
        {
            *ch2 += 1;
            return 0;
        }
    }
    else
        if (**ch2 != 0)
            *ch2 -= 1;
    return 1;
}

int division(char **delim, char **delit, char *result, long long *e)
{
    result[1] = 0;
    int err = OK;
    int sh;
    int countshift = 0;
    result[1] = 0;
    result[2] = 10;
    while (countshift < 31)
        if (compere(*delim, *delit))
        {
            minus(*delim, *delit);
            (result[countshift + 1])++;
        }
        else
        {
            sh = shift(delim, delit);
            if (countshift == 0 && result[1] == 0)
                (*e)--;
            else if (sh)
            {
                countshift++;
                result[countshift + 1] = 0;
                result[countshift + 2] = 10;
            }
        }
    return err;
}

int input_int(char *c, int *zn)
{
    char cr;
    int i = 0;
    *zn = 0;
    printf("Введите целое число не превышающее 30 знаков:\n");
	printf("123456789012345678901234567890\n");
    while (i <= MAXINT + 1 && (cr = getc(stdin)) != '\n' && (strchr(DIGIT, cr) != NULL ||\
    (i == 0 && strchr(ZNAK, cr) != NULL)))
    {
        if (i == 0 && strchr(ZNAK, cr) == NULL)
        {
            c[i] = '+';
            i++;
        }
        if (strchr(DIGIT, cr) != NULL)
        {
            c[i] = (cr - 48);
        }
        else 
            c[0] = cr;
        if (!(i == 1 && !c[i]))
        {
            i++;
            if (strchr(DIGIT, cr) != NULL)
                (*zn)++;
        }
    }
    if (cr == '\n')
        return OK;
    else
        return INCORRECT_INPUT;
}    

int input_float(char *c, long long *e)
{
    char cr;
    int dot = 0;
    int i = 1;
    int zn = 0;
    c[1] = 0;
    c[2] = 0;
    printf("\nВведите вещественное число в формате n.mEs (n+m<=30 s<=5):\n");
	printf("123456789012345678901234567890\n");
    while (i <= MAXINT + 2 && (cr = getc(stdin))!= '\n' && (strchr(DIGIT, cr) != NULL ||\
    (i == 1 && strchr(ZNAK, cr) != NULL) || (!dot && cr == '.')))
    {
        if (i == 1 && strchr(ZNAK, cr) == NULL)
        {
            c[0] = '+';
            i++;
        }
        if (strchr(DIGIT, cr) != NULL)
            c[i] = (cr - 48);
        else if (cr == '.')
        {
            dot = 1;
        }
        else
            c[0] = cr;
        if (!(i == 2 && !c[i]) && cr != '.')
        {
            i++;
            if (!dot && strchr(DIGIT, cr) != NULL)
                zn++;
        }
        else if (dot && cr != '.')
            zn--;
        
    }
    if ((cr == 'e' || cr == 'E') && scanf("%I64d", e) && (-100000 < *e) && (*e < 100000))
    {
        *e += zn - 1;
        return OK;
    }
    else
        return INCORRECT_INPUT;
}

void correct_result(char *res, char *c1, char *c2, long long *e)
{
    if ((c1[0] == '-' && c2[0] == '+') || (c1[0] == '+' && c2[0] == '-'))
        res[0] = '-';
    else
        res[0] = '+';
    int i;
    if (res[31] >= 5)
    {
        (res[30])++;
        i = 30;
        while (res[i] == 10 && i > 1)
        {
            res[i] = 0;
            (res[i - 1])++;
            i--;
        }
        if (res[1] == 10)
        {
            res[1] = 1;
            (*e)++;
        }
    }
    i = 30;
    while (res[i] == 0)
    {
        res[i] = 10;
        i--    ;
    }
}

void print_result(char *res, long long e)
{
    printf("Результат деления: %c0.", res[0]);
    for (int i = 1; i < MAXINT + 1 && res[i] < 10; i++)
        printf("%c", DIGIT[(int) res[i]]);
    printf("E%I64d", e);
}