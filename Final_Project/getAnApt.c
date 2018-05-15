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
		mergeSortApts(res, logSize);
		if (sort == 1) {
			printAptsArrHighToLow(res, logSize);
		}
		if (sort == 2) {
			printAptsArrLowToHigh(res, logSize);
		}
	}
	else {
		printAptsArrHighToLow(res, logSize);
	}
	free(res);
}
void mergeSortApts(Apartment** arr, int size) {
	if (size > 1) {
		Apartment** temp;
		mergeSortApts(arr, size / 2);
		mergeSortApts(arr + size / 2, size - size / 2);
		temp = malloc(size * sizeof(Apartment*));
		sortedMerge(arr, size / 2, arr + size / 2, size - size / 2,temp);
		for (int i = 0; i < size; i++) {
			arr[i] = temp[i];
		}
		free(temp);
	}
}
void sortedMerge(Apartment** arr1, int size1, Apartment** arr2, int size2, Apartment** res) {

	int read1;
	int read2;
	int write;
	read1 = 0;
	read2 = 0;
	write = 0;
	while (read1 != size1 && read2 != size2) {
		if (arr1[read1]->price >= arr2[read2]->price) {
			res[write++] = arr2[read2++];
		}
		else {
			res[write++] = arr1[read1++];
		}
	}
	while (read1 < size1) {
		res[write++] = arr1[read1++];
	}
	while (read2 < size2) {
		res[write++] = arr2[read2++];
	}
}
void printAptsArrHighToLow(Apartment** arr, int size) {
	for (int i = size - 1; i >= 0; i--) {
		printf("Apt details:\n");
		printf("Code: %d\n", arr[i]->code);
		printf("Adress: %s\n", arr[i]->adress);
		printf("Number of rooms: %d\n", arr[i]->rooms);
		printf("Price: %d\n", arr[i]->price);
		printf("Entry date: %d.%d.%d\n", arr[i]->date.day, arr[i]->date.month, arr[i]->date.year);
		printf("Database date: %d.%d.%d\n", arr[i]->dbDate.day, arr[i]->dbDate.month, arr[i]->dbDate.year);
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
		printf("Database date: %d.%d.%d\n", arr[i]->dbDate.day, arr[i]->dbDate.month, arr[i]->dbDate.year);
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