#define _CRT_SECURE_NO_WARNINGS
#include "apartment.h"
#include "history_structsAndConsts.h"
#include <stdio.h>
#include <stdbool.h>
void addAnApt(char** command, List* list);
List makeEmptyList();
void insertDataToEndList(List* lst, int code, char* adress, short int rooms, int price, EntryDate date, Apartment* next);
Apartment* createApartment(int code, char* adress, short int rooms, int price, EntryDate date, Apartment* next);
bool isEmpty(List lst);
void insertNodeToTail(List* lst, Apartment* node);
void buyAnApt(List lst, int code);
void analizeParametersForGet(int* price, int* minRooms, int* maxRooms, char** command, int* sort);
void getAnApt(int price, int minRooms, int maxRooms, int sort, char* command, List apartments);
bool conditionsAreMet(int price, int minRooms, int maxRooms, Apartment* apt);
char recognizeCommand(char* command);
char* getCommand();
void printAptsArrLowToHigh(Apartment** arr, int size);
void printAptsArrHighToLow(Apartment** arr, int size);


HistoryEntry * createHistoryEntry(int order, char * command, HistoryEntry * prev, HistoryEntry * next);
void createEmptyHistoryList(HistoryList * hList);
bool isEmptyHistoryList(HistoryList * hList);
void insertToStartOfHistoryList(HistoryList * hList, char * command);
void archiveQuery(History_Data * hData, char ** command);
int clasifyQueryTaskParams(char * command, int * commandNumber, char ** str1, char ** str2);
void copyString(char ** dest, char * source);
void executeFromHistory(History_Data * hData, int commandNumber);
void substituteAndRun(History_Data * hData, int commandNumber, char * str1, char * str2);
char * substituteCommandParams(History_Data * hData, char * command, char * str1, char * str2);
char * retrieveCommand(History_Data * hData, int commandNumber);
void addToArchive(History_Data * hData, char * command);
void archivePrinter(History_Data * hData, int task);
#define arc_print_params
#define SHORT_HISTORY_PRINT 4
#define FULL_HISTORY_PRINT 5