/*****************************************************************//**
 * \file   Main.c
 * \brief
 *
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/

#include "Screen.h"

int main() {

	int op = -1;
	ClientList* firstClient = ReadClient(CLIENT_SAVE_FILE_NAME);
	VehicleList* firstVehicle = ReadVehicle(VEHICLE_SAVE_FILE_NAME);
	ManagerList* firstManager = ReadManagers(MANAGER_SAVE_FILE_NAME);

	while (op != 0) {
		ShowMainMenu(&op);


		switch (op) {
		case 1:
			ShowClientMenu(firstClient);
			break;
		case 2:
			ShowVehicleMenu(firstVehicle);
			break;
		case 3:
			ShowManagerScreen(firstManager);
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
