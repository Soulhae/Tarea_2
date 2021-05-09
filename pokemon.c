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
    //printf("\n");
}

void menu_pokemon(){
  printf("\nMenu de opciones\n"); // mejorar mensaje
  printf("\n");
  printf("1.- Importar/Exportar archivo.\n");
  printf("2.- Atrapar un pokemon\n");
  printf("3.- Evolucionar un pokemon\n");
  printf("4.- Mostrar pokemones de acuerdo a su tipo\n");
  printf("5.- Buscar pokemones por nombre y su informacion de combate\n");
  printf("6.- Buscar pokemon por nombre y su informacion personal\n");
  printf("7.- Mostrar todos los pokemones\n");
  printf("8.- Mostrar pokemones ordenados por puntos de combate\n");
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
    //printf("%d ", int_id);
    //printf("%s ", pokemon->id);
    strcpy(pokemon->nombre, nombre);
    //printf("%s ", pokemon->nombre);
    pokemon->pc = pc;
    //printf("%d ", pokemon->pc);
    pokemon->ps = ps;
    //printf("%d ", pokemon->ps);
    strcpy(pokemon->sexo, sexo);
    //printf("%s ", pokemon->sexo);
    return pokemon;
}

Pokedex *crear_pokedex(char *nombre, char *tipos, char *ev_prev, char *ev_post, int num_pokedex, char *region){
    Pokedex *pokedex = (Pokedex *) malloc (sizeof(Pokedex));
    strcpy(pokedex->nombre, nombre);
    //printf("%s ", pokedex->nombre);
    pokedex->existencia = 1;
    //printf("%d ", pokedex->existencia);

    strcpy(pokedex->string_tipos, tipos);
    //printf("%s ", pokedex->string_tipos);

    pokedex->tipos = createList();
    char *aux = strtok(pokedex->string_tipos, ", ");
    while(aux){
        pushBack(pokedex->tipos, aux);
        aux = strtok(NULL, ", ");
    }

    char *aux2 = firstList(pokedex->tipos);
    while(aux2){
        //printf("%s ", aux2);
        aux2 = nextList(pokedex->tipos);
    }

    strcpy(pokedex->ev_prev, ev_prev);
    //printf("%s ", pokedex->ev_prev);
    strcpy(pokedex->ev_post, ev_post);
    //printf("%s ", pokedex->ev_post);
    pokedex->num_pokedex = num_pokedex;
    //printf("%d ", pokedex->num_pokedex);
    strcpy(pokedex->region, region);
    //printf("%s ", pokedex->region);
    return pokedex;
}

void exportar_archivo(HashMap *map_id, HashMap *map_pokedex){
    char archivo[30];
    printf("Por favor ingrese el archivo al que desea exportar (.csv): ");
    getchar();

    fgets(archivo, 30, stdin);
    archivo[strlen(archivo) - 1] = '\0';

    FILE *archivoSalida = fopen(archivo, "w");
    if(archivoSalida == NULL){
        printf("No se pudo crear el archivo");
        return;
    }

    Pokemon *pokemon = firstMap(map_id);
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
        printf("El archivo no se pudo cerrar correctamente.");
    }
}

void leer_archivo(List *list_pc, List *list_numpokedex, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region){

    char archivo[30];
    printf("Por favor ingrese el archivo que se desea leer (.csv): ");
    getchar();
    
    fgets(archivo, 30, stdin);
    archivo[strlen(archivo) - 1] = '\0';

    FILE *archivoEntrada = fopen(archivo, "r");
    if (archivoEntrada == NULL){
        printf("El archivo no se pudo abrir en modo lectura");
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
            printf("Has superado la capacidad de tu almacenamiento");
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
        pushBack(list_pc, pokemon);
        insert_map_pokedex(pokedex, map_pokedex, list_numpokedex);
        insert_map_region(pokedex, map_region);
        insert_map_tipo(pokemon, pokedex, map_tipo);
        capacidad++;
    }

    //leer_mapa_id(map_id);
    //leer_mapa_pokemon(map_pokemon);
    //leer_list_pokemon(list_pc);
    //leer_mapa_pokedex(map_pokedex);
    //leer_mapa_region(map_region);
    //leer_list_numpokedex(list_numpokedex);
    //leer_mapa_tipos(map_tipo);

    if (fclose(archivoEntrada) == EOF){
        printf("El archivo no se pudo cerrar correctamente.");
    }

}

