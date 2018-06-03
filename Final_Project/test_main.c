//#include "declerations.h"
//
//int main() {
//	int hours;
//	struct tm time;
//	struct tm * time2;
//	time_t t;
//	int day = 3;
//	int year = 2018;
//	int month = 6;
//	time.tm_year = year - 1900;
//	time.tm_mon = month - 1;
//	time.tm_mday = day;
//	time.tm_hour = 10;
//	time.tm_min = 10;
//	time.tm_sec = 10;
//	time.tm_isdst = 1;
//	t = mktime(&time);
//	hours = t / 3600;
//	if (t == -1) {
//		printf("Error!\n");
//	}
//	else {
//		printf("%ld\n", (long)t);
//		printf("Hours: %d", hours);
//	}
//	time2 = localtime(&t);
//	printf("Time: %s", asctime(time2));
//
//}