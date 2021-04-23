#include "map.h"

typedef struct Pokemon Pokemon;
typedef struct Pokedex Pokedex;

struct Pokemon{
 int id;
 char* nombre;
 int pc;
 int ps;
 char sexo;
};

struct Pokedex{
 char * nombre;
 int existencia;
 char ** tipos;
 char * EPrevia;
 char * EPosterior;
 int numeroPokedex;
 char* region;
};

Pokemon* crearPokemon(char * nombre, char ** tipos, int PC, int PS, char * sexo, char * ePrevia, char * ePosterior, int numPokedex, char * region)
{
    Pokemon * aux = (Pokemon *) malloc(sizeof(Pokemon));
    
}

void agregarPokemon(HashMap* mapaNombre, HashMap* mapaId, HashMap* mapaTipo, HashMap* mapaRegion, char* nombre, char** tipos, int PC, int PS, char *sexo, char* ePrevia, char* ePosterior, int numPokedex, char* region)
{
    Pokemon* nuevo = crearPokemon(nombre, tipos, PC, PS, sexo, ePrevia, ePosterior, numPokedex, region);

	insertMap(mapaNombre, nombre, nuevo);
	insertMap(mapaId, nombre, nuevo);
	insertMap(mapaTipo, nombre, nuevo);
	insertMap(mapaRegion, nombre, nuevo);
}

void evolucionarPokemon(HashMap* almacenamiento, HashMap* pokedex,int id)
{
	calcularEvolucion();
}

void calcularEvolucion()
{	

}

