/*****************************************************************//**
 * \file   Vehicle.c
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/


#include "Vehicle.h"


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

VehicleList* LoadVehicle(Vehicle* firstVehicle, char* initialFilePath, char* saveFilePath) {
	ResetVehicle(firstVehicle);
	firstVehicle = ReadFirstVehicle(initialFilePath);
	SaveVehicle(firstVehicle, firstVehicle);
	return firstVehicle;
}

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
		VehicleList* newVehicle= (Vehicle*)malloc(sizeof(Vehicle));

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
		firstVehicle= newVehicle;
		
		bytesRead = fread(&vehicle, sizeof(Vehicle), 1, file);
	}
	fclose(file);
	firstVehicle = OrderVehiclesByID(firstVehicle);
	return firstVehicle;
}

bool SaveVehicle(char* filePath, VehicleList* firstVehicle) {
	FILE* file;
	file = fopen(VEHICLE_SAVE_FILE_NAME, "wb");

	if (file == NULL) {
		printf("Error opening file\n");
		return false;
	}

	VehicleList* currentVehicle = firstVehicle;

	while(currentVehicle != NULL) 
		fwrite(&currentVehicle->v, sizeof(Vehicle), 1, file);
		currentVehicle = currentVehicle->next;


	fclose(file);
	return true; 
}


VehicleList* AddVehicle(VehicleList* firstVehicle, Vehicle newVehicle) {
	VehicleList* newNode = (VehicleList*)malloc(sizeof(VehicleList));
	
	if (newNode == NULL)
			return false;

	newVehicle.active = true;
	newVehicle.id = GetNextVehicleId(firstVehicle);
	newNode->next = (firstVehicle != NULL) ? firstVehicle : NULL;
	
	newNode->v = newVehicle;
	firstVehicle = newNode;

		return true;
	}


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

bool EditVehicle(VehicleList* firstVehicle, Vehicle selectedVehicle) {

	VehicleList* currentVehicle = firstVehicle;

	while (currentVehicle->next != NULL ){

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

VehicleList* OrderVehicleById(VehicleList* firstVehicle) {
	VehicleList* current;
	VehicleList* next;
	Vehicle temp;

	for (current = firstVehicle; next != NULL; current = current->next) {
		for (next = current->next; next != NULL; next = next->next) {
			if (current->v.id > next->v.id) {
				temp = current->v;
				current->v = next->v;
				next->v = temp;
			}
		}
	}
	return firstVehicle;
}

VehicleList* OrderVehicleByAutonomy(VehicleList* firstVehicle) {
	VehicleList* current;
	VehicleList* next;
	Vehicle temp;
	for (current = firstVehicle; next != NULL; current = current->next) {
		for (next = current->next; next != NULL; next = next->next) {
			if (current->v.batteryCharge < next->v.batteryCharge) {
				temp = current->v;
				current->v = next->v;
				next->v = temp;
			}
		}
	}
	return firstVehicle;
}


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



VehicleList* SearchVehicleById(VehicleList*firstVehicle, int id){
VehicleList* currentVehicle = firstVehicle;
while (currentVehicle != NULL) {
	if (currentVehicle->v.id == id) {
			return &(currentVehicle->v);
		}
		currentVehicle = currentVehicle->next;
	}
	return NULL;
}

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


bool RentedVehicle(Vehicle vehicle) {
	return vehicle.rentedById != 0;
}
