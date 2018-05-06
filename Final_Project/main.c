#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "apartment.h"
#include <stdbool.h>

char* getCommand();
void analizeParameters(int*, int*, int*, char**);
char recognizeCommand(char*);
int main() {
	//get-an-apt -MinimumNumRooms 3 -MaximumNumRooms 10
	char* command = NULL;
	char recognize;
	int price = -1;
	int minRooms = -1;
	int maxRooms = -1;
	command = getCommand();
	while (strcmp(command, "exit") != 0) {
		recognize = recognizeCommand(command);
		switch (recognize) {
		case 'g':
			analizeParameters(&price,&minRooms,&maxRooms,&command);
			//invokeGet(price, minRooms, maxRooms);
			break;
		case 'b':
			break;
		case 'd':
			break;

		}
	}
}
void analizeParameters(int* price, int* minRooms, int* maxRooms, char** command) {
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
		if (strcmp(subCommand, "MaxmumPrice") == 0) {
			*price = atoi(subCommand = strtok(NULL, abc));
		}
		subCommand = strtok(NULL, digits);
	}
	*command = copy;
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
			realloc(command, phSize);
		}
		command[logSize++] = input;
		scanf("%c", &input);
	}
	command[logSize] = '\0';
	return command;
}
