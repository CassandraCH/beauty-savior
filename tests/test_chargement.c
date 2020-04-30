#include <stdlib.h>
#include <stdio.h>



extern void ChargementCollider(const char * filename) 
{

    
    //Ouverture du fichier 
    FILE * file = fopen(filename, "r");
    
    //Gestion des erreurs d'ouverture du fichier
    if (file != NULL) 
       printf("Le test a reussi\n");   
    else
        printf("Le test a echoue\n");    



}



int main()
{

    ChargementCollider( "test.txt ");

    ChargementCollider( "test1.txt ");


    return 0;

}