/*****************************************************************//**
 * \file   Screen.c
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/
#include "Screen.h"

void ShowMainMenu(int* op) {

	 *op = -1;


	system("cls");
	//create a menu using - and |
	printf("+------------------------------------------------+\n");
	printf("|              Moderator screen                  |\n");
	printf("+------------------------------------------------+\n");
	printf("| 1- Client Options                              |\n");
	printf("|                                                |\n");
	printf("| 2- Vehicle Options                             |\n");
	printf("|                                                |\n");
	printf("| 3- Manager Options                             |\n");
	printf("|                                                |\n");
	printf("| 4- Load Initial Data                           |\n");
	printf("+------------------------------------------------+\n");
	printf("| 5- Exit                                        |\n");
	printf("+------------------------------------------------+\n");

	printf("Select an option: ");
	scanf_s("%d", op);
	
}


void LoadInitialData(ClientList** firstClient, VehicleList** firstVehicle, ManagerList** firstManager) {

	int op = -1;

	system("cls");

	if (Confirm() == IS_CANCELED)
		return;

	*firstClient = LoadInitialClients(*firstClient, CLIENT_HARDDATA_FILE_NAME, CLIENT_SAVE_FILE_NAME);
	*firstVehicle = LoadVehicle(*firstVehicle, VEHICLE_HARDDATA_FILE_NAME, VEHICLE_SAVE_FILE_NAME);
	*firstManager = LoadInitialManagers(*firstManager, MANAGER_HARDDATA_FILE_NAME, MANAGER_SAVE_FILE_NAME);


}


void ShowClientMenu(int* op) {
	*op = -1;
 	system("cls");
	 	
	 	printf("+------------------------------------------------+\n");
		printf("|              Client screen                     |\n");
		printf("+------------------------------------------------+\n");
		printf("| 1- Add Client                                  |\n");
	 	printf("|                                                |\n");
	 	printf("| 2- Remove Client                               |\n");
		printf("|                                                |\n");
	 	printf("| 3- Edit Client                                 |\n");
	 	printf("|                                                |\n");
	 	printf("| 4- List CLients                                |\n");
	 	printf("+------------------------------------------------+\n");
	 	printf("| 6- Back                                        |\n");
	 	printf("+------------------------------------------------+\n");
	 	printf("Select an option: ");
	 	scanf_s("%d", op);

		while (op != 0) {
			ShowMainMenu(&op);


			switch(&op) {
			case 1:
				ShowAddClientMenu(ClientList** lastClient);
				break;
			case 2:
				ShowRemoveClientMenu(ClientList** firstClient);
				break;
			case 3:
				ShowEditClientMenu(ClientList** firstClient);
				break;
			case 4:
				ShowListClientMenu(ClientList** firstClient);
				break;
			case 5:
				ShowMainMenu(&op);
				break;
			}

		}



	}

void ShowVehicleMenu(int* op) {
	*op = -1;
	 
	system("cls");

	printf("+------------------------------------------------+\n");
	printf("|              Vehicle screen                    |\n");
	printf("+------------------------------------------------+\n");
	printf("| 1- Add Vehicle                                 |\n");
	printf("|                                                |\n");
	printf("| 2- Remove Vehicle                              |\n");
	printf("|                                                |\n");
	printf("| 3- Edit Vehicle                                |\n");
	printf("|                                                |\n");
	printf("| 4- Rent Vehicle                                |\n");
	printf("|                                                |\n");
	printf("| 5- List Vehicles                               |\n");
	printf("|                                                |\n");
	printf("| 6- List by Autonomy                            |\n");
	printf("|                                                |\n");
	printf("| 7-Search by location                           |\n");
	printf("+------------------------------------------------+\n");
	printf("| 6- Back                                        |\n");
	printf("+------------------------------------------------+\n");
	printf("Select an option: ");
	scanf_s("%d", op);

}

void ShowManagerScreen(int* op) {
	*op = -1;
	
	system("csl");

	printf("+------------------------------------------------+\n");
	printf("|              Manager screen                    |\n");
	printf("+------------------------------------------------+\n");
	printf("| 1- Add Manager                                 |\n");
	printf("|                                                |\n");
	printf("| 2- Remove Manager                              |\n");
	printf("|                                                |\n");
	printf("| 3- Edit Manager                                |\n");
	printf("|                                                |\n");
	printf("| 4- List Managers                               |\n");
	printf("+------------------------------------------------+\n");
	printf("| 6- Back                                        |\n");
	printf("+------------------------------------------------+\n");
	printf("Select an option: ");
	scanf_s("%d", op);


}


void ShowAddClientMenu(ClientList** lastClient) {
	Client newClient;

	system("cls");
	printf("+------------------------------------------------+\n");
	printf("|              Add Client                        |\n");
	printf("+------------------------------------------------+\n");

	printf("Name: ");
	scanf_s("%s", newClient.name, CLIENT_NAME_LENGHT);
	fflush(stdin);

	printf("NIF: ");
	scanf_s("%s", &newClient.nif);
	fflush(stdin);
	
	printf("Address: ");
	scanf_s("%s", newClient.address, CLIENT_ADDRESS_LENGHT);
	fflush(stdin);
	
	printf("Balance: ");
	scanf_s("%f", &newClient.balance);
	fflush(stdin);

	if (Confirm() == IS_CANCELED)
		return;

	*lastClient = AddClient(*lastClient, newClient);
	
	SaveClient(CLIENT_SAVE_FILE_NAME, *lastClient);

}

void ShowRemoveClientMenu(ClientList* firstClient) {
	int id;

	system("cls");
	printf("+------------------------------------------------+\n");
	printf("|              Remove Client                     |\n");
	printf("+------------------------------------------------+\n");

	printf("ID: ");
	scanf_s("%d", &id);
	fflush(stdin);

	if (Confirm() == IS_CANCELED)
		return;

	RemoveClient(firstClient, id);

	SaveClient(CLIENT_SAVE_FILE_NAME, firstClient);
}




void ShowEditClientMenu(ClientList* firstClient){
	Client newClient;

	system("cls");
	printf("+------------------------------------------------+\n");
	printf("|              Edit Client                       |\n");
	printf("+------------------------------------------------+\n");

	printf("ID: ");
	scanf_s("%d", &newClient.id);
	fflush(stdin);

	printf("Name: ");
	scanf_s("%s", newClient.name, CLIENT_NAME_LENGHT);
	fflush(stdin);

	printf("NIF: ");
	scanf_s("%s", &newClient.nif);
	fflush(stdin);

	printf("Address: ");
	scanf_s("%s", newClient.address, CLIENT_ADDRESS_LENGHT);
	fflush(stdin);

	printf("Balance: ");
	scanf_s("%f", &newClient.balance);
	fflush(stdin);

	if (Confirm() == IS_CANCELED)
		return;

	EditClient(firstClient, newClient);

	SaveClient(CLIENT_SAVE_FILE_NAME, firstClient);

}


void ShowListClientMenu(ClientList* firstClient) {
	
	int i;
	system("cls");
	printf("+------------------------------------------------------------------------+\n");
	printf("| Id |       Name       |    Nif     |       Address        |  Balance   |\n");
	printf("+------------------------------------------------------------------------+\n");

	ClientList* client = firstClient;
	while (client != NULL) {
		if (client->c.active == true)
		{
			printf("| %2d | %16s | %10s | %20s | %10.2f |\n", client->c.id, client->c.name, client->c.nif, client->c.address, client->c.balance);

		}
		client = client->next;
	}

	printf("+------------------------------------------------------------------------+\n");

	if (Confirm() == IS_CANCELED)
		return;
	
}



void ShowAddVehicleMenu(VehicleList** firstVehicle) {
	Vehicle newVehicle;


	system("cls");
	printf("+------------------------------------------------+\n");
	printf("|                Add Vehicle                     |\n");
	printf("+------------------------------------------------+\n");
	printf("| Options:                                       |\n");
	printf("| 1- Bicicle                                     |\n");
	printf("| 2- Scooter                                     |\n");
	printf("| 3- Motorcycle                                  |\n");
	printf("| 4- Other                                       |\n");
	printf("+------------------------------------------------+\n");

	printf("Select vehicle: ");
	scanf_s("%d", &newVehicle.type);
	fflush(stdin);

	printf("Select Batery Charge: ");
	scanf_s("%f", &newVehicle.batteryCharge);
	fflush(stdin);

	printf("Select price for rent: ");
	scanf_s("%f", &newVehicle.price);
	fflush(stdin);

	printf("Select vehicle location: ");
	scanf_s("%s", newVehicle.location, LOCATION_LENGHT);
	fflush(stdin);

	if (Confirm() == IS_CANCELED)
		return;

	*firstVehicle = AddVehicle(firstVehicle, newVehicle);
	 
	SaveVehicle(VEHICLE_SAVE_FILE_NAME, *firstVehicle);
	
}

void RemoveVehicleMenu(VehicleList* firstVehicle) {

	int id;

	system("cls");
	printf("+------------------------------------------------+\n");
	printf("|              Remove Vehicle                    |\n");
	printf("+------------------------------------------------+\n");

	printf("ID: ");
	scanf_s("%d", &id);
	fflush(stdin);

	if (Confirm() == IS_CANCELED)
		return;

	RemoveVehicle(firstVehicle, id);

	SaveVehicle(VEHICLE_SAVE_FILE_NAME, firstVehicle);

	
}

void ShowEditVehicleMenu(VehicleList* firstVehicle) {
	Vehicle newVehicle;
	system("cls");
	printf("+------------------------------------------------+\n");
	printf("|              Edit Vehicle                      |\n");
	printf("+------------------------------------------------+\n");
	printf("ID: ");
	scanf_s("%d", &newVehicle.id);
	fflush(stdin);
	printf("Select Batery Charge: ");
	scanf_s("%f", &newVehicle.batteryCharge);
	fflush(stdin);
	printf("Select price for rent: ");
	scanf_s("%f", &newVehicle.price);
	fflush(stdin);
	printf("Select vehicle location: ");
	scanf_s("%s", newVehicle.location, LOCATION_LENGHT);
	fflush(stdin);
	if (Confirm() == IS_CANCELED)
		return;
	EditVehicle(firstVehicle, newVehicle);
	SaveVehicle(VEHICLE_SAVE_FILE_NAME, firstVehicle);
}

void ShowRentVehicleMenu(VehicleList* firstVehicle, ClientList* firstClient) {

	int clientId, vehicleId;

	system("cls");
	printf("+------------------------------------------------+\n");
	printf("|              Rent Vehicle                      |\n");
	printf("+------------------------------------------------+\n");
	printf("Client ID: ");
	scanf_s("%d", &clientId);
	fflush(stdin);

	printf("Vehicle ID: ");
	scanf_s("%d", &vehicleId);
	fflush(stdin);

	if (Confirm() == IS_CANCELED)
		return;

	Client* client = SearchById(firstClient, clientId);
	Vehicle* vehicle = SearchVehicleById(firstVehicle, vehicleId);

	if (client == NULL || vehicle == NULL)
		return;

	bool rentedVehicle = RentVehicle(vehicle, client);

	if (rentedVehicle)
		SaveVehicle(VEHICLE_SAVE_FILE_NAME, firstVehicle);

}



	void ShowVehicleListMenu(VehicleList * firstVehicle, ClientList * firstClient) {

		int i;


		system("cls");
		printf("+------------------------------------------------------------------------+\n");
		printf("| Id |   Type    | Battery Charge |   Price   |   Location   |  Client   |\n");
		printf("+------------------------------------------------------------------------+\n");

		VehicleList* currentVehicle = firstVehicle;
		while (currentVehicle != NULL) {
			if (currentVehicle->v.active) {
				Client* client = SearchById(firstClient, currentVehicle->v.rentedById);
				char* nameClient = client == NULL ? "" : client->name;

				printf("| %2d | %9s | %14.2f | %10.2f | %12s | %9s |", currentVehicle->v.id, VehicleTypeToString(currentVehicle->v.type), currentVehicle->v.batteryCharge, currentVehicle->v.price, currentVehicle->v.location,nameClient);



			}
			currentVehicle = currentVehicle->next;
		}



		printf("+------------------------------------------------------------------------+\n");


		if (Confirm() == IS_CANCELED)
			return;

}



void ShowVehicleByAutonomyMenu(VehicleList* firstVehicle, ClientList* firstClient) {

	firstVehicle= OrderVehicleByAutonomy(firstVehicle);
	ShowVehicleListMenu(firstVehicle, firstClient);
	firstVehicle = OrderVehicleById;
}




void ShowVehicleListByLocationMenu(VehicleList* firstVehicle, ClientList* firstClient) {
	char location[LOCATION_LENGHT];


	system("cls");
	printf("+------------------------------------------------+\n");
	printf("+              Search By Location                +\n");
	printf("+------------------------------------------------+\n");

	preintf("Select the geocode of the Location: ");
	scanf_s("%s", location, LOCATION_LENGHT);
	fflush(stdin);

	VehicleList* firstVehicleLocation = SearchvehicleByLocation(firstVehicle, location);
	
	ShowVehicleListMenu(firstVehicle, firstClient);

	ResetVehicle(firstVehicleLocation);


}

void ShowAddManagerMenu(ManagerList** firstManager) {

	Manager newManager;


	system("cls");
	printf("+------------------------------------------------+\n");
	printf("|                Add Manager                     |\n");
	printf("+------------------------------------------------+\n");
	printf("Name: ");
	scanf_s("%s", newManager.name, NAME_LENGHT);
	fflush(stdin);

	//email
	printf("Email: ");
	scanf_s("%s", newManager.email, EMAIL_LENGHT);
	fflush(stdin);

	printf("Password: ");
	scanf_s("%s", newManager.password, PASSOWORD_LENGHT);
	fflush(stdin);


	if (Confirm() == IS_CANCELED)
		return;

	*firstManager = AddManager(firstManager, newManager);
	
	SaveManager(MANAGER_SAVE_FILE_NAME, *firstManager);

	
}



void ShowEditManagerMenu(ManagerList* firstManager) {


	Manager newManager;

	system("cls");
	printf("+------------------------------------------------+\n");
	printf("|                Edit Manager                    |\n");
	printf("+------------------------------------------------+\n");

	printf("ID: ");
	scanf_s("%d", &newManager.id);


	printf("Name: ");
	scanf_s("%s", newManager.name, NAME_LENGHT);
	fflush(stdin);

	printf("Email: ");
	scanf_s("%s", newManager.email, EMAIL_LENGHT);
	fflush(stdin);

	printf("Password: ");
	scanf_s("%s", newManager.password, PASSOWORD_LENGHT);
	fflush(stdin);


	if (Confirm() == IS_CANCELED)
		return;

	EditManager(firstManager, newManager);

	SaveManager(MANAGER_SAVE_FILE_NAME, firstManager);



}


void ShowRemoveManagerMenu(ManagerList* firstManager) {
	int id;


	system("cls");
	printf("+------------------------------------------------+\n");
	printf("|                Remove Manager                  |\n");
	printf("+------------------------------------------------+\n");

	printf("ID: ");
	scanf_s("%d", &id);
	fflush(stdin);

	if (Confirm() == IS_CANCELED)
		return;

	RemoveManager(firstManager, id);

	SaveManager(MANAGER_SAVE_FILE_NAME, firstManager);


}


void ShowManagerListMenu(ManagerList* firstManager) {

	int i;

	system("cls");
	printf("+--------------------------------------------------------------------------+\n");
	printf("|                             Manager List                                 |\n");
	printf("+--------------------------------------------------------------------------+\n");
	printf("| Id |         Name           |                   Email                    |\n");
	printf("+--------------------------------------------------------------------------+\n");

	ManagerList* currentManager = firstManager;
	while (currentManager != NULL) {
		if (currentManager->m.active == true) {
			printf("| %2d | %22s | %45s |\n", currentManager->m.id, currentManager->m.name, currentManager->m.email);
		}

		currentManager = currentManager->next;
	}
	


	printf("+--------------------------------------------------------------------------+\n");

	if (Confirm() == IS_CANCELED)
		return;


}
