#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "menu.h"
#include "pokemon.h"

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

void caso2()
{
	char nombre[15];
	char tipo[18][10]; // OJITOOOOOOOOOOOOOOO
	char sexo[3];
	char evoucionPrevia[15];
	char evolucionPosterior[15];
	int PC, PS, numPokedex;

	Pokemon* nuevo = crearPokemon();
}

void aplicarOpciones(int opcion)
{
	switch (opcion)
	{
		case 1:
	
			break;
		case 2:
			caso2();
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

void interfaz()
{
	imagen();

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
		else aplicarOpciones(opcion);
	} while(opcion != 0);
}