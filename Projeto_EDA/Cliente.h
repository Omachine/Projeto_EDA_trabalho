/*****************************************************************//**
 * \file   Cliente.h
 * \brief  
 * 
 * \author Gon�alo M.
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

/**
 * Fun��o para limpar os dados de clientes nos ficheiros
 * 
 * .
 */
bool ResetClient(Client* lastClient);

/**
 * .Fun��o para carregar os dados iniciais de clientes
 */

ClientList* LoadInitialClients(ClientList* lastClient, char* initialFilePath, char* saveFilePath);
/**
 * Fun��o para ler os dados iniciais de clientes
 * .
 */

ClientList* ReadInitialClients(char* filePath);
/**
 * Fun��o para ler os dados de clientes
 * .
 */

ClientList* ReadClient(char* filePath);
/**
 * Fun��o para guardar os dados de clientes na Lista
 * .
 */

bool SaveClient(char* filePath, ClientList* lastClient);
/**
 * Fun��o para adicionar um cliente a lista
 * .
 */

ClientList* AddClient(ClientList* lastClient, Client newClient);
/**
 * Fun��o para remover um cliente da lista
 *  .
 * */

bool RemoveClient(ClientList* lastClient, int id);
/**
 * Fun��o para editar um cliente da lista
 * .
 */

bool EditClient(ClientList* lastClient, Client selectedClient);
/**
 * Fun��o para ordenar os clientes da lista a partir do seu id
 * .
 */

ClientList* OrderByID(ClientList* lastClient);
/**
 * Fun��o para procurar um cliente a partir do seu id
 * 
 * .
 */

Client* SearchbyId(ClientList* lastClient, int id);
/**
 * Fun��o para procurar o id do cliente a seguir ao selecionado
 * .
 */


int SearchNextId(ClientList* lastClient);
/**
 * Fun��o para verificar se o cliente tem saldo suficiente para pagar o aluguel
 * .
 */
bool HasEnoughBalance(Client client, float value);



#endif



