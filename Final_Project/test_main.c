//#include "declerations.h"
//
//int main() {
//	char * command = (char *)calloc(52 + 1, sizeof(char));
//	strcpy(command, "add-an-apt \"Ben Gurion 25 Herzliya\" 25 25 01 08 25");
//	char * str1 = (char *)calloc(2 + 1, sizeof(char));
//	char * str2 = (char *)calloc(3 + 1, sizeof(char));
//	strcpy(str1, "25");
//	strcpy(str2, "100");
//	char * newCommand = NULL;
//	int newCmdSize;
//	int str1Size = (int)strlen(str1);
//	int str2Size = (int)strlen(str2);
//	int cmdSize = (int)strlen(command);
//	bool isEqual = false;
//	int counter = 0;
//	char * p1 = command;
//	char * p2 = str2;
//	char * pStr1 = strstr(command, str1);
//	char * pNewCmd;
//
//
//	
//	if (str1Size == str2Size) {
//		while (pStr1 != NULL) {
//			isEqual = true;
//			while (*p2) {
//				*pStr1 = *p2;
//				pStr1++; p2++;
//			}
//			p2 = str2;
//			pStr1 = strstr(pStr1, str1);
//		}
//		newCommand = command;
//	}
//	else {
//		while (pStr1 != NULL) {
//			counter++;
//			pStr1 += str1Size;
//			pStr1 = strstr(pStr1, str1);
//		}
//		newCmdSize = cmdSize - (counter * str1Size) + (counter * str2Size);
//		newCommand = (char *)calloc(newCmdSize + 1, sizeof(char));
//		pNewCmd = newCommand;
//		pStr1 = strstr(command, str1);
//		while (pStr1 != NULL) {
//			while (p1 < pStr1) {
//				*(pNewCmd++) = *(p1++);
//			}
//
//			while (*p2) {
//				*(pNewCmd++) = *(p2++);
//			}
//			p2 = str2;
//			p1 += str1Size;
//			pStr1 = strstr(p1, str1);
//		}
//		free(command);
//	}
//
//	for (int i = 0; i < strlen(str1); i++)
//		printf("%c", str1[i]);
//
//	free(str1);
//	free(str2);
//	printf("%s\n", newCommand);
//
//}