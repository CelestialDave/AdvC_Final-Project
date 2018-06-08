#include "declerations.h"

// createEmptyHistoryList(); creates an empty History List for Long Term History
void createEmptyHistoryList(HistoryList * hList) {
	HistoryEntry * dummyHead = createHistoryEntry(0, NULL, NULL, NULL);
	hList->tail = hList->head = dummyHead;
}

// isEmptyHistoryList(); checks whether or not a Long Term History List is empty
bool isEmptyHistoryList(HistoryList * hList) {
	return (hList->head->next == NULL);
}

// createHistoryEntry(); create a History List Node
HistoryEntry* createHistoryEntry(int order, char * command, HistoryEntry * prev, HistoryEntry * next) {
	HistoryEntry * newEntry = (HistoryEntry *)calloc(1, sizeof(HistoryEntry));
	newEntry->order = order;
	newEntry->command = command;
	newEntry->next = next;
	newEntry->prev = prev;
	return newEntry;
}

// insertToEndOfHistoryList(); receives a command and inserts it as a History Entry to the end of Long Term History List
void insertToEndOfHistoryList(Data * data, char * command) {
	int order = data->total - SHORT_TERM_SIZE;
	HistoryEntry * newEntry = createHistoryEntry(order, command, data->LongTerm_HistoryList.tail, NULL);
	data->LongTerm_HistoryList.tail->next = newEntry;
	data->LongTerm_HistoryList.tail = newEntry;
}

// insertToStartOfHistoryList(); receives a command and inserts it as a History Entry to the start of Long Term History List
//	used when loading history entries from file in program start.
void insertToStartOfHistoryList(Data * data, char * command) {
	int order = 0; // an init value
	HistoryEntry * nextEntry = data->LongTerm_HistoryList.head->next;
	HistoryEntry * newEntry = createHistoryEntry(order, command, data->LongTerm_HistoryList.head, nextEntry);
	data->LongTerm_HistoryList.head->next = newEntry;
	if (nextEntry == NULL) // Entering the 1st node to list
		data->LongTerm_HistoryList.tail = newEntry; // 1st entry will remain last in List
	else
		nextEntry->prev = newEntry;
}

// preDataLoaderPrep(); initializes program data before loading or any additional input
void preDataLoaderPrep(Data * data) {
	data->apartments = makeEmptyList();
	initShortTermArr(data->shortTerm_HistoryArr);
	createEmptyHistoryList(&data->LongTerm_HistoryList);
	data->total = 0;
	data->code = 1;
}

// initShortTermArr; initializes the Short Term History array values
void initShortTermArr(char * stArr[]) {
	for (int i = 0; i < SHORT_TERM_SIZE; i++)
		stArr[i] = NULL;
}

// executeFromHistory(); receives a pointer to the program data struct and a command number from history and executes the command
void executeFromHistory(Data * data, int commandNumber) {
	char * command = retrieveCommand(data, commandNumber);
	commander(data, command);
}

// substituteAndRun(); substitutes each str1 occurence in received command with str2, then executes the new command created
void substituteAndRun(Data * data, int commandNumber, char * str1, char * str2) {
	char * command = retrieveCommand(data, commandNumber);
	char * newCommand = substituteCommandParams(data, command, str1, str2);
	commander(data, newCommand);
}

// substituteCommandParams(); perform the string substitution for substituteAndRun()
char * substituteCommandParams(Data * data, char * command, char * str1, char * str2) {
	char * newCommand = NULL;
	int newCmdSize; // new command length var
	char * pNewCmd; // pointer for the beginning of newCommand
	int str1Size = (int)strlen(str1); // str1 length
	int str2Size = (int)strlen(str2); // str2 length
	int cmdSize = (int)strlen(command); // command received length
	bool isEqual = false; // bool var whether str1 & str2 length is equal
	int counter = 0; // counter of str1 occurences in received command
	char * p1 = command; // pointer to the beginning of received command
	char * p2 = str2; // pointer to the beginning of str2
	
	char * pStr1 = strstr(command, str1); // pointer for the start of str1 occurence in command

	if (str1Size == str2Size) { // both str1 & str2 length are the same
		// replace each char of str1 with str2's
		while (pStr1 != NULL) {
			isEqual = true;
			while (*p2) {
				*pStr1 = *p2;
				pStr1++; p2++;
			}
			p2 = str2; // go back to start of str2
			pStr1 = strstr(pStr1, str1); // get next occurence of str1
		}
		newCommand = command;
	}
	else { // str1 & str2 differ in length
		// count the number of occurences of str1 in command for memory allocation
		while (pStr1 != NULL) {
			counter++;
			pStr1 += str1Size; // skip past current str1 occurence
			pStr1 = strstr(pStr1, str1); // get next occurence of str1
		}
		// calculate new required size and allocate accordingly
		newCmdSize = cmdSize - (counter * str1Size) + (counter * str2Size);
		newCommand = (char *)calloc(newCmdSize + 1, sizeof(char));
		pNewCmd = newCommand;

		pStr1 = strstr(command, str1); // go to 1st str1 occurence in command
		while (pStr1 != NULL) {
			while (p1 < pStr1) { // copy from original command untill reaching str1 occurence
				*(pNewCmd++) = *(p1++);
			}

			while (*p2) { // copy str2 chars
				*(pNewCmd++) = *(p2++);
			}
			p2 = str2; // go back to start of str2
			p1 += str1Size; // skip past str1 occurence in command
			pStr1 = strstr(p1, str1); // get next occurence of str1
		}
		while (*p1) { // copy any chars left in original command
			*(pNewCmd++) = *(p1++);
		}
		free(command); // free memory of original command
	}

	// Free memory used by str1 & str2
	free(str1);
	free(str2);

	return newCommand;
}

