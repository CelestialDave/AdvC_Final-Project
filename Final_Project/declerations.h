#include "apartment.h"
#include <stdio.h>
#include <stdbool.h>
void addAnApt(char** command, List* list);
List makeEmptyList();
void insertDataToEndList(List* lst, int code, char* adress, short int rooms, int price, Date date, Apartment* next);
Apartment* createApartment(int code, char* adress, short int rooms, int price, Date date, Apartment* next);
bool isEmpty(List lst);
void insertNodeToTail(List* lst, Apartment* node);
void buyAnApt(List lst, int code);
void analizeParametersForGet(int* price, int* minRooms, int* maxRooms, char** command, int* sort);
Apartment** getAnApt(int price, int minRooms, int maxRooms, int sort, List apartments, int* size);
bool conditionsAreMet(int price, int minRooms, int maxRooms, Apartment* apt);
char recognizeCommand(char* command);
char* getCommand();
void printAptsArr(Apartment** arr, int size);