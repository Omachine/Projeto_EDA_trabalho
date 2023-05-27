/*****************************************************************//**
 * \file   Cliente.c
 * \brief
 *
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/

 //Includes
#include "Cliente.h"


/**
 * @brief Limpa a lista de dados dos clientes.
 * A função percorre a lista de clientes, verificando se cada um deles existe e liberando a memória associada a ele.
 * \param lastClient
 * \return
 */
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



/**
 * @brief Carrega a lista de clientes inicial a partir de um arquivo e a salva em outro arquivo.
 *A função limpa a lista de clientes, lê os dados dos clientes a partir do arquivo especificado pelo caminho "initialFilePath",
 *  adiciona os clientes lidos à lista e salva a lista no arquivo especificado pelo caminho "saveFilePath".
 * \param lastClient
 * \param initialFilePath
 * \param saveFilePath
 * \return
 */
ClientList* LoadInitialClients(ClientList* lastClient, char* initialFilePath, char* saveFilePath) {
	ResetClient(lastClient);
	lastClient = ReadInitialClients(initialFilePath);
	SaveClient(lastClient, lastClient);

	return true;
}
/**
 * @brief Lê os dados dos clientes a partir de um arquivo e os adiciona a uma lista encadeada.
 * A função lê os dados dos clientes a partir do arquivo especificado pelo caminho "filePath"
 *  e cria um nó para cada cliente lido.
 * Cada nó contém as informações de um cliente e um ponteiro para o próximo nó da lista.
 *
 * \param filePath
 * \return
 */
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


/**
 * @brief Lê os dados dos clientes a partir de um arquivo binário e os adiciona a uma lista encadeada.
 * A função lê os dados dos clientes a partir do arquivo especificado pelo caminho "filePath" e cria um nó para cada cliente lido.
 * Cada nó contém as informações de um cliente e um ponteiro para o próximo nó da lista.
 *
 * \param filePath
 * \return
 */

ClientList* ReadClient(char* filePath) {
	FILE* file;
	ClientList* lastClient = NULL;
	file = fopen(filePath, "rb");

	if (file == NULL) {
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
		newClient->next = lastClient;
		lastClient = newClient;

		bytesRead = fread(&client, sizeof(Client), 1, file);
	}

	fclose(file);

	return lastClient;
}


/**
 *
 * A função vai guardar os clientes da lista em ficheiro binário.
 *
 * \param filePath
 * \param lastClient
 * \return
 */

bool SaveClient(char* filePath, ClientList* lastClient) {
	FILE* file;
	file = fopen(filePath, "wb");



	if (file == NULL) {
		return false;
	}
	ClientList* currentClient = lastClient;

	while (currentClient != NULL) {
		fprintf(&currentClient->c, sizeof(Client), 1, file);	//fwrite
		currentClient = currentClient->next;
	}

	fclose(file);

	return true;

}

/**
 * @brief Salva os dados dos clientes em um arquivo binário.
 * A função percorre a lista encadeada de clientes a partir do ponteiro "lastClient" e salva as informações de cada cliente em um arquivo binário
 * especificado pelo caminho "filePath".
 * \param lastClient
 * \param newClient
 * \return
 */

ClientList* AddClient(ClientList* lastClient, Client newClient) {

	ClientList* newNode = (ClientList*)malloc(sizeof(ClientList));

	if (newNode == NULL) {
		//printf("Error allocating memory\n");
		return;//REVER
	}
	
	newClient.active = true;
	newClient.id = SearchNextId(lastClient);
	newNode->next = (lastClient != NULL) ? lastClient : NULL;
	
	newNode->c = newClient;
	lastClient = newNode;

	return lastClient;
}


/**
 * @brief Remove um cliente da lista pelo seu id
 * A função vai tornar os clientes inativos
 * A função percorre a lista de clientes até encontrar o cliente com o id especificado e altera o valor do atributo "active" para false, removendo-o da lista de clientes ativos.
 * \param lastClient
 * \param id
 * \return
 */
bool RemoveClient(ClientList* lastClient, int id) { // ** para devolver lista alterada e bool

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
/**
 * @brief Edita os dados de um cliente pelo seu id
 * A função percorre a lista de clientes até encontrar o cliente com o id especificado
 *  e atualiza os valores dos atributos de acordo com os valores do cliente selecionado.
 * \param lastClient
 * \param selectedClient
 * \return
 */

bool EditClient(ClientList* lastClient, Client selectedClient) {

	ClientList* currentClient = lastClient;

	while (currentClient != NULL) {
		if (currentClient->c.id == selectedClient.id) {
			strcpy(currentClient->c.name, selectedClient.name);
			strcpy(currentClient->c.nif, selectedClient.nif);
			strcpy(currentClient->c.address, selectedClient.address);
			currentClient->c.balance = selectedClient.balance;
			return true;
		}
		currentClient = currentClient->next;
	}
	return true;
}

/**
 * .@brief Ordena a lista de clientes pelo ID em ordem decrescente
 * A função percorre a lista de clientes e compara o ID de cada um com o ID dos clientes
 * seguintes, trocando a posição dos clientes caso necessário, até que toda a lista esteja ordenada em ordem decrescente pelo ID.
 * \param lastClient
 * \return
 */

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

/**
 * @brief Procura um cliente na lista pelo seu ID
 * .Esta função percorre a lista de clientes e procura o cliente com o ID especificado.
 * \param lastClient
 * \param id
 * \return
 */
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

/**
 * @brief Procura o próximo ID disponível na lista de clientes..
 * A função percorre a lista de clientes e retorna o próximo ID disponível para adicionar um novo cliente.
 * \param lastClient
 * \return
 */
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
/**
 * @brief Verifica se o cliente tem saldo suficiente para efetuar uma operação.
 * A função recebe um cliente e um valor e verifica se o saldo do cliente é maior ou igual ao valor fornecido.
 * \param client
 * \param value
 * \return
 */
bool HasEnoughBalance(Client client, float value) {
	return client.balance >= value;
}



