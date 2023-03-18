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
#define CLIENT_ADDRESS_LENGHT 50
#define CLIENT_NIF_LENGHT 20

#define CLIENT_HARDDATA_FILE_NAME "Clientes.txt"
#define CLIENT_SAVE_FILE_NAME "Clientes.dat"

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

typedef struct ClientList {
	Client c;
	ClientList* next;
}ClientList;

bool ResetClient(Client* lastClient);

ClientList* LoadInitialClients(Client* lastClient, char* initialFilePath, char* saveFilePath);

ClientList* ReadInitialClients(char* filePath);

ClientList* ReadClient(char* filePath);

bool SaveClient(char* filePath, Client* lastClient);

ClientList* AddClient(ClientList* lastClient, Client newClient);

bool RemoveClient(Client* lastClient, int id);

bool EditClient(ClientList* lastClient, Client selectedClient);

ClientList* OrderById(ClientList* lastClient);

Client* SearchById(ClientList* lastClient);

int SearchNextId(ClientList* lastClient);

bool HasEnoughBalance(Client client, float value);

#endif
