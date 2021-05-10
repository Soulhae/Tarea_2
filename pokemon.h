#ifndef POKEMON_H
#define POKEMON_H
#include "map.h"
#include "list.h"

typedef struct Pokemon Pokemon;

typedef struct Pokedex Pokedex;

void bienvenida();

void menu_pokemon();

void exportar_archivo(HashMap *map_id, HashMap *map_pokedex);

/*
 * Se lee linea por linea cada dato del archivo, los cuales se separan por comas. En el caso de los tipos, se guardan en una cadena
 * el cual se separa y se almacena en una lista en la funcion 'crear_pokedex'
 */
void leer_archivo(HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region);

/* Funcion que le pide los datos al usuario cuando este desee agregar un pokemon */
void pedir_datos(HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region);

/* Funcion utilizada para guardar en la estructura del almacenamiento pokemon la información de combate de este. */
Pokemon *crear_pokemon(char *nombre, int pc, int ps, char *sexo);

/* Funcion utilizada para guardar en la estructura de la Pokedex la información de personal de este. */
Pokedex *crear_pokedex(char *nombre, char *tipos, char *ev_prev, char *ev_post, int num_pokedex, char *region);

/* Funcion utilizada para insertar los datos de la Pokedex de cada pokemon en el mapa, donde el cual la clave seran sus nombres. */
void insert_map_pokedex(Pokedex *pokedex, HashMap *map_pokedex);

/*
 * Funcion utilizada para insertar los datos del almacenamiento pokemon en el mapa donde la clave seran sus nombres. Como en el
 * almacenamiento pokemon se almacenan todos los pokemones y su respectiva información de combate, en este caso se utiliza una lista
 * con el fin de guardar ahí los pokemones de igual nombre.
 */
void insert_map_pokemon(Pokemon *pokemon, HashMap *map_pokemon);

/*
 * Funcion utilizada para insertar los datos del almacenamiento pokemon en el mapa que almacena la informacion de combate de los
 * pokemones, en el cual la clave será la 'id' de cada pokemon.
 */
void insert_map_id(Pokemon *pokemon, HashMap *map_id);

/*
 * Funcion utilizada para insertar los datos del almacenamiento pokemon en el mapa donde la clave será el tipo de cada pokemon. Como
 * cada pokemon tiene uno o más tipos distintos, en este caso se utiliza una lista con el fin de guardar ahí los pokemones de acuerdo
 * a sus tipos.
 */
void insert_map_tipo(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_tipo);

/*
 * Funcion utilizada para insertar los datos de la Pokedex en el mapa donde la clave será la región de los pokemones. Como
 * cada pokemon tiene una región igual o distinta, en este caso se utiliza una lista con el fin de guardar ahí los pokemones de acuerdo
 * a la región que pertenezca.
 */
void insert_map_region(Pokedex *pokedex, HashMap *map_region);

int contarDigitos(int num);

/*
 * Esta función busca a todos los pokemones con igual nombre en el mapa 'map_pokemon', el cual retornará una lista de pokemones y su
 * respectiva información de combate.
 */
void buscar_nombre_pokemon(HashMap *map_pokemon, char *nombre);

/* Esta funcion busca a un pokemon de acuerdo a su nombre en el mapa 'map_pokedex', en cual imprimirá su información de Pokedex */
void buscar_nombre_pokedex(HashMap *map_pokedex, char *nombre);

/*
 * Esta función busca a todos los pokemones de acuerdo a un tipo ingresado en el mapa 'map_tipo', el cual retornará una lista de pokemones y su
 * respectiva información de combate.
 */
void buscar_tipo(HashMap *map_tipo, char *tipo);

/*
 * Esta función busca a todos los pokemones de acuerdo a una region ingresado en el mapa 'map_region', el cual retornará una lista de
  *pokemones y su respectiva información de Pokedex.
 */
void buscar_region(HashMap *map_region, char *region);

<<<<<<< HEAD
/* Si se desea liberar a un pokemon de acuerdo a su id, esta funcion lo elimina de todos los mapas utilizados */
void liberar_pokemon(char * id, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region);
=======
void liberar_pokemon(char * id, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region, int flag);
>>>>>>> afce0dd7cbbf80c472828d5a34b4b5f3f6232366

void evolucionar(HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region);
/*Evoluciona a un pokemon, si es que tiene evolcuon en la pokedex*/

void ordenar_pc(HashMap* map_id);
/* Muestra ordenado por puntos de combate */

void ordenar_pokedex(HashMap *map_pokedex);
/* Muestra ordenado por numero de pokedex */

#endif /* POKEMON_H */