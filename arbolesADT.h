//
// ADT para manejo de treeList
//

#ifndef aroblesADT_h
#define arbolesADT_h

#include <string.h>


typedef struct treeCDT * treeADT;

static int compare(const char * s1, const char * s2){
  return strcmp(s1,s2);
}

treeADT newTreeList(void);

void freeTreeList(treeADT list);

int addNeighbourhood(treeADT trees, const char * name, int pop);

int addSpecies(treeADT trees, const char * name, int diameter);

int addSpeciesToHood(treeADT trees, const char * hood, const char * species, const char * road);

#endif /*arbolesADT_h*/
