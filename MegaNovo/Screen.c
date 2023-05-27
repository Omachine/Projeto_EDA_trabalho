/*****************************************************************//**
 * \file   Screen.c
 * \brief
 *
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/
#include "Screen.h"
 /**
  * @brief Displays the main menu of the program and reads the selected option..
  *
  * \param op
  */
void ShowMainMenu(int* op) {

	*op = -1;


	system("cls");

	printf("+------------------------------------------------+\n");
	printf("|              Moderator screen                  |\n");
	printf("+------------------------------------------------+\n");
	printf("| 1- Client Options                              |\n");
	printf("| 2- Vehicle Options                             |\n");
	printf("| 3- Manager Options                             |\n");
	printf("| 4- Load Initial Data                           |\n");
	printf("+------------------------------------------------+\n");
	printf("| 5- Exit                                        |\n");
	printf("+------------------------------------------------+\n");

	printf("Select an option: ");
	scanf_s("%d", op);

}

/**
 * @brief Remove is dados dos ficheiros binarios e carrega os dados iniciais
 *
 *
 *\param firstClient
 */
void LoadInitialData(ClientList** firstClient, VehicleList** firstVehicle, ManagerList** firstManager) {

	int op = -1;

	if (Confirm() == IS_CANCELED)
		return;

	*firstClient = LoadInitialClients(*firstClient, CLIENT_HARDDATA_FILE_NAME, CLIENT_SAVE_FILE_NAME);
	*firstVehicle = LoadVehicle(*firstVehicle, VEHICLE_HARDDATA_FILE_NAME, VEHICLE_SAVE_FILE_NAME);
	*firstManager = LoadInitialManagers(*firstManager, MANAGER_HARDDATA_FILE_NAME, MANAGER_SAVE_FILE_NAME);


}

//Mostra o menu cliente
void ShowClientMenu(ClientList* firstClient, int* op) {
	*op = -1;
	system("cls");

	printf("+------------------------------------------------+\n");
	printf("|              Client screen                     |\n");
	printf("+------------------------------------------------+\n");
	printf("| 1- Add Client                                  |\n");
	printf("| 2- Remove Client                               |\n");
	printf("| 3- Edit Client                                 |\n");
	printf("| 4- List CLients                                |\n");
	printf("+------------------------------------------------+\n");
	printf("| 5- Back                                        |\n");
	printf("+------------------------------------------------+\n");
	printf("Select an option: ");
	scanf_s("%d", op);

	void options1(ClientList * firstClient, int* op);
	
}


void options1(ClientList* firstClient, int* op) {
	while (*op != 0) {
		ShowMainMenu(&op);


		switch (*op) {
		case 1:
			ShowAddClientMenu(firstClient);
			break;
		case 2:
			ShowRemoveClientMenu(firstClient);
			break;
		case 3:
			ShowEditClientMenu(firstClient);
			break;
		case 4:
			ShowListClientMenu(firstClient);
			break;
		case 5:
			ShowMainMenu(&op);
			break;
		}

	}
}
//Mostra o menu veiculo
void ShowVehicleMenu(VehicleList* firstVehicle, ClientList* firstClient, int* op) {
	*op = -1;

	system("cls");

	printf("+------------------------------------------------+\n");
	printf("|              Vehicle screen                    |\n");
	printf("+------------------------------------------------+\n");
	printf("| 1- Add Vehicle                                 |\n");
	printf("| 2- Remove Vehicle                              |\n");
	printf("| 3- Edit Vehicle                                |\n");
	printf("| 4- Rent Vehicle                                |\n");
	printf("| 5- List Vehicles                               |\n");
	printf("| 6- List by Autonomy                            |\n");
	printf("| 7-Search by location                           |\n");
	printf("+------------------------------------------------+\n");
	printf("| 8- Back                                        |\n");
	printf("+------------------------------------------------+\n");
	printf("Select an option: ");
	scanf_s("%d", op);

	void options2(VehicleList * firstVehicle, ClientList * firstClient, int* op);
}
void options2(VehicleList* firstVehicle, ClientList* firstClient, int* op) {
	while (*op != 0) {
		ShowMainMenu(&op);


		switch (*op) {
		case 1:
			ShowAddClientMenu(firstVehicle);
			break;
		case 2:
			ShowRemoveClientMenu(firstVehicle);
			break;
		case 3:
			ShowEditVehicleMenu(firstVehicle);
			break;
		case 4:
			ShowRentVehicleMenu(firstVehicle, firstClient);
			break;
		case 5:
			ShowVehicleListMenu(firstVehicle, firstClient);
			break;
		case 6:
			ShowVehicleByAutonomyMenu(firstVehicle, firstClient);
			break;
		case 7:
			ShowVehicleListByLocationMenu(firstVehicle, firstClient);
			break;
		case 8:
			ShowMainMenu(&op);
			break;
		}

	}
}
//Mostra o menu moderador
void ShowManagerScreen(ManagerList* firstManager, int* op) {
	*op = -1;

	system("csl");

	printf("+------------------------------------------------+\n");
	printf("|              Manager screen                    |\n");
	printf("+------------------------------------------------+\n");
	printf("| 1- Add Manager                                 |\n");
	printf("| 2- Remove Manager                              |\n");
	printf("| 3- Edit Manager                                |\n");
	printf("| 4- List Managers                               |\n");
	printf("+------------------------------------------------+\n");
	printf("| 6- Back                                        |\n");
	printf("+------------------------------------------------+\n");
	printf("Select an option: ");
	scanf_s("%d", op);

	

}
void options3(ManagerList* firstManager, int* op) {
	while (*op != 0) {
		ShowMainMenu(&op);


		switch (*op) {
		case 1:
			ShowAddManagerMenu(firstManager);
			break;
		case 2:
			ShowRemoveManagerMenu(firstManager);
			break;
		case 3:
			ShowEditManagerMenu(firstManager);
			break;
		case 4:
			ShowManagerListMenu(firstManager);
			break;
		case 5:
			ShowMainMenu(&op);
			break;
		}

	}
}
//Mostra menu adicionar clinte
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
//Mostra menu remove cliente
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

	bool x= RemoveClient(firstClient, id);

	x = SaveClient(CLIENT_SAVE_FILE_NAME, firstClient);
}



