#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "list.h"
#include "pokemon.h"

int int_id = 0;
int capacidad = 0;

typedef struct Pokemon Pokemon;
typedef struct Pokedex Pokedex;

struct Pokemon{
    char id[4];
    char nombre[20];
    int pc;
    int ps;
    char sexo[10];
};

struct Pokedex{
    char nombre[20];
    int existencia;
    char string_tipos[1024];
    List *tipos;
    char ev_prev[20];
    char ev_post[20];
    int num_pokedex;
    char region[20];
};

void bienvenida()
{
    printf("                                  ,'\\\n");
    printf("    _.----.        ____         ,'  _\\   ___    ___     ____\n");
    printf("_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n");
    printf("\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n");
    printf(" \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n");
    printf("   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n");
    printf("    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n");
    printf("     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n");
    printf("      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n");
    printf("       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n");
    printf("        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n");
    printf("                                `'                            '-._|\n");
    printf("\n   Bienvenido a Zona Pokemiau!!\n"); 
}

void menu_pokemon(){
  printf("\n   Por favor ingrese una opcion\n\n");
  printf("1.- Importar/Exportar archivo.\n");
  printf("2.- Atrapar un pokemon\n");
  printf("3.- Evolucionar un pokemon\n");
  printf("4.- Mostrar pokemones de acuerdo a su tipo\n");
  printf("5.- Buscar pokemones por nombre y mostrar su informacion de combate\n");
  printf("6.- Buscar pokemon por nombre y mostrar su informacion de pokedex\n");
  printf("7.- Mostrar todos los pokemones con su informacion de pokedex\n");
  printf("8.- Mostrar pokemones del almacenamiento ordenados por puntos de combate\n");
  printf("9.- Liberar un pokemon\n");
  printf("10.- Mostrar pokemones de acuerdo a su region\n");
  printf("11.- Salir del juego\n");
  printf("\n");
  printf("Ingrese opcion: ");
}

Pokemon *crear_pokemon(char *nombre, int pc, int ps, char *sexo){
    Pokemon *pokemon = (Pokemon *) malloc (sizeof(Pokemon));

    char id[4];
    int_id ++;
    sprintf(id, "%d", int_id);

    strcpy(pokemon->id, id);
    int_id = atoi(id);
    char * nombre_aux = strtok(nombre, " ");
    strcpy(pokemon->nombre, nombre_aux);
    pokemon->pc = pc;
    pokemon->ps = ps;
    strcpy(pokemon->sexo, sexo);
    return pokemon;
}

Pokedex *crear_pokedex(char *nombre, char *tipos, char *ev_prev, char *ev_post, int num_pokedex, char *region){
    Pokedex *pokedex = (Pokedex *) malloc (sizeof(Pokedex));
    char * nombre_aux = strtok(nombre, " ");
    strcpy(pokedex->nombre, nombre_aux);
    pokedex->existencia = 1;
    strcpy(pokedex->string_tipos, tipos);
    pokedex->tipos = createList();

    char *aux = strtok(pokedex->string_tipos, ", ");
    while(aux){
        pushBack(pokedex->tipos, aux);
        aux = strtok(NULL, ", ");
    }

    char *aux2 = firstList(pokedex->tipos);
    while(aux2){
        aux2 = nextList(pokedex->tipos);
    }

    strcpy(pokedex->ev_prev, ev_prev);
    strcpy(pokedex->ev_post, ev_post);
    pokedex->num_pokedex = num_pokedex;
    strcpy(pokedex->region, region);
    return pokedex;
}

