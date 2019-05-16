

#ifndef his_structs
#define his_structs

#define SHORT_TERM_SIZE 7
#define SHORT_HISTORY_PRINT 4
#define FULL_HISTORY_PRINT 5

#define RUN_LAST 1
#define RUN_COMMAND_NUM 2
#define SUBSTITUTE 3

// Files:
#define FILE_HISTORY "history.txt"
#define FILE_APARTMENTS "Apartments.bin"

typedef unsigned char byte;

typedef struct date {
	short int day;
	short int month;
	short int year;
	int hours;
}Date;

typedef struct apartment {
	int code;
	char* adress;
	short int rooms;
	int price;
	Date date;
	Date dbDate;
	struct apartment* next;
}Apartment;

typedef struct list {
	Apartment* head;
	Apartment* tail;
}List;


// History List Node:
typedef struct history_entry {
	int order;
	char * command;
	struct history_entry * next;
	struct history_entry * prev;
}HistoryEntry;

// History List:
typedef struct history_list {
	HistoryEntry * head;
	HistoryEntry * tail;
}HistoryList;

// Data struct that envelopes all program data that requires access during program life-cycle.
typedef struct data {
	List apartments;
	char* shortTerm_HistoryArr[SHORT_TERM_SIZE];
	HistoryList LongTerm_HistoryList;
	int total;
	int code;
}Data;

#endif