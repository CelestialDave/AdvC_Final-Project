#include "declerations.h"
void addAnApt(char** command, List* list) {
	static int code = 1;
	char* copy = NULL;
	char* address = NULL;
	char* temp;
	int price;
	short int rooms;
	Date date;
	time_t currentTime;
	struct tm* tm;
	Date sDate; // time_t mktime(struct tm* tm) - to read from binary file - send tm pointer struct with date values 
	time(&currentTime);
	sDate.hours = currentTime / 3600;
	tm = localtime(&currentTime);
	sDate.day = tm->tm_mon + 1;
	sDate.month = tm->tm_mday;
	sDate.year = tm->tm_year + 1900;
	// Dudi:
	//copy = malloc(strlen(*command) * sizeof(char));
	//strcpy(copy, *command);
	copyString(&copy, *command);
	temp = strtok(copy, "\"");
	temp = strtok(NULL, "\"");
	copyString(&address, temp);
	price = atoi(strtok(NULL, " "));
	rooms = atoi(strtok(NULL, " "));
	date.day = atoi(strtok(NULL, " "));
	date.month = atoi(strtok(NULL, " "));
	date.year = atoi(strtok(NULL, " "));
	insertDataToEndList(list, code, address, rooms, price, sDate, date, NULL);
	code++;
	// Dudi:
	free(copy);
	//*command = copy;
}
List makeEmptyList() {
	List res;
	res.head = calloc(1, sizeof(Apartment));
	res.head->next = NULL;
	res.tail = NULL;
	return res;
}
void insertDataToEndList(List* lst, int code, char* adress, short int rooms, int price, Date sDate, Date date, Apartment* next) {
	Apartment* newApt;
	newApt = createApartment(code, adress, rooms, price, sDate, date, next);
	insertNodeToTail(lst, newApt);
}
Apartment* createApartment(int code, char* adress, short int rooms, int price, Date sDate, Date date, Apartment* next) {
	Apartment* res;
	res = calloc(1, sizeof(Apartment));
	res->adress = adress;
	res->code = code;
	res->date = date;
	res->next = next;
	res->price = price;
	res->rooms = rooms;
	res->dbDate = sDate;
	return res;
}
void insertNodeToTail(List* lst, Apartment* node) {
	if (isEmpty(*lst)) {
		lst->head->next = node;
	}
	else {
		lst->tail->next = node;
	}
	lst->tail = node;
}
bool isEmpty(List lst) {
	return lst.head->next == NULL;
}
