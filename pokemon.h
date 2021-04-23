#ifndef POKEMON_H
#define POKEMON_H
#include "map.h"

typedef struct Pokemon Pokemon;

typedef struct Pokedex Pokedex;

Pokemon* crearPokemon(char* nombre, char** tipos, int PC, int PS, char* sexo, char* ePrevia, char* ePosterior, int numPokedex, char* region);

void agregarPokemon(HashMap* mapaNombre, HashMap* mapaId, HashMap* mapaTipo, HashMap* mapaRegion, char* nombre, char** tipos, int PC, int PS, char *sexo, char* ePrevia, char* ePosterior, int numPokedex, char* region);

void evolucionarPokemon();

void calcularEvolucion();

void buscarId(HashMap* mapaId, int id_pokemon);

void buscarTipo(HashMap* mapaTipo);

void buscarNombre(HashMap* mapaNombre);

void buscarNombrePokedex();

void leerArchivo(HashMap* mapaNombre, HashMap* mapaId, HashMap* mapaTipo, HashMap* mapaRegion , char* archivo);

#endif /* POKEMON_H */