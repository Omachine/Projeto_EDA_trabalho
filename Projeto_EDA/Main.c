/*****************************************************************//**
 * \file   Main.c
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/

#include "Screen.h"

int main() {
	setlocate(LC_ALL, "Portuguese");


	int op = -1;
	ClientList* firstClient = ReadClient(CLIENT_SAVE_FILE_NAME);
	VehicleList* firstVehicle = ReadVehicle(VEHICLE_SAVE_FILE_NAME);
	ManagerList* firstManager = ReadManager(MANAGER_SAVE_FILE_NAME);

	while (op != 0) {
		ShowMainMenu(&op);


		switch (op) {
		case 1:
			ShowClientMenu(&op);
			break;
		case 2:
			ShowVehicleMenu(&op);
			break;
		case 3:
			ShowManagerScreen(&op);
			break;
		case 4:
			LoadInitialData(&firstClient, &firstVehicle, &firstManager);
			break;
		case 5:
			ResetClient(firstClient);
			ResetVehicle(firstVehicle);
			ResetManager(firstManager);
			op = 0;
		default:
			break;
		}

	}
	return 0;
}
