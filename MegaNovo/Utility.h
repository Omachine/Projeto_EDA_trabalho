/*****************************************************************//**
 * \file   Utility.h
 * \brief
 *
 * \author Gon�alo M.
 * \date   March 2023
 *********************************************************************/
#pragma once

#ifndef UTILITY
#define UTILITY
#define _CRT_SECURE_NO_WARNINGS
#define MAX_PATH_LENGHT 100


 // Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Constants
#define Max_Size 1000
#define UID_lenght 40
#define IS_CONFIRMED 1
#define IS_CANCELED 2

typedef enum { false, true } bool;


int Confirm();





#endif
