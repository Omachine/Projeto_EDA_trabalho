/*****************************************************************//**
 * \file   Utility.c
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/


#include "Utility.h"

void GetFullPath(const char* path, char* fullPath) {
	strcpy(fullPath, __FILE__);
	char* p = strrchr(fullPath, '\\');
	*p = '\0';
	strcat(fullPath, '\\');
	strcat(fullPath, path);
}


int Confirm() {
	int value = -1;

	puts("");
	puts("Operation completed. Do you want to save the changes?");
	puts("[1] - Yes");
	puts("[2] - No");
	printf(">");

	while (value != 1 && value != 2)
		scanf_s("%d", &value);

	return value;
}

void GetDate(char* date) {
	int d, m, y;

	printf("Enter the date (dd/mm/yyyy): ");
	scanf_s("%d/%d/%d", &d, &m, &y);

	struct tm timeinfo = { 0 };
	timeinfo.tm_year = y - 1900;
	timeinfo.tm_mon = m - 1;
	timeinfo.tm_mday = d;

	strftime(date, 11, "%d/%m/%Y", &timeinfo);

}



float Pertentage(int nums, int n) {
	float result;

	result = (nums * 100) / (float)n;

	return result;
}

float Average(int* nums, int n) {
	int i, sum = 0;
	float result;

	for (i = 0; i < n; i++) {
		sum += nums[i];
	}

	result = sum / (float)n;

	return result;
}
