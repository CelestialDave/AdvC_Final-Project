#include "declerations.h"
// a function that gets a command and a list of apartments and adds the apartmets to the list's tail
void addAnApt(char** command, List* list,int* code) {
	char* copy = NULL;
	char* address = NULL;
	char* temp;
	int price;
	short int rooms;
	Date date;
	//cTime avaluation
	time_t currentTime;
	struct tm* tm;
	Date sDate; 
	time(&currentTime);
	sDate.hours = currentTime / 3600;
	tm = localtime(&currentTime);
	sDate.day = tm->tm_mon + 1;
	sDate.month = tm->tm_mday;
	sDate.year = tm->tm_year + 1900;
	sDate.year = (tm->tm_year + 1900) % 100;
	// apartmet fieds avaluation
	copyString(&copy, *command);
	temp = strtok(copy, "\"");
	temp = strtok(NULL, "\"");
	copyString(&address, temp);
	price = atoi(strtok(NULL, " "));
	rooms = atoi(strtok(NULL, " "));
	date.day = atoi(strtok(NULL, " "));
	date.month = atoi(strtok(NULL, " "));
	date.year = atoi(strtok(NULL, " "));
	insertDataToEndList(list, *code, address, rooms, price, sDate, date, NULL);
	(*code)++;
	
	free(copy);
}
// a function that creates an empty list
List makeEmptyList() {
	List res;
	res.head = calloc(1, sizeof(Apartment));
	res.head->next = NULL;
	res.tail = res.head;
	return res;
}
// a function that gets an apartment's data and ads a new apartment to the list's tail
void insertDataToEndList(List* lst, int code, char* adress, short int rooms, int price, Date sDate, Date date, Apartment* next) {
	Apartment* newApt;
	newApt = createApartment(code, adress, rooms, price, sDate, date, next);
	insertNodeToTail(lst, newApt);
}
// a function that creats a node of an a partment
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
// a function that inserts a node to the tail of the list of the apartments
void insertNodeToTail(List* lst, Apartment* node) {
	if (isEmpty(*lst)) {
		lst->head->next = node;
	}
	else {
		lst->tail->next = node;
	}
	lst->tail = node;
}
// a function that checks if a list is empty
bool isEmpty(List lst) {
	return lst.head->next == NULL;
}
