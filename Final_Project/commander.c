#include "declerations.h"
void commander(History_Data* hData, char* command) {
	List apartments;
	int getSize;
	int price = -1;
	int minRooms = -1;
	int maxRooms = -1;
	int sort = 0; // 1 for sr 2 for s 0 for nothing
	apartments = makeEmptyList();
	char recognize;
	recognize = recognizeCommand(command);
	switch (recognize) {
	case 'g':
		analizeParametersForGet(&price, &minRooms, &maxRooms, &command, &sort);
		getAnApt(price,minRooms,maxRooms,sort,command, apartments);
		break;
	case 'b':
		break;
	case 'd':
		break;
	case 'a':
		addAnApt(&command, &apartments);
		break;
	case 's':
		archivePrinter(&hData, SHORT_HISTORY_PRINT);
		break;
	case 'h':
		archivePrinter(&hData, FULL_HISTORY_PRINT);
		break;
	case '!':
		archiveQuery(&hData, &command);
		break;
	default:
		return -1;
	}
}
char recognizeCommand(char* command) {

	char* res;
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
}
char* getCommand() {
	char* command;
	char input;
	int phSize;
	int logSize;
	command = NULL;
	logSize = 0;
	phSize = 5;
	scanf("%c", &input);
	if (input != '\n') {
		command = malloc(phSize * sizeof(char));
		command[logSize++] = input;
		scanf("%c", &input);
	}
	while (input != '\n') {
		if (logSize == phSize) {
			phSize *= 2;
			command = realloc(command, phSize * (sizeof(char)));
		}
		command[logSize++] = input;
		scanf("%c", &input);
	}
	command[logSize] = '\0';
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