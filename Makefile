
include Makefile.compilation


SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


run_linux:
	./$(EXEC) 


clean_linux:
	rm src/*.o 


run_win:
	$(EXEC) 


clean_win: 
	del src\*.o
