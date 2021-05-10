#ifndef POKEMON_H
#define POKEMON_H
#include "map.h"
#include "list.h"

typedef struct Pokemon Pokemon;

typedef struct Pokedex Pokedex;

void bienvenida();

void menu_pokemon();

void exportar_archivo(HashMap *map_id, HashMap *map_pokedex);

void leer_archivo(HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region);

void pedir_datos(HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region);

Pokemon *crear_pokemon(char *nombre, int pc, int ps, char *sexo);

Pokedex *crear_pokedex(char *nombre, char *tipos, char *ev_prev, char *ev_post, int num_pokedex, char *region);

void insert_map_pokedex(Pokedex *pokedex, HashMap *map_pokedex);

void insert_map_pokemon(Pokemon *pokemon, HashMap *map_pokemon);

void insert_map_id(Pokemon *pokemon, HashMap *map_id);

void insert_map_tipo(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_tipo);

void insert_map_region(Pokedex *pokedex, HashMap *map_region);

int contarDigitos(int num);

void buscar_nombre_pokemon(HashMap *map_pokemon, char *nombre);

void buscar_nombre_pokedex(HashMap *map_pokedex, char *nombre);

void buscar_tipo(HashMap *map_tipo, char *tipo);

void buscar_region(HashMap *map_region, char *region);

void liberar_pokemon(HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region);

void evolucionar(HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region);

void ordenar_pc(HashMap* map_id);

void ordenar_pokedex(HashMap *map_pokedex);

#endif /* POKEMON_H */