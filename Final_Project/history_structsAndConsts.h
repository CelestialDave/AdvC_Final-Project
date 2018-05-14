

#ifndef his_structs
#define his_structs
#define SHORT_TERM_SIZE 7

#define ADD 0
#define RUN_LAST 1
#define RUN_COMMAND_NUM 2
#define SUBSTITUTE 3

#define FILE_HISTORY_SHORT_TERM "shortTermArchive.out"
#define FILE_HISTORY_LONG_TERM "longTermArchive.out"

typedef struct history_entry {
	int order;
	char * command;
	struct history_entry * next;
	struct history_entry * prev;
}HistoryEntry;

typedef struct history_list {
	HistoryEntry * head;
	HistoryEntry * tail;
}HistoryList;

typedef struct history_data {
	char* shortTerm_HistoryArr[SHORT_TERM_SIZE];
	HistoryList LongTerm_HistoryList;
}History_Data;
#endif