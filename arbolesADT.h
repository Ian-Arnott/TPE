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

treeADT newTreeList();

void freeTreeList(treeADT list);

#endif /*arbolesADT_h*/
