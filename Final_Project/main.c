#define _CRT_SECURE_NO_WARNINGS
#include "declerations.h"
int main() {
	/*add-an-apt "Dizengoff 180 Tel Aviv" 2000000 4 28 09 16
add-an-apt "Rothschild 67 Rishon Le Zion" 1700000 3 03 10 16
add-an-apt "Ben Gurion 25 Herzliya" 200000 5 01 08 16
add-an-apt "Gordon 85 Holon" 1500000 3 15 06 17
get-an-apt –MinimumNumRooms 3 –MaximumNumRooms 5 –MaximumPrice 1750000 -s*/

	char* command;
	History_Data hData;
	historyDataPreLoaderPrep(&hData);
	// Data Loader() 
	// Opening Message:
	printf("Please enter one of the following commands:\nadd-an-apt, get-an-apt, buy-an-apt or delete-an-apt\nFor reconstruction commands, please enter:\n!!, !num, history, short_history or !num^str1^str2\nTo exit, enter exit.\n");
	command = getCommand();
	while (strcmp(command, "exit") != 0) {
		commander(&hData, command);
		command = getCommand();
	}
	writeDataToFiles(hData.apartments);
	// Release Data:
	freeHistoryData(&hData);
}