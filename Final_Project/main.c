
//	Advanced Programming with C - Final Projact
//	Authors:	Noam Waissman & David Chen

#include "declerations.h"

int main() {
	/*add-an-apt "Dizengoff 180 Tel Aviv" 2000000 4 28 04 16
add-an-apt "Rothschild 67 Rishon Le Zion" 1700000 3 03 10 16
add-an-apt "Ben Gurion 25 Herzliya" 200000 5 01 08 16
add-an-apt "Gordon 85 Holon" 1500000 3 15 06 17
get-an-apt –MinimumNumRooms 0
delete-an-apt -Enter 1
*/

	// Declaring Variabls:
	char* command;
	Data data;

	// Program init prep:
	preDataLoaderPrep(&data);

	// Data-Loader; Load Data from files:
	readDataFromFiles(&data);

	// Opening Message:
	printf("Please enter one of the following commands:\nadd-an-apt, get-an-apt, buy-an-apt or delete-an-apt\nFor reconstruction commands, please enter:\n!!, !num, history, short_history or !num^str1^str2\nTo exit, enter exit.\n");
	
	// Start program by prompting for user command:
	command = getCommand();
	while (strcmp(command, "exit") != 0) {
		commander(&data, command);
		command = getCommand();
	}

	// Data-Loader; Unload Data to files:
	writeDataToFiles(data);
	
	// Free Data:
	freeData(&data);

	printf("Good Bye!\n");
}