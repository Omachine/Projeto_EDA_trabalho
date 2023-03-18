/*****************************************************************//**
 * \file   Cliente.c
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/

//Includes
#include "Cliente.h"


bool ResetClient(Client* lastClient) {
	Client* client = lastClient;

	while (client != NULL) {
		Client* lastClient = client;
		client = client->next;
		free(lastClient);
		
	}

	lastClient = NULL;

	return true;
}




ClientList* LoadInitialClients(ClientList* lastClient, char* initialFilePath, char* saveFilePath) {
	ResetClient(lastClient);
	lastClient = ReadInitialClients(initialFilePath);
	SaveClient(lastClient, lastClient);

	return true;
}

ClientList* ReadInitialClients(char* filePath) {
	FILE* file;
	ClientList* lastClient = NULL;
	char line[Max_Size];
	file = fopen(filePath, "r");

	if (file == NULL) {
		printf("Error opening file\n");
		return NULL;
	}

	while (fgets(line, Max_Size, file)) {
		ClientList* newClient = (ClientList*)malloc(sizeof(ClientList));

		if (newClient == NULL) {
			printf("Error allocating memory\n");
			return NULL;

		}

		char* context = NULL;
		char* camp = strtok_s(line, ";", &context);
		newClient->c.id = atoi(camp);

		camp = strtok_s(NULL, ";", &context);
		strcpy_s(newClient->c.name, CLIENT_NAME_LENGHT, camp);

		camp = strtok_s(NULL, ";", &context);
		strcpy_s(newClient->c.address, CLIENT_ADDRESS_LENGHT, camp);

		camp = strtok_s(NULL, ";", &context);
		strcpy_s(newClient->c.nif, CLIENT_NIF_LENGHT, camp);

		camp = strtok_s(NULL, ";", &context);
		newClient->c.balance = atof(camp);

		camp = strtok_s(NULL, ";", &context);
		newClient->c.active = (bool)atoi(camp);

		newClient->next = lastClient;
		lastClient = newClient;
	}

	fclose(file);

	return lastClient;

}

ClientList* ReadClient(char* filePath){
	FILE* file;
	ClientList* lastClient = NULL;
	file = fopen(filePath, "rb");
	
	if(file==NULL) {
		printf("Erro ao abrir ficheiro\n");
		return NULL;
	}

	Client client;
size_t bytesRead = fread(&client, sizeof(Client), 1, file);

	while (bytesRead > 0) {
		ClientList* newClient = (ClientList*)malloc(sizeof(ClientList));

		if (newClient == NULL) {
			printf("Error allocating memory\n");
			return NULL;
		}

		newClient->c.id = client.id;

		strcpy(newClient->c.name, client.name);
		strcpy(newClient->c.address, client.address);
		strcpy(newClient->c.nif, client.nif);
		newClient->c.balance = client.balance;
		newClient->c.active = client.active;
		newClient->next=lastClient;
		lastClient = newClient;

		bytesRead = fread(&client, sizeof(Client), 1, file);
	}

	fclose(file);

	return lastClient;
}

bool SaveClient(char* filePath, ClientList* lastClient){
	FILE* file;
	file = fopen(filePath, "wb");


	
	if (file == NULL) {
		return false;
	}
	ClientList* currentClient = lastClient;

	while (currentClient != NULL) {
		fprintf(&currentClient->c, sizeof(Client), 1, file);
		currentClient = currentClient->next;
	}

	fclose(file);

	return true;

}

ClientList* AddClient(ClientList* lastClient, Client newClient) {

	ClientList* newNode = (ClientList*)malloc(sizeof(ClientList));

	if (newNode == NULL) {
		printf("Error allocating memory\n");
			return;
	}
	
	newClient.active = true;
	newClient.id = SearchNextId(lastClient);
	newNode->next = (lastClient != NULL) ? lastClient : NULL;

	newNode->c = newClient;
	lastClient = newNode;

	return lastClient;
}



bool RemoveClient(ClientList* lastClient, int id){

	ClientList* currentClient = lastClient;

	while (currentClient != NULL) {
		if (currentClient->c.id == id) {
			currentClient->c.active = false;
			return true;
		}
		currentClient = currentClient->next;
		
	}
	return true;
}

bool EditClient(ClientList* lastClient,Client selectedClient){

	ClientList* currentClient = lastClient;

	while (currentClient != NULL) {
		if (currentClient->c.id == selectedClient.id) {
			strcpy(currentClient->c.name,selectedClient.name);
			strcpy(currentClient->c.nif, selectedClient.nif);
			strcpy(currentClient->c.address, selectedClient.address);
			currentClient->c.balance = selectedClient.balance;
			return true;
		}
		currentClient = currentClient->next;
	}
	return true;
}



ClientList* OrderByID(ClientList* lastClient) {
	ClientList* current;
	ClientList* next;
	Client temp;
	
	for (current = lastClient; current != NULL; current = current->next) {
		
		for (next = current->next; next != NULL; next = next->next) {
				if (current->c.id < next->c.id) {
					temp = current->c;
					current->c = next->c;
					next->c = temp;
				}
				
			}
			
		
	}
	return lastClient;
}


Client* SearchbyId(ClientList* lastClient, int id) {
	ClientList* currentClient = lastClient;
	while (currentClient != NULL) {
		if (currentClient->c.id == id) {
			return &(currentClient->c);
		}
		currentClient = currentClient->next;
	}
	return NULL;
}


int SearchNextId(ClientList* lastClient) {
	ClientList* currentClient = lastClient;
	int id = 0;
	while (currentClient != NULL) {
		if (currentClient->c.id > id) {
			id = currentClient->c.id;
		}
		currentClient = currentClient->next;
	}
	return id + 1;
}

bool HasEnoughBalance(Client client, float value) {
	return client.balance >= value;
}
