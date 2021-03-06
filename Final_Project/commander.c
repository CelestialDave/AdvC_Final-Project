#include "declerations.h"

// a function that gets a command, analizes it, and initiates it
void commander(Data* data, char* command) {
	if (command == "") return;

	List apartments = data->apartments;
	int hours; // parameter for delte-an-apt
	int price = -1; // parameter for get-an-apt
	int minRooms = -1; //parameter for get-an-apt
	int maxRooms = -1;//parameter for get-an-apt
	short int day = -1;
	short int month = -1;
	short int year = -1;
	int sort = 0; // parameter for get-an-apt 1 for sr 2 for s 0 for nothing
	char recognize;
	int code;
	recognize = recognizeCommand(command);
	switch (recognize) {
	case 'g':
		analizeParametersForGet(&price, &minRooms, &maxRooms, &day, &month, &year, &command, &sort);
		getAnApt(price, minRooms, maxRooms, day, month, year, sort, command, apartments);
		addToArchive(data, command);
		break;
	case 'b':
		code = analizeCodeForBuy(command);
		buyAnApt(&data->apartments,code);
		addToArchive(data, command);
		break;
	case 'd':
		analizeParametersForDelete(&hours, &command);
		deleteAnApt(&apartments, hours);
		data->apartments = apartments;
		addToArchive(data, command);
		break;
	case 'a':
		addAnApt(&command, &apartments,&data->code);
		data->apartments = apartments;
		addToArchive(data, command);
		break;
	case 's':
		archivePrinter(data, SHORT_HISTORY_PRINT);
		break;
	case 'h':
		archivePrinter(data, FULL_HISTORY_PRINT);
		break;
	case '!':
		archiveQuery(data, &command);
		break;
	default:
		return;
	}
}

// a function that analizes parameters from a buy-an-apt-command
int analizeCodeForBuy(char* command) {

	int res = 0;
	int read = 0;
	while (command[read] != '\0') {
		if (command[read] >= '0' && command[read] <= '9') {
			res *= 10;
			res += command[read] - '0';
		}
		read++;
	}
	return res;
}

// a function that analizes parameters from a delete-an-apt-command
void analizeParametersForDelete(int* hours, char** command) {
	char* copy = NULL;
	int res;
	char* delimeters = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz<>-";
	copyString(&copy, *command);
	res = 24 * atoi(strtok(copy, delimeters));
	*hours = res;
	free(copy);
}

// a function that recognizes the command that was entered by the user
char recognizeCommand(char* command) {

	char* res;

	if (command[0] == '!')
		return '!';
	if (strcmp(command, "short_history") == 0)
		return 's';
	if (strcmp(command, "history") == 0)
		return 'h';

	res = strtok(command, "-");
	if (strcmp(res, "get") == 0) {
		res[strlen(res)] = '-';
		return 'g';
	}
	if (strcmp(res, "buy") == 0) {
		res[strlen(res)] = '-';
		return 'b';
	}
	if (strcmp(res, "delete") == 0) {
		res[strlen(res)] = '-';
		return 'd';
	}
	if (strcmp(res, "add") == 0) {
		res[strlen(res)] = '-';
		return 'a';
	}
	else
		return '0';
}

// a function that gets a command of unknown length from the user
char* getCommand() {
	char* command;
	char input;
	int phSize;
	int logSize;
	command = NULL;
	logSize = 0;
	phSize = 5;
	printf(">> ");
	scanf("%c", &input);
	if (input != '\n') {
		command = (char *)malloc(phSize * sizeof(char));
		command[logSize++] = input;
		scanf("%c", &input);
	}
	else {
		return "";
	}
	while (input != '\n') {
		if (logSize == phSize) {
			phSize *= 2;
			command = (char *)realloc(command, phSize * (sizeof(char)));
		}
		command[logSize++] = input;
		scanf("%c", &input);
	}
	if (logSize == phSize) {
		phSize++;
		command = (char *)realloc(command, phSize * (sizeof(char)));
	}
	command[logSize++] = '\0';
	if (logSize < phSize)
		command = (char *)realloc(command, logSize * (sizeof(char)));
	return command;
}

