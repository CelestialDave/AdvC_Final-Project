#include "declerations.h"

void readDataFromFiles(History_Data * data) {

	readApartments(&data->apartments);
	readHistory(data);

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


void readHistory(History_Data * data) {
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
				insertToEndOfHistoryList(data, command);
			}
			logS = phS = 0;
			ch = getc(file);
		}
		fclose(file);
	}
}

void allocStr(char ** str, int * phS, int logS, int isFinished) {
	if (isFinished == 0) {
		if (*phS == 0) {
			*phS = 1;
			*str = (char *)calloc(*phS , sizeof(char));
		}
		else if (logS == *phS) {
			*phS *= 2;
			*str = (char *)realloc(*str, *phS * sizeof(char));
		}
	}
	else if (isFinished == 1) {
		if (logS < *phS) {
			*str = (char *)realloc(*str, (logS + 1)* sizeof(char));
			*phS = logS;
		}
	}
}