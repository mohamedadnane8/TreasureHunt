//this file is to create the graph.
//Using edge list adjacency implementation

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"Map.h"
char str[400];
FILE* infp;
// this function is used to transform all capital letters 
void lowerCase(char* str){
    for(int i = 0;i<strlen(str);i++)
        str[i] = tolower(str[i]);
}
// this function remove any * or ) that exist in a string 
// since we were not able to do it using sscanf
void cleanstr(char* arr){
    for(int i = 0;i<strlen(arr);i++){
        if(arr[i] == ')' || arr[i] == '*')
            arr[i] = '\0';
    }
}
// this function returns the index of a room
int SearchRoom(char* name){
    for(int i = 0;i<theMap.numRooms;i++)
        if(strcmp(theMap.room[i].roomName,name) == 0)
            return i;
    return -1;
}

//this function creates an edge between to rooms.
void addRoad(int start, int destination) {
	Room *startNode = &theMap.room[start];
	Room *destNode = &theMap.room[destination];
    startNode->roaddirection[startNode->numRoads] = (Road*) malloc(sizeof(Road));
	startNode->roaddirection[startNode->numRoads]->target = destNode;
	startNode->numRoads++;
}
//this function reads the edges(lines that start with '(')
//and create them
//It takes as imput the index of the room that we are filling.
void fillEdgeName(int i){
    int index,value;
    char name[30], direction[30];
    //fgets the line
    while(str[0] == '('){
        // seperate its element
        //fix the sscanf
        sscanf(str,"(%s %s %d",direction,name,&value);
        // remove the )
        cleanstr(direction);
        lowerCase(direction);
        lowerCase(name);
        // search if we already have that name in the array.
        index = SearchRoom(name);
        if(index == -1){
            //we dont have it so we add it
            index = theMap.numRooms;
            theMap.numRooms++;
            strcpy(theMap.room[index].roomName,name);
        }
        //create the edge. btween the two rooms.
        addRoad(i,index);
        maxScore += value;
        theMap.room[i].roaddirection[(theMap.room[i].numRoads)-1]->score = value;
        //add the direction
        strcpy(theMap.room[i].roaddirection[(theMap.room[i].numRoads)-1]->name,direction);
        fgets(str,200,infp);
    }
}
// this function create a treasure.
Treasure* createNodeTreasure(){
    int tempValueBef,tempValueAft;
    char tempName[15];

    Treasure* tempTreasure = (Treasure*)malloc(sizeof(Treasure));    

    sscanf(str,"*%s %d %d",tempName,&tempValueBef,&tempValueAft);

    cleanstr(tempName);
    lowerCase(tempName);
                  
    tempTreasure->treasure = (char *)malloc(sizeof(char)*(strlen(tempName)+1)); 
    strcpy(tempTreasure->treasure,tempName);

    tempTreasure->valueTake = tempValueBef;
    maxScore += tempValueBef;
 
    tempTreasure->valueReturn = tempValueAft; 
    maxScore += tempValueAft;

    tempTreasure->next = NULL;   
    return tempTreasure;
}
//this function creates the linked list of treasures.
Treasure* fillTreasure(){
    Treasure* headerTreasure = NULL,* w_Treasure;
    while(str[0] == '*'){
        if(headerTreasure == NULL){//No linked list.
            headerTreasure = createNodeTreasure();
            w_Treasure = headerTreasure;
        }else{
            w_Treasure->next = createNodeTreasure();
            w_Treasure = w_Treasure->next;
        }
        //getting the next sentence
        if(!feof(infp))
            fgets(str,200,infp);
        else break;

    }
    return headerTreasure;
}
//this functions fills the descriptions
void fillDescription(int position){
    char longDescriptionTemp[400];
    longDescriptionTemp[0] = '\0';
    //fgets the short description of the room
    theMap.room[position].shortDescription = (char*)malloc(sizeof(char)*(strlen(str)+1));
    strcpy(theMap.room[position].shortDescription,str);

    fgets(str,200,infp);
    while((str[0] <= 'z' && str[0] >= 'a') || (str[0] <= 'Z' && str[0] >= 'A')){
        strcmp(theMap.room[position].shortDescription,str);
        strcat(longDescriptionTemp,str);
        fgets(str,200,infp);

    }
    theMap.room[position].longDescription = (char*)malloc(sizeof(char)*(strlen(longDescriptionTemp)+1));
    strcpy(theMap.room[position].longDescription,longDescriptionTemp);

}
// this function fills the name of the vertex
// and return its position
int fillName(){
    char name[30];
    int value,position;

    sscanf(str,"%s %d",name,&value);
    position = SearchRoom(name);
    
    if(position == -1){
        position = theMap.numRooms;
        theMap.numRooms++;
        strcpy(theMap.room[position].roomName,name);
    }
    theMap.room[position].score = value;
    theMap.room[position].visited = 1;

    maxScore += value;
    fgets(str,100,infp);
    return position;   
}
// this function creates a vertex
void createNode(){
    int index,position;
    // check if this room already exist or not
    //if not we add it.
    position = fillName();
    //create the roads in the matrix and fill the name of the road that are available for that room
    //fills both the short and long description
    fillDescription(position);
    fillEdgeName(position);

    //fill the treasures.
    theMap.room[position].treasures = fillTreasure();
}

//this function fills theMap (the graph)
void fillMap(){
    int rooms = 0;
    maxScore = 0;
    infp = fopen("Map.txt","r");

    fscanf(infp,"%d\n",&rooms);
        fgets(str,100,infp);

    for(int i = 0;i<rooms;i++){
        createNode();
    }
    fclose(infp);
}
