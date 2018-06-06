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
			freeApt(&toDel);
		}
		else {
			current = current->next;
		}
	}
}
void freeData(History_Data * data) {
	freeApartments(&data->apartments);
	freeHistoryData(data);
}

void freeApt(Apartment ** apt) {
	free((*apt)->adress);
	free(*apt);
}

void freeApartments(List * apartments) {
	Apartment * p = apartments->head;
	Apartment * temp;

	while (p != NULL) {
		temp = p;
		p = p->next;
		freeApt(&temp);
	}
}

void freeHistoryData(History_Data * hData) {
	freeShortTermHisArr(hData->shortTerm_HistoryArr);
	freeHistoryList(&hData->LongTerm_HistoryList);
	return;
}

void freeShortTermHisArr(char ** shortTermArr) {
	int i;
	for (i = SHORT_TERM_SIZE - 1; i >= 0; i--) {
		if (shortTermArr[i] != NULL)
			free(shortTermArr[i]);
	}
}

void freeHistoryList(HistoryList * hList) {
	HistoryEntry * p = hList->tail;
	HistoryEntry *  temp;
	while (p != NULL) {
		if (p->command != NULL)
			free(p->command);
		temp = p;
		p = p->prev;
		free(temp);
	}
}