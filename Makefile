
include Makefile.compilation


SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


run_linux:
	./bin/$(EXEC) 


clean_linux:
	rm src/*.o 


run_win:
	bin\$(EXEC) 


clean_win: 
	del src\*.o
