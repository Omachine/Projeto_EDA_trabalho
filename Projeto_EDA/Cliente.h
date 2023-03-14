/*****************************************************************//**
 * \file   Cliente.h
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/
#pragma once


#ifndef CLIENTE
#define CLIENTE

	//Includes
#include "Utility.h"
    //Constants
#define CLIENT_NAME_LENGHT 50
#define CLIENT_ADDRESS_LENGHT 100
#define CLIENT_NIF_LENGHT 9
#define HARDDATA_FILE_NAME "Clientes.txt"
#define SAVE_FILE_NAME "Clientes.dat"

//Structs

typedef struct Client {
	int id;
	char name[CLIENT_NAME_LENGHT];
	char address[CLIENT_ADDRESS_LENGHT];
	char nif[CLIENT_NIF_LENGHT];
	float balance;
	bool active;
	struct Client* next;
	
} Client;


void ResetClient(Client* lastClient);

void LoadInitialClients(Client* lastClient);

Client* ReadInitialClients();

Client* ReadClient();

void SaveClient(Client* lastClient);

void AddClient(Client** lastClient, char* name, char* nif, char* address, float balance);

void RemoveClient(Client* lastClient, int id);

void EditClient(Client* lastClient, int id, char* name, char* nif, char* address, float balance);

#endif
