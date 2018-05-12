#define _CRT_SECURE_NO_WARNINGS
#include "declerations.h"
int main() {
	/*add-an-apt "Dizengoff 180 Tel Aviv" 2000000 4 28 09 16
add-an-apt "Rothschild 67 Rishon Le Zion" 1700000 3 03 10 16
add-an-apt "Ben Gurion 25 Herzliya" 2200000 5 01 08 16
add-an-apt "Gordon 85 Holon" 1500000 3 15 06 17
get-an-apt –MinimumNumRooms 3 –MaximumNumRooms 5 –MaximumPrice 1750000*/

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
	apartments = makeEmptyList();
	while (strcmp(command, "exit") != 0) {
		recognize = recognizeCommand(command);
		switch (recognize) {
		case 'g':
			analizeParametersForGet(&price, &minRooms, &maxRooms, &command, &sort);
			get = getAnApt(price, minRooms, maxRooms, sort, apartments, &getSize);
			price = -1;
			minRooms = -1;
			maxRooms = -1;
			sort = 0;
			printAptsArr(get, getSize);
			break;
		case 'b':
			break;
		case 'd':
			break;
		case 'a':
			addAnApt(&command, &apartments);
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
			command = realloc(command, phSize * (sizeof(char)));
		}
		command[logSize++] = input;
		scanf("%c", &input);
	}
	command[logSize] = '\0';
	return command;
}
