#include <stdio.h>
#include <stdlib.h>
#include "dataManagementADT.h"
#define MAX 1000

// usando el arbolesVAN.csv y barriosVAN.csv
enum head {TREE_ID=1,CIVIC_NUMBER,STD_STREET,GENUS_NAME,SPECIES_NAME,CULTIVAR_NAME,COMMON_NAME,ASSIGNED,ROOT_BARRIER,PLANT_AREA,ON_STREET_BLOCK,ON_STREET,NEIGHBOURHOOD_NAME,STREET_SIDE_NAME,HEIGHT_RANGE_ID,DIAMETER,CURB,DATE_PLANTED,GEOM};


int main(int argc, char const *argv[]){
  if(argc!=3){
    fprintf(stderr, "ERROR: Cantidad incorrecta de argumentos\n");
    exit(2);
  }
  if(checkArguments(argv,2)){
		fprintf(stderr, "ERROR: Los argumentos introducidos no son los correctos\nO el orden de los argumentos es incorrecto\n");
		exit(3);
	}
  if(checkQuery()){
    fprintf(stderr, "ERROR: Ya existe algun archivo con alguno de los nombres a crear\n");
    exit(4);
  }

  FILE * treeFile;
  treeFile = fopen(argv[1],"r");
  FILE * hoodFile;
  hoodFile = fopen(argv[2],"r");
  if(treeFile == NULL || hoodFile == NULL){
		fprintf(stderr, "ERROR: No se pudo abrir alguno de los archivos\n");
		exit(5);
	}

  treeADT trees = newTreeList();
  if(trees==NULL){
    fprintf(stderr, "ERROR: No hay espacio de memoria\n");
    exit(1);
  }


  fillHoods(trees,hoodFile);
  int fields[] = {TREE_ID, NEIGHBOURHOOD_NAME, STREET_SIDE_NAME, SPECIES_NAME, DIAMETER, GEOM};
  fillSpecies(trees,treeFile, fields);

  char ** hoodVec = getAll(trees,1);
  int totalHoods = sizeHoods(trees);
  char ** speciesVec = getAll(trees,2);
  int totalSpecies = sizeSpecies(trees);



  query1(trees,hoodVec,totalHoods);
  query2(trees,hoodVec,totalHoods);
  query3(trees,hoodVec,totalHoods);
  query4(trees,speciesVec,totalSpecies);
  query5(trees,speciesVec,totalSpecies);
  query6(trees,hoodVec,totalHoods);


  for (int i = 0; i < totalHoods ; i++){
    free(hoodVec[i]);
  }
  free(hoodVec);
  for (int i = 0; i < totalSpecies ; i++){
    free(speciesVec[i]);
  }
  fclose(hoodFile);
  fclose(treeFile);
  free(speciesVec);
  freeTreeList(trees);
  return 0;
}
