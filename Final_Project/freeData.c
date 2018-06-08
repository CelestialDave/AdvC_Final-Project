#include "declerations.h"

// a function that deletes all the apartments that was entered to the database in the last given hours
void deleteAnApt(List* list, int hours) {
	time_t t;
	Apartment* current;
	Apartment* toDel;
	int currentHoursTime;
	time(&t);
	currentHoursTime = t / 3600;
	current = list->head;
	// checking all the apratments to see which apartmet to delete
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
// a function that frees memory allocations
void freeData(Data * data) {
	freeApartments(&data->apartments);
	freeHistoryData(data);
}
// a function that frees an apartments
void freeApt(Apartment ** apt) {
	free((*apt)->adress);
	free(*apt);
}
// a function that frees the apartments
void freeApartments(List * apartments) {
	Apartment * p = apartments->head;
	Apartment * temp;

	while (p != NULL) {
		temp = p;
		p = p->next;
		freeApt(&temp);
	}
}
// a function that frees the history data of commands
void freeHistoryData(Data * hData) {
	freeShortTermHisArr(hData->shortTerm_HistoryArr);
	freeHistoryList(&hData->LongTerm_HistoryList);
	return;
}
// a function that frees the short term history array strings
void freeShortTermHisArr(char ** shortTermArr) {
	int i;
	for (i = SHORT_TERM_SIZE - 1; i >= 0; i--) {
		if (shortTermArr[i] != NULL)
			free(shortTermArr[i]);
	}
}
// a function that frees the long term history list
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