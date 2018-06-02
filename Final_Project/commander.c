#include "declerations.h"

void commander(History_Data* data, char* command) {

	List apartments = data->apartments;
	int hours; // parameter for delte-an-apt
	int price = -1; // parameter for get-an-apt
	int minRooms = -1; //parameter for get-an-apt
	int maxRooms = -1;//parameter for get-an-apt
	int sort = 0; // parameter for get-an-apt 1 for sr 2 for s 0 for nothing
	char recognize;
	recognize = recognizeCommand(command);
	switch (recognize) {
	case 'g':
		analizeParametersForGet(&price, &minRooms, &maxRooms, &command, &sort);
		getAnApt(price,minRooms,maxRooms,sort,command, apartments);
		addToArchive(data, command);
		break;
	case 'b':
		// MISSING //
		addToArchive(data, command);
		//data->apartments = apartments;
		break;
	case 'd':
		analizeParametersForDelete(&hours, &command);
		deleteAnApt(&apartments, hours);
		data->apartments = apartments;
		addToArchive(data, command);
		break;
	case 'a':
		addAnApt(&command, &apartments);
		data->apartments = apartments;
		addToArchive(data, command);
		break;
	case 's':
		archivePrinter(data, SHORT_HISTORY_PRINT);
		addToArchive(data, command);
		break;
	case 'h':
		archivePrinter(data, FULL_HISTORY_PRINT);
		addToArchive(data, command);
		break;
	case '!':
		archiveQuery(data, &command);
		break;
	default:
		return;
	}
}
void analizeParametersForDelete(int* hours, char** command) {
	char* copy;
	int res;
	char* delimeters = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz<>-";
	copy = malloc(strlen(*command) * sizeof(char));
	strcpy(copy, *command);
	res = 24 * atoi(strtok(*command, delimeters));
	*hours = res;
	*command = copy;
}

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

void analizeParametersForGet(int* price, int* minRooms, int* maxRooms, char** command, int* sort) {
	char* copy;
	char* subCommand;
	char* abc = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-";
	char* digits = "-1234567890 ";
	copy = malloc(strlen(*command) * sizeof(char));
	strcpy(copy, *command);
	subCommand = strtok(*command, digits);
	while (subCommand != NULL) {
		if (strcmp(subCommand, "MinimumNumRooms") == 0) {
			*minRooms = atoi(subCommand = strtok(NULL, abc));
		}
		if (strcmp(subCommand, "MaximumNumRooms") == 0) {
			*maxRooms = atoi(subCommand = strtok(NULL, abc));
		}
		if (strcmp(subCommand, "MaximumPrice") == 0) {
			*price = atoi(subCommand = strtok(NULL, abc));
		}
		if (strcmp(subCommand, "sr") == 0) {
			*sort = 1;
		}
		if ((strcmp(subCommand, "s") == 0)) {
			*sort = 2;
		}
		subCommand = strtok(NULL, digits);
	}
	*command = copy;
}

/////////////////////////////////
// History related functions:
////////////////////////////////

void archiveQuery(History_Data * hData, char ** command) {
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

void copyString(char ** dest, char * source) {
	int size = (int)strlen(source);
	*dest = (char *)calloc(size + 1, sizeof(char));
	strcpy(*dest, source);
}