void exportar_archivo(HashMap *map_id, HashMap *map_pokedex){
    char archivo[30];

    Pokemon *pokemon = firstMap(map_id);
    if(!pokemon){
        printf("\n        No hay pokemones en tu almacenamiento para exportar\n");
        return;
    }

    printf("Por favor ingrese el archivo al que desea exportar (.csv): ");
    getchar();

    fgets(archivo, 30, stdin);
    archivo[strlen(archivo) - 1] = '\0';

    FILE *archivoSalida = fopen(archivo, "w");
    if(archivoSalida == NULL){
        printf("\nNo se pudo crear/abrir el archivo\n");
        return;
    }

    fprintf(archivoSalida, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "id", "nombre", "tipos", "pc", "ps", "sexo", "evolucion previa", "evolucion posterior", "numero pokedex", "region");
    while (pokemon){
        Pokedex *pokedex = searchMap(map_pokedex, pokemon->nombre);
        fprintf(archivoSalida, "%s,%s,", pokemon->id, pokemon->nombre);
        char *tipos = firstList(pokedex->tipos);
        int cont=0;
        int cont2=0;
        while(tipos){
            cont++;
            tipos = nextList(pokedex->tipos);
        }
        tipos = firstList(pokedex->tipos);
        while(tipos){
            if(cont>1){
                if(cont2 == 0) fprintf(archivoSalida, "\"%s, ", tipos);
                else if(cont2 == cont-1) fprintf(archivoSalida, "%s\",", tipos);
                else fprintf(archivoSalida, "%s, ", tipos);
            }else{
                fprintf(archivoSalida, "%s,", tipos);
            }
            tipos = nextList(pokedex->tipos);
            cont2++;
        }
        fprintf(archivoSalida, "%i,%i,%s,%s,%s,%i,%s\n", pokemon->pc, pokemon->ps, pokemon->sexo, pokedex->ev_prev, pokedex->ev_post, pokedex->num_pokedex, pokedex->region);
        pokemon = nextMap(map_id);
    }

    if (fclose(archivoSalida) == EOF){
        printf("\nEl archivo no se pudo cerrar correctamente.\n");
    }else{
        printf("\nEl archivo se creo/modifico correctamente.\n");
    }
}

void leer_archivo(HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region){

    char archivo[30];
    printf("Por favor ingrese el archivo que se desea leer (.csv): ");
    getchar();
    
    fgets(archivo, 30, stdin);
    archivo[strlen(archivo) - 1] = '\0';

    FILE *archivoEntrada = fopen(archivo, "r");
    if (archivoEntrada == NULL){
        printf("\nEl archivo no se pudo abrir, o no existe\n");
        return;
    }

    char linea[1024];
    char *token;
    char *id;
    char *nombre;
    int pc;
    int ps;
    char *sexo;
    char *tipo;
    char *ev_prev;
    char *ev_post;
    int num_pokedex;
    char *region;

    Pokemon *pokemon;
    Pokedex *pokedex;

    fgets(linea, 1023, archivoEntrada);
    while (fscanf(archivoEntrada, "%[^\n]s", linea) != EOF){
        fgetc(archivoEntrada);

        if(capacidad>=100){
            printf("\nHas superado la capacidad de tu almacenamiento\n");
            return;
        } 

        token = strtok(linea, ",");
        id = token;

        token = strtok(NULL, ",");
        nombre = token;

        token = strtok(NULL, "\"");
        tipo = token;

        token = strtok(NULL, ",");
        if (token == NULL){
            token = strtok(tipo, ",");
            tipo = token;
            token = strtok(NULL, ",");
            pc = atoi(token);
        }
        else{
            pc = atoi(token);
        }

        token = strtok(NULL, ",");
        ps = atoi(token);

        token = strtok(NULL, ",");
        sexo = token;

        token = strtok(NULL, ",");
        ev_prev = token;

        token = strtok(NULL, ",");
        ev_post = token;

        token = strtok(NULL, ",");
        num_pokedex = atoi(token);

        token = strtok(NULL, ",");
        region = token;

        pokemon = crear_pokemon(nombre, pc, ps, sexo);
        pokedex = crear_pokedex(nombre, tipo, ev_prev, ev_post, num_pokedex, region);
        //printf("\n");
        insert_map_pokemon(pokemon, map_pokemon);
        insert_map_id(pokemon, map_id);
        insert_map_pokedex(pokedex, map_pokedex);
        insert_map_region(pokedex, map_region);
        insert_map_tipo(pokemon, pokedex, map_tipo);
        capacidad++;
    }

    if (fclose(archivoEntrada) == EOF){
        printf("\nEl archivo no se pudo cerrar correctamente.\n");
    }else{
        printf("\nEl archivo se leyo correctamente.\n");
    }

}

