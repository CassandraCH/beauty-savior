include Makefile.compilation

#
# Objets
#
fich_test_player = test_player.o 
fich_test_niveau = test_niveau.o
fich_test_chargement = test_chargement.o



#
# Tests (executables+objets)
#

BIN = test_player \
	  fich_test_niveau \
	  fich_test_chargement \

test_player : $(fich_test_player) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_test_player) -o test_player 

test_player.o : test_player.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_player.c -o test_player.o -I./ 


test_niveau : $(fich_test_niveau) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_test_niveau) -o test_niveau 

test_niveau.o : test_niveau.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_niveau.c -o test_niveau.o -I./ 


test_chargement : $(fich_test_chargement) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_test_chargement) -o test_chargement 

test_chargement.o : test_chargement.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_chargement.c -o test_chargement.o -I./ 

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
	del  *.o
	del *.exe

