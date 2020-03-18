CC=gcc
CFLAGS= -Iincludes/ -Wfatal-errors -O 
LDFLAGS=  -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 
EXEC=dog.exe
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
	del -f $(EXEC)

run:
	$(EXEC) 




#-lSDL2main \
#	-lSDL2_image \
#	-lSDL2_ttf \
#~ 	-lSDL2_mixer \
#~ 	-lSDL2 
