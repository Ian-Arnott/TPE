#include "dataManagementADT.h"
#include <stdio.h>
#include <string.h>

int checkQuery(void){
  if(fopen("query1.csv", "r") != NULL || fopen("query2.csv", "r") != NULL || fopen("query3.csv", "r") != NULL || fopen("query4.csv", "r") != NULL || fopen("query5.csv", "r") != NULL || fopen("query4.csv", "r") != NULL)
    return 1;
  return 0;
}

void fillHoods(treeADT trees, FILE * neighbourhoods){
	char fileLine[MAX];
  fgets(fileLine, MAX, neighbourhoods);//como no quiero usar la primera linea, le hago un fgets para pasarla de largo

  float population;
  int flag;
  char * name;
  char * aux;
	while (fgets(fileLine, MAX, neighbourhoods) != NULL) {
    aux = strtok(fileLine, ";");
    name = aux;
		aux = strtok(NULL, "\n");
    population = atof(aux);
		flag = addNeighbourhood(trees,name,population);
		if (flag==0){
			exit(1);
		}
	}
}

void fillSpecies(treeADT trees, FILE * treeFile, const int * vec){
  char fileLine[MAX];
  fgets(fileLine, MAX, treeFile);
  char * hood;
  char * specie;
  char * road;
  float diameter;
  int flag;
  char * aux;
  while (fgets(fileLine, MAX, treeFile) != NULL){ //para otras bases de dato, se utiliza el ultimo header como limite
    for (int i = 1; i <= vec[5]; i++){
      if(i==vec[5])
        aux = strtok(NULL, "\n");
      else if(i==vec[0])
        aux = strtok(fileLine, ";");
      else
        aux = strtok(NULL, ";");
      switch(i){  //para otras bases de datos, se utilizan los headers para barrio, calle, nombre_cientifico, DIAMETRO_ALTURA_PECHO
        case vec[1]:
          hood = aux;
          break;
        case vec[2]:
          road = aux;
          break;
        case vec[3]:
          specie = aux;
          break;
        case vec[4]:
          diameter = atof(aux);
          break;
      }
    }
    flag = addSpecies(trees,specie,diameter);
    if( flag == 0 ){
      fprintf(stderr, "ERROR: No se pudieron agregar todas las especies\n");
      exit(1);
    }
    addSpeciesToHood(trees, hood, specie, road);
  }
}