//Mostra menu editar cliente
void ShowEditClientMenu(ClientList* firstClient) {
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

//Mostra menu listar clientes
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


//Mostra menu adicionar veiculo
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
//Menu remover veiculo
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
//Mostrar menu editar clientes
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
//Menu alugar veiculos
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

	Client* client = OrderByID(firstClient);
	Vehicle* vehicle = SearchVehicleById(firstVehicle, vehicleId);

	if (client == NULL || vehicle == NULL)
		return;

	bool rentedVehicle = RentVehicle(vehicle, client);

	if (rentedVehicle)
		SaveVehicle(VEHICLE_SAVE_FILE_NAME, firstVehicle);

}


//Menu listar veiculos
void ShowVehicleListMenu(VehicleList* firstVehicle, ClientList* firstClient) {

	int i;


	system("cls");
	printf("+------------------------------------------------------------------------+\n");
	printf("| Id |   Type    | Battery Charge |   Price   |   Location   |  Client   |\n");
	printf("+------------------------------------------------------------------------+\n");

	VehicleList* currentVehicle = firstVehicle;
	while (currentVehicle != NULL) {
		if (currentVehicle->v.active) {
			Client* client = SearchVehicleById(firstClient, currentVehicle->v.rentedById);
			char* nameClient = client == NULL ? "" : client->name;

			printf("| %2d | %9s | %14.2f | %10.2f | %12s | %9s |", currentVehicle->v.id, VehicleTypeToString(currentVehicle->v.type), currentVehicle->v.batteryCharge, currentVehicle->v.price, currentVehicle->v.location, nameClient);



		}
		currentVehicle = currentVehicle->next;
	}



	printf("+------------------------------------------------------------------------+\n");


	if (Confirm() == IS_CANCELED)
		return;

}


//Menu listar veiculos por autonomia
void ShowVehicleByAutonomyMenu(VehicleList* firstVehicle, ClientList* firstClient) {

	firstVehicle = OrderVehicleByAutonomy(firstVehicle);
	ShowVehicleListMenu(firstVehicle, firstClient);
	
}



//Menu listar vehiclus por localização
void ShowVehicleListByLocationMenu(VehicleList* firstVehicle, ClientList* firstClient) {
	char location[LOCATION_LENGHT];


	system("cls");
	printf("+------------------------------------------------+\n");
	printf("+              Search By Location                +\n");
	printf("+------------------------------------------------+\n");

	printf("Select the geocode of the Location: ");
	scanf_s("%s", location, LOCATION_LENGHT);
	fflush(stdin);

	VehicleList* firstVehicleLocation = SearchvehicleByLocation(firstVehicle, location);

	ShowVehicleListMenu(firstVehicle, firstClient);

	ResetVehicle(firstVehicleLocation);


}
//Menu adicionar Manager
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


//Menu editar manager
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

//Menu remover manager
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

//Menu lista de manager
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
