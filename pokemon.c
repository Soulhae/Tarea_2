#include<string.h>
#include<stdio.h>
#include "map.h"

int ID = 0;

typedef struct Pokemon Pokemon;
typedef struct Pokedex Pokedex;

struct Pokemon{
 int id;
 char* nombre;
 int pc;
 int ps;
 char sexo;
};

struct Pokedex{
 char * nombre;
 int existencia;
 char ** tipos;
 char * EPrevia;
 char * EPosterior;
 int numeroPokedex;
 char* region;
};

Pokemon* crearPokemon(int ID, char * nombre, int PC, int PS, char * sexo)
{
    Pokemon * nuevo = (Pokemon *) malloc(sizeof(Pokemon));
    nuevo->id = ID;
    strcpy(nuevo->nombre, nombre);
    nuevo->pc = PC;
    nuevo->ps = PS;
    strcpy(nuevo->sexo, sexo); 
    return nuevo;
}

Pokedex *crearPokemondex(char *nombre, char **tipos, char *EPrevia, char *EPosterior, int numPokedex, char *region){ //falta la existencia
    Pokedex *aux = (Pokedex *) malloc(sizeof(Pokedex));
    strcpy(aux->nombre, nombre);
    aux->tipos = tipos; //como guardamos los tipos?
    strcpy(aux->EPrevia, EPrevia);
    strcpy(aux->EPosterior, EPosterior);
    aux->numeroPokedex = numPokedex;
    strcpy(aux->region, region);

}

void agregarPokemon(HashMap* mapaNombre, HashMap* mapaId, HashMap* mapaTipo, HashMap* mapaRegion, char* nombre, char** tipos, int PC, int PS, char *sexo, char* EPrevia, char* EPosterior, int numPokedex, char* region)
{
    ID++;

    Pokemon* nuevo = crearPokemon(ID, nombre, PC, PS, sexo);
    Pokedex* aux = crearPokemondex(nombre, tipos, EPrevia, EPosterior, numPokedex, region); //falta la existencia
    //falta crear mapa pokedex y agregarlo a este
	insertMap(mapaNombre, nombre, nuevo);
	insertMap(mapaId, nombre, nuevo);
	insertMap(mapaTipo, nombre, nuevo);
	insertMap(mapaRegion, nombre, nuevo);
}

void evolucionarPokemon(HashMap* almacenamiento, HashMap* pokedex,int id)
{
	calcularEvolucion();
}

void calcularEvolucion()
{	

}

void leerArchivo(HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion , char * nombreArchivo){
    FILE *archivo;
    Pokemon *nuevo;
    archivo = fopen(nombreArchivo, "r");
    if(!archivo){
        printf("----------------------------------\n");
        printf("%10s\n","No se pudo encontrar el archivo");
        printf("----------------------------------\n");
    }else{
        char line[150];
        char *token;
        int id;
        char *nombre;
        int existencia; //como verificamos si ya ingresamos este pokemon?
        char **tipos;
        tipos = (char **) malloc(18*sizeof(char *));
        int pc;
        int ps;
        char sexo;
        char *EPrevia;
        char *EPosterior;
        int numeroPokedex;
        char *region;
        fgets(line,150,archivo); //elimina primera linea
        while(fgets(line,150,archivo)){
            token = strtok(line,",");
            id = atoi(token);
            token = strtok(NULL,",");
            nombre = token;
            //duda cantidad de tipos, como sabemos cuando parar? lo preguntamos?
            token = strtok(NULL,",");
            pc = atoi(token);
            token = strtok(NULL,",");
            ps = atoi(token);
            token = strtok(NULL,",");
            sexo = token;
            token = strtok(NULL,",");
            EPrevia = token;
            token = strtok(NULL,",");
            EPosterior = token;
            token = strtok(NULL,",");
            numeroPokedex = atoi(token);
            token = strtok(NULL,",");
            region = token;
            agregarPokemon(mapaNombre, mapaId, mapaTipo, mapaRegion, nombre, tipos, pc, ps, sexo, EPrevia, EPosterior, numeroPokedex, region); //falta pasar la existencia

        }
    }
}