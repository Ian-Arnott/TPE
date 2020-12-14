#include "arbolesADT.h"
#include <stdlib.h>
#include <stddef.h>

typedef struct hoodNode{
  size_t totalSpecies;
  size_t totalTrees;
  size_t population;
  char * name;
  struct specie * species;
  struct road * roads;
  struct hoodNode * tail;
}hoodNode;

typedef struct speciesNode{
  size_t hoods;  //se suma cuando se agrega la especie en un barrio dado en el specie*
  size_t min;  //radio del tronco minimo
  size_t max; //radio del tronco maximo
  char * name;
}speciesNode;

typedef struct specie{
  char * name;
  size_t qty;
}species;

typedef struct road{
  size_t qty;
  char * name;
}road;

typedef struct treesCDT{
  struct hoodNode * hFirst;  // cada nodo es un barrio nuevo, se llenan en la primera lectura del barrio(dependiendo de la ciudad)
  struct speciesNode * sFirst;  // cada nodo es una especie nueva, cada aparicion de un arbol se compara con los nodos, si no esta se agrega
  size_t totalHoods;
}treesCDT;
