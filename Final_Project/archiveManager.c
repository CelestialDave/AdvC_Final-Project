#include "declerations.h"

HistoryEntry* createHistoryEntry(int order, char * command, HistoryEntry * prev, HistoryEntry * next) {
	HistoryEntry * newEntry = (HistoryEntry *)calloc(1, sizeof(HistoryEntry));
	newEntry->order = order;
	newEntry->command = command;
	newEntry->next = next;
	newEntry->prev = prev;
	return newEntry;
}

void createEmptyHistoryList(HistoryList * hList) {
	HistoryEntry * dummyHead = createHistoryEntry(0, NULL, NULL, NULL);
	hList->tail = hList->head = dummyHead;
}

bool isEmptyHistoryList(HistoryList * hList) {
	return (hList->head->next == NULL);
}

void historyDataPreLoaderPrep(History_Data * hData) {
	initShortTermArr(hData->shortTerm_HistoryArr);
	createEmptyHistoryList(&hData->LongTerm_HistoryList);
	hData->total = 0;
}

void initShortTermArr(char * stArr[]) {
	for (int i = 0; i < SHORT_TERM_SIZE; i++)
		stArr[i] = NULL;
}

void insertToEndOfHistoryList(History_Data * hData, char * command) {
	int order = hData->total - SHORT_TERM_SIZE;
	HistoryEntry * newEntry = createHistoryEntry(order, command, hData->LongTerm_HistoryList.tail, NULL);
	hData->LongTerm_HistoryList.tail->next = newEntry;
	hData->LongTerm_HistoryList.tail = newEntry;
}


void executeFromHistory(History_Data * hData, int commandNumber) {
	char * command = retrieveCommand(hData, commandNumber);
	commander(hData, command);
}

void substituteAndRun(History_Data * hData, int commandNumber, char * str1, char * str2) {
	char * command = retrieveCommand(hData, commandNumber);
	char * newCommand = substituteCommandParams(hData, command, str1, str2);
	commander(hData, newCommand);
}

char * substituteCommandParams(History_Data * hData, char * command, char * str1, char * str2) {
	char * newCommand;
	int newCmdSize;
	int str1Size = (int)strlen(str1);
	int str2Size = (int)strlen(str2);
	int cmdSize = (int)strlen(command);
	char * p1 = strstr(command, str1);

	if (p1 == NULL)
		return NULL;

	char * p2 = str2;
	newCmdSize = cmdSize - str1Size + str2Size;
	if (newCmdSize == cmdSize) {
		while (*p2) {
			*p1 = *p2;
			p1++; p2++;
		}
		newCommand = command;
	}
	else {// (newCmdSize != cmdSize) {
		newCommand = (char *)calloc(newCmdSize + 1, sizeof(char));
		*p1 = '\0';
		strcpy(newCommand, command);
		*p1 = str1[0];
		strcat(newCommand, str2);
		int i = (int)(p1 - command) + str2Size; // newCommand index
		p1 = p1 + str1Size; // move pointer past str1 in 'command'
		// complete string leftovers:
		while (*p1) {
			newCommand[i++] = *p1;
			p1++;
		}
		newCommand[i] = '\0';
		free(command);
	}
	free(str1);
	free(str2);
	return newCommand;
}

char * retrieveCommand(History_Data * hData, int commandNumber) {
	char * commandCopy = NULL;

	if (!isEmptyHistoryList(&hData->LongTerm_HistoryList)) {
		// commandNumber corelates with command in short-term:
		if ((commandNumber > (hData->total - SHORT_TERM_SIZE)) && (commandNumber <= hData->total)) {
			commandNumber = commandNumber - (hData->total - SHORT_TERM_SIZE);
			copyString(&commandCopy, hData->shortTerm_HistoryArr[SHORT_TERM_SIZE - commandNumber]);
		}
		// commandNumber corelates with command in long-term:
		else {
			HistoryEntry * p;
			p = hData->LongTerm_HistoryList.head->next;
			while (p != NULL) {
				if (commandNumber == p->order) {
					copyString(&commandCopy, p->command);
					break;
				}
				p = p->next;
			}
		}
	}
	else {
		copyString(&commandCopy, hData->shortTerm_HistoryArr[hData->total - commandNumber]);
	}
	return commandCopy;
}

void addToArchive(History_Data * hData, char * command) {
	if (command != NULL) {
		int i;
		int iLastSTHEntry;
		bool isShortTermFull = false;
		char * tempCommand = NULL;
		if (hData->shortTerm_HistoryArr[SHORT_TERM_SIZE - 1] != NULL) {
			isShortTermFull = true;
			i = SHORT_TERM_SIZE - 1;
			copyString(&tempCommand, hData->shortTerm_HistoryArr[i]);
		}
		else {
			isShortTermFull = false;
			for (i = 0; i <= SHORT_TERM_SIZE - 1; i++) {
				if (hData->shortTerm_HistoryArr[i] == NULL)
					break;
			}
		}
		iLastSTHEntry = (int)i;

		if (isShortTermFull) {
			free(hData->shortTerm_HistoryArr[iLastSTHEntry]); // Free the memory for the command string in last ShortTerm History array cell
			hData->shortTerm_HistoryArr[iLastSTHEntry] = NULL;
		}
		for (i = iLastSTHEntry; i > 0; i--) {
			hData->shortTerm_HistoryArr[i] = hData->shortTerm_HistoryArr[i - 1];
		}
		// When i = 0:
		hData->shortTerm_HistoryArr[i] = command;
		
		// Increment total history entries counter:
		if (iLastSTHEntry == 0) // if ShortTerm history was empty to begin with
			hData->total = 1;
		else
			hData->total++;

		if (isShortTermFull)
			insertToEndOfHistoryList(hData, tempCommand);
	}
}

void archivePrinter(History_Data * hData, int task) {
	int i;
	HistoryEntry *p;
	if ((task == SHORT_HISTORY_PRINT) || (task == FULL_HISTORY_PRINT)) {
		if ((task == FULL_HISTORY_PRINT) && (!isEmptyHistoryList(&hData->LongTerm_HistoryList))) {
			p = hData->LongTerm_HistoryList.head->next;
			while (p != NULL) {
				printf("%d: %s\n", p->order, p->command);
				p = p->next;
			}
		}
		for (i = SHORT_TERM_SIZE - 1; i >= 0; i--) {
			if (hData->shortTerm_HistoryArr[i] != NULL) {
				int order = hData->total - i;
				if (hData->shortTerm_HistoryArr[i] != NULL)
					printf("%d: %s\n", order, hData->shortTerm_HistoryArr[i]);
				else
					break;
			}
		}
	}
	else {
		return;
	}
}

void freeHistoryData(History_Data * hData) {
	freeShortTermHisArr(hData->shortTerm_HistoryArr);
	freeHistoryList(&hData->LongTerm_HistoryList);
	return;
}

void freeShortTermHisArr(char ** shortTermArr) {
	int i;
	for (i = SHORT_TERM_SIZE - 1; i >= 0; i--) {
		if (shortTermArr[i] != NULL)
			free(shortTermArr[i]);
	}
}

void freeHistoryList(HistoryList * hList) {
	HistoryEntry * p = hList->tail;
	HistoryEntry *  temp;
	while (p != NULL) {
		if (p->command != NULL)
			free(p->command);
		temp = p;
		p = p->prev;
		free(temp);
	}
}