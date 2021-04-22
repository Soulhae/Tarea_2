#ifndef MAP_H
#define MAP_H

typedef struct HashMap HashMap;

HashMap * createMap(long capacity);

void insertMap(HashMap * table, char * key, void * value);

void eraseMap(HashMap * table, char * key);

void * searchMap(HashMap * table, char * key);

void * firstMap(HashMap * table);

void * nextMap(HashMap * table);

void enlarge(HashMap * map);

#endif /* MAP_H */