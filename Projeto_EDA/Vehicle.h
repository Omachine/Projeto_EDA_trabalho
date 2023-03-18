/*****************************************************************//**
 * \file   Vehicle.h
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/
#pragma once

#ifndef VEHICLE
#define VEHICLE
	//Includes

#include "Utility.h"
#include "Cliente.h"

//Constants
#define LOCATION_LENGHT 20

#define VEHICLE_HARDDATA_FILE_NAME "Vehicle.txt"
#define CLIENT_SAVE_FILE_SAVE "Vehicle.dat"

typedef enum {
	Bycicle,
	Scooter,
	Motorcycle,
	Other
} TypeVehicle;

//structs
typedef struct Vehicle {
	int id;
	TypeVehicle type;
	float bateryCharge;
	float price;
	char location [LOCATION_LENGHT];
	int rentedById;
	bool active;
	struct Vehicle* next;
}Vehicle;

typedef struct VehicleList {
	Vehicle v;
	VehicleList* next;
}VehicleList;

bool ResetVehicle(Vehicle* firstVehicle);

VehicleList* LoadVehicle(Vehicle* firstVehicle);

VehicleList* ReadFirstVehicle();

VehicleList* ReadVehicle();

bool SaveVehicle(Vehicle* firstVehicle);

VehicleList* AddVehicle(Vehicle* firstVehicle, Vehicle* newVehicle);

bool RemoveVehicle(Vehicle* firstVehicle, int id);

bool EditVehicle(Vehicle* firstVehicle, Vehicle* selectedVehicle);

char* VehicleTypeToString(TypeVehicle TypeVehicle);

VehicleList* OrderVehicleById(VehicleList* firstVehicle);

VehicleList* OrderVehicleByAutonomy(VehicleList* firstVehicle);

VehicleList* SearchVehicleLocation(VehicleList* firstVehicle);

VehicleList* SearchvehicleById(VehicleList* firstVehicle, int id);

int SearchNextVehicleId(VehicleList* firstVehicle);

bool RentVehicle(Vehicle* vehicle, Client* client);

bool RentedVehicle(Vehicle vehicle);



#endif

