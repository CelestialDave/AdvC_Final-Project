
#ifndef included
typedef struct date {
	short int day;
	short int month;
	short int year;
}EntryDate;

typedef struct apartment {
	int code;
	char* adress;
	short int rooms;
	int price;
	EntryDate date;
	struct apartment* next;
}Apartment;
typedef struct list {
	Apartment* head;
	Apartment* tail;
}List;
#define included
#endif