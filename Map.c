#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "map.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void * key1, void * key2){
    if(key1 == NULL || key2 == NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void enlarge(HashMap * map) {
    Pair ** aux = map->buckets;
    long capacidad = map->capacity;
    map->capacity *= 2;
    map->buckets = (Pair **) calloc(map->capacity, sizeof(Pair *));
    map->size = 0;
    int i;
    for(i = 0 ; i<capacidad ; i++){
      if(aux[i] != NULL){
        insertMap(map, aux[i]->key, aux[i]->value);
      }
    }
}

void insertMap(HashMap * map, char * key, void * value) {
    if(!key) exit(-1);
    long posicion;
    Pair * bucket;
    bucket = createPair(key, value);
    posicion=hash(key, map->capacity);
    while(map->buckets[posicion]!=NULL){
        posicion++;
        if(posicion == map->capacity) posicion = 0;
    }
    map->buckets[posicion] = bucket;
    map->size++;
    map->current = posicion;
}

HashMap * createMap(long capacity) {
    HashMap *mapa = (HashMap *) malloc(sizeof(HashMap));
    mapa->buckets = (Pair **) calloc(capacity, sizeof(Pair *));
    mapa->size = 0;
    mapa->current = -1;
    mapa->capacity = capacity;
    int i;
    for(i = 0 ; i<capacity ; i++){
      mapa->buckets[i] = NULL;
    }
    return mapa;
}

void eraseMap(HashMap * map,  char * key) {    
  long posicion = hash(key, map->capacity);
  while((is_equal(key, map->buckets[posicion]->key) == 0)){
    posicion++;
    if(map->buckets[posicion] == NULL) return;
    if(posicion>=map->capacity){
      posicion=0;
    }
  }
  map->buckets[posicion]->key = NULL;
  map->size--;
  map->current = posicion;
}

void * searchMap(HashMap * map,  char * key) {
    int posicion;
    posicion = hash(key, map->capacity);
    for(int i=posicion; i<map->capacity; i++){
        if(map->buckets[i]!=NULL && map->buckets[i]->key!=NULL && strcmp(map->buckets[i]->key, key) == 0){
            map->current = i;
            return map->buckets[i]->value;
        }
    }
    return NULL;
}

void * firstMap(HashMap * map) {
    long posicion = 0;
    while(posicion != map->capacity){
      if(map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL){
        map->current = posicion;
        return map->buckets[posicion]->value;
      }
      posicion++;
    }
    return NULL;
}

void * nextMap(HashMap * map) {
    long posicion = map->current + 1;
    while(posicion != map->capacity){
      if(map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL){
        map->current = posicion;
        return map->buckets[posicion]->value;
      }
      posicion++;
    }
    return NULL;
}

long size(HashMap * map)
{
  return map->size;
}