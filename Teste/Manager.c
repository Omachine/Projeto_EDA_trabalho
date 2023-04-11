/*****************************************************************//**
 * \file   Manager.c
 * \brief
 *
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/

#include "Manager.h"

 /**
  * @brief Resets a list of managers and frees the allocated memory..
  *
  * \param firstManager
  * \return
  */
bool Resetmanager(ManagerList* firstManager) {
	ManagerList* currentManager = firstManager;

	while (currentManager != NULL) {
		ManagerList* lastManager = currentManager;
		currentManager = currentManager->next;
		free(lastManager);
	}
	firstManager = NULL;

	return true;
}
/**
 * @brief Loads the initial managers from a file and saves them to another file..
 *
 * \param firstManager
 * \param initialFilePath
 * \param saveFilePath
 * \return
 */
ManagerList* LoadInitialManagers(ManagerList* firstManager, char* initialFilePath, char* saveFilePath) {
	Resetmanager(firstManager);
	firstManager = ReadInitialManagers(initialFilePath);
	SaveManager(firstManager, saveFilePath);
	return true;
}

/**
 * @brief Reads the initial managers from a file and creates a linked list of managers..
 * The function reads the initial managers from a file specified by the file path and creates a linked list of managers.
 * Each line in the file represents a manager, with the fields separated by semicolons.
 * The fields are: ID, name, email, password, and active status (1 for active, 0 for inactive).
 * \param filePath
 * \return
 */
ManagerList* ReadInitialManagers(char* filePath) {

	FILE* file;
	ManagerList* firstManager = NULL;
	char line[Max_Size];

	file = fopen(filePath, "r");
	if (file == NULL)
		return NULL;

	while (fgets(line, Max_Size, file)) {
		ManagerList* newManager = (ManagerList*)malloc(sizeof(ManagerList));

		if (newManager == NULL) {
			printf("Error allocating memory\n");
			return NULL;
		}

		char* context = NULL;
		char* camp = strtok_s(line, ";", &context);
		newManager->m.id = atoi(camp);

		camp = strtok_s(NULL, ";", &context);
		strcpy(newManager->m.name, Max_Size, camp);

		camp = strtok_s(NULL, ";", &context);
		strcpy(newManager->m.email, Max_Size, camp);

		camp = strtok_s(NULL, ";", &context);
		strcpy(newManager->m.password, Max_Size, camp);

		camp = strtok_s(NULL, ";", &context);
		newManager->m.active = (bool)atoi(camp);

		newManager->next = firstManager;
		firstManager = newManager;

	}
	fclose(file);
	return firstManager;
}

/**
 * @brief Reads the managers from a binary file..
 * This function reads the managers stored in a binary file specified by the filePath parameter.
 * The managers are stored in a linked list of type ManagerList.
 * The function returns the first node of the linked list.
 * \param filePath
 * \return
 */
ManagerList* ReadManagers(char* filePath) {
	FILE* file;
	Manager* firstManager = NULL;

	file = fopen(filePath, "rb");

	if (file == NULL)
		return NULL;

	Manager manager;
	size_t bytesRead = fread(&manager, sizeof(Manager), 1, file);

	while (bytesRead > 0) {
		ManagerList* newManager = (ManagerList*)malloc(sizeof(ManagerList));

		if (newManager == NULL)
			return NULL;

		newManager->m.id = manager.id;
		strcpy(newManager->m.name, manager.name);
		strcpy(newManager->m.email, manager.email);
		strcpy(newManager->m.password, manager.password);
		newManager->m.active = manager.active;
		newManager->next = firstManager;
		firstManager = newManager;

		bytesRead = fread(&manager, sizeof(Manager), 1, file);

	}
	fclose(file);
	firstManager = OrderManagerById(firstManager);

	return firstManager;
}

bool SaveManager(char* filePath, ManagerList* firstManager) {
	FILE* file;
	file = fopen(filePath, "wb");

	if (file == NULL)
		return false;

	ManagerList* currentManager = firstManager;

	while (currentManager != NULL) {
		fwrite(&currentManager->m, sizeof(Manager), 1, file);
		currentManager = currentManager->next;
	}

	fclose(file);

	return true;
}


/**
 * @brief Saves the list of managers in a binary file.
 *
 * \param firstManager
 * \param newManager
 * \return
 */
ManagerList* AddManager(ManagerList* firstManager, Manager newManager) {
	ManagerList* newNode = (ManagerList*)malloc(sizeof(ManagerList));

	if (newNode == NULL)
		return firstManager;

	if (newManager.active == NULL)
		newManager.active = true;
	if (newManager.id == NULL)
		newManager.id = SearchNextManagerId(firstManager);

	newNode->next = (firstManager != NULL) ? firstManager : NULL;

	newNode->m = newManager;
	firstManager = newNode;

	return firstManager;
}
/**
 * @brief Removes a manager from the list by setting their 'active' status to false..
 *
 * \param firstManager
 * \param id
 * \return
 */
bool RemoveManager(ManagerList* firstManager, int id) {
	ManagerList* currentManager = firstManager;

	while (currentManager != NULL) {
		if (currentManager->m.id == id) {

			currentManager->m.active = false;
			return true;
		}

		currentManager = currentManager->next;
	}
	return false;
}
/**
 * @brief Edits an existing manager with the information of the provided manager..
 *
 * \param firstManager
 * \param selectedManager
 * \return
 */

bool EditManager(ManagerList* firstManager, Manager selectedManager) {
	ManagerList* currentManager = firstManager;

	while (currentManager != NULL) {
		if (currentManager->m.id == selectedManager.id) {
			strcpy(currentManager->m.name, selectedManager.name);
			strcpy(currentManager->m.email, selectedManager.email);
			strcpy(currentManager->m.password, selectedManager.password);
			return true;
		}
		currentManager = currentManager->next;
	}
	return false;
}
/**
 * @brief Orders the manager list by ID in descending order using a bubble sort algorithm..
 *
 * \param firstManager
 * \return
 */
ManagerList* OrderManagerById(ManagerList* firstManager) {
	ManagerList* current;
	ManagerList* next;
	Manager temp;

	for (current = firstManager; current != NULL; current = current->next) {
		for (next = current->next; next != NULL; next = next->next) {
			if (current->m.id < next->m.id) {
				temp = current->m;
				current->m = next->m;
				next->m = temp;
			}
		}
	}
	return firstManager;
}

/**
 * @brief Searches the next available manager id in the list by finding the maximum existing id and adding 1 to it..
 *
 * \param firstManager
 * \return
 */
int SearchNextManagerId(ManagerList* firstManager) {
	ManagerList* currentManager = firstManager;
	int id = 0;
	while (currentManager != NULL) {
		if (currentManager->m.id > id)
			id = currentManager->m.id;
		currentManager = currentManager->next;
	}
	return id + 1;
}

