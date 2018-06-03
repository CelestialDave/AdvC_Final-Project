
#ifndef included
typedef struct date {
	short int day;
	short int month;
	short int year;
	int hours;
}Date;

typedef struct apartment {
	int code;
	char* adress;
	short int rooms;
	int price;
	Date date;
	Date dbDate;
	struct apartment* next;
}Apartment;
typedef struct list {
	Apartment* head;
	Apartment* tail;
}List;

#define FILE_APARTMENTS "Apartments.bin"

#define included
#endif