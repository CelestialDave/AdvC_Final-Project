#include "declerations.h"
void deleteAnApt(List* list, int hours) {
	time_t t;
	Apartment* current;
	Apartment* toDel;
	int currentHoursTime;
	time(&t);
	currentHoursTime = t / 3600;
	current = list->head;
	while (current->next != NULL) {
		if (currentHoursTime - current->next->dbDate.hours <= hours) {
			toDel = current->next;
			current->next = current->next->next;
			free(toDel);
			current = list->head;
		}
		else {
			current = current->next;
		}
	}
}