// retrieveCommand(); retrieves command from history by number
char * retrieveCommand(Data * data, int commandNumber) {
	char * commandCopy = NULL;

	if (!isEmptyHistoryList(&data->LongTerm_HistoryList)) { // Long Term History List is not empty
		// commandNumber corelates with command in short-term:
		if ((commandNumber > (data->total - SHORT_TERM_SIZE)) && (commandNumber <= data->total)) {
			commandNumber = commandNumber - (data->total - SHORT_TERM_SIZE);
			copyString(&commandCopy, data->shortTerm_HistoryArr[SHORT_TERM_SIZE - commandNumber]);
		}
		// commandNumber corelates with command in long-term:
		else {
			HistoryEntry * p;
			p = data->LongTerm_HistoryList.head->next;
			while (p != NULL) {
				if (commandNumber == p->order) {
					copyString(&commandCopy, p->command);
					break;
				}
				p = p->next;
			}
		}
	}
	else { // Long History List is Empty; extract from Short Term History Array
		copyString(&commandCopy, data->shortTerm_HistoryArr[data->total - commandNumber]);
	}
	return commandCopy;
}

// addToArchive(); adds a received command string to History
void addToArchive(Data * data, char * command) {
	if (command != NULL) {
		int i; // short term array index
		int iLastSTHEntry; // index for the last Short Term History array entry
		bool isShortTermFull = false;
		char * tempCommand = NULL;

		if (data->shortTerm_HistoryArr[SHORT_TERM_SIZE - 1] != NULL) {
			isShortTermFull = true;
			i = SHORT_TERM_SIZE - 1; // i will point to last short term array position
		}
		else {
			isShortTermFull = false;
			for (i = 0; i <= SHORT_TERM_SIZE - 1; i++) {
				if (data->shortTerm_HistoryArr[i] == NULL)
					break; // have i pointing to 1st empty position in short term array
			}
		}
		iLastSTHEntry = (int)i;

		if (isShortTermFull) {
			tempCommand = data->shortTerm_HistoryArr[iLastSTHEntry]; // get the address of last command in short term history arr
		}
		for (i = iLastSTHEntry; i > 0; i--) { // swap address upwards in short term history arr
			data->shortTerm_HistoryArr[i] = data->shortTerm_HistoryArr[i - 1];
		}
		// i = 0: Adding current command to 1st position in Short Term History Array
		data->shortTerm_HistoryArr[i] = command;
		
		// Increment total history entries counter:
		if (iLastSTHEntry == 0) // if ShortTerm history was empty to begin with
			data->total = 1;
		else
			data->total++;

		if (isShortTermFull)
			insertToEndOfHistoryList(data, tempCommand);
	}
}

// archivePrinter(); Prints the history in archive by specified task (short_history / history (full))
void archivePrinter(Data * data, int task) {
	int i;
	HistoryEntry *p;
	if ((task == SHORT_HISTORY_PRINT) || (task == FULL_HISTORY_PRINT)) {
		if ((task == FULL_HISTORY_PRINT) && (!isEmptyHistoryList(&data->LongTerm_HistoryList))) {
			p = data->LongTerm_HistoryList.head->next;
			while (p != NULL) {
				printf("%d: %s\n", p->order, p->command);
				p = p->next;
			}
		}
		for (i = SHORT_TERM_SIZE - 1; i >= 0; i--) {
			if (data->shortTerm_HistoryArr[i] != NULL) {
				int order = data->total - i;
				if (data->shortTerm_HistoryArr[i] != NULL)
					printf("%d: %s\n", order, data->shortTerm_HistoryArr[i]);
				else
					break;
			}
		}
	} 
	else {
		return;
	}
}
