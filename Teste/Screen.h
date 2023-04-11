/*****************************************************************//**
 * \file   Screen.h
 * \brief
 *
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/
#pragma once
#ifndef ECRAS
#define ECRAS

#include <locale.h>
#include <stdio.h>
#include "Vehicle.h"
#include "Cliente.h"
#include "Manager.h"
#include "Utility.h"

void ShowMainMenu(int* op);
void LoadInitialData(ClientList** firstClient, VehicleList** firstVehicle, ManagerList** firstManager);
void ShowClientMenu(int* op);
void ShowVehicleMenu(int* op);
void ShowManagerScreen(int* op);
void ShowAddClientMenu(ClientList** lastClient);
void ShowEditClientMenu(ClientList* firstClient);
void ShowListClientMenu(ClientList* firstClient);
void ShowAddVehicleMenu(VehicleList** firstVehicle);
void RemoveVehicleMenu(VehicleList* firstVehicle);
void ShowEditVehicleMenu(VehicleList* firstVehicle);
void ShowRentVehicleMenu(VehicleList* firstVehicle, ClientList* firstClient);
void ShowVehicleListMenu(VehicleList* firstVehicle, ClientList* firstClient);
void ShowVehicleByAutonomyMenu(VehicleList* firstVehicle, ClientList* firstClient);
void ShowVehicleListByLocationMenu(VehicleList* firstVehicle, ClientList* firstClient);
void ShowAddManagerMenu(ManagerList** firstManager);
void ShowEditManagerMenu(ManagerList* firstManager);
void ShowRemoveManagerMenu(ManagerList* firstManager);
void ShowManagerListMenu(ManagerList* firstManager);








#endif // !ECRAS