void pedir_datos(List *list_pc, List *list_numpokedex, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region){

    if(capacidad>=100){
        printf("Has superado la capacidad de tu almacenamiento");
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
    
    insert_map_pokedex(pokedex, map_pokedex, list_numpokedex);
    insert_map_pokemon(pokemon, map_pokemon);
    insert_map_id(pokemon, map_id);
    insert_map_tipo(pokemon, pokedex, map_tipo);
    insert_map_region(pokedex, map_region);
    pushBack(list_pc, pokemon);
    capacidad++;

    //leer_mapa_id(map_id);
    //leer_mapa_pokemon(map_pokemon);
    //leer_list_pokemon(list_pc);
    //leer_mapa_pokedex(map_pokedex);
    //leer_mapa_region(map_region);
    //leer_list_numpokedex(list_numpokedex);
    //leer_mapa_tipos(map_tipo);

}

void insert_map_pokedex(Pokedex *pokedex, HashMap *map_pokedex, List *list_numpokedex){
    
    Pokedex *dato_pokemon = searchMap(map_pokedex, pokedex->nombre);
    if (dato_pokemon == NULL){
        insertMap(map_pokedex, pokedex->nombre, pokedex);
        pushBack(list_numpokedex, pokedex);
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

void leer_mapa_id(HashMap *map){

    Pokemon *pokemon = firstMap(map);
    while (pokemon){
        printf("- %s -\n", pokemon->id );
        printf("%s %d %d %s \n", pokemon->nombre, pokemon->pc, pokemon->ps, pokemon->sexo);
        pokemon = nextMap(map);
    }

}

void leer_mapa_pokedex(HashMap *map){

    Pokedex *pokedex = firstMap(map);
    List *list_tipos = createList();
    char *tipo;
    while (pokedex){
        printf("%s %d %s %s %d %s %s\n", pokedex->nombre, pokedex->existencia, pokedex->ev_prev, pokedex->ev_post, pokedex->num_pokedex, pokedex->region, pokedex->string_tipos);
        pokedex = nextMap(map);
    }

}

void leer_mapa_tipos(HashMap *map_tipo){

    List *list_tipos = firstMap(map_tipo);
    Pokemon *tipo;
    while(list_tipos){
        printf("- tipo -\n");
        tipo = firstList(list_tipos);
        while(tipo){
            printf("%s %s %d %d %s \n", tipo->id, tipo->nombre, tipo->pc, tipo->ps, tipo->sexo);
            tipo = nextList(list_tipos);
        }
        list_tipos = nextMap(map_tipo);
    }

}

void leer_mapa_pokemon(HashMap *map_pokemon){

    List *list_nombres = firstMap(map_pokemon);
    Pokemon *pokemon;
    while(list_nombres){
        pokemon = firstList(list_nombres);
        if(pokemon == NULL){
            printf("No existe.\n");
            break;
        }
        else{
            printf("- %s -\n", pokemon->nombre);
            while(pokemon){
                printf("%s %d %d %s \n", pokemon->id, pokemon->pc, pokemon->ps, pokemon->sexo);
                pokemon = nextList(list_nombres);
            }
            list_nombres = nextMap(map_pokemon);
        }
    }

}

void leer_mapa_region(HashMap *map_region){

    List *list_region = firstMap(map_region);
    Pokedex *pokedex;
    while(list_region){
        pokedex = firstList(list_region);
        printf("- %s -\n", pokedex->region);
        while(pokedex){
            printf("%s %d %s %s %s\n", pokedex->nombre, pokedex->existencia, pokedex->ev_prev, pokedex->ev_post, pokedex->string_tipos);
            pokedex = nextList(list_region);
        }
        list_region = nextMap(map_region);
    }

}

void leer_tipos(HashMap *map_region, Pokedex *pokedex){

    List *list = searchMap(map_region, pokedex->region);
    Pokedex *dato = firstList(list);
    while(dato){
        List *list_tipos = dato->tipos;
        char *tipo = firstList(list_tipos);
        while(tipo){
            printf("%s ", tipo);
            tipo = nextList(list_tipos);
        }
        printf("\n");
        dato = nextList(list);
    }

}

void leer_list_pokemon(List *list_pc){

    Pokemon *pokemon = firstList(list_pc);
    while(pokemon){
        printf("%s %s %d %d %s \n", pokemon->id, pokemon->nombre, pokemon->pc, pokemon->ps, pokemon->sexo);
        pokemon = nextList(list_pc);
    }

}

void leer_list_numpokedex(List *list_num_pokedex){
    
    Pokedex *pokedex = firstList(list_num_pokedex);
    List *list_tipos;
    char *tipo;
    while (pokedex){
        printf("%s %d %s %s %d %s %s\n", pokedex->nombre, pokedex->existencia, pokedex->ev_prev, pokedex->ev_post, pokedex->num_pokedex, pokedex->region, pokedex->string_tipos);
        pokedex = nextList(list_num_pokedex);
    }
}

void buscar_nombre_pokemon(HashMap *map_pokemon, char *nombre){

    List *list_pokemon = searchMap(map_pokemon, nombre);
    Pokemon *pokemon = firstList(list_pokemon);
    if (list_pokemon == NULL || pokemon == NULL){
        printf("El pokemon buscado no existe.\n");
        return;
    }
    
    printf("\n- Informacion de combate del pokemon: %s \n", pokemon->nombre);
    while(pokemon){
        printf("%s %d %d %s\n", pokemon->id, pokemon->pc, pokemon->ps, pokemon->sexo);
        pokemon = nextList(list_pokemon);
    }
}

void buscar_nombre_pokedex(HashMap *map_pokedex, char *nombre){

    Pokedex *pokedex = searchMap(map_pokedex, nombre);
    if (pokedex == NULL){
        printf("El pokemon ingresado no existe.\n");
        return;
    }
    printf("\n- Informacion de pokedex del pokemon: %s -\n", pokedex->nombre);
    printf("%d ", pokedex->existencia);

    List *list_tipos = pokedex->tipos;
    char *tipo = firstList(list_tipos);
    while(tipo){
        printf("%s ", tipo);
        tipo = nextList(list_tipos);
    }
    printf("%s %s %d %s \n", pokedex->ev_prev, pokedex->ev_post, pokedex->num_pokedex, pokedex->region);

}

void buscar_tipo(HashMap *map_tipo, char *tipo){

    List *list_pokemon = searchMap(map_tipo, tipo);
    if (list_pokemon == NULL){
        printf("El tipo de pokemon ingresado no existe.\n");
        return;
    }
    Pokemon *pokemon = firstList(list_pokemon);
    printf("- Informacion de combate del pokemon: %s \n", tipo);
    while(pokemon){
        printf("%s %s %d %d %s\n", pokemon->id, pokemon->nombre, pokemon->pc, pokemon->ps, pokemon->sexo);
        pokemon = nextList(list_pokemon);
    }
}

void buscar_region(HashMap *map_region, char *region){

    List *list_pokemon = searchMap(map_region, region);
    if (list_pokemon == NULL){
        printf("La region ingresada no existe.\n");
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

    printf("Tienes %i pokemones de la region '%s' en tu almacenamiento:\n", cont, region);
    while(pokedex){
        if(pokedex->existencia > 0){
            printf("%s %d ", pokedex->nombre, pokedex->existencia);

            List *list_tipos = pokedex->tipos;
            char *tipo = firstList(list_tipos);
            while(tipo)
            {
                printf("%s ", tipo);
                tipo = nextList(list_tipos);
            }
            printf("%s %s %d \n", pokedex->ev_prev, pokedex->ev_post, pokedex->num_pokedex);
        }
        pokedex = nextList(list_pokemon);
    }

}

void liberar_pokemon(List *list_pc, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region){

    int int_id;
    char id[4];
    printf("Ingrese la ID del pokemon a eliminar: ");
    scanf("%i", &int_id);
    sprintf(id, "%d", int_id);
    
    Pokemon* pokemon = searchMap(map_id, id);
    char* nombre = pokemon->nombre;

    Pokedex* pokedex = searchMap(map_pokedex, nombre);
    pokedex->existencia--;
    Pokedex* borrado2 = pokedex;
    
    eraseMap(map_id, id);
    
    List* lista = searchMap(map_pokemon, nombre);
    pokemon = firstList(lista);
    while(pokemon)
    {
        if(strcmp(pokemon->id, id) == 0){
            popCurrent(lista);
            break;
        }
        else pokemon = nextList(lista);
    }

    pokemon = firstList(list_pc);
    while(pokemon)
    {
        if(strcmp(pokemon->id, id) == 0){ 
            popCurrent(list_pc);
            break;
        }
        else pokemon = nextList(list_pc);
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

    //leer_mapa_id(map_id);
    //leer_mapa_pokemon(map_pokemon);
    //leer_list_pokemon(list_pc);
    //leer_mapa_pokedex(map_pokedex);
    //leer_mapa_region(map_region);
    //leer_mapa_tipos(map_tipo);

    printf("Pokemon liberado correctamente. \n");
    capacidad--;

}

void evolucionar(List *list_pc, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region)
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
        printf("no se encuentra"); // nos salimos de la funcion o pedimos que ingrese denuevo otro id?
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
        printf("El pokemon ingresado no tiene evolucion.\n");
        return;
    }
    char *previa = pokedex->ev_prev;
    pokedex->existencia--;
    //printf("PC y PS originales: %i - %i \n", pokemon->pc, pokemon->ps);
    strcpy(pokemon->nombre, pokedex->ev_post);
    pokemon->pc *= 1.5;
    pokemon->ps *= 1.25;

    int num;

    /* pasar lista a string
    Pokedex* evolucion = searchMap(map_pokedex, pokemon->nombre);
    if(evolucion)
        evolucion->existencia++;
    else
    {
        char posterior[20] = "No tiene";
        crear_pokedex(pokemon->nombre, pokedex->tipos, previa, posterior, num, pokedex->region);
        // falta numero pokedex
    }*/


    //printf("PC y PS ev mapa id: %i - %i \n", pokemon->pc, pokemon->ps);
    //printf("PC y PS otro mapa: %i - %i \n", pokemon->pc, pokemon->ps);
}

void ordenar_pc(List *list_pc)
{
    int cont = capacidad;
    Pokemon* pokemon = firstList(list_pc);
    /*while(pokemon)
    {
        cont++;
        pokemon = nextList(list_pc);
    }

    pokemon = firstList(list_pc);*/

    Pokemon* arreglo = (Pokemon*) malloc(cont * sizeof(Pokemon));

    int i, j, flag;
    for(i = 0; i < cont; i++)
    {
        strcpy(arreglo[i].id, pokemon->id);
        strcpy(arreglo[i].nombre, pokemon->nombre);
        arreglo[i].pc = pokemon->pc;
        arreglo[i].ps = pokemon->ps;
        strcpy(arreglo[i].sexo, pokemon->sexo);

        pokemon = nextList(list_pc);
    }

    Pokemon aux;
    
    /*for(i = 0; i < cont-1; i++)
    {
        for(j = i+1; j < cont-1; j++)
        {
            printf("%i %i ", arreglo[j].pc, arreglo[j+1].pc);
            if(arreglo[j].pc > arreglo[j+1].pc)
            {
                printf("si\n");
                aux = arreglo[j];
                arreglo[j] = arreglo[j+1];
                arreglo[j+1] = aux;
            }else 
                printf("no\n");
        }
    }*/

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
    int benja = 0;
   for  (i = 0; i < cont; i++)
   {
       benja++;
       printf("%s %i %i\n", arreglo[i].nombre, arreglo[i].pc, benja);
   }
   printf("%i", capacidad);
   
    
    /* 
    List* ordenada = createList();
    for(int i=0; i < cont; i++)
    {
        pushBack(ordenada, &arreglo[i]);
    } 

    Pokemon* nuevo = firstList(ordenada);
    while(nuevo)
    {
        printf("%s %s %i %i %s\n", nuevo->id, nuevo->nombre, nuevo->pc, nuevo->ps, nuevo->sexo);
        nuevo = nextList(ordenada);
    } */
}

void ordenar_pokedex(List* list_numpokedex)
{
    int cont = 0;
    Pokedex* pokemon = firstList(list_numpokedex);
    while(pokemon)
    {
        cont++;
        pokemon = nextList(list_numpokedex);
    }

    int* arreglo = (int*) malloc(cont * sizeof(int));
    int i, j, flag, aux;
    
    pokemon = firstList(list_numpokedex);
    for (i = 0; i < cont; i++)
    {
        arreglo[i] = pokemon->num_pokedex;
        pokemon = nextList(list_numpokedex);
    }
    
    /*for(i = 0; i < cont-1; i++)
    {
        for(j = i+1; j < cont-1; j++)
        {
            printf("%i %i ", arreglo[j].pc, arreglo[j+1].pc);
            if(arreglo[j].pc > arreglo[j+1].pc)
            {
                printf("si\n");
                aux = arreglo[j];
                arreglo[j] = arreglo[j+1];
                arreglo[j+1] = aux;
            }else 
                printf("no\n");
        }
    }*/

    for(i = 1; i < cont; i++) // Es mas rapido si la lista ya esta ordenada?
    {          
        aux = arreglo[i];
        j = i-1;
        while((aux < arreglo[j]) && (j >= 0))
        {
            arreglo[j+1] = arreglo[j];
            j = j-1;
        }
        arreglo[j+1] = aux;
   }
   for  (i = 0; i < cont; i++)
   {
       printf("%i\n", arreglo[i]);
   }
   
    
    /* 
    List* ordenada = createList();
    for(int i=0; i < cont; i++)
    {
        pushBack(ordenada, &arreglo[i]);
    } 

    Pokemon* nuevo = firstList(ordenada);
    while(nuevo)
    {
        printf("%s %s %i %i %s\n", nuevo->id, nuevo->nombre, nuevo->pc, nuevo->ps, nuevo->sexo);
        nuevo = nextList(ordenada);
    } */
}