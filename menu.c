#include <stdio.h>
#include <stdlib.h> // lo usamos????
#include <string.h>
#include "map.h"
#include "menu.h"
#include "pokemon.h"

void imagen()
{
	printf("                                    ,'\\\n");
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
	printf("opcion\n");
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

void caso2(HashMap* mapaNombre, HashMap* mapaId, HashMap* mapaTipo, HashMap* mapaRegion)
{
	char nombre[15];
	char tipos[18][10]; // OJITOOOOOOOOOOOOOOO
	char sexo[3];
	char evPrevia[15];
	char evPosterior[15];
	int PC, PS, numPokedex;
	char region[10];

	printf("Ingrese el nombre del pokemon: \n");
	scanf("%s", nombre);
	//getchar(); // ???
	
	// SCAN tipo pero no sabemos como aun OJITO 

	printf("Ingrese los puntos de combate del pokemon: \n");
	scanf("%i", &PC);

	printf("Ingrese los puntos de salud del pokemon: \n");
	scanf("%i", &PS);

	printf("Ingrese el sexo del pokemon (M o F): \n");
	do
	{
		scanf("%s", sexo);
	} while((strlen(sexo)) > 1);

	printf("Ingrese su evolucion previa (Si no tiene simplemente escriba: No tiene):\n");
	scanf("%s", evPrevia);

	printf("Ingrese su evolucion posterior (Si no tiene simplemente escriba: No tiene):\n");
	scanf("%s", evPosterior);

	printf("Ingrese el numero en la pokedex del pokemon: \n");
	// Funcion comparar numero pokedex????
	scanf("%i", &numPokedex);

	printf("Ingese la region del pokemon: \n");
	scanf("%s", region);

}

void aplicarOpciones(int opcion, HashMap* mapaNombre, HashMap* mapaId, HashMap* mapaTipo, HashMap* mapaRegion)
{
	switch (opcion)
	{
		case 1:
	
			break;
		case 2:
			caso2(mapaNombre, mapaId, mapaTipo, mapaRegion);
			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		case 9:

			break;
		case 10:

			break;
		default: 
		
			break;
	}
}

void interfaz()
{
	imagen();

	HashMap* almacenamiento = createMap(20);
	HashMap* pokedex = createMap(20);
	HashMap* mapaNombre = createMap(20);
	HashMap* mapaId = createMap(20);
	HashMap* mapaTipo = createMap(20);
	HashMap* mapaRegion = createMap(20);

	int opcion;

	do{
		mostrarOpciones();
		scanf("%i", &opcion);
		if (opcion == 0)
		{
			printf("Pokemon\n");
			printf("Atrapalos ya!\n");
			return;
		}
		else aplicarOpciones(opcion, mapaNombre, mapaId, mapaTipo, mapaRegion);
	} while(opcion != 0);
}