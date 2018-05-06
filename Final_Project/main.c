#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "apartment.h"
#include <stdbool.h>

int main() {
	//get-an-apt -MinimumNumRooms 3 -MaximumNumRooms 10
	char* command = NULL;
	List apartments;
	char recognize;
	int price = -1;
	int minRooms = -1;
	int maxRooms = -1;
	int sort = 0; // 1 for sr 2 for s 0 for nothing
	int getSize; // the size of getList
	Apartment** get; // list of get apartments
	command = getCommand();
	while (strcmp(command, "exit") != 0) {
		recognize = recognizeCommand(command);
		switch (recognize) {
		case 'g':
			analizeParametersForGet(&price, &minRooms, &maxRooms, &command, &sort);
			get = getAnApt(price, minRooms, maxRooms,sort, apartments, &getSize);
			printAptsArr(get);//////
			break;
		case 'b':
			break;
		case 'd':
			break;
		case 'a':
			break;
		}
		command = getCommand();
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
			realloc(command, phSize);
		}
		command[logSize++] = input;
		scanf("%c", &input);
	}
	command[logSize] = '\0';
	return command;
}
