CC=gcc
CFLAGS= -Iinclude/ -Wall -O 
LDFLAGS=  -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 
EXEC=prog.exe
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	del -f *.o core

mrproper: clean
	del -f $(EXEC)

run:
	$(EXEC) 
