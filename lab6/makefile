FLAGS :=  -std=c99 -Wall -Werror -c
CC := gcc

go: app.exe
	./app.exe

app.exe : main.o tree.c hash.c file.c menu.c
	$(CC) -o $@ $^

tree.o : tree.c
	$(CC) $(FLAGS) $< -o $@

hash.o : hash.c
	$(CC) $(FLAGS) $< -o $@
	
file.o : file.c
	$(CC) $(FLAGS) $< -o $@	
	
menu.o : menu.c
	$(CC) $(FLAGS) $< -o $@

main.o : main.c
	$(CC) $(FLAGS) $< -o $@

clear:
	rm *.o
	rm *.exe