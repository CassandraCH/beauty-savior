#include <stdlib.h>
#include <stdio.h>



void setNiveau(int niveau) 
{

    if( niveau == 1 || niveau == 2 || niveau == 3 || niveau == 4 )
        printf("Le test a reussi\n");
    else 
        printf("Le test a echoue\n");

}

void afficher_textures_niveau(int niveau)
{
    if( niveau == 0 || niveau == 1 || niveau == 2 || niveau == 3 )
        printf("Le test a reussi\n");
    else 
        printf("Le test a echoue\n");
}


int main()
{

    setNiveau(1);
    setNiveau(3);
    setNiveau('a');
    setNiveau(5.5);
    setNiveau(-3);

    afficher_textures_niveau( 4 );


    return 0;

}