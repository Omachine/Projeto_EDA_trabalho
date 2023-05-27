/*****************************************************************//**
 * \file   Graph.c
 * \brief  
 * 
 * \author Gonçalo M.
 * \date   May 2023
 *********************************************************************/
#include "Graph.h"
#include <stdlib.h>
#include <string.h>


#pragma region Grafo

//Cria um grafo
Vertice* CreateGraph() {
	Vertice* graph = (Vertice*)malloc(sizeof(Vertice));

	if (graph == NULL) {
		free(graph);
		return NULL;
	}

	
	return graph;
}

//Cria um vertice

Vertice* CreateVertice(char city[], int code) {
	Vertice* new = (Vertice*)calloc(1, sizeof(Vertice));
	if (new == NULL) return NULL;
	new->code = code;
	strcpy(new->city, city);
	new->next = NULL;
	new->adjacent = NULL;
	return new;
}

//inserir um vertice no grafo

Vertice* InsertVertice(Vertice* graph, Vertice* new, bool* res[]) {
	if (graph == NULL) {
		graph = new;
		*res = true;
		return graph;
	}
	else
	{
		Vertice* aux = graph;
		Vertice* ant = aux;
		while (aux && strcmp(aux->city, new->city) < 0) {
			ant = aux;
			aux = aux->next;
		}
		if (aux == graph) {
			new->next = graph;
			graph = new;


		}
		else
		{


			new->next = aux;
			ant->next = new;


		}
		*res = true;
	}
	return graph;
}
//Mostrar grafo
void ShowGraph(Vertice* graph) {
	if (graph == NULL) return;
	printf("V: %d\t-\t%s\n", graph->code, graph->city);
	ShowAdj(graph->adjacent);
	ShowGraph(graph->next);
}


//Procurar um vertice no grafo
Vertice* SearchVertice(Vertice* g, char* city) {
	if(g == NULL) return NULL;
	if (strcmp(g->city, city) == 0)return g;
	return SearchVertice(g->next, city);
}
//Eliminar Grafo
Vertice* DestroyGraph(Vertice* graph) {
	if (graph==NULL) return NULL;
	Vertice* aux = NULL;
	while (graph) {
		if (graph->next) 
			aux = graph->next;
			graph->adjacent = DestroyAdj(graph->adjacent);
			free(graph);
			graph =aux;
			aux = NULL;
		
	}
	return graph;
}
//Procurar o codigo de localização de um vertice
Vertice* SearchVerticeCode(Vertice* graph, int code) {
	if (graph == NULL) return NULL;
	if (graph->code == code) return graph;
	return (SearchVertice(graph->next, code));
}





#pragma endregion



#pragma region Adj
//Criar um adjacente
Adj* CreateAdj(int code, float distance) {
	Adj* new = (Adj*)calloc(1, sizeof(Adj));
	if (new == NULL) return NULL;
	new->code = code;
	new->distance = distance;
	new->next = NULL;
	return new;
}

//Inserir um adjacente a um vertice
Vertice* InsertAdjVert(Vertice* g, char* origin, char* dest, float weight, bool* res) {
	
		*res = false;
		
		if (g == NULL) return g;

		 Vertice* aux = SearchVertice(g, origin);
		 int cod = SearchVertice(g, dest);

		 if(aux == NULL || cod < 0 ) return g;

		 if(AdjExists(aux->adjacent, cod)== true)
				return g;

			 Adj* newAdj= CreateAdj(cod, weight);
			 aux->adjacent = InsertAdj(aux->adjacent, newAdj, res);
			 return g;
		 }


//Inserir um adjacente a um vertice com codigo de origem e destino
Vertice* InsertAdjVerticeCode(Vertice* g, int CodOrigem, int CodDest, float weight, bool* res) {

	*res = false;
	
	if(g== NULL) return g;

	Vertice* origin = SearchVerticeCode(g, CodOrigem);
	Vertice* destiny= SearchVerticeCode(g, CodDest);

	if(origin == NULL || destiny == NULL) return g;




}



#pragma endregion



#pragma region Gere_Lista_Adj
// verifica a existencia de adjacencias
bool AdjExists(Adj* h, int code) {
	if (h == NULL) return false;
	if (h->code == code) return true;
	return AdjExists(h->next, code);
}

//Insere uma adjacencia
Adj* InsertAdj(Adj* h, Adj* new, bool* res) {
	if (h == NULL) {
		h = new;
		res = true;
				return h;
		 	}
			else
		 	{
		 		Adj* aux = h;
		 		while (aux->next != NULL) {
		 			if (aux->code == new->code) {
		 				*res = false;
		 				return h;
		 			}
		 			aux = aux->next;
		 		}
				if (aux->code == new->code) {
		 			*res = false;
					return h;
		 		}
		 		aux->next = new;
		 		*res = true;
		 		return h;
		 	}
		 }


