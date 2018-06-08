#define _CRT_SECURE_NO_WARNINGS
#include "declerations.h"
int main() {
	char* command;
	History_Data hData;
	historyDataPreLoaderPrep(&hData);
	// Data Loader() 
	readDataFromFiles(&hData);
	// Opening Message:
	printf("Please enter one of the following commands:\nadd-an-apt, get-an-apt, buy-an-apt or delete-an-apt\nFor reconstruction commands, please enter:\n!!, !num, history, short_history or !num^str1^str2\nTo exit, enter exit.\n");
	command = getCommand();
	while (strcmp(command, "exit") != 0) {
		commander(&hData, command);
		command = getCommand();
	}

	// Load Data onto files:
	writeDataToFiles(hData);
	
	// Release Data:
	freeData(&hData);
}