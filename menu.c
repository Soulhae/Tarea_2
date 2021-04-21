#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "menu.h"

void mostrarOpciones()
{
	printf("titulo\n");
	printf("opcion\n");
	printf("1. Importar/Exportar desde un archivo CSV\n");
	printf("2. Pokemon atrapado\n");
	printf("3. Evolcuionar pokemon\n");
	printf("4. Buscar mis pokemon por tipo\n");
	printf("5. Buscar mis pokemon por nombre\n");
	printf("6. Buscar por nombre en pokedex\n");
	printf("7. Mostrar todos los pokemon de la pokedex\n");
	printf("8. Mostrar mis pokemon ordenados por PC\n");
	printf("9. Liberar pokemon\n");
	printf("10. Mostrar pokemon por region\n");

}

void aplicarOpciones(int opcion)
{
	switch (opcion)
	{
		case 1:
			agregarPokemon()
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
	}
}

void interfaz()
{
	int opcion;
	mostrarOpciones();
	scanf("%i", &opcion);
	if (opcion == 0)
	{
		printf("Pokemon\n");
		printf("Atrapalos ya!\n");
		return;
	}
	else 
		aplicarOpciones(opcion);

	
}