// a function that analizes parameters from a get-an-apt-command
void analizeParametersForGet(int* price, int* minRooms, int* maxRooms, short int* day, short int* month, short int* year, char** command, int* sort) {
	char* copy = NULL;
	char* subCommand;
	char* abc = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-";
	char* digits = " -1234567890";
	int rawDate;
	// breaking down the command to the search parameters
	copyString(&copy, *command);
	subCommand = strtok(copy, digits);
	while (subCommand != NULL) {
		if (strcmp(subCommand, "MinimumNumRooms") == 0) {
			*minRooms = atoi(subCommand = strtok(NULL, abc));
		}
		else if (strcmp(subCommand, "MaximumNumRooms") == 0) {
			*maxRooms = atoi(subCommand = strtok(NULL, abc));
		}
		else if (strcmp(subCommand, "MaximumPrice") == 0) {
			*price = atoi(subCommand = strtok(NULL, abc));
		}
		else if (strcmp(subCommand, "Date") == 0) {
			subCommand = strtok(NULL, abc);
			rawDate = atoi(subCommand);
			*year = (rawDate % 10000) % 100;
			rawDate /= 10000;
			*month = rawDate % 100;
			rawDate /= 100;
			*day = rawDate % 100;
		}
		else if (strcmp(subCommand, "sr") == 0) {
			*sort = 1;
		}
		else if ((strcmp(subCommand, "s") == 0)) {
			*sort = 2;
		}
		subCommand = strtok(NULL, digits);
	}
	free(copy);
}

// -------------------------------
// History related functions:

// archiveQuery(); receives a history query command (starting with '!' char) and executes it accordingly
void archiveQuery(Data * hData, char ** command) {
	int commandNumber = -1;
	char *str1, *str2;
	str1 = str2 = NULL;
	int task;

	char * tempCommand;
	copyString(&tempCommand, (*command + 1)); // send address following first char of '!'

	task = clasifyQueryTaskParams(tempCommand, &commandNumber, &str1, &str2);
	switch (task) {
	case RUN_LAST:
		executeFromHistory(hData, hData->total);
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

// clasifyQueryTaskParams(); returns the type of task required by archiveQuery() by the content of query received
int clasifyQueryTaskParams(char * command, int * commandNumber, char ** str1, char ** str2) {
	char *p;
	char *string1, *string2;
	bool subStrRequired = false;
	string1 = string2 = NULL;
	if (command[0] == '!') {
		return RUN_LAST;
	}
	else {
		p = command;
		while (*p) {
			if (*p == '^') {
				subStrRequired = true;
				break;
			}
			p++;
		}
		
		if (subStrRequired) {
			char * data = strtok(command, "^");
			*commandNumber = atoi(data);
			data = strtok(NULL, "^");
			if (data != NULL) {
				string1 = (char *)calloc(strlen(data), sizeof(char));
				copyString(&string1, data);

				data = strtok(NULL, "^");
				if (data != NULL) {
					string2 = (char *)calloc(strlen(data), sizeof(char));
					copyString(&string2, data);
				}
			}
			*str1 = string1;
			*str2 = string2;
			return SUBSTITUTE;
		}
		else {
			sscanf(command, "%d", commandNumber);
			if (*commandNumber >= 1)
				return RUN_COMMAND_NUM;
			else
				return -1;
		}
	}
}


// -----------------------
//	General Functions:

// allocStr(); manages string (char *) memory allocations
void allocStr(char ** str, int * phS, int logS, int isFinished) {
	if (isFinished == 0) {
		if (*phS == 0) {
			*phS = 1;
			*str = (char *)calloc(*phS + 1, sizeof(char));
			(*str)[*phS] = '\0';
		}
		else if (logS == *phS) {
			*phS *= 2;
			*str = (char *)realloc(*str, (*phS + 1)* sizeof(char));
			(*str)[*phS] = '\0';
		}
	}
	else if (isFinished == 1) {
		if (logS < *phS) {
			*str = (char *)realloc(*str, (logS + 1) * sizeof(char));
			(*str)[logS] = '\0';
			*phS = logS;
		}
	}
}

// copyString(); handles memory allocations and copying of strings (char *)
void copyString(char ** dest, char * source) {
	int size = (int)strlen(source);
	*dest = (char *)calloc(size + 1, sizeof(char));
	strcpy(*dest, source);
}