/*****************************************************************//**
 * \file   Graph.h
 * \brief
 *
 * \author Gonçalo M.
 * \date   May 2023
 *********************************************************************/
#pragma once

#include <stdio.h>
#include <stdbool.h>


#define N 20	
//structs

typedef struct Adj {
	int code;
	float distance;
	struct Adj* next;
}Adj;

typedef struct AdjFile {
	int codeOrigin;
	int codeDestiny;
	float weight;
}AdjFile;


typedef struct Vertice {
	int code;
	char city[N];
	bool visited;
	struct Vertice* next;
	struct Adj* adjacent;
}Vertice;


typedef struct VerticeFile {
	int code;
	char city[N];
}VerticeFile;



Vertice* CreateGraph();
Vertice* CreateVertice(char city[], int code);
Vertice* InsertVertice(Vertice* graph, Vertice* new, bool* res[]);
void ShowGraph(Vertice* graph);
Vertice* SearchVertice(Vertice* g, char* city);
Vertice* SearchVerticeCode(Vertice* graph, int code);
Adj* CreateAdj(int code, float distance);
Vertice* InsertAdjVert(Vertice* g, char* origin, char* dest, float weight, bool* res);
Vertice* InsertAdjVerticeCode(Vertice* g, int CodOrigem, int CodDest, float weight, bool* res);
bool AdjExists(Adj* h, int code);
Adj* InsertAdj(Adj* h, Adj* new, bool* res);
void ShowAdj(Adj* h);
Adj* DestroyAdj(Adj* h);
int CountPaths(Vertice* g, int origin, int destiny, int PathCount);
int CountPathVertName(Vertice* g, char* origin, char* destiny, int PathCount);
bool DepthFirstSearchRec(Vertice* g, int origin, int destiny);
bool DepthFirstSearchNamesRec(Vertice* g, char* origin, char* destiny);
Vertice* ResetVerticeTraveled(Vertice* g);
int SaveGraph(Vertice* g, char* filename);
int SaveAdjacent(Adj* h, char* filename, int OriginVerticeCode);
Vertice* LoadGraph(Vertice* h, char* filename, bool* res);
Vertice* LoadAdj(Vertice* g, bool* res);
Vertice* DestroyGraph(Vertice* graph);