void pedir_datos(HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region){

    if(capacidad>=100){
        printf("\nHas superado la capacidad de tu almacenamiento\n");
        return;
    }

	char nombre[20];
	char sexo[10];
    char tipos[1024];
	char ev_prev[20];
	char ev_post[20];
	int pc, ps, num_pokedex;
	char region[20];

	printf("Ingrese el nombre del pokemon: ");
	scanf("%s", nombre);
    getchar();
	
    printf("Ingrese el tipo o los tipos de su pokemon: ");
    fgets(tipos, 1024, stdin);
    tipos[strlen(tipos) - 1] = '\0';

	printf("Ingrese los puntos de combate del pokemon: ");
	scanf("%d", &pc);

	printf("Ingrese los puntos de salud del pokemon: ");
	scanf("%d", &ps);
    getchar();

	printf("Ingrese el sexo del pokemon (Macho, Hembra o 'No tiene'): ");
	fgets(sexo, 10, stdin);
    sexo[strlen(sexo) - 1] = '\0';
    
	printf("Ingrese su evolucion previa (Si no tiene simplemente escriba: 'No tiene'): ");
	fgets(ev_prev, 20, stdin);
    ev_prev[strlen(ev_prev) - 1] = '\0';

	printf("Ingrese su evolucion posterior (Si no tiene simplemente escriba: 'No tiene'): ");
	fgets(ev_post, 20, stdin);
    ev_post[strlen(ev_post) - 1] = '\0';

    /* Falta comparar num de pokedex */
	printf("Ingrese el numero en la pokedex del pokemon: ");
	scanf("%d", &num_pokedex);

	printf("Ingrese la region del pokemon: ");
	scanf("%s", region);

    Pokemon *pokemon = crear_pokemon(nombre, pc, ps, sexo);
    Pokedex *pokedex = crear_pokedex(nombre, tipos, ev_prev, ev_post, num_pokedex, region);
    
    insert_map_pokedex(pokedex, map_pokedex);
    insert_map_pokemon(pokemon, map_pokemon);
    insert_map_id(pokemon, map_id);
    insert_map_tipo(pokemon, pokedex, map_tipo);
    insert_map_region(pokedex, map_region);
    capacidad++;

}

void insert_map_pokedex(Pokedex *pokedex, HashMap *map_pokedex){
    
    Pokedex *dato_pokemon = searchMap(map_pokedex, pokedex->nombre);
    if (dato_pokemon == NULL){
        insertMap(map_pokedex, pokedex->nombre, pokedex);
    }
    else{
        dato_pokemon->existencia ++;
    }
    
}

void insert_map_pokemon(Pokemon *pokemon, HashMap *map_pokemon){

    List *list = searchMap(map_pokemon, pokemon->nombre);
    if (list == NULL){
        List *list_nombres = createList();
        pushBack(list_nombres, pokemon);
        insertMap(map_pokemon, pokemon->nombre, list_nombres);
    }
    else{
        pushBack(list, pokemon);
    }

}

void insert_map_id(Pokemon *pokemon, HashMap *map_id){

    insertMap(map_id, pokemon->id, pokemon);

}

void insert_map_tipo(Pokemon *pokemon, Pokedex *pokedex, HashMap *map_tipo){

    List *aux = pokedex->tipos;
    char *tipo = firstList(aux);
    while(tipo){
        List *list = searchMap(map_tipo, tipo);
        if (list == NULL){
            List *list_tipos = createList();
            pushBack(list_tipos, pokemon);
            insertMap(map_tipo, tipo, list_tipos);
        }
        else{
            pushBack(list, pokemon);
        }
        tipo = nextList(aux);
    }

}

void insert_map_region(Pokedex *pokedex, HashMap *map_region){

    List *list = searchMap(map_region, pokedex->region);
    if (list == NULL){
        List *list_region = createList();
        pushBack(list_region, pokedex);
        insertMap(map_region, pokedex->region, list_region);
    }else{
        Pokedex* aux = firstList(list);
        char* nombre = pokedex->nombre;
        while(aux){
            if(strcmp(aux->nombre, nombre) == 0) return;
            else aux = nextList(list);
        }
        pushBack(list, pokedex);
    }

}

