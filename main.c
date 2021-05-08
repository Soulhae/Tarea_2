#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "pokemon.h"


int main()
{

	List *list_pc = createList();
	List *list_numpokedex = createList();
	HashMap *map_pokedex = createMap(300);
	HashMap *map_pokemon = createMap(300);
	HashMap *map_id = createMap(300);
	HashMap *map_tipo = createMap(300);
	HashMap *map_region = createMap(300);

	int opcion;
	do{

		menu_pokemon();
		scanf("%d", &opcion);
		printf("\n");

		char nombre[20];

		switch(opcion){

			case 1: /* Leer archivo */
				leer_archivo(list_pc, list_numpokedex, map_pokedex, map_pokemon, map_id, map_tipo, map_region);
				printf("Se leyo el archivo correctamente.\n");
				break;
			case 2: /* Atrapar pokemon */
				pedir_datos(list_pc, list_numpokedex, map_pokedex, map_pokemon, map_id, map_tipo, map_region);
				break;
			case 3: /* Evolucionar pokemon */
				break;
			case 4:; /* Buscar pokemones por tipo */

				/* Se cae, no funcionara hasta que se arreglen los tipos */
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
				break;
			case 8: /* Mostrar pokemones ordenar por pc */
				break;
			case 9: /* Liberar pokemon */
				liberar_pokemon(list_pc, map_pokedex, map_pokemon, map_id, map_tipo, map_region);
				//leer_list_numpokedex(list_numpokedex);
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