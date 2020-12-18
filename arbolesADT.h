//
// ADT para manejo de treeList
//

#ifndef aroblesADT_h
#define arbolesADT_h

#include <string.h>


typedef struct treeCDT * treeADT;

treeADT newTreeList(void);

void freeTreeList(treeADT list);

int addNeighbourhood(treeADT trees, const char * name, float pop);

int addSpecies(treeADT trees, const char * name, float diameter);

void addSpeciesToHood(treeADT trees, const char * hood, const char * species, const char * road);

//Hace un vector con los nombres de (opcion 1) todos los barrios o (opcion 2) todas las especies.
char ** getAll(treeADT trees, int option);

//Hace que el current sea de (opcion 1) la lista de barrios o (opcion 2) la lista de especies.
void toBegin(treeADT trees, int option);

//1 si hay un proximo nodo en la lista, 0 si no. Opcion 1 la lista de barrios, opcion 2 la lista de especies.
int hasNext(treeADT trees, int option);

//Retorna un puntero a char, y si es necesario se modifican num1 y num2.
char * next(treeADT trees, int option, float * num1, float * num2);

int sizeHoods(treeADT trees);

int sizeSpecies(treeADT trees);

#endif /*arbolesADT_h*/
