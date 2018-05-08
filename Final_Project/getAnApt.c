#include "declerations.h"
void analizeParametersForGet(int* price, int* minRooms, int* maxRooms, char** command,int* sort) {
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
Apartment** getAnApt(int price, int minRooms, int maxRooms,int sort, List apartments, int* size) {

	Apartment** res;
	Apartment* current;
	int logSize;
	int phSize;
	current = apartments.head->next;
	logSize = 0;
	phSize = 2;
	res = malloc(phSize * sizeof(Apartment*));
	while (current != NULL) {
		if (conditionsAreMet(price, minRooms, maxRooms, current)) {
			if (logSize == phSize) {
				phSize *= 2;
				realloc(res, phSize);
			}
			res[logSize++] = current;
		}
		current = current->next;
	}
	*size = logSize;
	if (sort == 1) {
		//sortLowToHigh(res, size); //////////
	}
	if (sort == 2) {
		//sortHighToLow(res, size); //////////
	}
	return res;
}
void printAptsArr(Apartment** arr, int size) {
	
	for (int i = 0; i < size; i++) {
		printf("Apt details:\n");
		printf("Code: %d\n", arr[i]->code);
		printf("Adress: %s\n", arr[i]->adress);
		printf("Number of rooms: %d\n", arr[i]->rooms);
		printf("Price: %d\n", arr[i]->price);
		printf("Entry date: %d.%d.%d\n", arr[i]->date.day, arr[i]->date.month, arr[i]->date.year);
		//printf("Database entry date: ",arr[i]->);
	}
}
bool conditionsAreMet(int price, int minRooms, int maxRooms, Apartment* apt) {

	if (price != -1) {
		if (apt->price <= price) {
			if (minRooms == -1 && maxRooms == -1) {
				return true;
			}
			else if (maxRooms == -1) {
				return apt->rooms >= minRooms;
			}
			else if (minRooms == -1) {
				return apt->rooms <= maxRooms;
			}
			else {
				return apt->rooms <= maxRooms && apt->rooms >= minRooms;
			}
		}
	}
	else if (minRooms != -1) {
		if (apt->rooms >= minRooms) {
			if (price == -1 && maxRooms == -1) {
				return true;
			}
			else if (price == -1) {
				return apt->rooms <= maxRooms;
			}
		}
	}
	else if (maxRooms != -1) {
		return apt->rooms <= maxRooms;
	}
}