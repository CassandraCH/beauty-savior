include Makefile.compilation

#
# Objets
#
fich_test_player=test_player.o 
fich_test_niveau=test_niveau.o




#
# Tests (executables+objets)
#

BIN = test_player \
	  fich_test_niveau \

test_player : $(fich_test_player) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_test_player) -o test_player 

test_player.o : test_player.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_player.c -o test_player.o -I./ 


test_niveau : $(fich_test_niveau) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_test_niveau) -o test_niveau 

test_niveau.o : test_niveau.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_niveau.c -o test_niveau.o -I./ 




#
# Modules
#

#
# Headers 
#

#
#
#

all : $(BIN) $(OBJ)

clean :
	- rm  *.o

tests :
	./adressage_indirect
	

dist : 
	- rm  Cours_1_Pointeurs.tar.gz
	tar cvfz Cours_1_Pointeurs.tar.gz cours_pointeurs.pdf *.c Makefile Makefile.compilation copie.h	
