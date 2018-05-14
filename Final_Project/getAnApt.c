#include "declerations.h"

void getAnApt(int price,int minRooms,int maxRooms,int sort, char* command, List apartments) {

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
				res = (Apartment **)realloc(res, phSize * sizeof(Apartment*));
			}
			res[logSize++] = current;
		}
		current = current->next;
	}
	if (sort != 0) {
		////sort ///// from low to high
		if (sort == 1) {
			printAptsArrLowToHigh(res, logSize);
		}
		if (sort == 2) {
			printAptsArrHighToLow(res, logSize);
		}
	}
	printAptsArrLowToHigh(res, logSize);
	free(res);
}
void printAptsArrHighToLow(Apartment** arr, int size) {
	for (int i = size - 1; i <= 0; i--) {
		printf("Apt details:\n");
		printf("Code: %d\n", arr[i]->code);
		printf("Adress: %s\n", arr[i]->adress);
		printf("Number of rooms: %d\n", arr[i]->rooms);
		printf("Price: %d\n", arr[i]->price);
		printf("Entry date: %d.%d.%d\n", arr[i]->date.day, arr[i]->date.month, arr[i]->date.year);
		//printf("Database entry date: ",arr[i]->);
	}
}
void printAptsArrLowToHigh(Apartment** arr, int size) {
	
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
	return false;
}