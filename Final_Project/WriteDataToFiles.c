#include "declerations.h"

void writeDataToFiles(History_Data data) {

	writeApartments(data.apartments);
	writeHistory(data.total, data.shortTerm_HistoryArr, data.LongTerm_HistoryList);

}
void writeApartments(List apartments) {

	FILE* binary = fopen(FILE_APARTMENTS, "wb");
	short int AptCode;
	short int adressLength;
	Apartment* current = apartments.head->next;
	while (current != NULL) {
		AptCode = (short int)current->code;
		adressLength = (short int)strlen(current->adress);
		fwrite(&AptCode, sizeof(short int), 1, binary);
		fwrite(&adressLength, sizeof(short int), 1, binary);
		fwrite(current->adress, sizeof(char), adressLength, binary);
		fwrite(&(current->price), sizeof(int), 1, binary);
		writeCompressedData(current, binary);
		current = current->next;
	}
	fclose(binary);
}
void writeCompressedData(Apartment* apt, FILE* file) {

	byte first = 0;
	byte second = 0;
	byte third = 0;
	byte cDate_first;
	byte cDate_second;
	short int first_mask = 0x1E;
	short int second_mask = 1;
	short int third_mask = 0x0F;
	short int forth_mask = 0x70;
	short int fifth_mask = 0x7F;
	first = (((byte)(apt->rooms)) << 4) | ((byte)((first_mask & apt->date.day) >> 1));
	second = ((byte)(second_mask & apt->date.day) << 7) | ((byte)(third_mask & apt->date.month) << 3) 
		| ((byte)(forth_mask & apt->date.year) >> 4);
	third = ((byte)(third_mask & apt->date.year) << 4);
	cDate_first = ((byte)(0x1F & apt->dbDate.day) << 3) | ((byte)(third_mask & apt->dbDate.month) >> 1);
	cDate_second = ((byte)(second_mask & apt->dbDate.month) << 7) | ((byte)(fifth_mask & apt->dbDate.year));
	fwrite(&first, sizeof(byte), 1, file);
	fwrite(&second, sizeof(byte), 1, file);
	fwrite(&third, sizeof(byte), 1, file);
	fwrite(&cDate_first, sizeof(byte), 1, file);
	fwrite(&cDate_second, sizeof(byte), 1, file);
}

void writeHistory(int total, char ** shortTerm_HistoryArr, HistoryList LongTerm_HistoryList) {
	FILE * file;
	int i;
	int sthSize;
	int hListSize;
	int strSize;
	if (total > SHORT_TERM_SIZE) {
		sthSize = SHORT_TERM_SIZE;
		hListSize = total - sthSize;
	}
	else {
		sthSize = total;
		hListSize = 0;
	}
	
	HistoryEntry *p = LongTerm_HistoryList.tail;

	file = fopen(FILE_HISTORY, "wt");

	for (i = 0; i < sthSize; i++) {
		strSize = (int)strlen(shortTerm_HistoryArr[i]);
		fwrite(shortTerm_HistoryArr[i], sizeof(char), strSize, file);
		putc('\n', file);
	}

	if ((hListSize > 0) && (p != NULL)) {
		while (p->prev != NULL) {
			strSize = (int)strlen(p->command);
			fwrite(p->command, sizeof(char), strSize, file);
			putc('\n', file);
			p = p->prev;
		}
	}

	fclose(file);
}