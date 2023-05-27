/*****************************************************************//**
 * \file   Main.c
 * \brief
 *
 * \author Gonçalo M.
 * \date   March 2023
 *********************************************************************/

#include "Screen.h"
#include <locale.h>

int main() {

	int op = -1;
	ClientList* firstClient = ReadClient(CLIENT_SAVE_FILE_NAME);
	VehicleList* firstVehicle = ReadVehicle(VEHICLE_SAVE_FILE_NAME);
	ManagerList* firstManager = ReadManagers(MANAGER_SAVE_FILE_NAME);

	while (op != 0) {
		ShowMainMenu(&op);


		switch (op) {
		case 1:
			ShowClientMenu(firstClient);
			break;
		case 2:
			ShowVehicleMenu(firstVehicle);
			break;
		case 3:
			ShowManagerScreen(firstManager);
			break;
		case 4:
			LoadInitialData(&firstClient, &firstVehicle, &firstManager);
			break;
		case 5:
			ResetClient(firstClient);
			ResetVehicle(firstVehicle);
			ResetManager(firstManager);
			op = 0;
		default:
			break;
		}

	}
	
	setlocale(LC_ALL, "Portuguese");

	static int tot = 0;
	bool res;

#pragma region grafos

	Vertice* graf = CreateGraph();
	Vertice* newVer = CreateVertice("Porto", tot);
	if (newVer != NULL) {
		graf = InsertVertice(graf, newVer, &res);
		tot++;
	}

	newVer = CreateVertice("Lisboa", tot);
	if (newVer != NULL)
{
	graf = InsertVertice(graf, newVer, &res);
	tot++;

}

	newVer = CreateVertice("Braga", tot);
if (newVer != NULL)
{
	graf = InsertVertice(graf, newVer, &res);
	tot++;

}

	newVer = CreateVertice("Coimbra", tot);
if (newVer != NULL)
{
	graf = InsertVertice(graf, newVer, &res);
	tot++;

}

	newVer = CreateVertice("Aveiro", tot);
if (newVer != NULL)
{
	graf = InsertVertice(graf, newVer, &res);
	tot++;

}

	newVer = CreateVertice("Viseu", tot);
if (newVer != NULL)
{
	graf = InsertVertice(graf, newVer, &res);
	tot++;

}

	newVer = CreateVertice("Faro", tot);
if (newVer != NULL)
{
	graf = InsertVertice(graf, newVer, &res);
	tot++;

}

	newVer = CreateVertice("Vila Real", tot);
if (newVer != NULL)
{
	graf = InsertVertice(graf, newVer, &res);
	tot++;

}

ShowGraph(graf);


graf = InsertAdjVertice(graf, "Porto", "Lisboa", 300, &res);
graf = InsertAdjVertice(graf, "Porto", "Braga", 60, &res);
graf = InsertAdjVertice(graf, "Porto", "Coimbra", 120, &res);
graf = InsertAdjVertice(graf, "Porto", "Aveiro", 70, &res);
graf = InsertAdjVertice(graf, "Porto", "Viseu", 120, &res);
graf = InsertAdjVertice(graf, "Porto", "Vila Real", 120, &res);
graf = InsertAdjVertice(graf, "Porto", "Faro", 600, &res);
graf = InsertAdjVertice(graf, "Lisboa", "Braga", 300, &res);
graf = InsertAdjVertice(graf, "Lisboa", "Coimbra", 200, &res);
graf = InsertAdjVertice(graf, "Lisboa", "Aveiro", 200, &res);
graf = InsertAdjVertice(graf, "Lisboa", "Viseu", 250, &res);
graf = InsertAdjVertice(graf, "Lisboa", "Vila Real", 300, &res);
graf = InsertAdjVertice(graf, "Lisboa", "Faro", 300, &res);
graf = InsertAdjVertice(graf, "Braga", "Coimbra", 200, &res);
graf = InsertAdjVertice(graf, "Braga", "Aveiro", 150, &res);
graf = InsertAdjVertice(graf, "Braga", "Viseu", 150, &res);
graf = InsertAdjVertice(graf, "Braga", "Vila Real", 100, &res);
graf = InsertAdjVertice(graf, "Braga", "Faro", 500, &res);
graf = InsertAdjVertice(graf, "Coimbra", "Aveiro", 50, &res);
graf = InsertAdjVertice(graf, "Coimbra", "Viseu", 50, &res);
graf = InsertAdjVertice(graf, "Coimbra", "Vila Real", 100, &res);
graf = InsertAdjVertice(graf, "Coimbra", "Faro", 400, &res);
graf = InsertAdjVertice(graf, "Aveiro", "Viseu", 50, &res);
graf = InsertAdjVertice(graf, "Aveiro", "Vila Real", 100, &res);
graf = InsertAdjVertice(graf, "Aveiro", "Faro", 400, &res);
graf = InsertAdjVertice(graf, "Viseu", "Vila Real", 50, &res)	;
graf = InsertAdjVertice(graf, "Viseu", "Faro", 400, &res);
graf = InsertAdjVertice(graf, "Vila Real", "Faro", 400, &res);
graf = InsertAdjVertice(graf, "Faro", "Porto", 600, &res);
graf = InsertAdjVertice(graf, "Faro", "Lisboa", 300, &res);


ShowGraph(graf);

printf("\nExiste Path?\n");
bool existe = DepthFirstSearchRec(graf, 0, 3);



graf = ResetVerticeTraveled(graf);

existe = DepthFirstSearchNamesRec(graf, "Braga", "Porto");
printf(" Existe Path entre %s e %s: %s\n", "Braga", "Porto", (existe == true ? "Sim" : "Não"));



int res1 = SaveGraph(graf, "Vertice.bin");
if (res1 > 0) puts("\nGrafo guardado\n");

graf = DestroyGraph(graf);

puts("\nGrafo na Memória");
ShowGraph(graf);

graf = LoadGraph(graf, "Vertices.bin", &res);
if (graf != NULL) puts("\nVertices do Grafo lido de ficheiro\n");
ShowGraph(graf);

puts("\nLer Adjacências do grafo de ficheiro\n");
graf = LoadAdj(graf, &res);

ShowGraph(graf);

#pragma endregion













	return 0;
}
