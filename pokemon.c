#include<string.h>
#include "map.h"

int ID = 0;

typedef struct Pokemon Pokemon;
typedef struct Pokedex Pokedex;

struct Pokemon{
 int id;   
 char * nombre;
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
 char * region;
};

Pokemon* crearPokemon(int id, char * nombre, int PC, int PS, char * sexo)
{
    Pokemon * nuevo = (Pokemon *) malloc(sizeof(Pokemon));
    nuevo->id = id;
    strcpy(nuevo->nombre, nombre);
    nuevo->pc = PC;
    nuevo->ps = PS;
    strcpy(nuevo->sexo, sexo); 
}

void agregarPokemon(HashMap* mapaNombre, HashMap* mapaId, HashMap* mapaTipo, HashMap* mapaRegion, char* nombre, char** tipos, int PC, int PS, char *sexo, char* ePrevia, char* ePosterior, int numPokedex, char* region)
{
    ID++;

    Pokemon* nuevo = crearPokemon(ID, nombre, PC, PS, sexo);

	insertMap(mapaNombre, nombre, nuevo);
	insertMap(mapaId, ID, nuevo);
	insertMap(mapaTipo, tipos, nuevo); // OJITO es un webeo
	insertMap(mapaRegion, region, nuevo);
}

