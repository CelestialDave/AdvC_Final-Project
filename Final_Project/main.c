
//	Advanced Programming with C - Final Projact
//	Authors:	Noam Waissman & David Chen

#include "declerations.h"

int main() {

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

	// User Farewell Message:
	printf("Good Bye!\n");
}