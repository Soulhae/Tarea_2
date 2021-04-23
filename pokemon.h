#ifndef POKEMON_H
#define POKEMON_H
#include "map.h"

typedef struct Pokemon Pokemon;

typedef struct Pokedex Pokedex;

Pokemon* crearPokemon(int ID, char * nombre, char **tipos, int PC, int PS, char * sexo, char *EPrevia, char *EPosterior, int numPokedex, char *region); //falta existencia

void agregarPokemon(HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion, char * nombre, char ** tipos, int PC, int PS, char * sexo, char * EPrevia, char * EPosterior, int numPokedex, char * region);

void calcularEvolucion();

void evolucionarPokemon();

void buscarId(HashMap* mapaId, int id_pokemon);

void buscarTipo(HashMap* mapaTipo);

int contar(int num);

void buscarNombre(HashMap* mapaNombre, char *nombre);

void buscarNombrePokedex();

void leerArchivo(HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion , char * nombreArchivo);

#endif /* POKEMON_H */