/*****************************************************************//**
 * \file   Utility.c
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/


#include "Utility.h"


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
