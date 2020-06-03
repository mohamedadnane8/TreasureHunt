#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"Map.h"
#include"game.h"
int score = 0;
// These functions are used to change the color of the output
void red () {
  printf("\033[3;31m");
}

void yellow (){
  printf("\033[3;33m");
}
void green (){
  printf("\033[1;32m");
}

void reset () {
  printf("\033[0m");
}
// this function checks if the room is visited or not.
int Visited(Room* theRoom){
    return theRoom->visited == 0;
}
//this function add score of traveling to the player's score
void addScore(Road* theRoad){
    score += theRoad->target->score;
    score += theRoad->score;
    theRoad->target->score = theRoad->score = 0;
}
//this function is used to insert treasure in a linked list.
Treasure* addTreasure(Treasure* head,Treasure* toAdd){
    Treasure *current;
    if(head == NULL)
        return toAdd;
    for(current = head; 
       current->next != NULL;
       current = current->next);

    current->next = toAdd;
    return head;
    
}
//this function is used to display items that exist in a room
void DisplayItems(Treasure* walker){
    if(walker == NULL)
        return;
    printf("You see: ");
    green();
    while(walker != NULL){
        printf("%s\t", walker->treasure);
        walker = walker->next;
    }
    reset();
    printf("\n");

}

// this function is used to display the correct description
void DisplayDescription(Room* theRoom){
    if(Visited(theRoom))
        printf("%s",theRoom->shortDescription);
    else{
        theRoom->visited = 0;
        yellow();
        printf("%s",theRoom->longDescription);
        reset();
    }
}
// this function is used to move from a room to another
Room* move(Room* theRoom,char* direction){
    for(int i = 0;i < theRoom->numRoads ;i++)
        if(strcmp(theRoom->roaddirection[i]->name,direction) == 0){
            //display the long or short description
            addScore(theRoom->roaddirection[i]);

            theRoom = theRoom->roaddirection[i]->target;
            return theRoom;
        }
    printf("I don’t know how to go %s\n",direction);
    return theRoom;

}
//this function is used to delete a node from a linkedlist of treasures 
Treasure* TakeFromListItems(Treasure** head,char*name){
    Treasure*pre,*w=*head;
    if(*head == NULL)
        return NULL;
    if(strcmp((*head)->treasure,name)==0){
        *head=(*head)->next;
        w->next = NULL;
        return w;
    }
    for(;w!=NULL&&strcmp(w->treasure,name)!=0;pre=w,w=w->next);
    if(w==NULL)
        return NULL;
    pre->next=w->next;
    w->next = NULL;
    return w;
}
// this function is used when the player drops an item 
// from his bag to the room 
// the player earn score only if he droped it in the first place.
void Drop(Room* theRoom,char* item){
    Treasure* toDrop = NULL;
    //Delete item from myTreasures list.
    toDrop = TakeFromListItems(&myTreasures,item);
    //the item was not found
    if(toDrop == NULL)
        printf("You don't have %s in your bag\n",item);
    else{
        //item Found, now we throw it in the room
        theRoom->treasures = addTreasure(theRoom->treasures,toDrop);
        //check the place where he droped the item.
        green();
        printf("\t =>You have have droped in the beginning. Thus, you earned %d\n",toDrop->valueReturn);
        reset();
        if(strcmp (theRoom->roomName,theMap.room[0].roomName)==0){
            score += toDrop->valueReturn;
            toDrop->valueReturn = 0;
        }
        printf("You have droped %s\n",item);
    }
}
//this function prints the long description
void Look(Room* theRoom){
    printf("%s",theRoom->longDescription);
}
//this function prints a guide for the user
void Help(){
    char c = '"';
    printf("I will help you explore the world and find treasures. You must find all of the treasures and bring them back to the beginning.");
    printf("You can tell me instructions like");
    red();

    printf(" %cgo%c, %clook%c, %ctake%c, %cdrop%c, %cscore%c, and %cbag%c.\n",c,c,c,c,c,c,c,c,c,c,c,c);
    reset();
}
//this function is used to check whether the player won or not.
int Continue(){
    return score < maxScore;
}
// this function takes a treasure from a room and put it in the player's bag
void Take(Room* theRoom,char* item){
    Treasure* theItem = NULL;
    theItem = TakeFromListItems(&(theRoom->treasures),item);
    if(theItem != NULL){
        score += theItem->valueTake;
        green();
        printf("\t=>You have gained %d from taking %s\n",theItem->valueTake,theItem->treasure);
        reset();
        theItem->valueTake = 0;
        myTreasures = addTreasure(myTreasures,theItem);
    }else printf("%s does not exist in %s\n",item,theRoom->roomName);
}
//this function displays a score.
void DisplayScore(){
    if((score/2) >maxScore){
        red();
    printf("Try even harder, You have only earned %d out of %d points.\n",score,maxScore);

    }else {
        green();
        printf("You are almost there. \nYou have earned %d out of %d points.\n",score,maxScore);
    }
    reset();
}
// this function displays the description and the the items in the room
void DisplayLocation(Room* theRoom){
    DisplayDescription(theRoom);
    Bag();
    DisplayItems(theRoom->treasures);

}
// this function prints the treasures that the player have.
void Bag(){
    Treasure* walker = myTreasures;
    if(myTreasures == NULL){
        red();
        printf("Your Bag is empty go discover!\n");
        reset();
        return;
    }printf("Your bag: ");
    green();
    while(walker !=NULL){
    printf("%s\t",walker->treasure);
    walker = walker->next;
    }
    reset();
    printf("\n");

}