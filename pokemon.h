#ifndef POKEMON_H
#define POKEMON_H
#include "map.h"

typedef struct Pokemon Pokemon;

typedef struct Pokedex Pokedex;

Pokemon* crearPokemon(char* ID, char * nombre, char **tipos, int PC, int PS, char * sexo, char *EPrevia, char *EPosterior, int numPokedex, char *region); //falta existencia

void agregarPokemon(HashMap *pokedex, HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion, char * nombre, List* tipos, int PC, int PS, char * sexo, char * EPrevia, char * EPosterior, int numPokedex, char * region);

void evolucionarPokemon(HashMap* almacenamiento, HashMap* pokedex,int id);

void calcularEvolucion(Pokemon * almacenamiento, Pokedex * pokedex);

void buscarId(HashMap* mapaId, int id_pokemon);

void buscarTipo(HashMap* mapaTipo);

int contar(int num);

void buscarNombre(HashMap* mapaNombre, char *nombre);

void buscarNombrePokedex(HashMap *pokedex, char *nombre);

void leerArchivo(HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion , char * nombreArchivo);

#endif /* POKEMON_H */