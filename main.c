#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "difLvl.c"

int displayFiled(char **field); //prints out the map of the field
int combine(char answer, int answer1); //combines user input and field numeration
int Randomizer(int **mineArray); //generates random mine map
int difficulty();
int playGame();

int main(){

    playGame();

    system("PAUSE");

    return 0;
}

int Randomizer(int **mineArray){

    int i, j;
    srand(time(NULL));
    int mines;
    int placeMine;
    int totalMines;
    int difLvl=difficulty();

    for(i=0, totalMines=0; i<10; i++){
        for(j=0, mines=0; j<10 && mines<difLvl; j++){
            placeMine= rand() % 2;
            mineArray[i][j] = placeMine;
            if(placeMine==1){
                ++mines;
            };
        };
        totalMines+=mines;
    };

    return totalMines;
}

int displayFiled(char **field){

    int i, j;

    printf("    A B C D E F G H I J\n");
    printf("   --------------------\n");
    for (i=0; i<10; i++){
            if (i==9){
                printf("%d |", i+1);
            }else{
                printf("%d  |", i+1);
            };
        for (j=0; j<10; j++){
            printf("%c ", field[i][j]);
            if (j==9){
                printf("\n");
                };
        };
    };
    printf("\n");

    return 0;
}

int playGame(){

    char Y_char=NULL;//column //answer
    int X_user=NULL;//user entered row
    int X; //row //answer1
    int Y; //answer converted to a number //answer2
    int **mineArray; //stores the map of mines
    char **fieldDisplay; //prints out the map of the field
    int i, j, k; //counters
    int life=1;
    int movePl=0; //no dying on the first move
    int globalMines; //number of mines placed
    int openedFields=0; //counts the number of fields opened

    system("cls");

    /*Allocates memory to mineArray*/
    mineArray = calloc(10, sizeof(*mineArray));
        for (i = 0; i < 10; i++) {
    mineArray[i] = calloc(10, sizeof(*mineArray[i]));
}


    /*Allocates memory to fieldDisplay*/
    fieldDisplay= calloc(10, sizeof(int*));
    for(i = 0; i < 10; i++){
		fieldDisplay[i] = calloc(10, sizeof(int));
    };

    /*default look of fields with ?*/
    for (i=0; i<10; i++){
        for (j=0; j<10; j++){
            fieldDisplay[i][j]='?';
        };
    };

    globalMines= Randomizer(mineArray);

    while(life==1 && openedFields<(100-globalMines)){

        /*for checking purposes only*/
        /*for (i=0; i<10; i++){
            for (j=0; j<10; j++){
                printf("%d ", mineArray[i][j]);
            if (j==9){
                printf("\n");
                };
            };
        };*/

        //printf("\nDifficulty level %d\n", difLvl
        while(1){
            printf("Total number of mines is %d\n\n", globalMines);
            printf("\tMove nr. %d\n\n", movePl+1);
            printf("Selected field- Column:%c Row:%d\n\n", Y_char, X_user);
            displayFiled(fieldDisplay);

            printf("Which field do You want to activate?\nType first the letter, space and then the number (A 1, B 10 etc.)\n");
            scanf(" %c %d", &Y_char, &X_user);
            if (Y_char >= 'A' && Y_char <= 'J'){
                Y = Y_char - 'A';
                break;
            }else if(Y_char >= 'a' && Y_char <= 'j'){
                Y = Y_char - 'a';
                break;
            }else{
                system("cls");
                printf("-----------------------------");
                printf("\nOnly use letters from A to J!\n");
                printf("-----------------------------\n\n");
            };
        };
        //makes 1 to 0
        X=X_user-1;
        /*checks if field is a mine*/
        if (mineArray[X][Y]==0 && fieldDisplay[X][Y]=='?'){
            movePl++;
            fieldDisplay[X][Y]='0';
            openedFields=openedFields+1;
OPEN:
            for (i=0;((X-i)<10 && (X-i)>=0) && mineArray[X-i][Y]!= 1; i++){
                fieldDisplay[X-i][Y]='0';
                openedFields=openedFields+1;
                for (j=1;((Y+j)<10 && (Y+j)>=0) && mineArray[X-i][Y+j]!= 1; j++){
                    fieldDisplay[X-i][Y+j]='0';
                    openedFields=openedFields+1;
                };
                for (j=1;((Y-j)<10 && (Y-j)>=0) && mineArray[X-i][Y-j]!= 1; j++){
                    fieldDisplay[X-i][Y-j]='0';
                    openedFields=openedFields+1;
                };
            };

            for (i=0;((X+i)<10 && (X+i)>=0) && mineArray[X+i][Y]!= 1; i++){
                fieldDisplay[X+i][Y]='0';
                openedFields=openedFields+1;
                for (k=1;((Y+k)<10 && (Y+k)>=0) && mineArray[X+i][Y+k]!= 1; k++){
                    fieldDisplay[X+i][Y+k]='0';
                    openedFields=openedFields+1;
                };
                for (k=1;((Y-k)<10 && (Y-k)>=0) && mineArray[X+i][Y-k]!= 1; k++){
                    fieldDisplay[X+i][Y-k]='0';
                    openedFields=openedFields+1;
                };
            };

            system("cls"); //clears console screen

        }else if (mineArray[X][Y]==0 && fieldDisplay[X][Y]=='0'){
            system("cls");
            printf("You can't choose an already opened field!\n\n");

        }else if(mineArray[X][Y]==1 && movePl==0){
            movePl++;
            mineArray[X][Y]= 0;
            fieldDisplay[X][Y]='0';
            globalMines=globalMines-1;
            goto OPEN;
            system("cls");

        }else{
            system("cls");
            printf("YOU DIED ! YOU DIED ! YOU DIED !\n\n");
            printf("Moves successfully made: %d\n\n", movePl-1);
            fieldDisplay[X][Y]='1';
            displayFiled(fieldDisplay);
            --life;
        };
    };

    if(openedFields==(100-globalMines)){
        printf("Congratulations! You won the game!\n\n");
        displayFiled(fieldDisplay);
    };

    for(i = 0; i < 10; i++){
		free(mineArray[i]);
    };
    free(mineArray);

    for(i = 0; i < 10; i++){
		free(fieldDisplay[i]);
    };
    free(fieldDisplay);



    return 0;

}
