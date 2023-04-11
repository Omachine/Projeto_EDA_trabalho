/*****************************************************************//**
 * \file   Utility.h
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/
#pragma once

#ifndef UTILITY
#define UTILITY

#define MAX_PATH_LENGHT 100


 // Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Cliente.h"


// Constants
#define Max_Size 1000
#define UID_lenght 40
#define IS_CONFIRMED 1
#define IS_CANCELED 2

typedef enum {false, true} bool;


int Confirm();

void ShowRemoveClientMenu(ClientList* firstClient);



#endif
