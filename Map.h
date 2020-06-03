// These are the structures for the treasure hunt.
#include <stdio.h>

typedef struct l Room;
typedef struct r Road;
typedef struct m Map;
typedef struct t Treasure;
//Nodes
struct  l{
	char roomName[20];
    // 0 if visited otherwise the score that the user will gain if he/she visited the room
    short visited;  
    short score;  
    char *shortDescription,*longDescription;
    //Linked list of treasures
	Treasure *treasures;
    //Edges
	Road* roaddirection[40];
    short numRoads;
};
//Edges
struct r{
    short score;
    char name[20];
    Room* target;
};
//Graph
struct m{
    Room room[40];
    short numRooms;
};
// linked list
struct t {
	char *treasure;
	int valueTake;
    int valueReturn;
	Treasure *next;
};

// To make a global variable visible in multiple files, declare it
// as 'exernal'. It still needs to be declared normally in one of 
// the program files.
Treasure *myTreasures;
Map theMap;
int maxScore;


void fillMap();



