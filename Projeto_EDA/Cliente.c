/*****************************************************************//**
 * \file   Cliente.c
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/

//Includes
#include "Cliente.h"


void ResetClient(Client* lastClient) {
	Client* client = lastClient;

	while (client != NULL) {
		Client* lastClient = client;
		client = client->next;
		free(lastClient);
		
	}
}




void LoadInitialClients(Client* lastClient) {
	ResetClient(lastClient);
	lastClient = ReadInitialClients();
	SaveClient(lastClient);
}

Client* ReadInitialClients() {
	FILE* fp;

	if (fopen_s(&fp, HARDDATA_FILE_NAME, "r") != 0) {
		printf("Error opening file\n");
		return NULL;
	}

	Client* lastClient = NULL;
	char linha[Max_Size];

	while (fgets(linha, Max_Size, fp)) {
		Client* client = (Client*)malloc(sizeof(Client));

		if (client == NULL) {
			printf("Error allocating memory\n");
			return NULL;

		}

		char* context = NULL;
		char* camp = strtok_s(linha, ";", &context);
		client->id = atoi(camp);

		camp = strtok_s(NULL, ";", &context);
		strcpy_s(client->name, CLIENT_NAME_LENGHT, camp);

		camp = strtok_s(NULL, ";", &context);
		strcpy_s(client->address, CLIENT_ADDRESS_LENGHT, camp);

		camp = strtok_s(NULL, ";", &context);
		strcpy_s(client->nif, CLIENT_NIF_LENGHT, camp);

		camp = strtok_s(NULL, ";", &context);
		client->balance = atof(camp);

		camp = strtok_s(NULL, ";", &context);
		client->active = (bool)atoi(camp);

		client->next = lastClient;
		lastClient = client;
	}

	fclose(fp);

	return lastClient;

}

Client* ReadClient(){
	FILE* fp;
	 
	if (fopen_s(&fp, SAVE_FILE_NAME, "rb") != 0) {
		printf("Erro ao abrir ficheiro\n");
		return NULL;
	}

	Client* lastClient = NULL;
	char linha[Max_Size];

	while (fgets(linha, Max_Size, fp)) {
		Client* client = (Client*)malloc(sizeof(Client));

		if (client == NULL) {
			printf("Error allocating memory\n");
			return NULL;
		}

		char* contexto = NULL;
		char* campo = strtok_s(linha, ";", &contexto);
		client->id = atoi(campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(client->name, CLIENT_NAME_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(client->nif, CLIENT_NIF_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		strcpy_s(client->address, CLIENT_ADDRESS_LENGHT, campo);

		campo = strtok_s(NULL, ";", &contexto);
		client->balance = atof(campo);

		campo = strtok_s(NULL, ";", &contexto);
		client->active = (bool)atoi(campo);

		client->next = lastClient;
		lastClient = client;
	}

	fclose(fp);

	return lastClient;
}

void SaveClient(Client* lastClient){
	FILE* fp;
	Client* client = lastClient;

	if (fopen_s(&fp, SAVE_FILE_NAME, "wb") != 0) {
		printf("Error opening file\n");
		return;
	}
	if (lastClient == NULL) {
		printf("No clients to save\n");
		return;
	}

	while (client != NULL) {
		fprintf(fp, "%d;%s;%s;%s;%f;%d\n", client->id, client->name, client->nif, client->address, client->balance, client->active);
		client = client->next;
	}

	fclose(fp);

}

void AddClient(Client** lastClient, char* name, char* nif, char* address, float balance) {

	Client* client = (Client*)malloc(sizeof(Client));

	if (client == NULL) {
		printf("Error allocating memory\n");
			return;
	}
	client->id = (*lastClient == NULL) ? 1: (*lastClient)->id + 1;
	strcpy_s(client->name, CLIENT_NAME_LENGHT, name);
	strcpy_s(client->nif, CLIENT_NIF_LENGHT, nif);
	strcpy_s(client->address, CLIENT_ADDRESS_LENGHT, address);
	client->balance = balance;
	client->active = true;

	client->next = *lastClient;
	*lastClient = client;
}


void RemoveClient(Client* lastClient, int id){

	Client* client = lastClient;

	while (client != NULL) {
		if (client->id == id) {
			client->active = false;
			return;
		}
		client = client->next;
		
	}

}

void EditClient(Client* lastClient, int id, char* name, char* nif, char* address, float balance){

	Client* client = lastClient;

	while (client != NULL) {
		if (client->id == id) {
			strcpy_s(client->name, CLIENT_NAME_LENGHT, name);
			strcpy_s(client->nif, CLIENT_NIF_LENGHT, nif);
			strcpy_s(client->address, CLIENT_ADDRESS_LENGHT, address);
			client->balance = balance;
			return;
		}
		client = client->next;
	}

}
