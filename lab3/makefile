FLAGS :=  -std=c99 -Werror -c
CC := gcc

app.exe : $(OUTDIR)input_output.o $(OUTDIR)matrix.o $(OUTDIR)menu.o $(OUTDIR)main.o
	$(CC) -o $@ $^

$(OUTDIR)matrix.o : $(APPDIR)matrix.c
	$(CC) $(FLAGS) $^ -o $@

$(OUTDIR)main.o : $(APPDIR)main.c $(LIBDIR)matrix.h $(LIBDIR)input_output.h
	$(CC) $(FLAGS) $< -o $@

$(OUTDIR)input_output.o : $(APPDIR)input_output.c
	$(CC) $(FLAGS) $^ -o $@

$(OUTDIR)menu.o : $(CHKDIR)menu.c 
	$(CC) $(FLAGS) $< -o $@

statistic : app.exe
	./app.exe
	3
	10 10 1
	3
	