int contarDigitos(int num){
    int cont=0;
    while(num){
        num/=10;
        cont++;
    }

    return cont;
}

void buscar_nombre_pokemon(HashMap *map_pokemon, char *nombre){

    List *list_pokemon = searchMap(map_pokemon, nombre);
    if (list_pokemon == NULL){
        printf("\n      El pokemon ingresado no existe en tu almacenamiento.\n");
        return;
    }

    Pokemon *pokemon = firstList(list_pokemon);

    printf("\n  Informacion de combate del pokemon: %s \n\n", pokemon->nombre);
    printf("%s %13s %15s %13s %18s\n", "ID", "Nombre", "PC", "PS", "Sexo");
    while(pokemon){
        //printf("%s %d %d %s\n", pokemon->id, pokemon->pc, pokemon->ps, pokemon->sexo);
        printf("%s%*s%*i%*i%*s\n", pokemon->id, (16-strlen(pokemon->id)), nombre, 16, pokemon->pc, 14, pokemon->ps, 19, pokemon->sexo);
        pokemon = nextList(list_pokemon);
    }
}

void buscar_nombre_pokedex(HashMap *map_pokedex, char *nombre){

    Pokedex *pokedex = searchMap(map_pokedex, nombre);
    if (pokedex == NULL){
        printf("\n      El pokemon ingresado no existe en la pokedex.\n");
        return;
    }
    printf("\n  Informacion de pokedex del pokemon: %s \n\n", pokedex->nombre);
    printf("%s %13s %15s %13s %18s %15s %17s\n", "Num. Pokedex", "Nombre", "Existencia", "Ev. Previa", "Ev. Posterior", "Region", "Tipos");
    List *list_tipos = pokedex->tipos;
    char *tipo = firstList(list_tipos);

    printf("     %i%*s%*i%*s%*s%*s", pokedex->num_pokedex, (21-contarDigitos(pokedex->num_pokedex)), pokedex->nombre, 11, pokedex->existencia, 19, pokedex->ev_prev, 19, pokedex->ev_post, 16, pokedex->region);
    printf("         ");
    while(tipo){
        printf("%s ", tipo);
        tipo = nextList(list_tipos);
    }
    printf("\n");
}

void buscar_tipo(HashMap *map_tipo, char *tipo){

    List *list_pokemon = searchMap(map_tipo, tipo);
    if (list_pokemon == NULL){
        printf("\n      El tipo de pokemon ingresado no existe.\n");
        return;
    }
    Pokemon *pokemon = firstList(list_pokemon);
    printf("\n  Informacion de combate de los pokemon de tipo: %s  \n\n", tipo);
    printf("%s %13s %15s %13s %18s\n", "ID", "Nombre", "PC", "PS", "Sexo");
    while(pokemon){
        printf("%s%*s%*i%*i%*s\n", pokemon->id, (16-strlen(pokemon->id)), pokemon->nombre, 16, pokemon->pc, 14, pokemon->ps, 19, pokemon->sexo);
        pokemon = nextList(list_pokemon);
    }
}

void buscar_region(HashMap *map_region, char *region){

    List *list_pokemon = searchMap(map_region, region);
    if (list_pokemon == NULL){
        printf("\n      La region ingresada no existe.\n");
        return;
    }

    Pokedex *pokedex = firstList(list_pokemon);
    int cont = 0;
    while(pokedex)
    {
        cont += pokedex->existencia;
        pokedex = nextList(list_pokemon);
    }

    pokedex = firstList(list_pokemon);

    printf("\n      Tienes %i pokemones de la region '%s' en tu almacenamiento:\n\n", cont, region);
    printf("%s %13s %15s %13s %18s %15s %17s\n", "Num. Pokedex", "Nombre", "Existencia", "Ev. Previa", "Ev. Posterior", "Region", "Tipos");
    while(pokedex){
        if(pokedex->existencia > 0){
            printf("     %i%*s%*i%*s%*s%*s", pokedex->num_pokedex, (21-contarDigitos(pokedex->num_pokedex)), pokedex->nombre, 11, pokedex->existencia, 19, pokedex->ev_prev, 19, pokedex->ev_post, 16, pokedex->region);
            printf("         ");

            List *list_tipos = pokedex->tipos;
            char *tipo = firstList(list_tipos);
            while(tipo)
            {
                printf("%s ", tipo);
                tipo = nextList(list_tipos);
            }
            printf("\n");
        }
        pokedex = nextList(list_pokemon);
    }

}

