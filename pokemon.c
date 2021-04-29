#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "map.h"
#include "list.h"

int ID = 0;

typedef struct Pokemon Pokemon;
typedef struct Pokedex Pokedex;

struct Pokemon{
 char* id;
 char* nombre;
 int pc;
 int ps;
 char *sexo;
};

struct Pokedex{
 char * nombre; // VA A EXPLOTAR
 int existencia;
 List* tipos; // lista???
 char * EPrevia;
 char * EPosterior;
 int numeroPokedex;
 char* region;
};

Pokemon* crearPokemon(char* ID, char * nombre, int PC, int PS, char * sexo) //falta la existencia
{
    Pokemon * nuevo = (Pokemon *) malloc(sizeof(Pokemon));
   
    strcpy(nuevo->id, ID);
    strcpy(nuevo->nombre, nombre);
    nuevo->pc = PC;
    nuevo->ps = PS;
    strcpy(nuevo->sexo, sexo);
   
    return nuevo;
}

Pokedex* crearPokedex(char * nombre, List* tipos, char * previa, char * posterior, int num, char * region)
{
    Pokedex * nuevo = (Pokedex *) malloc(sizeof(Pokedex));

    strcpy(nuevo->nombre, nombre);
    nuevo->existencia = 1;
    nuevo->tipos = tipos;
    nuevo->EPrevia = previa;
    nuevo->EPosterior = posterior;
    nuevo->numeroPokedex = num;
    nuevo->region = region;

    return nuevo;
}

void agregarLista(HashMap * map, char * key, Pokedex * nuevo)
{
    if(searchMap(map, key) == NULL)
    {
        List* lista = createList();
        pushBack(lista, nuevo); 
        insertMap(map, key, lista);
    }
    else
    {
        List* aux = searchMap(map, key);
        pushBack(aux, nuevo);
    }
}

void agregarPokemon(List* almacenamiento, HashMap * mapaPokedex, HashMap* mapaNombre, HashMap* mapaId, HashMap* mapaTipo, HashMap* mapaRegion, HashMap* mapaNumpPokedex, char* nombre, List* tipos, int PC, int PS, char *sexo, char* previa, char* posterior, int numPokedex, char* region)
{
    ID++;
    char* id = ID + '0';

    Pokemon* pokemon = crearPokemon(id, nombre, PC, PS, sexo);
    
    if (searchMap(mapaPokedex, nombre) == NULL){ //ojitoo
        Pokedex* pokedex = crearPokedex(nombre, tipos, previa, posterior, numPokedex, region);
        insertMap(mapaPokedex, nombre, pokedex);
        insertMap(mapaNumpPokedex, numPokedex, pokedex);
    }
    else{
        Pokedex *aux = searchMap(mapaPokedex, nombre);
        aux->existencia ++;
    }

	insertMap(mapaId, id, pokemon); 
    
    agregarLista(mapaRegion, region, pokemon);
    agregarLista(mapaNombre, nombre, pokemon);

    char * tipo = firstList(tipos);
    while(tipo != NULL)
    {
        agregarLista(mapaTipo, tipo, pokemon);
        tipo = nextList(tipos);
    }
}

void calcularEvolucion(Pokemon * pokemon, Pokedex* pokedex)
{
    strcpy(pokemon->nombre, pokedex->EPosterior);
    pokemon->pc *= 1.5;
    pokemon->ps *= 1.25;
}

void evolucionarPokemon(HashMap* mapaId, HashMap* mapaPokedex, int id)
{
	Pokemon * pokemon = searchMap(mapaId, id);
    Pokedex* pokedex = searchMap(mapaPokedex, pokemon->nombre);

	if(pokemon == NULL){
        printf("-----------------------------------------------\n");
        printf("No se ha encontrado el pokemon en el almacenamiento\n");
        printf("-----------------------------------------------\n");
	    return;	
	}else
    {
        if(pokedex->EPosterior == NULL){
            printf("-----------------------------------------------\n");
            printf("El pokemon ingresado no cuenta con evolución\n");
            printf("-----------------------------------------------\n");
            return;
        }else
        {
            pokedex->existencia --;
            calcularEvolucion(pokemon, pokedex);
            printf("-----------------------------------------------\n");
            printf("Felicitaciones su %s a evolucionado a %s!", pokedex->EPrevia, pokemon->nombre);
            printf("-----------------------------------------------\n");
        
            Pokedex * evolucion = searchMap(mapaPokedex, pokemon);
            evolucion->existencia++;
        }
        //Intento 2 que no se subio este miau
    }
}

