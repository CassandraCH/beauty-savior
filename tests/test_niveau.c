#include <stdlib.h>
#include <stdio.h>



extern void setNiveau(int niveau) 
{
   //getPlayer()->niveau = niveau;
    if( niveau == 1 || niveau == 2 || niveau == 3 || niveau == 4 )
        printf("Le test a reussi\n");
    else 
        printf("Le test a echoue\n");

}


int main()
{


    


    return 0;