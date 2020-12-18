#include "arbolesADT.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#define BLOCK 10

typedef struct hoodNode{
  size_t totalTrees;
  float population;
  char * name;
  struct elementQty * species;
  size_t speciesDim;
  struct elementQty * roads;
  size_t roadsDim;
  struct hoodNode * tail;
}hoodNode;

typedef struct speciesNode{
  size_t hoods;  //se suma cuando se agrega la especie en un barrio dado en el specie*
  float min;  //radio del tronco minimo
  float max; //radio del tronco maximo
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
  size_t totalSpecies;
  struct hoodNode * currentH;
  struct speciesNode * currentS;
}treeCDT;


treeADT newTreeList(void){
  return calloc(1,sizeof(treeCDT));
}


static hoodNode * addNeighbourhoodRec(hoodNode * list, const char * name, int * added, float pop){
  int c;
  if(list==NULL || (c=strcmp(list->name,name)) > 0){
    hoodNode * aux = malloc(sizeof(hoodNode));
    if( aux == NULL )
      exit(1);
    aux->tail = list;
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
int addNeighbourhood(treeADT trees, const char * name, float pop){
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
  free(list->currentH);
  free(list->currentS);
  free(list);
  return;
}


static speciesNode * addSpeciesRec(speciesNode * list, const char * name, float diameter, int * added){
  int c;
  if(list == NULL || (c=strcmp(list->name,name)) > 0){
    speciesNode * new = malloc(sizeof(speciesNode));
    if(new == NULL)
      exit(1);
    new->hoods = 0;
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
int addSpecies(treeADT trees, const char * name, float diameter){
  int added = 0;
  trees->sFirst = addSpeciesRec(trees->sFirst,name,diameter,&added);
  if(added==1)
    trees->totalSpecies += added;
  return added;
}//si agrega retorna 1, si no 0, si cambia el min o el max retorna 2


static int checkElem(elementQty * vec, const char * name, size_t dim){
  int i = 0;
  if(dim == 0)
    return -1;
  for( i = 0 ; i < dim ; i++){
    if( strcmp(vec[i].name,name) == 0)
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
  int c = strcmp(list->name,hood);
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
    list->tail = addSpeciesToHoodRec(list->tail,hood,specie,road,added);
  return list;
}
static speciesNode * addHoodToSpecies(speciesNode * list, const char * specie){
  if(list == NULL)
    return NULL;
  int c = strcmp(list->name,specie);
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


int sizeHoods(treeADT trees){
  return trees->totalHoods;
}
int sizeSpecies(treeADT trees){
  return trees->totalSpecies;
}


static void getAllHoods(char ** vec, int * k, hoodNode * aux1){
  while(aux1!=NULL){
    vec[*k] = malloc(strlen(aux1->name)+1);
    if(vec[*k] == NULL)
      exit(1);
    strcpy(vec[*k], aux1->name);
    (*k)++;
    aux1 = aux1->tail;
  }
}
static void getAllSpecies(char ** vec, int * k, speciesNode * aux2){
  while(aux2!=NULL){
    vec[*k] = malloc(strlen(aux2->name)+1);
    if(vec[*k] == NULL)
      exit(1);
    strcpy(vec[*k], aux2->name);
    (*k)++;
    aux2 = aux2->tail;
  }
}
char ** getAll(treeADT trees, int option){
  hoodNode * aux1;
  speciesNode * aux2;
  switch (option){
    case 1:
      aux1 = trees->hFirst;
      break;
    case 2:
      aux2 = trees->sFirst;
      break;
    default:
      exit(6);
  }
  //dependiendo del option se le asigna una cantidad de memoria a vec
  char ** vec = (option == 1)? malloc((trees->totalHoods+1)*sizeof(char*)):malloc((trees->totalSpecies+1)*sizeof(char*));
  if(vec == NULL)
    exit(1);
  int k = 0;
  if(option == 1){
    getAllHoods(vec,&k,aux1);
  }
  else{
    getAllSpecies(vec,&k,aux2);
  }
  vec[k]=NULL;
  return vec;
}


void toBegin(treeADT trees, int option){
  if(option == 1)
    trees->currentH = trees->hFirst;
  else if(option == 2)
    trees->currentS = trees->sFirst;
  else
    exit(6);
}
static int getMax(elementQty * vec, size_t dim){
  int i=0;
  size_t max = vec[i].qty;
  for(i=1; i<dim; i++){
    if(max<vec[i].qty)
      max = vec[i].qty;
  }
  return i;
}
int hasNext(treeADT trees, int option){
  if(option == 1){
    return (trees->currentH==NULL)?0:1;
  }
  else if(option == 2){
    return (trees->currentS==NULL)?0:1;
  }
  else
    exit(6);
}
char * next(treeADT trees, int option, float * num1, float * num2){
  hoodNode * aux1;
  speciesNode * aux2;
  //este switch elige el current.
  switch (option) {
    case 1:
    case 2:

    case 3:
    case 6:
      aux1 = trees->currentH;
      break;
    case 4:
    case 5:
      aux2 = trees->currentS;
      break;
  }
  int i;
  switch (option) {
    case 1:
      (*num1) = aux1->totalTrees;
      (*num2) = aux1->population;
      trees->currentH = aux1->tail;
      return aux1->name;
    case 2:
      i = getMax(aux1->species, aux1->speciesDim);
      trees->currentH = aux1->tail;
      return aux1->species[i].name;
    case 3:
      i = getMax(aux1->roads, aux1->roadsDim);
      trees->currentH = aux1->tail;
      return aux1->roads[i].name;
    case 4:
      (*num1) = aux2->min;
      (*num2) = aux2->max;
      trees->currentS = aux2->tail;
      return aux2->name;
    case 5:
      if(trees->totalHoods == aux2->hoods){
        trees->currentS = aux2->tail;
        return aux2->name;
      }
      else
        trees->currentS = aux2->tail;
      return NULL;
    case 6:
      (*num1) = aux1->speciesDim;
      trees->currentH = aux1->tail;
      return aux1->name;
  }
  return NULL;
}
