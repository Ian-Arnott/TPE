//
// ADT para manejo de treeList
//

#ifndef dataManagementADT_h
#define dataManagementADT_h

#include "arbolesADT.h"

void fillHoods(treeADT trees, FILE * neighbourhoods);

void fillSpecies(treeADT trees, FILE * treeFile, const int * vec);

int checkQuery(void);

void query1(treeADT trees, char ** hoodVec, int totalHoods);




#endif /*dataManagementADT_h*/