void liberar_pokemon(char* id, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region, int flag){
    
    Pokemon* pokemon = searchMap(map_id, id);
    if(pokemon == NULL)
    {
        printf("\n      La ID ingresada no corresponde a ningun pokemon.\n");
        return;
    }
    char* nombre = pokemon->nombre;

    Pokedex* pokedex = searchMap(map_pokedex, nombre);
    pokedex->existencia--;
    Pokedex* borrado2 = pokedex;
    
    eraseMap(map_id, id);

    List* lista = searchMap(map_pokemon, nombre);
    pokemon = firstList(lista);
    if(pokedex->existencia == 0)
    {
        eraseMap(map_pokemon, nombre);
    }
    else
    {
        while(pokemon)
        {
            if(strcmp(pokemon->id, id) == 0){
                popCurrent(lista);
                break;
            }
            else pokemon = nextList(lista);
        }
    }
    

    char* tipo = firstList(borrado2->tipos);

    while(tipo)
    {
        lista = searchMap(map_tipo, tipo);
        pokemon = firstList(lista);
        while(pokemon)
        {
            if(strcmp(pokemon->id, id) == 0){
                popCurrent(lista);
                break;
            }
            else pokemon = nextList(lista);
        }

        tipo = nextList(borrado2->tipos);
    }
    capacidad--;

    if (flag == 1)
        printf("\n      Pokemon liberado correctamente. \n");
    

}

void evolucionar(HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region)
{
    // que se hace con lista num pokedex?
    int int_id;
    char id[4];
    printf("Ingrese la ID del pokemon a evolucionar: ");
    scanf("%i", &int_id);
    sprintf(id, "%d", int_id);

    Pokemon* pokemon = searchMap(map_id, id);
    if(!pokemon)
    {
        printf("\n                 La ID no corresponde a ningun pokemon.\n"); 
        return;
    }

    List* lista = searchMap(map_pokemon, pokemon->nombre);
    pokemon = firstList(lista);
    while(pokemon)
    {
        if (strcmp(pokemon->id, id) == 0) break;
        else pokemon = nextList(lista);
    }

    Pokedex* pokedex = searchMap(map_pokedex, pokemon->nombre);
    if(strcmp(pokedex->ev_post, "No tiene") == 0)
    {
        printf("\n                 El pokemon ingresado no tiene evolucion.\n");
        return;
    }
    
    char antiguo[20];
    char evolucion[20];
	char sexo[10];
    char tipos[1024];
	char ev_prev[20];
	char ev_post[20];
	int pc, ps, num_pokedex;
	char region[20];
    Pokedex* posterior = searchMap(map_pokedex, evolucion);
    if (posterior)
        strcpy(ev_post, posterior->ev_post);
    else
        strcpy(ev_post, "No tiene");
    
    strcpy(antiguo, pokemon->nombre);
    strcpy(evolucion, pokedex->ev_post);
    strcpy(sexo, pokemon->sexo);
    pc = pokemon->pc * 1.5;
    ps = pokemon->ps * 1.25;
    strcpy(tipos, pokedex->string_tipos);
    strcpy(ev_prev, antiguo);
    num_pokedex = pokedex->num_pokedex + 1;
    strcpy(region, pokedex->region);

    liberar_pokemon(id, map_pokedex, map_pokemon, map_id, map_tipo, map_region, 0);

    Pokemon *nuevo = (Pokemon *) malloc (sizeof(Pokemon));

    strcpy(nuevo->id, id);
    strcpy(nuevo->nombre, evolucion);
    nuevo->pc = pc;
    nuevo->ps = ps;
    strcpy(nuevo->sexo, sexo);
    pokedex = crear_pokedex(evolucion, tipos, ev_prev, ev_post, num_pokedex, region);
    
    insert_map_pokedex(pokedex, map_pokedex);
    insert_map_pokemon(nuevo, map_pokemon);
    insert_map_id(nuevo, map_id);
    insert_map_tipo(nuevo, pokedex, map_tipo);
    insert_map_region(pokedex, map_region);

    printf("\n                 Su %s ha evolucionado a un %s!\n", antiguo, evolucion);
}

