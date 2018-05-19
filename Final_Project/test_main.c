//#include "declerations.h"
//
//int main() {
//	//char ** shortTerm_HistoryArr = (char **)calloc(7, sizeof(char *));
//	History_Data hData1;
//	History_Data * hData = &hData1;
//	int index;
//	//char * shortTerm_HistoryArr[SHORT_TERM_SIZE];
//	int size = (int)strlen("add-an-apt \"Rothschild 67 Rishon Le Zion\" 1700000 3 03 10 16");
//	char * str1 = (char *)calloc(size + 1, sizeof(char));
//	char * str2;
//	//str1 = "add-an-apt \"Rothschild 67 Rishon Le Zion\" 1700000 3 03 10 16";
//	strcpy(str1, "add-an-apt \"Rothschild 67 Rishon Le Zion\" 1700000 3 03 10 16");
//	copyString(&str2, str1);
//	hData->shortTerm_HistoryArr[SHORT_TERM_SIZE - 1] = str2;
//	printf("%s\n", hData->shortTerm_HistoryArr[SHORT_TERM_SIZE - 1]);
//	free(str1);
//	index = SHORT_TERM_SIZE - 1;
//	//free(str2);
//	free(hData->shortTerm_HistoryArr[index]);
//
//	return 0;
//}