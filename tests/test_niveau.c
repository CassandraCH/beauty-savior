#include <stdlib.h>
#include <stdio.h>



void Set_Level(int niveau) 
{

    if( niveau == 1 || niveau == 2 || niveau == 3 || niveau == 4 )
        printf("Le test a reussi\n");
    else 
        printf("Le test a echoue\n");

}

void Level_Textures_Render(int niveau)
{
    if( niveau == 0 || niveau == 1 || niveau == 2 || niveau == 3 )
        printf("Le test a reussi\n");
    else 
        printf("Le test a echoue\n");
}


int main()
{

    Set_Level(1);
    Set_Level(3);
    Set_Level('a');
    Set_Level(5.5);
    Set_Level(-3);

    Level_Textures_Render( 4 );


    return 0;

}