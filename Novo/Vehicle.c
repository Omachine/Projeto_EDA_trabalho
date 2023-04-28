/*****************************************************************//**
 * \file   Vehicle.c
 * \brief
 *
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/


#include "Vehicle.h"

 /**
  * .@brief Liberta a memória alocada para a lista de veículos.
  * A função percorre a lista de veículos e libera a memória alocada para cada um deles.
  * \param firstVehicle
  * \return
  */
bool ResetVehicle(Vehicle* firstVehicle) {
	Vehicle* currentVehicle = firstVehicle;
	while (currentVehicle != NULL) {
		Vehicle* temp = currentVehicle;
		currentVehicle = currentVehicle->next;
		free(temp);
	}
	firstVehicle = NULL;

	return true;
}
/**
 * .@brief Carrega a lista de veículos a partir de um ficheiro.
 * Esta função irá resetar a lista de veículos existente,
 *  carregar os veículos do ficheiro especificado por initialFilePath e
 * guardar a lista de veículos no ficheiro especificado por saveFilePath.
 * \param firstVehicle
 * \param initialFilePath
 * \param saveFilePath
 * \return
 */
VehicleList* LoadVehicle(Vehicle* firstVehicle, char* initialFilePath, char* saveFilePath) {
	ResetVehicle(firstVehicle);
	firstVehicle = ReadFirstVehicle(initialFilePath);
	SaveVehicle(firstVehicle, firstVehicle);
	return firstVehicle;
}
/**
 * @brief Le um ficheiro de texto com os dados dos veiculos e cria uma lista encadeada de veiculos
 * A funcao le um ficheiro de texto com os dados dos veiculos, cria uma lista encadeada de veiculos
 * e retorna o ponteiro para o primeiro elemento da lista.
 * \param filePath
 * \return
 */
VehicleList* ReadFirstVehicle(char* filePath) {
	FILE* file;
	VehicleList* firstVehicle = NULL;
	char line[Max_Size];

	if (fopen_s(&file, VEHICLE_HARDDATA_FILE_NAME, "r") != 0) {
		printf("Error opening file\n");
		return NULL;
	}
	while (fgets(line, Max_Size, file)) {
		VehicleList* newVehicle = (VehicleList*)malloc(sizeof(VehicleList));
		if (newVehicle == NULL) {
			printf("Error allocating memory\n");
			return NULL;
		}
		char* context = NULL;
		char* camp = strtok(line, ";");
		newVehicle->v.id = atoi(camp);
		camp = strtok(NULL, ";");
		newVehicle->v.type = atoi(camp);
		camp = strtok(NULL, ";");
		newVehicle->v.batteryCharge = atof(camp);
		camp = strtok(NULL, ";");
		newVehicle->v.price = atof(camp);
		camp = strtok(NULL, ";");
		strcpy(newVehicle->v.location, Max_Size, camp);
		camp = strtok(NULL, ";");
		newVehicle->v.active = (bool)atoi(camp);
		camp = strtok(NULL, ";");
		newVehicle->next = firstVehicle;

	}


	fclose(file);
	return firstVehicle;
}

/**
 * .@brief Lê um arquivo binário contendo informações de veículos e retorna uma lista encadeada de veículos.
 * A função aloca memória para cada nó da lista encadeada
 * \param filePath
 * \return
 */

VehicleList* ReadVehicle(char* filePath) {
	FILE* file;
	VehicleList* firstVehicle = NULL;

	file = fopen(VEHICLE_SAVE_FILE_NAME, "rb");

	if (file == NULL) {
		printf("Error opening file\n");
		return NULL;
	}

	Vehicle vehicle;
	size_t bytesRead = fread(&vehicle, sizeof(Vehicle), 1, file);

	while (bytesRead > 0) {
		VehicleList* newVehicle = (Vehicle*)malloc(sizeof(Vehicle));

		if (newVehicle == NULL) {
			printf("Error allocating memory\n");
			return NULL;
		}

		newVehicle->v.id = vehicle.id;
		newVehicle->v.type = vehicle.type;
		newVehicle->v.batteryCharge = vehicle.batteryCharge;
		newVehicle->v.price = vehicle.price;
		strcpy(newVehicle->v.location, Max_Size, vehicle.location);
		newVehicle->v.active = vehicle.active;
		newVehicle->v.next = firstVehicle;
		firstVehicle = newVehicle;

		bytesRead = fread(&vehicle, sizeof(Vehicle), 1, file);
	}
	fclose(file);
	firstVehicle = OrderVehicleById(firstVehicle);
	return firstVehicle;
}
/**
 * .@brief Salva as informações de uma lista encadeada de veículos em um arquivo binário
 *
 * \param filePath
 * \param firstVehicle
 * \return
 */
bool SaveVehicle(char* filePath, VehicleList* firstVehicle) {
	FILE* file;
	file = fopen(VEHICLE_SAVE_FILE_NAME, "wb");

	if (file == NULL) {
		printf("Error opening file\n");
		return false;
	}

	VehicleList* currentVehicle = firstVehicle;

	while (currentVehicle != NULL)
		fwrite(&currentVehicle->v, sizeof(Vehicle), 1, file);
	currentVehicle = currentVehicle->next;


	fclose(file);
	return true;
}

/**
 * @brief Adiciona um novo veículo na lista de veículos
 *
 * \param firstVehicle
 * \param newVehicle
 * \return
 */
