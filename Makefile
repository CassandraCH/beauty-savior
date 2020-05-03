
include Makefile.compilation


EXEC= game.exe
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)



clean:
	del src\*.o 

mrproper: clean
	del $(EXEC)

run:
	$(EXEC) 



