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

void insertToStartOfHistoryList(HistoryList * hList, char * command) {
	HistoryEntry * newEntry = createHistoryEntry(SHORT_TERM_SIZE + 1, command, hList->head, hList->head->next);
	HistoryEntry * p;
	hList->head->next->prev = newEntry;
	hList->head->next = newEntry;
	p = newEntry->next;
	// increment the order number for the rest of the History List entries:
	while (p != NULL) {
		p->order++;
	}
}

//void archiveManagerAgent(char ** command) {
void archiveQuery(History_Data * hData, char ** command) { // move to commander
														   //FILE * shortTermArch;
														   //FILE * longTermArch;
	int commandNumber = -1;
	char *str1, *str2;
	str1 = str2 = NULL;
	int task;

	char * tempCommand;
	copyString(&tempCommand, (*command + 1)); // send address following first char of '!'

	task = clasifyQueryTaskParams(tempCommand, &commandNumber, &str1, &str2);

	switch (task) {
	case RUN_LAST:
		executeFromHistory(hData, 1);
		break;
	case RUN_COMMAND_NUM:
		executeFromHistory(hData, commandNumber);
		break;
	case SUBSTITUTE:
		if ((str1 != NULL) && (str2 != NULL)) {
			substituteAndRun(hData, commandNumber, str1, str2);
			break;
		}
	default:
		return;
		break;
	}

}


int clasifyQueryTaskParams(char * command, int * commandNumber, char ** str1, char ** str2) {
	char *string1, *string2;
	string1 = string2 = NULL;
	if (command[0] == '!') {
		return RUN_LAST;
	}
	else {
		char * data = strtok(command, "^");
		if (data == NULL) { // Received only a number past the '!' char - no string to substitute
			sscanf(command, "%d", commandNumber);
			if (*commandNumber >= 1)
				return RUN_COMMAND_NUM;
			else
				return -1;
		}
		else {
			string1 = (char *)calloc(strlen(data), sizeof(char));
			copyString(&string1, data);
			data = strtok(NULL, "^");
			if (data != NULL) {
				string2 = (char *)calloc(strlen(data), sizeof(char));
				copyString(&string2, data);
			}
			*str1 = string1;
			*str2 = string2;
			return SUBSTITUTE;
		}
	}
}

void copyString(char ** dest, char * source) {
	*dest = (char *)calloc(strlen(source), sizeof(char));
	char * pDest = *dest;
	while (*source) {
		*pDest = *source;
		source++;
		pDest++;
	}
	*pDest = '\0';
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
	return newCommand;
}

char * retrieveCommand(History_Data * hData, int commandNumber) {
	char * commandCopy = NULL;
	if ((commandNumber >= 1) && (commandNumber <= SHORT_TERM_SIZE)) { // in short-term history
		return (hData->shortTerm_HistoryArr[commandNumber - 1]);
	}
	else if (commandNumber > SHORT_TERM_SIZE) { // in long-term history list
		if (!isEmptyHistoryList(&hData->LongTerm_HistoryList)) {
			HistoryEntry * entry = hData->LongTerm_HistoryList.head->next;
			while (entry != NULL) {
				if (entry->order == commandNumber) {
					copyString(&commandCopy, entry->command);
					break;
				}
				else {
					entry = entry->next;
				}
			}
		}
		else {
			return NULL;
		}
	}
	else {
		return NULL;
	}
	return commandCopy;
}

void addToArchive(History_Data * hData, char * command) {
	// Add logic for when short term arr is not full + replace copies with pointer swappimg
	if (command != NULL) {
		int i;
		char * tempCommand = NULL;
		copyString(&tempCommand, hData->shortTerm_HistoryArr[SHORT_TERM_SIZE - 1]);
		// Missing check for short-term array!!!!
		insertToStartOfHistoryList(&hData->LongTerm_HistoryList, tempCommand);

		for (i = SHORT_TERM_SIZE - 1; i > 0; i--) {
			free(hData->shortTerm_HistoryArr[i]);
			hData->shortTerm_HistoryArr[i] = NULL;
			copyString(&hData->shortTerm_HistoryArr[i], hData->shortTerm_HistoryArr[i - 1]);
		}
		// i = 0;
		hData->shortTerm_HistoryArr[i] = command;
	}
}
// (!) INCOMPLETE:
void archivePrinter(History_Data * hData, int task) {
	if (task == SHORT_HISTORY_PRINT) {

	}
	else if (task == FULL_HISTORY_PRINT) {

	}
	else {
		return;
	}
}