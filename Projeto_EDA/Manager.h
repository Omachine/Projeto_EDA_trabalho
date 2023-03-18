/*****************************************************************//**
 * \file   Manager.h
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/

#pragma once

#ifndef MANAGER
#define MANAGER

#include "Utility.h"

#define NAME_LENGHT 50
#define EMAIL_LENGHT 50
#define PASSOWORD_LENGHT 20

#define MANAGER_HARDDATA_FILE_NAME "Manager.txt"
#define MANAGER_SAVE_FILE_NAME "Manager.dat"

typedef struct Manager {
	int id;
	char name[NAME_LENGHT];
	char email[EMAIL_LENGHT];
	char password[PASSOWORD_LENGHT];
	bool active;
}Manager;

typedef struct ManagerList {
	Manager m;
	ManagerList* next;
}ManagerList;

bool Resetmanager(ManagerList* firstManager);

ManagerList* LoadInitialManagers(ManagerList* firstManager, char* initialFilePath, char* saveFilePath);

ManagerList* ReadInitialManagers(char* filePath);

ManagerList* ReadManagers(char* filePath);

bool SaveManager(char* filePath, ManagerList* firstManager);

ManagerList* AddManager(ManagerList* firstManager, Manager newManager);

bool RemoveManager(ManagerList* firstManager, int id);

bool EditManager(ManagerList* firstManager, Manager selectedManager);

ManagerList* OrderManagerById(ManagerList* firstManager);

int SearchNextManagerId(ManagerList* firstManager);





#endif MANAGER