//Mostrar adjacencias
void ShowAdj(Adj* h) {
	if (h == NULL)return;
	printf("\tAdj: %d - (%.0f)\n", h->code, h->distance);
	ShowAdj(h->next);
}

//Eliminar adjacencias
Adj* DestroyAdj(Adj* h) {
	if (h == NULL) return NULL;
	Adj* aux = NULL;
	while (h) {
		if(h->next!= NULL)
			aux = h->next;
		free(h);
		h = aux;
		aux = NULL;

	}
	return h;
}

#pragma endregion

#pragma region Algoritmos

//Conta o numero de adjacencias
int CountPaths(Vertice* g, int origin, int destiny, int PathCount) {
	
	if (g == NULL) return 0;

	if (origin == destiny)return (++PathCount);

	else {
		Vertice* aux = SearchVerticeCode(g, origin);
		Adj* adj = aux->adjacent;
		while (adj != NULL) {
			Vertice* v = SearchVerticeCode(g, adj->code);
			PathCount = CountPaths(g, adj->code, destiny, PathCount);
			adj = adj->next;
		}
	}

	return PathCount;
}
//Pocura o path a partir do codigo das localizações
int CountPathVertName(Vertice* g, char* origin, char* destiny, int PathCount) {
	int s = SearchVerticeCode(g, origin);
	int d = SearchVerticeCode(g, destiny);
	return CountPaths(g, s, d, 0);
}


//verifica se um ponto esta ligado ao outro
bool DepthFirstSearchRec(Vertice* g, int origin, int destiny) {
	int j;


	if (origin == destiny) return true;

	Vertice* aux = SearchVerticeCode(g, origin);
	aux->visited = true;

	Adj* adj = aux->adjacent;

	while (adj != NULL) {
		Vertice* v = SearchVerticeCode(g, adj->code);
		if (v->visited == false) {
			if (DepthFirstSearchRec(g, adj->code, destiny) == true) return true;
		}

		adj = adj->next;
	}
	return false;
}

//verifica se um ponto esta ligado ao outro a partir do nome
bool DepthFirstSearchNamesRec(Vertice* g, char* origin, char* destiny) {
	int o = SearchVerticeCode(g, origin);
	int d = SearchVerticeCode(g, destiny);
	return DepthFirstSearchRec(g, o, d);
}
//remove o estado de visitado
Vertice* ResetVerticeTraveled(Vertice* g) {
	Vertice* aux = g;
	while (aux) {
		aux->visited = false;
		aux = aux->next;
	}
	return	g;
}


#pragma endregion


#pragma region Ficheiros

//Guarda o grapho em binário
int SaveGraph(Vertice* g, char* filename) {

	if (g == NULL) return -1;
	
	FILE* fp;
	int r;

	fp = fopen(filename, "wb");
	if (fp == NULL) return -2;
	Vertice* aux = g;
	VerticeFile auxFile;
	while (aux != NULL) {
		auxFile.code = aux->code;
		strcpy(auxFile.city, aux->city);
		fwrite(&auxFile, 1, sizeof(VerticeFile), fp);
		if (aux->adjacent) {
			r = SaveAdjacent(aux->adjacent, aux->city, aux->code);
		}
	}
	fclose(fp);
	return 1;
}

//guarda o adjacente em binario
int SaveAdjacent(Adj* h, char* filename, int OriginVerticeCode) {
	FILE* fp;

	if (h == NULL) return -2;
	fp = fopen(filename, "ab");
	if(fp == NULL) return -1;
	Adj* aux = h;
	AdjFile auxFile;
	while (aux) {
		auxFile.codeDestiny = aux->code;
		auxFile.codeOrigin = OriginVerticeCode;
		auxFile.weight = aux->distance;
		fwrite(&auxFile, 1, sizeof(AdjFile), fp);
		aux = aux->next;
	}
	fclose(fp);
	return 1;
}

//Carrega o grafo a partir de um ficheiro
Vertice* LoadGraph(Vertice* h, char* filename, bool* res) {

	*res = false;
	
	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) return NULL;

	VerticeFile aux;
	Vertice* new;
	while (fread(&aux, 1, sizeof(VerticeFile), fp)) {
		new = CreateVertice(aux.city, aux.code);
		h = InsertVertice(h, new, res);
	}
	fclose(fp);
	return h;
}



//carrega o adjacentes a partir de um ficheiro
Vertice* LoadAdj(Vertice* g, bool* res) {
	*res = false;
	
	FILE* fp;

	AdjFile aux;
	Vertice* auxGraph = g;
	while (auxGraph)
	{
		fp = fopen(auxGraph->city, "rb");
		if (fp != NULL)
		{
			while (fread(&aux, 1, sizeof(AdjFile), fp)) {
				g = InsertAdjVert(g, aux.codeOrigin, aux.codeDestiny, aux.weight, res);
			}
			fclose(fp);

		}
		auxGraph = auxGraph->next;
	}
	return g;
}





#pragma endregion