int contar(int num){
    int contador = 0;
    while(num > 0){
        num /= 10;
        contador++;
    }
    return contador;
}

void buscarNombre(HashMap* mapaNombre, char *nombre){
    List * buscado = searchMap(mapaNombre, nombre);
    Pokemon * pokemon = firstList(buscado);
    if(!buscado){
        printf("-----------------------------------------------\n");
        printf("No se ha podido encontrar el pokemon solicitado\n");
        printf("-----------------------------------------------\n");
        return;        
    }
    printf("%s %13s %15s %13s %18s\n", "ID", "Nombre", "PC", "PS", "Sexo"); //arreglar esta funcion (que pasa si ingresan mas de 1 pokemon del mismo nombre?)
    while(pokemon != NULL){
        printf("%i%*s%*i%*i%*c\n", pokemon->id, (16-contar(pokemon->id)), nombre, 16, pokemon->pc, 14, pokemon->ps, 17, pokemon->sexo);
        pokemon = nextList(buscado);
    }
    printf("\n");
}

/*void buscarNombrePokedex(HashMap *pokedex, char *nombre){  //falta ver con distintos tipos de casos
    Pokedex *buscado = searchMap(pokedex, nombre);
    if(!buscado){
        printf("---------------------------------------------------\n");
        printf("El pokemon solicitado no se encuentra en la pokedex\n");
        printf("---------------------------------------------------\n");
        return;
    }
    printf("%s %15s %10s %22s %25s %20s %15s\n", "Nombre", "Existencia", "Tipos", "Ev. Previa", "Ev. Posterior", "N° Pokedex", "Region");
    printf("%s%*i ", buscado->pokemon->nombre, (15-strlen(buscado->pokemon->nombre)), buscado->existencia);
    int arraylen = (sizeof(buscado->tipos)/sizeof(buscado->tipos[0]))-1;
    for(int i=0; i<=arraylen; i++){
        if(i==arraylen){
            printf("%s ", buscado->tipos[i]);
        }else{
            printf("%*s, ", 13, buscado->tipos[i]);
        }
    }
    printf("%*s%*s%*i%*s\n", 16, buscado->EPrevia, 25, buscado->EPosterior, 18, buscado->numeroPokedex, 20, buscado->region);
}*/

void mostrarRegion(char * region, HashMap * map)
{
    List* lista = searchMap(map, region);
    Pokedex* pokemon = firstList(lista);
    
    printf("Tus pokemones de %s son: \n", region);
    printf("Nombre Existencia Tipos Ev. Previa Ev. Posterior Numero pokedex region\n");
    
    while(pokemon != NULL)
    {
        printf("%s, %i, %s, %s, %i, %s\n", pokemon->nombre, pokemon->existencia, pokemon->EPrevia, pokemon->EPosterior, pokemon->numeroPokedex, pokemon->region); // lista de tipos
        pokemon = nextList(lista);
    }
}

void leerArchivo(List* almacenamiento, HashMap *mapaPokedex, HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion , HashMap * mapaNumPokedex, char * nombreArchivo){
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
        List* tipos;
        char * tipo;
        int pc;
        int ps;
        char *sexo;
        char *EPrevia;
        char *EPosterior;
        int numeroPokedex;
        char *region;
        int cont; // como lo hacemos?

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
            agregarPokemon(almacenamiento, mapaPokedex, mapaNombre, mapaId, mapaTipo, mapaRegion, mapaNumPokedex, nombre, tipos, pc, ps, sexo, EPrevia, EPosterior, numeroPokedex, region); //falta pasar la existencia

        }
    }
}

