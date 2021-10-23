FLAGS :=  -std=c99 -Wall -Werror -c
CC := gcc

main.exe : functions.o sort.o main.o
	$(CC) -o $@ $^

functions.o : functions.c struct.h functions.h
	$(CC) $(FLAGS) $< -o $@

main.o : main.c functions.h struct.h
	$(CC) $(FLAGS) $< -o $@
	
sort.o : sort.c functions.h struct.h
	$(CC) $(FLAGS) $< -o $@