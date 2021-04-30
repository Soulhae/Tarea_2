#ifndef MENU_H
#define MENU_H
#include "list.h"
#include "map.h"

void imagen();

void mostrarOpciones();

void caso1(List* almacenamiento, HashMap *mapaPokedex, HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion , HashMap * mapaNumPokedex);

void caso2(List * almacenamiento, HashMap * pokedex, HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion, HashMap * mapaNumPokedex);

void caso10(HashMap * map);

void aplicarOpciones(int opcion, List * almacenamiento, HashMap *mapaPokedex, HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion, HashMap * mapaNumPokedex);

void interfaz();

#endif /* MENU_H */