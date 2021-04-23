#ifndef POKEMON_H
#define POKEMON_H
#include "map.h"

typedef struct Pokemon Pokemon;

typedef struct Pokedex Pokedex;

Pokemon * crearPokemon(int id, char * nombre, int PC, int PS, char * sexo);

Pokedex *crearPokemondex(char *nombre, char **tipos, char *EPrevia, char *EPosterior, int numPokedex, char *region); //falta existencia

void agregarPokemon(HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion, char * nombre, char ** tipos, int PC, int PS, char * sexo, char * EPrevia, char * EPosterior, int numPokedex, char * region);

void buscarId(HashMap * mapaId, int id_pokemon);

void buscarTipo(HashMap * mapaTipo);

void buscarNombre(HashMap * mapaNombre);

void buscarNombrePokedex();

void leerArchivo(HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion , char * nombreArchivo);

#endif /* POKEMON_H */