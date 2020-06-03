#include<stdio.h>
#include"Map.h"
#include<string.h>
#include<stdlib.h>
#include"game.h"

void lowerCase(char*);
//this function changes the color of the output

void greenMain (){
    printf("\033[1;32m");
}
//this function rests the color of the output
void resetMain () {
    printf("\033[0m");
}
int main(){
    // I can also use 2 scanfs and buffer.
    char order1[30],order2[30],ans[60];
    char str[60];
    int flag = 1;
    Room * theRoom;
    fillMap();
    myTreasures = NULL;
    theRoom = &(theMap.room[0]);
    do{
        //this to print the location and its desciption if it was not visited 
        if(flag == 1)
            DisplayLocation(theRoom);
        flag = 1;
        fgets(str, 60, stdin); 
        sscanf(str,"%s",order1);
        lowerCase(order1);
        if(strcmp(order1,"look") == 0){
            //print the description
            flag = 0;
            Look(theRoom);
        }else if(strcmp(order1,"go") == 0){
            // traverse.
            sscanf(str,"%s %s",order1,order2);
            lowerCase(order2);
            theRoom = move(theRoom, order2);
        }else if(strcmp(order1,"drop") == 0){
            sscanf(str,"%s %s",order1,order2);
            lowerCase(order2);
            Drop(theRoom,order2);
        }else if(strcmp(order1,"take") == 0){
            sscanf(str,"%s %s",order1,order2);
            lowerCase(order2);       
            Take(theRoom,order2);
        }else if (strcmp(order1,"score") == 0){
            DisplayScore();
        }else if(strcmp(order1,"help") == 0){
            Help();
        }else if(strcmp(order1,"bag") == 0){
            Bag();
        }else printf("Sorry, I do not know how to %s",order1);

    }while(Continue());
    greenMain();
    printf("\nCongratulations! You won!\n");
    resetMain();

    return 0;
}