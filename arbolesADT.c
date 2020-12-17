#include "arbolesADT.h"
#include <stdlib.h>
#include <stddef.h>
#define BLOCK 10

typedef struct hoodNode{
  size_t totalTrees;
  int population;
  char * name;
  struct elementQty * species;
  size_t speciesDim;
  struct elementQty * roads;
  size_t roadsDim;
  struct hoodNode * tail;
}hoodNode;

typedef struct speciesNode{
  size_t hoods;  //se suma cuando se agrega la especie en un barrio dado en el specie*
  int min;  //radio del tronco minimo
  int max; //radio del tronco maximo
  char * name;
  struct speciesNode * tail;
}speciesNode;

typedef struct elementQty{  //struct generica para guardar un tipo de dato con nombre y tiene una cantidad x de apariciones
  char * name;
  size_t qty;
}elementQty;

typedef struct treeCDT{
  struct hoodNode * hFirst;  // cada nodo es un barrio nuevo, se llenan en la primera lectura del barrio(dependiendo de la ciudad)
  struct speciesNode * sFirst;  // cada nodo es una especie nueva, cada aparicion de un arbol se compara con los nodos, si no esta se agrega
  size_t totalHoods;
}treeCDT;

treeADT newTreeList(void){
  return calloc(1,sizeof(treeCDT));
}


static hoodNode * addNeighbourhoodRec(hoodNode * list, const char * name, int * added, int pop){
  if(list==NULL){
    hoodNode * aux = malloc(sizeof(hoodNode));
    if( aux == NULL )
      exit(1);
    aux->tail = NULL;
    aux->name = malloc((strlen(name)+1));
    if(aux->name == NULL)
      exit(1);
    strcpy(aux->name,name);
    aux->population = pop;
    aux->speciesDim = 0;
    aux->roadsDim = 0;
    aux->totalTrees = 0;
    aux->species = NULL;
    aux->roads = NULL;
    (*added) = 1;
    return aux;
  }
  else
    list->tail = addNeighbourhoodRec(list->tail,name,added,pop);
  return list;
}
int addNeighbourhood(treeADT trees, const char * name, int pop){
  int added=0;
  trees->hFirst = addNeighbourhoodRec(trees->hFirst,name,&added,pop);
  trees->totalHoods += added;
  return added;
}


static void freeStruct(elementQty * vec, size_t dim){
  for( int i = 0 ; i < dim ; i++){
    free(vec[i].name);
  }
}
static void freeHoods(hoodNode * list){
  if(list == NULL)
    return;
  freeHoods(list->tail);
  freeStruct(list->roads,list->roadsDim);
  free(list->roads);
  freeStruct(list->species,list->speciesDim);
  free(list->species);
  free(list->name);
  free(list);
  return;
}
static void freeSpecies(speciesNode * list) {
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





static speciesNode * addSpeciesRec(speciesNode * list, const char * name, int diameter, int * added){
  int c;
  if(list == NULL || (c=compare(list->name,name)) > 0){
    speciesNode * new = malloc(sizeof(speciesNode));
    if(new == NULL)
      exit(1);
    new->min = diameter;
    new->max = diameter;
    new->name = malloc(sizeof(char)*(strlen(name)+1));
    if(new->name == NULL)
      exit(1);
    strcpy(new->name,name);
    new->tail = list;
    (*added) = 1;
    return new;
  }
  if(c==0){
    if(diameter > list->max)
      list->max = diameter;
    else if(diameter<list->min)
      list->min = diameter;
    (*added)=2;
  }
  else
    list->tail = addSpeciesRec(list->tail,name,diameter,added);
  return list;
}
int addSpecies(treeADT trees, const char * name, int diameter){
  int added = 0;
  trees->sFirst = addSpeciesRec(trees->sFirst,name,diameter,&added);
  return added;
}//si agrega retorna 1, si no 0, si cambia el min o el max retorna 2





static int checkElem(elementQty * vec, const char * name, size_t dim){
  int i = 0;
  if(dim == 0)
    return -1;
  for( i = 0 ; i < dim ; i++){
    if( compare(vec[i].name,name) == 0)
      return i;
  }
  return -1;
}  // -1 si no esta y si esta retorna el indice
static elementQty * addElem(elementQty * vec, const char * name, size_t * dim){
  if((*dim)%BLOCK == 0){
    if((vec = realloc(vec, (BLOCK+(*dim))*sizeof(elementQty)))==NULL)
      exit(1);
  }
  vec[(*dim)].name = malloc(sizeof(char)*(strlen(name)+1));
  strcpy(vec[(*dim)].name,name);
  vec[(*dim)++].qty=1;
  return vec;
}
static hoodNode * addSpeciesToHoodRec(hoodNode * list, const char * hood, const char * specie, const char * road, int * added){
  if(list == NULL)
    return NULL;
  int c = compare(list->name, hood);
  if( c == 0 ){
    int i;
    list->totalTrees++;
    //para el vector que contiene las calles
    if((i=checkElem(list->roads,road,list->roadsDim))!=-1)
      list->roads[i].qty++;
    else
      list->roads = addElem(list->roads,road,&(list->roadsDim));
    //idem a lo anterior pero con el vector de species
    if((i=checkElem(list->species,specie,list->speciesDim))!=-1)
      list->species[i].qty++;
    else{
      list->species = addElem(list->species,specie,&(list->speciesDim));
      (*added)=1;
    }
    }
  else
    list->tail = addSpeciesToHoodRec(list,hood,specie,road,added);
  return list;
}
static speciesNode * addHoodToSpecies(speciesNode * list, const char * specie){
  if(list == NULL)
    return NULL;
  int c = compare(list->name,specie);
  if(c==0)
    list->hoods++;
  else if(c<0)
    list->tail = addHoodToSpecies(list->tail,specie);
  return list;
}
void addSpeciesToHood(treeADT trees, const char * hood, const char * specie, const char * road){
  // agregamos todos los datos que faltan al ADT
  int added=0; // si se agrega a la lista de Neighbourhood en el vector species => added=1
  trees->hFirst = addSpeciesToHoodRec(trees->hFirst,hood,specie,road,&added);
  if(added)
    trees->sFirst = addHoodToSpecies(trees->sFirst,specie);
}
