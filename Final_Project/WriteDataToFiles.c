#include "declerations.h"

void writeDataToFiles(List apartments) {

	writeApartments(apartments);

}
void writeApartments(List apartments) {

	FILE* binary = fopen("Apartments.bin", "wb");
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
	cDate_first = ((byte)(first_mask & apt->dbDate.day) << 3) | ((byte)(third_mask & apt->dbDate.month) >> 1);;
	cDate_second = ((byte)(second_mask & apt->dbDate.month) << 7) | ((byte)(fifth_mask & apt->dbDate.year));
	fwrite(&first, sizeof(byte), 1, file);
	fwrite(&second, sizeof(byte), 1, file);
	fwrite(&third, sizeof(byte), 1, file);
	fwrite(&cDate_first, sizeof(byte), 1, file);
	fwrite(&cDate_second, sizeof(byte), 1, file);
}