
#include "declerations.h"

////////////////////////////
// Read-Data related funcs:
////////////////////////////

void readDataFromFiles(Data * data) {
	readApartments(&data->apartments);
	readHistory(data);
	data->code = data->apartments.tail->code + 1;
}

void readApartments(List * apartments) {
	FILE * file;
	long int fSize = fileSize(FILE_APARTMENTS);

	if (fSize > 0) {
		short int code;
		short int addressLen;
		char * address;
		short int nRooms;
		int price = 0;
		short int day = 0;
		short int month = 0;
		short int year = 0;
		short int dbDay = 0;
		short int dbMonth = 0;
		short int dbYear = 0;
		struct tm time;
		time_t epoch;
		int hours;
		byte byte1;
		byte byte2;
		byte byte3;
		byte byte4;
		byte byte5;
		Date entryDate;
		Date dbDate;

		file = fopen(FILE_APARTMENTS, "rb");
		while (ftell(file) < fSize) {
			fread(&code, sizeof(short int), 1, file);
			fread(&addressLen, sizeof(short int), 1, file);
			address = (char *)calloc(addressLen + 1, sizeof(char));
			fread(address, sizeof(char), addressLen, file);
			fread(&price, sizeof(int), 1, file);
			fread(&byte1, sizeof(byte), 1, file);
			fread(&byte2, sizeof(byte), 1, file);
			fread(&byte3, sizeof(byte), 1, file);
			fread(&byte4, sizeof(byte), 1, file);
			fread(&byte5, sizeof(byte), 1, file);
			nRooms = (short int)(byte1 >> 4);
			day = (short int)(((byte1 & MASK_DAY1) << 1) | ((byte2 & MASK_DAY2) >> 7));
			month = (short int)((byte2 & MASK_MONTH) >> 3);
			year = (short int)(((byte2 & MASK_YEAR1) << 4) | ((byte3 & MASK_YEAR2) >> 4));
			dbDay = (short int)(byte4 >> 3);
			dbMonth = (short int)(((byte4 & MASK_DBMONTH1) << 1) | ((byte5 & MASK_DBMONTH2) >> 7));
			dbYear = (short int)(byte5 & MASK_DBYEAR);

			time.tm_year = (dbYear + 2000) - 1900;
			time.tm_mon = dbMonth - 1;
			time.tm_mday = dbDay;
			time.tm_hour = 12;
			time.tm_min = 12;
			time.tm_sec = 12;
			time.tm_isdst = 1;
			epoch = mktime(&time);
			hours = (int)(epoch / 3600);
			entryDate.day = day;
			entryDate.month = month;
			entryDate.year = year;
			entryDate.hours = 0;
			dbDate.day = dbDay;
			dbDate.month = dbMonth;
			dbDate.year = dbYear;
			dbDate.hours = hours;

			insertDataToEndList(apartments, code, address, nRooms, price, dbDate, entryDate, NULL);
		}
		fclose(file);
	}
}

long int fileSize(char * filename) {
	long int res = -1;
	FILE * file = fopen(filename, "rb");
	if (file != NULL) {
		fseek(file, 0, SEEK_END);
		res = ftell(file);
		fclose(file);
	}

	return res;
}


void readHistory(Data * data) {
	char * command;
	int logS = 0;
	int phS = 0;
	char ch;
	FILE * file;
	file = fopen(FILE_HISTORY, "rt");
	if (file != NULL) {
		ch = getc(file);
		while (!feof(file)) {
			while (ch != '\n') {
				allocStr(&command, &phS, logS, 0);
				command[logS++] = ch;
				ch = getc(file);
			}
			allocStr(&command, &phS, logS, 1);
			command[logS] = '\0';
			data->total++;
			if (data->total <= SHORT_TERM_SIZE) {
				data->shortTerm_HistoryArr[data->total - 1] = command;
			}
			else {
				insertToStartOfHistoryList(data, command);
			}
			logS = phS = 0;
			ch = getc(file);
		}
		fclose(file);
		applyHListOrder(data->LongTerm_HistoryList, data->total);
	}
}

void applyHListOrder(HistoryList hList, int total) {
	int i = 0;
	HistoryEntry * p = hList.tail;
	while (p->prev != NULL) {
		p->order = (total - SHORT_TERM_SIZE) - i++;
		p = p->prev;
	}
}


////////////////////////////
// Write-Data related funcs:
////////////////////////////

void writeDataToFiles(Data data) {
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