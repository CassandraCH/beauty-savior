
include Makefile.compilation


EXEC= game
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean_linux:
	rm src/*.o 

clean_win: 
	del src\*.o

run:
	$(EXEC) 



