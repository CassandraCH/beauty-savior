#include <stdlib.h>
#include <stdio.h>



extern void ChargementCollider(const char * filename) 
{

    
    //Ouverture du fichier 
    FILE * file = fopen(filename, "r");
    
    //Gestion des erreurs d'ouverture du fichier
    if (file == NULL) {
        fprintf(stderr, "Erreur avec le fichier\n");
        exit(1);    
    }



}



int main()
{



    return 0;

}