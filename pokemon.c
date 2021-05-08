#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "list.h"
#include "pokemon.h"

int int_id = 0;

typedef struct Pokemon Pokemon;
typedef struct Pokedex Pokedex;

struct Pokemon{
    char id[3];
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

void menu_pokemon(){
  printf("\nMenu de opciones\n");
  printf("1.- Leer archivo.\n");
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
  printf("Ingrese opcion: ");
}

Pokemon *crear_pokemon(char *id, char *nombre, int pc, int ps, char *sexo){
    Pokemon *pokemon = (Pokemon *) malloc (sizeof(Pokemon));
    strcpy(pokemon->id, id);
    int_id = atoi(id);
    printf("%d ", int_id);
    printf("%s ", pokemon->id);
    strcpy(pokemon->nombre, nombre);
    printf("%s ", pokemon->nombre);
    pokemon->pc = pc;
    printf("%d ", pokemon->pc);
    pokemon->ps = ps;
    printf("%d ", pokemon->ps);
    strcpy(pokemon->sexo, sexo);
    printf("%s ", pokemon->sexo);
    return pokemon;
}

Pokedex *crear_pokedex(char *nombre, char *tipos, char *ev_prev, char *ev_post, int num_pokedex, char *region){
    Pokedex *pokedex = (Pokedex *) malloc (sizeof(Pokedex));
    strcpy(pokedex->nombre, nombre);
    printf("%s ", pokedex->nombre);
    pokedex->existencia = 1;
    printf("%d ", pokedex->existencia);

    strcpy(pokedex->string_tipos, tipos);
    printf("%s ", pokedex->string_tipos);

    pokedex->tipos = createList();
    char *aux = strtok(pokedex->string_tipos, ", ");
    while(aux){
        pushBack(pokedex->tipos, aux);
        aux = strtok(NULL, ", ");
    }

    char *aux2 = firstList(pokedex->tipos);
    while(aux2){
        printf("%s ", aux2);
        aux2 = nextList(pokedex->tipos);
    }

    strcpy(pokedex->ev_prev, ev_prev);
    printf("%s ", pokedex->ev_prev);
    strcpy(pokedex->ev_post, ev_post);
    printf("%s ", pokedex->ev_post);
    pokedex->num_pokedex = num_pokedex;
    printf("%d ", pokedex->num_pokedex);
    strcpy(pokedex->region, region);
    printf("%s ", pokedex->region);
    return pokedex;
}

void leer_archivo(List *list_pc, List *list_numpokedex, HashMap *map_pokedex, HashMap *map_pokemon, HashMap *map_id, HashMap *map_tipo, HashMap *map_region){

    char archivo[30];
    printf("\nPor favor ingrese el archivo que se desea leer: ");
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

        pokemon = crear_pokemon(id, nombre, pc, ps, sexo);
        pokedex = crear_pokedex(nombre, tipo, ev_prev, ev_post, num_pokedex, region);
        printf("\n");
        insert_map_pokemon(pokemon, map_pokemon);
        insert_map_id(pokemon, map_id);
        pushBack(list_pc, pokemon);
        insert_map_pokedex(pokedex, map_pokedex, list_numpokedex);
        insert_map_region(pokedex, map_region);
        insert_map_tipo(pokemon, pokedex, map_tipo);
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

    char id[3];
	char nombre[20];
	char sexo[10];
    char tipos[1024];
	char ev_prev[20];
	char ev_post[20];
	int pc, ps, num_pokedex;
	char region[20];

    int_id ++;
    sprintf(id, "%d", int_id);

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

	printf("Ingrese el sexo del pokemon (Macho o Hembra): ");
	scanf("%s", sexo);

    /* Falta verificar 'No tiene' */
	printf("Ingrese su evolucion previa (Si no tiene simplemente escriba: No tiene): ");
	scanf("%s", ev_prev);

    /* Falta verificar 'No tiene' */
	printf("Ingrese su evolucion posterior (Si no tiene simplemente escriba: No tiene): ");
	scanf("%s", ev_post);

    /* Falta comparar num de pokedex */
	printf("Ingrese el numero en la pokedex del pokemon: ");
	scanf("%d", &num_pokedex);

	printf("Ingrese la region del pokemon: ");
	scanf("%s", region);

    Pokemon *pokemon = crear_pokemon(id, nombre, pc, ps, sexo);
    Pokedex *pokedex = crear_pokedex(nombre, tipos, ev_prev, ev_post, num_pokedex, region);
    printf("\n");
    insert_map_pokedex(pokedex, map_pokedex, list_numpokedex);
    insert_map_pokemon(pokemon, map_pokemon);
    insert_map_id(pokemon, map_id);
    insert_map_tipo(pokemon, pokedex, map_tipo);
    insert_map_region(pokedex, map_region);
    pushBack(list_pc, pokemon);

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
    char id[3];
    printf("Ingrese el ID del pokemon a eliminar: ");
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
        if(strcmp(pokemon->nombre, nombre) == 0){
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

}