void ordenar_pc(HashMap* map_id)
{
    int cont = capacidad;
    
    Pokemon* pokemon = firstMap(map_id);
    Pokemon* arreglo = (Pokemon*) malloc(cont * sizeof(Pokemon));

    if(!pokemon){
        printf("        No hay pokemones en tu almacenamiento\n");
        return;
    }
    
    int i, j;
    Pokemon aux;
    for(i = 0; i < cont; i++)
    {
        strcpy(arreglo[i].id, pokemon->id);
        strcpy(arreglo[i].nombre, pokemon->nombre);
        arreglo[i].pc = pokemon->pc;
        arreglo[i].ps = pokemon->ps;
        strcpy(arreglo[i].sexo, pokemon->sexo);

        pokemon = nextMap(map_id);
    }

    for(i = 1; i < cont; i++) // Es mas rapido si la lista ya esta ordenada?
    {          
        aux = arreglo[i];
        j = i-1;
        while((aux.pc < arreglo[j].pc) && (j >= 0))
        {
            arreglo[j+1] = arreglo[j];
            j = j-1;
        }
        arreglo[j+1] = aux;
   }

    printf("\n                 Pokemones del almacenamiento\n\n");
    printf("%s %13s %15s %13s %18s\n", "ID", "Nombre", "PC", "PS", "Sexo");
    for  (i = 0; i < cont; i++)
    {
        printf("%s%*s%*i%*i%*s\n", arreglo[i].id, (16-strlen(arreglo[i].id)), arreglo[i].nombre, 16, arreglo[i].pc, 14, arreglo[i].ps, 19, arreglo[i].sexo);
    }
}

void ordenar_pokedex(HashMap* map_pokedex)
{
    int cont = size(map_pokedex);
    Pokedex* pokemon = firstMap(map_pokedex);

    Pokedex* arreglo = (Pokedex*) malloc(cont * sizeof(Pokedex));
    if(!pokemon){
        printf("        No hay pokemones en la pokedex\n");
        return;
    }
    int i, j;
    Pokedex aux;
    
    for (i = 0; i < cont; i++)
    {
        strcpy(arreglo[i].nombre, pokemon->nombre);
        arreglo[i].existencia = pokemon->existencia;
        arreglo[i].tipos = pokemon->tipos;
        strcpy(arreglo[i].ev_prev, pokemon->ev_prev);
        strcpy(arreglo[i].ev_post, pokemon->ev_post);
        arreglo[i].num_pokedex = pokemon->num_pokedex;
        strcpy(arreglo[i].region, pokemon->region);

        pokemon = nextMap(map_pokedex);
    }

    for(i = 1; i < cont; i++) // Es mas rapido si la lista ya esta ordenada?
    {          
        aux = arreglo[i];
        j = i-1;
        while((aux.num_pokedex < arreglo[j].num_pokedex) && (j >= 0))
        {
            arreglo[j+1] = arreglo[j];
            j = j-1;
        }
        arreglo[j+1] = aux;
    }

    
    printf("%s %13s %15s %13s %18s %15s %17s\n", "Num. Pokedex", "Nombre", "Existencia", "Ev. Previa", "Ev. Posterior", "Region", "Tipos");
    for  (i = 0; i < cont; i++)
    {
        char *aux = firstList(arreglo[i].tipos);
        printf("   %i%*s%*i%*s%*s%*s ", arreglo[i].num_pokedex, (23-contarDigitos(arreglo[i].num_pokedex)), arreglo[i].nombre, 11, arreglo[i].existencia, 19, arreglo[i].ev_prev, 19, arreglo[i].ev_post, 16, arreglo[i].region);
        printf("          ");
        while(aux){
            printf("%s ", aux);
            aux=nextList(arreglo[i].tipos);
        }
        printf("\n");
    }
}