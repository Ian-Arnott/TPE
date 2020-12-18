//
// ADT para manejo de treeList
//

#ifndef dataManagementADT_h
#define dataManagementADT_h

#include <stdio.h>
#include "arbolesADT.h"

void fillHoods(treeADT trees, FILE * neighbourhoods);

void fillSpecies(treeADT trees, FILE * treeFile, int vec[]);

int checkQuery(void);

int checkArguments(const char ** argv);

void query1(treeADT trees,  char ** hoodVec, int totalHoods);

void query2(treeADT trees,  char ** hoodVec, int totalHoods);

void query3(treeADT trees,  char ** hoodVec, int totalHoods);


#endif /*dataManagementADT_h*/
