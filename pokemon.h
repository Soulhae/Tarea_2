#ifndef POKEMON_H
#define POKEMON_H
#include "map.h"
#include "list.h"

typedef struct Pokemon Pokemon;

typedef struct Pokedex Pokedex;

Pokemon* crearPokemon(char* ID, char * nombre, int PC, int PS, char *sexo);

Pokedex* crearPokedex(char * nombre, List* tipos, char * previa, char * posterior, int num, char * region);

void agregarLista(HashMap * map, char * key, Pokemon * nuevo);

void agregarPokemon(List * almacenamiento, HashMap *mapaPokedex, HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion, HashMap * mapNumPokedex, char * nombre, List* tipos, int PC, int PS, char *sexo, char * previa, char * posterior, int numPokedex, char * region);

void evolucionarPokemon(HashMap* almacenamiento, HashMap* pokedex,int id);

void calcularEvolucion(Pokemon * pokemon, Pokedex* pokedex);

void buscarId(HashMap* mapaId, int id_pokemon);

void buscarTipo(HashMap* mapaTipo);

int contar(int num);

void buscarNombre(HashMap* mapaNombre, char *nombre);

void buscarNombrePokedex(HashMap *pokedex, char *nombre);

void leerArchivo(List* almacenamiento, HashMap *mapaPokedex, HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion , char * nombreArchivo);

void mostrarRegion(char * region, HashMap * map);

void ordenarPorPC(List *list_pokemon);

void liberarPokemon(char *id, HashMap * mapaPokedex, HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion, HashMap * mapaNumPokedex);


#endif /* POKEMON_H */