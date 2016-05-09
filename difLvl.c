#include <stdio.h>
#include <stdlib.h>

int difficulty(){

    int difLvl;

    while(1){
        printf("Please choose a difficulty level:\n");
        printf("Easy-1\nNormal-2\nNightmare-3\n");
        printf("Your answer: ");
        scanf(" %d", &difLvl);
        if(difLvl>=1 && difLvl<=3){
            break;
        }else{
            system("cls");
            continue;
        };
    };
    system("cls");
    return difLvl;
}
