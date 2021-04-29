#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
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
 char * nombre;
 int existencia;
 List* tipos;
 char * EPrevia;
 char * EPosterior;
 int numeroPokedex;
 char* region;
};

Pokemon* crearPokemon(char* ID, char * nombre, int PC, int PS, char *sexo) //falta la existencia
{
    Pokemon * nuevo = (Pokemon *) malloc(sizeof(Pokemon));
   
    strcpy(nuevo->id, ID);
    strcpy(nuevo->nombre, nombre);
    nuevo->pc = PC;
    nuevo->ps = PS;
    nuevo->sexo = sexo;
   
    return nuevo;
}

Pokedex* crearPokedex(char * nombre, List* tipos, char * previa, char * posterior, int num, char * region)
{
    Pokedex * nuevo = (Pokedex *) malloc(sizeof(Pokedex));
    printf("a");
        sleep(2);
    nuevo->numeroPokedex = num;
    printf("g");
        sleep(2);
    nuevo->tipos = tipos;
    printf("asdsada");
        sleep(2);
    strcpy(nuevo->EPrevia, previa);
    printf("e");
        sleep(2);
    strcpy(nuevo->EPosterior, posterior);
    printf("f");
        sleep(2);
    strcpy(nuevo->region, region);
    printf("h");
        sleep(2);  
    strcpy(nuevo->nombre, nombre);
    printf("b");
        sleep(2);
    nuevo->existencia = 1;
    printf("c");
        sleep(2);

    return nuevo;
}

void agregarLista(HashMap * map, char * key, Pokemon * nuevo)
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
    char auxId[4];
    sprintf(auxId, "%i", ID); 
    char numPoke[4];
    sprintf(numPoke, "%i", numPokedex);

    Pokemon* pokemon = crearPokemon(auxId, nombre, PC, PS, sexo);
    printf("alo");
    sleep(5);
    
    if (searchMap(mapaPokedex, nombre) == NULL){
        printf("1\n");
        sleep(2);
        sleep(10);
        Pokedex* pokedex = crearPokedex(nombre, tipos, previa, posterior, numPokedex, region);
        printf("2");
        sleep(2);
        insertMap(mapaPokedex, nombre, pokedex);
        printf("3");
        sleep(2);
        insertMap(mapaNumpPokedex, numPoke, pokedex);
        printf("4");
        sleep(2);
    }
    else{
        Pokedex *aux = searchMap(mapaPokedex, nombre);
        aux->existencia ++;
    }

	insertMap(mapaId, auxId, pokemon); 
    
    agregarLista(mapaRegion, region, pokemon);
    agregarLista(mapaNombre, nombre, pokemon);

    char * tipo = firstList(tipos);
    while(tipo != NULL)
    {                                                           //arreglar guardar tipos en menu.c
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
    char *auxId = (char *) (id + '0');  //cambiar por sprintf
	Pokemon * pokemon = searchMap(mapaId, auxId);
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
            printf("Felicitaciones su %s a evolucionado a %s!", pokedex->nombre, pokemon->nombre);
            printf("-----------------------------------------------\n");
        
            Pokedex * evolucion = searchMap(mapaPokedex, pokemon->nombre);
            evolucion->existencia++;
        }
    }
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
    printf("%s %13s %15s %13s %18s\n", "ID", "Nombre", "PC", "PS", "Sexo");
    while(pokemon != NULL){
        printf("%i%*s%*i%*i%*c\n", pokemon->id, (16-strlen(pokemon->id)), nombre, 16, pokemon->pc, 14, pokemon->ps, 17, pokemon->sexo);
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
        int existencia;
        List* tipos;
        char * tipo;
        int pc;
        int ps;
        char *sexo;
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
            //duda cantidad de tipos, como sabemos cuando parar? si hay mas de un tipo tiene comillas
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

        if (fclose(archivo) == EOF){
            printf("El archivo no se pudo cerrar correctamente.");
        }

    }
}

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

void ordenarPorPC(List *list_pokemon){

    Pokemon *prev = firstList(list_pokemon);
    Pokemon *post;
    Pokemon *aux;
    while(prev != NULL){
        post = nextList(list_pokemon);
        while(post != NULL){
            if (prev->pc > post->pc){
                aux = post;
                post = prev;
                prev = aux;
            }
        }
        prev = nextList(list_pokemon);
    }

    aux = firstList(list_pokemon);
    while(aux != NULL){
        printf("%s - %s - %d - %d - %s\n", aux->id, aux->nombre, aux->pc, aux->ps, aux->sexo);
        aux = nextList(list_pokemon);
    }

}

/* ojito ver detalles no sé si funcione */
void liberarPokemon(char *id, HashMap * mapaPokedex, HashMap * mapaNombre, HashMap * mapaId, HashMap * mapaTipo, HashMap * mapaRegion, HashMap * mapaNumPokedex){

    Pokemon *pokemon = searchMap(mapaId, id);
    Pokedex *pokedex = searchMap(mapaPokedex, pokemon->nombre);
    pokedex->existencia --;

    eraseMap(mapaId, id);
    eraseMap(mapaNombre, pokemon->nombre);
    eraseMap(mapaPokedex, pokedex->nombre);
    eraseMap(mapaNumPokedex, pokedex->numeroPokedex);

    List *list_tipos = searchMap(mapaTipo, pokedex->tipos);
    Pokemon *iterador = firstList(list_tipos);
    while(iterador != NULL){
        if ( strcmp(iterador->id, pokemon->id) == 0 ){
            popCurrent(list_tipos);
        }
        iterador = next(list_tipos);
    }

    List *list_region = searchMap(mapaRegion, pokedex->region);
    iterador = firstList(list_region);
    while(iterador != NULL){
        if ( strcmp(iterador->id, pokemon->id) == 0 ){
            popCurrent(list_region);
        }
        iterador = nextList(list_region);
    }

}