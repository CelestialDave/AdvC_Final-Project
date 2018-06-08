#define _CRT_SECURE_NO_WARNINGS

// General Libraries:
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
// Program Libraries:
#include "dataLoader_header.h"
#include "structsAndDefinitions.h"

// General Funcs:
void copyString(char ** dest, char * source);
void preDataLoaderPrep(Data * hData);
void allocStr(char ** str, int * phS, int logS, int isFinished);

// Commander:
void commander(Data* hData, char* command);
char recognizeCommand(char* command);
char* getCommand();

// Apartment Funcs:
bool isEmpty(List lst);
List makeEmptyList();
Apartment* createApartment(int code, char* adress, short int rooms, int price, Date sDate, Date date, Apartment* next);
void insertDataToEndList(List* lst, int code, char* adress, short int rooms, int price, Date sDate, Date date, Apartment* next);
void insertNodeToTail(List* lst, Apartment* node);
void addAnApt(char** command, List* list, int* code);
void buyAnApt(List* lst, int code);
int analizeCodeForBuy(char* command);
void getAnApt(int price, int minRooms, int maxRooms, short int day, short int month, short int year, int sort, char* command, List apartments);
void analizeParametersForGet(int* price, int* minRooms, int* maxRooms, short int* day, short int* month, short int* year, char** command, int* sort);
bool conditionsAreMet(int maxPrice, int minRooms, int maxRooms, short int day, short int month, short int year, Apartment* apt);
void printAptsArrLowToHigh(Apartment** arr, int size);
void printAptsArrHighToLow(Apartment** arr, int size);
void mergeSortApts(Apartment** arr, int size);
void sortedMerge(Apartment** arr1, int size1, Apartment** arr2, int size2, Apartment** res);
void deleteAnApt(List* list, int hours);
void analizeParametersForDelete(int* hours, char** command);

// History funcs:
bool isEmptyHistoryList(HistoryList * hList);
HistoryEntry * createHistoryEntry(int order, char * command, HistoryEntry * prev, HistoryEntry * next);
void createEmptyHistoryList(HistoryList * hList);
void insertToEndOfHistoryList(Data * hData, char * command);
void insertToStartOfHistoryList(Data * hData, char * command);
void initShortTermArr(char * stArr[]);
void addToArchive(Data * hData, char * command);
void archiveQuery(Data * hData, char ** command);
int clasifyQueryTaskParams(char * command, int * commandNumber, char ** str1, char ** str2);
char * retrieveCommand(Data * hData, int commandNumber);
void executeFromHistory(Data * hData, int commandNumber);
void substituteAndRun(Data * hData, int commandNumber, char * str1, char * str2);
char * substituteCommandParams(Data * hData, char * command, char * str1, char * str2);
void archivePrinter(Data * hData, int task);

// Read Data:
void readDataFromFiles(Data * data);
void readApartments(List * apartments);
long int fileSize(char * filename);
void readHistory(Data * data);
void applyHListOrder(HistoryList hList, int total);

// Write Data:
void writeDataToFiles(Data data);
void writeApartments(List apartments);
void writeCompressedData(Apartment* apt, FILE* file);
void writeHistory(int total, char ** shortTerm_HistoryArr, HistoryList LongTerm_HistoryList);

// Free Data:
void freeData(Data * data);
void freeApt(Apartment ** apt);
void freeApartments(List * apartments);
void freeHistoryData(Data * hData);
void freeShortTermHisArr(char ** shortTermArr);
void freeHistoryList(HistoryList * hList);

