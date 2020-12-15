#include "arbolesADT.h"
#include <stdlib.h>
#include <stddef.h>

typedef struct hoodNode{
  size_t totalSpecies;
  size_t totalTrees;
  int population;
  char * name;
  struct specie * species;
  struct road * roads;
  struct hoodNode * tail;
}hoodNode;

typedef struct speciesNode{
  size_t hoods;  //se suma cuando se agrega la especie en un barrio dado en el specie*
  int min;  //radio del tronco minimo
  int max; //radio del tronco maximo
  char * name;
  struct speciesNode * tail;
}speciesNode;

typedef struct specie{
  char * name;
  size_t qty;
}species;

typedef struct road{
  size_t qty;
  char * name;
}road;

typedef struct treeCDT{
  struct hoodNode * hFirst;  // cada nodo es un barrio nuevo, se llenan en la primera lectura del barrio(dependiendo de la ciudad)
  struct speciesNode * sFirst;  // cada nodo es una especie nueva, cada aparicion de un arbol se compara con los nodos, si no esta se agrega
  size_t totalHoods;
}treeCDT;

treeADT newTreeList(void){
  return calloc(1,sizeof(treeCDT));
}

static hoodNode * addNeighbourhoodRec(hoodNode list, const char * name, int * added, int pop){
  if(list==NULL){
    hoodNode aux = malloc(sizeof(hoodNode));
    if( aux == NULL )
      exit(1);
    aux->tail = NULL;
    aux->name = malloc(sizeof(char)*(strlen(name)+1));
    if(aux->name == NULL)
      exit(1);
    strcpy(aux->name,name);
    aux->population = pop;
    aux->totalSpecies = 0;
    aux->totalTrees = 0;
    aux->species = NULL;
    aux->roads = NULL;
    (*added) = 1;
    return aux;
  }
  else
    list->tail = addNeighbourhoodRec(list->tail,s,added);
  return list;
}
int addNeighbourhood(treeADT trees, const char * name, int pop){
  int added=0;
  trees->hFirst = addNeighbourhoodRec(trees->hFirst,name,&added);
  trees->totalHoods += added;
  return added;
}

static void freeHoods(hoodNode list){
  if(list == NULL)
    return;
  freeHoods(list->tail);
  free(list->species);
  free(list->roads);
  free(list);
  return;
}
static void freeSpecies(speciesNode list) {
  if(list == NULL)
    return;
  freeSpecies(list->tail);
  free(list->name);
  free(list);
  return;
}
void freeTreeList(treeADT list){
  freeHoods(list->hFirst);
  freeSpecies(list->sFirst);
  free(list);
  return;
}

static speciesNode * addSpeciesRec(speciesNode list, const char * name, int diameter, int * added){
  if(list == NULL || (c=compare(list->name,name)) > 0){
    speciesNode new = malloc(sizeof(speciesNode));
    if(new == NULL)
      exit(1);
    new->min = diameter;
    new->max = diameter;
    new->name = malloc(sizeof(char)*(strlen(name)+1));
    if(new->name == NULL)
      exit(1);
    strcpy(new->name,name);
    (*added) = 1;
    return new;
  }
  if(c==0){
    if(diameter > list->max)
      list->max = diameter;
    else if(diameter<list->min)
      list->min = diameter;
  }
  else
    list->tail = addSpeciesRec(list->tail)
  return list;
}
int addSpecies(treeADT trees, const char * name, int diameter){
  int added = 0;
  trees->sFirst = addSpeciesRec(trees->sFirst,name,diameter,added)
  return added;
}
