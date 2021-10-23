#include <stdio.h>
#include <string.h>
#define OK 0
#define DIV_BY_ZERO 1
#define INCORRECT_INPUT 2
#define DIGIT "0123456789"
#define ZNAK "+-"
#define MAXINT 30
#define MAXFLOAT 30
#define MAXE 5
#define OVERFLOW 3

struct my_float
{
	char digit[34];
	long long e;
};