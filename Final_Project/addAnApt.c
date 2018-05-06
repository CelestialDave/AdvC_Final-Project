#include "apartment.h"
#include <stdio.h>
#include <stdbool.h>
List makeEmptyList() {
	List res;
	res.head = malloc(sizeof(Apartment));
	res.head->next = NULL;
	res.tail = NULL;
	return res;
}
void insertDataToEndList(List lst, int code, char* adress, short int rooms, int price, Date date, Apartment* next) {
	Apartment* newApt;
	newApt = createApartment(code, adress, rooms, price, date, next);
	insertNodeToTail(&lst, newApt);
}
Apartment* createApartment(int code, char* adress, short int rooms, int price, Date date, Apartment* next) {
	Apartment* res;
	res = calloc(1, sizeof(Apartment));
	res->adress = adress;
	res->code = code;
	res->date = date;
	res->next = next;
	res->price = price;
	res->rooms = rooms;
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