VehicleList* AddVehicle(VehicleList* firstVehicle, Vehicle newVehicle) {
	VehicleList* newNode = (VehicleList*)malloc(sizeof(VehicleList));

	if (newNode == NULL)
		return false;

	newVehicle.active = true;
	newVehicle.id = SearchNextVehicleId(firstVehicle);
	newNode->next = (firstVehicle != NULL) ? firstVehicle : NULL;

	newNode->v = newVehicle;
	firstVehicle = newNode;

	return true;
}

/**
 * .@brief Remove um veículo da lista de veículos ativos.
 *
 * \param firstVehicle
 * \param id
 * \return
 */
bool RemoveVehicle(VehicleList* firstVehicle, int id) {
	VehicleList* currentVehicle = firstVehicle;

	while (currentVehicle->next != NULL) {

		if (currentVehicle->v.id == id) {
			currentVehicle->v.active = false;
			return;
		}
		currentVehicle = currentVehicle->next;
	}
	return false;

}
/**
 * .@brief Edita um veículo existente na lista de veículos.
 *
 * \param firstVehicle
 * \param selectedVehicle
 * \return
 */
bool EditVehicle(VehicleList* firstVehicle, Vehicle selectedVehicle) {

	VehicleList* currentVehicle = firstVehicle;

	while (currentVehicle->next != NULL) {

		if (currentVehicle->v.id == selectedVehicle.id) {
			currentVehicle->v.type = selectedVehicle.type;
			currentVehicle->v.batteryCharge = selectedVehicle.batteryCharge;
			currentVehicle->v.price = selectedVehicle.price;
			strcpy(currentVehicle->v.location, selectedVehicle.location);
			return;
		}

		currentVehicle = currentVehicle->next;
	}

	return true;

}
/**
 * Converts a TypeVehicle enum to a string representation..
 *
 * \param TypeVehicle
 * \return
 */
char* VehicleTypeToString(TypeVehicle TypeVehicle) {

	switch (TypeVehicle) {
	case Bycicle:
		return"Bycicle";
	case Scooter:
		return"Scooter";
	case Motorcycle:
		return "Motorcycle";
	case Other:
		return"Other";
	default:
		return "Unknown";
	}
}
/**
 * @brief Orders a linked list of vehicles by their ID in ascending order..
 *
 * \param firstVehicle
 * \return
 */
VehicleList* OrderVehicleById(VehicleList* firstVehicle) {
	VehicleList* current;
	VehicleList* n=NULL;
	Vehicle temp;

	for (current = firstVehicle; (n != NULL); current = current->next) {
		for (n = current->next; n != NULL; n = n->next) {
			if (current->v.id > n->v.id) {
				temp = current->v;
				current->v = n->v;
				n->v = temp;
			}
		}
	}
	return firstVehicle;
}
/**
 * .@brief Orders the list of vehicles by their autonomy (battery charge), from highest to lowest.
 *
 * \param firstVehicle
 * \return
 */
VehicleList* OrderVehicleByAutonomy(VehicleList* firstVehicle) {
	VehicleList* current;
	VehicleList* n=NULL; //REVER
	Vehicle temp;
	for (current = firstVehicle; n != NULL; current = current->next) {
		for (n = current->next; n != NULL; n = n->next) {
			if (current->v.batteryCharge < n->v.batteryCharge) {
				temp = current->v;
				current->v = n->v;
				n->v = temp;
			}
		}
	}
	return firstVehicle;
}

/**
 *  @brief Searches for vehicles with a given location and returns a new linked list containing them.
 *
 * \param firstVehicle
 * \param location
 * \return
 */
VehicleList* SearchvehicleByLocation(VehicleList* firstVehicle, char* location) {
	VehicleList* vehicleLocation = NULL;
	VehicleList* currentVehicle = firstVehicle;


	while (currentVehicle != NULL) {
		if (strcmp(currentVehicle->v.location, location) == 0) {
			vehicleLocation = AddVehicle(vehicleLocation, currentVehicle->v);
		}
		currentVehicle = currentVehicle->next;
	}
	return vehicleLocation;
}

/**
 * .Searches for a vehicle in the given linked list based on its ID.
 *
 * \param firstVehicle
 * \param id
 * \return
 */

VehicleList* SearchVehicleById(VehicleList* firstVehicle, int id) {
	VehicleList* currentVehicle = firstVehicle;
	while (currentVehicle != NULL) {
		if (currentVehicle->v.id == id) {
			return &(currentVehicle->v);
		}
		currentVehicle = currentVehicle->next;
	}
	return NULL;
}
/**
 * .@brief Search for the next available vehicle ID.
 * This function searches through the linked list of vehicles and finds the largest ID. It then returns that ID plus 1 to obtain the next available ID.
 * \param firstVehicle
 * \return
 */
int SearchNextVehicleId(VehicleList* firstVehicle) {
	VehicleList* currentVehicle = firstVehicle;
	int id = 0;

	while (currentVehicle != NULL) {
		if (currentVehicle->v.id > id)
			id = currentVehicle->v.id;

		currentVehicle = currentVehicle->next;
	}
	return id + 1;
}

/**
 * @brief Attempts to rent a vehicle to a client.
 *
 * \param vehicle
 * \param client
 * \return
 */
bool RentVehicle(Vehicle* vehicle, Client* client) {
	if (!HasEnoughBalance(*client, vehicle->price))
		return false;

	if (vehicle->active == false)
		return false;

	if (RentedVehicle(*vehicle))
		return false;

	vehicle->rentedById = client->id;
	client->balance -= vehicle->price;

	return true;
}

/**
 * @brief Checks if a vehicle is currently rented..
 *
 * \param vehicle
 * \return
 */
bool RentedVehicle(Vehicle vehicle) {
	return vehicle.rentedById != 0;
}
