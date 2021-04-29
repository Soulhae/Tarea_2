#include <stdio.h>
#include <stdlib.h> // lo usamos????
#include <string.h>
#include <unistd.h>
#include "list.h"
#include "map.h"
#include "menu.h"
#include "pokemon.h"


void imagen()
{
	printf("                                  ,'\\\n");
    printf("    _.----.        ____         ,'  _\\   ___    ___     ____\n");
    printf("_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n");
    printf("\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n");
    printf(" \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n");
    printf("   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n");
    printf("    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n");
    printf("     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n");
    printf("      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n");
    printf("       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n");
    printf("        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n");
    printf("                                `'                            '-._|\n");
    printf("\n");
    printf("\n");

}

void mostrarOpciones()
{
	printf("Por favor ingrese una opcion (Ingrese '0' para salir)\n");
	printf("1. Importar/Exportar desde un archivo CSV\n");
	printf("2. Pokemon atrapado\n");
	printf("3. Evolucionar pokemon\n");
	printf("4. Buscar mis pokemon por tipo\n");
	printf("5. Buscar mis pokemon por nombre\n");
	printf("6. Buscar por nombre en pokedex\n");
	printf("7. Mostrar todos los pokemon de la pokedex\n");
	printf("8. Mostrar mis pokemon ordenados por PC\n");
	printf("9. Liberar pokemon\n");
	printf("10. Mostrar pokemon por region\n");

}

void caso1();

void caso2(List * almacenamiento, HashMap *mapaPokedex, HashMap *mapaNombre, HashMap *mapaId, HashMap *mapaTipo, HashMap *mapaRegion, HashMap *mapaNumPokedex)
{
	char nombre[15]; 
	char sexo[10];
	char evPrevia[15];
	char evPosterior[15];
	int PC, PS, numPokedex;
	char region[10];
	List* lista = createList();

	printf("Ingrese el nombre del pokemon: ");
	scanf("%s", nombre);
	
	int cont;
	printf("De cuantos tipos es su pokemon (ingrese un numero entero): ");
	scanf("%i", &cont);
	
	char *aux;
	for (int i = 0; i < cont; i++)
	{
		char* tipo;
		tipo = (char*)malloc(10*sizeof(char)); 
		printf("Ingrese el tipo de su pokemon: ");
		scanf("%s", tipo);
		pushBack(lista, tipo);
	}
	aux = firstList(lista);
	while(aux!=NULL){
		printf("%s\n", aux);
		aux = nextList(lista);
	}

	printf("Ingrese los puntos de combate del pokemon: \n");
	scanf("%i", &PC);

	printf("Ingrese los puntos de salud del pokemon: \n");
	scanf("%i", &PS);

	printf("Ingrese el sexo del pokemon (Macho o Hembra): \n");
	scanf("%s", sexo);

	printf("Ingrese su evolucion previa (Si no tiene simplemente escriba: No tiene):\n");
	scanf("%s", evPrevia); // OJITOOO

	printf("Ingrese su evolucion posterior (Si no tiene simplemente escriba: No tiene):\n");
	scanf("%s", evPosterior); //OJITOO

	printf("Ingrese el numero en la pokedex del pokemon: \n");
	// Funcion comparar numero pokedex????
	scanf("%i", &numPokedex);



	printf("Ingrese la region del pokemon: \n");
	scanf("%s", region);

	agregarPokemon(almacenamiento, mapaPokedex, mapaNombre, mapaId, mapaTipo, mapaRegion, mapaNumPokedex, nombre, lista, PC, PS, sexo, evPrevia, evPosterior, numPokedex, region);
	printf("hola mundo");
    sleep(3);
}

void caso10(HashMap * map)
{
	char * region;
	printf("Ingrese el nombre de la region que desea buscar: ");
	scanf("%s", region);

	mostrarRegion(region, map);	
}

void aplicarOpciones(int opcion)
{
	List* almacenamiento = createList();
	HashMap* mapaPokedex = createMap(20);
	HashMap* mapaNombre = createMap(20);
	HashMap* mapaId = createMap(20);
	HashMap* mapaTipo = createMap(20);
	HashMap* mapaRegion = createMap(15);
	HashMap* mapaNumPokedex = createMap(20);
	
	switch (opcion)
	{
		case 1:
	
			break;
		case 2:
			caso2(almacenamiento, mapaPokedex, mapaNombre, mapaId, mapaTipo, mapaRegion, mapaNumPokedex);
			break;
		case 3: // evolcuionar

			break;
		case 4: // buscar por tipo

			break;
		case 5: // buscar por nombre en almacenamiento

			break;
		case 6: // buscar por nombre en pokedex

			break;
		case 7: // mostrar todos los de la pokedex, ordenados por numpokedex

			break;
		case 8: // ordenar lista de pc, y mostrarlos en ese orden

			break;
		case 9: // liberar pokemon

			break;
		case 10: // mostrar por region
			caso10(mapaRegion);
			break;
		default: 
		
			break;
	}
}

void interfaz()
{
	imagen();

	int opcion;

	do{
		mostrarOpciones();
		scanf("%i", &opcion);
		if (opcion == 0)
		{
			printf("\nPokemon\n");
			printf("Atrapalos ya!\n");
			sleep(3);
			return;
		}
		else aplicarOpciones(opcion);
		
	} while(opcion != 0);
}