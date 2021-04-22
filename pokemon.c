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

