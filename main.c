#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "map.h"
#include "pokemon.h"


int main()
{

	HashMap *map_pokedex = createMap(30);
	HashMap *map_pokemon = createMap(30);
	HashMap *map_id = createMap(30);
	HashMap *map_tipo = createMap(30);
	HashMap *map_region = createMap(30);

	bienvenida();

	int opcion;
	int caso1;
	do{
		sleep(1);
		menu_pokemon();
		scanf("%d", &opcion);
		printf("\n");

		char nombre[20];

		switch(opcion){ // ola

			case 1: /* Leer archivo */
				printf("1.- Importar archivo\n2.- Exportar archivo\n\n");
				printf("Ingrese opcion: ");
				scanf("%i", &caso1);
				if(caso1==1) leer_archivo(map_pokedex, map_pokemon, map_id, map_tipo, map_region);
				else if(caso1==2) exportar_archivo(map_id, map_pokedex);
				break;
			case 2: /* Atrapar pokemon */
				pedir_datos(map_pokedex, map_pokemon, map_id, map_tipo, map_region);
				break;
			case 3: /* Evolucionar pokemon */
				evolucionar(map_pokedex, map_pokemon, map_id, map_tipo, map_region);
				break;
			case 4:; /* Buscar pokemones por tipo */

				char tipo[20];
				printf("Ingrese el tipo de pokemon que desea buscar: ");
				scanf("%s", tipo);
				buscar_tipo(map_tipo, tipo);

				break;

			case 5:; /* Buscar pokemones por nombre */

				printf("Ingrese nombre del pokemon que desea buscar: ");
				scanf("%s", nombre);
				buscar_nombre_pokemon(map_pokemon, nombre);

				break;

			case 6:; /* Buscar pokemon por nombre en pokedex */

				printf("Ingrese nombre del pokemon que desea buscar: ");
				scanf("%s", nombre);
				buscar_nombre_pokedex(map_pokedex, nombre);

				break;

			case 7: /* Mostrar todos los pokemones de la pokedex (en orden por num pokedex) */
				ordenar_pokedex(map_pokedex);
				break;
			case 8: /* Mostrar pokemones ordenar por pc */
				ordenar_pc(map_id);
				break;
			case 9:; /* Liberar pokemon */
				int int_id;
				char id[4];
				printf("Ingrese la ID del pokemon a eliminar: ");
				scanf("%i", &int_id);
				sprintf(id, "%d", int_id);
				liberar_pokemon(id, map_pokedex, map_pokemon, map_id, map_tipo, map_region);
				printf("\n      Pokemon liberado correctamente. \n");
				break;
			case 10:; /* Mostrar pokemones por region */

				char region[20];
				printf("Ingrese la region: ");
				scanf("%s", region);
				buscar_region(map_region, region);
				
				break;
			case 11: /* Salir */
				break;
			default:
				opcion = 12;
				printf("Intentelo nuevamente.\n");
				getchar();
				break;
		}
		
	}while(opcion != 11);

	return 0;
}