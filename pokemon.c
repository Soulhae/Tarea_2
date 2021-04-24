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
 Pokemon *pokemon;
 int existencia;
 char ** tipos;
 char * EPrevia;
 char * EPosterior;
 int numeroPokedex;
 char* region;
};

Pokedex* crearPokemon(int ID, char * nombre, char **tipos, int PC, int PS, char * sexo, char *EPrevia, char *EPosterior, int numPokedex, char *region) //falta la existencia
{
    Pokedex * nuevo = (Pokedex *) malloc(sizeof(Pokedex));
    nuevo->pokemon->id = ID;
    strcpy(nuevo->pokemon->nombre, nombre);
    nuevo->tipos = tipos; //como guardamos los tipos?
    nuevo->pokemon->pc = PC;
    nuevo->pokemon->ps = PS;
    strcpy(nuevo->pokemon->sexo, sexo);
    strcpy(nuevo->EPrevia, EPrevia);
    strcpy(nuevo->EPosterior, EPosterior);
    nuevo->numeroPokedex = numPokedex;
    strcpy(nuevo->region, region); 
    return nuevo;
}

void agregarPokemon(HashMap* mapaNombre, HashMap* mapaId, HashMap* mapaTipo, HashMap* mapaRegion, char* nombre, char** tipos, int PC, int PS, char *sexo, char* EPrevia, char* EPosterior, int numPokedex, char* region)
{
    ID++;

    Pokemon* nuevo = crearPokemon(ID, nombre, PC, PS, sexo, tipos, EPrevia, EPosterior, numPokedex, region); //falta la existencia
    //falta crear mapa pokedex y agregarlo a este
	insertMap(mapaNombre, nombre, nuevo);
	insertMap(mapaId, ID, nuevo);
	insertMap(mapaTipo, nombre, nuevo);
	insertMap(mapaRegion, region, nuevo);
}

void evolucionarPokemon(HashMap* almacenamiento, HashMap* pokedex,int id)
{
	Pokemon * PokemonAlmacenamiento=searchMap(almacenamiento,id);
	if(PokemonAlmacenamiento==NULL){
    printf("-----------------------------------------------\n");
	printf("No se ha encontrado el pokemon en el almacenamiento\n");
     printf("-----------------------------------------------\n");
	return 0;	
	}else
    {
        Pokedex * PokemonPokedex=searchMap(pokedex,PokemonAlmacenamiento);
        if(PokemonPokedex->EPosterior==NULL){
            printf("-----------------------------------------------\n");
            printf("El pokemon ingresado no cuenta con evolución\n");
            printf("-----------------------------------------------\n");
            return 0;
        }else
        {
        calcularEvolucion(PokemonAlmacenamiento);
        printf("-----------------------------------------------\n");
        printf("Felicitaciones su %s a evolucionado a %s!",PokemonAlmacenamiento->nombre,PokemonPokedex->EPosterior);
        printf("-----------------------------------------------\n");
        }
        //Intento 2 que no se subio este miau
    }
	
	
}

void calcularEvolucion(Pokemon * PokemonAlmacenamiento)
{

}

int contar(int num){
    int contador=0;
    while(num>0){
        num/=10;
        contador++;
    }
    return contador;
}

void buscarNombre(HashMap* mapaNombre, char *nombre){
    Pokedex *buscado = searchMap(mapaNombre, nombre);
    if(!buscado){
        printf("-----------------------------------------------\n");
        printf("No se ha podido encontrar el pokemon solicitado\n");
        printf("-----------------------------------------------\n");
        return;        
    }
    printf("%s %13s %15s %13s %18s\n", "ID", "Nombre", "PC", "PS", "Sexo");
    if(buscado->existencia > 1){
        for(int i=0 ; i<buscado->existencia ; i++){
            printf("%i%*s%*i%*i%*c\n", buscado->pokemon->id, (16-contar(buscado->pokemon->id)), nombre, 16, buscado->pokemon->pc, 14, buscado->pokemon->ps, 17, buscado->pokemon->sexo);
            buscado=nextMap(mapaNombre);
        }
    }else{
        printf("%i%*s%*i%*i%*c\n", buscado->pokemon->id, (16-contar(buscado->pokemon->id)), nombre, 16, buscado->pokemon->pc, 14, buscado->pokemon->ps, 17, buscado->pokemon->sexo);                
    }
    printf("\n");
}

void leerArchivo(HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion , char * nombreArchivo){
    FILE *archivo;
    Pokemon *nuevo;
    archivo = fopen(nombreArchivo, "r");
    if(!archivo){
        printf("-------------------------------\n");
        printf("No se pudo encontrar el archivo\n");
        printf("-------------------------------\n");
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