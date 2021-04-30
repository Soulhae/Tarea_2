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
 char id[10];
 char nombre[20];
 int pc;
 int ps;
 char sexo[10];
};

struct Pokedex{
 char nombre[20];
 int existencia;
 List* tipos;
 char EPrevia[20];
 char EPosterior[20];
 char numeroPokedex[10];
 char region[15];
};

Pokemon* crearPokemon(char* ID, char * nombre, int PC, int PS, char *sexo) //falta la existencia
{
    Pokemon * nuevo = (Pokemon *) malloc(sizeof(Pokemon));
   
    strcpy(nuevo->id, ID);
    strcpy(nuevo->nombre, nombre);
    nuevo->pc = PC;
    nuevo->ps = PS;
    strcpy(nuevo->sexo, sexo);
   
    return nuevo;
}

Pokedex* crearPokedex(char * nombre, List* tipos, char * previa, char * posterior, char * num, char * region)
{
    Pokedex * nuevo = (Pokedex *) malloc(sizeof(Pokedex));
    
    strcpy(nuevo->nombre, nombre);
    nuevo->tipos = tipos;
    strcpy(nuevo->EPrevia, previa);
    strcpy(nuevo->EPosterior, posterior);
    strcpy(nuevo->numeroPokedex, num);
    strcpy(nuevo->region, region);

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
    pushBack(almacenamiento, pokemon);
    
    Pokedex *aux1 = searchMap(mapaPokedex, nombre);
    if (aux1 == NULL){
        Pokedex* pokedex = crearPokedex(nombre, tipos, previa, posterior, numPoke, region);
        insertMap(mapaPokedex, nombre, pokedex);
        insertMap(mapaNumpPokedex, numPoke, pokedex);
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
        if(strcmp(pokedex->EPosterior,"No tiene" || "no tiene")!=0){
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

void buscarNombre(HashMap* mapaNombre, char *nombre){ // debugear para ver donde explota

    List *buscado = searchMap(mapaNombre, nombre);
    if (buscado == NULL){
        printf("aa\n");
    }
    printf("hola2\n");
    sleep(2);
    Pokemon *pokemon = firstList(buscado);
    printf("hola3\n");
    sleep(2);
    if(!buscado){
        printf("hola4\n");
        sleep(2);
        printf("-----------------------------------------------\n");
        printf("No se ha podido encontrar el pokemon solicitado\n");
        printf("-----------------------------------------------\n");
        return;
        printf("hola5\n");
        sleep(2);
    }
    printf("hola6\n");
    sleep(2);
    printf("%s %13s %15s %13s %18s\n", "ID", "Nombre", "PC", "PS", "Sexo");
    printf("hola7\n");
    sleep(2);
    while(pokemon != NULL){
        printf("hola8\n");
        sleep(2);
        printf("%i%*s%*i%*i%*c\n", pokemon->id, (16-strlen(pokemon->id)), nombre, 16, pokemon->pc, 14, pokemon->ps, 17, pokemon->sexo);
        pokemon = nextList(buscado);
        printf("hola9\n");
        sleep(2);
    }
    printf("hola10\n");
    sleep(2);
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

// intente arregloarlo con los cambios actuales a si que hay que revisarlo
/*void buscarNombrePokedex(HashMap *pokedex, char *nombre){

    Pokedex *buscado = searchMap(pokedex, nombre);
    if(!buscado){
        printf("---------------------------------------------------\n");
        printf("El pokemon solicitado no se encuentra en la pokedex\n");
        printf("---------------------------------------------------\n");
        return;
    }
    printf("%s %15s %10s %22s %25s %20s %15s\n", "Nombre", "Existencia", "Tipos", "Ev. Previa", "Ev. Posterior", "N° Pokedex", "Region");
    printf("%s%*i ", buscado->nombre, (15-strlen(buscado->nombre)), buscado->existencia);

    // Imprimir tipos
    Pokedex *iterador = firstMap(buscado->tipos);
    while (iterador != NULL){
        printf("%s", iterador->tipos);
        iterador = nextList(buscado->tipos);
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
        List* tipos = createList();
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
            id = atoi(token); // id debe entrar a agregar pokemon
            token = strtok(NULL,",");
            strcpy(nombre, token);

            //duda cantidad de tipos, como sabemos cuando parar? si hay mas de un tipo tiene comillas
            token = strtok(NULL, "\"");
            strcpy(tipo, token);

            token = strtok(NULL,",");
            pc = atoi(token);
            token = strtok(NULL,",");
            ps = atoi(token);
            token = strtok(NULL,",");
            strcpy(sexo, token);
            token = strtok(NULL,",");
            strcpy(EPrevia, token);
            token = strtok(NULL,",");
            strcpy(EPosterior, token);
            token = strtok(NULL,",");
            numeroPokedex = atoi(token);
            token = strtok(NULL,",");
            strcpy(region, token);

            /* separar por tipos, hay que probar si funciona sino intentar de otra forma ><< */
            token = strtok(tipo, ", ");
            pushBack(tipos, token);
            token = strtok(NULL, ", ");
            while (token != NULL){
                pushBack(tipos, token);
                token = strtok(NULL, ", ");
            }

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
    
    List *list_tipos = pokedex->tipos;
    Pokemon *iterador = firstList(list_tipos);
    while(iterador != NULL){
        if ( strcmp(iterador->id, pokemon->id) == 0 ){
            popCurrent(list_tipos);
        }
        iterador = nextList(list_tipos);
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