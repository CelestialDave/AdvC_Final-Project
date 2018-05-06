
#ifndef included
typedef struct date {
	short int day;
	short int month;
	short int year;
}Date;
typedef struct apartment {
	int code;
	char* adress;
	short int rooms;
	int price;
	Date date;
	struct apartment* next;
}Apartment;
typedef struct list {
	Apartment* head;
	Apartment* tail;
}List;
#define included
#endif