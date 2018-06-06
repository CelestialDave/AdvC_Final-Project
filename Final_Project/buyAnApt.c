#include "declerations.h"
void buyAnApt(List* lst, int code) {
	Apartment* current;
	Apartment* toDel;
	current = lst->head;
	while (current->next->code != code) {
		current = current->next;
	}
	if (current != NULL) {
		toDel = current->next;
		current->next = current->next->next;
		freeApt(&toDel);
	}
}