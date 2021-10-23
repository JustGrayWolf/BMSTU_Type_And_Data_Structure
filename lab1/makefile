FLAGS :=  -std=c99 -Wall -Werror -c
CC := gcc

main.exe : functions.o main.o
	$(CC) -o $@ $^

functions.o : functions.c struct.h
	$(CC) $(FLAGS) $< -o $@

main.o : main.c functions.h struct.h
	$(CC) $(FLAGS) $< -o $@