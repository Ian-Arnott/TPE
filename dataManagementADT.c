#include "dataManagementADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

typedef struct node{
  float number;
  char * name;
  struct node * tail;
}TNode;

typedef TNode * TList; // lista con un nombre y un numero, ordenada de mayor a menor.

int checkQuery(void){
  if(fopen("query1.csv", "r") != NULL || fopen("query2.csv", "r") != NULL || fopen("query3.csv", "r") != NULL || fopen("query4.csv", "r") != NULL || fopen("query5.csv", "r") != NULL || fopen("query4.csv", "r") != NULL)
    return 1;
  return 0;
}

int checkArguments(const char ** argv, int option){
  int flag = 0;
  if((strstr(argv[1], "arbolesBUE.csv") == NULL || strstr(argv[2], "barriosBUE.csv") == NULL) && option == 1)
    flag = 1;
  if((strstr(argv[1], "arbolesVAN.csv") == NULL || strstr(argv[2], "barriosVAN.csv") == NULL) && option == 2)
    flag = 1;
  return flag;
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

void fillSpecies(treeADT trees, FILE * treeFile, int vec[]){
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
      if(i==vec[1]){
        hood = aux;
      }
      else if(i==vec[2]){
        road = aux;
      }
      else if(i==vec[3]){
        specie = aux;
      }
      else if(i==vec[4]){
        diameter = atof(aux);
      }
    }
    flag = addSpecies(trees,specie,diameter);
    if( flag == 0 ){
      exit(1);
    }
    addSpeciesToHood(trees, hood, specie, road);
  }
}

static void freeList(TList list){
  if(list==NULL)
    return;
  freeList(list->tail);
  free(list->name);
  free(list);
}
static TList addToList(TList list, float number, char * name){
  if(list == NULL || list->number<number){
    TList new = malloc(sizeof(TNode));
    if(new == NULL)
      exit(1);
    new->number = number;
    new->name = malloc(sizeof(char)*(strlen(name)+1));
    if(new->name == NULL)
      exit(1);
    strcpy(new->name,name);
    new->tail = list;
    return new;
  }
  else
    list->tail = addToList(list->tail,number,name);
  return list;
}
void query1(treeADT trees,  char ** hoodVec, int totalHoods){
  FILE * newFile;
  newFile = fopen("query1.csv", "w");
  if(newFile == NULL)
    exit(5);
  fprintf(newFile,"BARRIO;ARBOLES_POR_HABITANTE\n");

  char * name;
  float totalTrees, population, ratio;
  TList fileList = NULL;

  toBegin(trees,1);
  for(int i = 0; i<totalHoods; i++){
    if(hasNext(trees,1)){
      name = next(trees,1,&totalTrees,&population);
      ratio = totalTrees/population;
      fileList = addToList(fileList,ratio,name);
    }
  }
  TList aux = fileList;
  while (aux!=NULL){
    fprintf(newFile, "%s;%.2f\n",aux->name,aux->number);
    aux = aux->tail;
  }
  freeList(fileList);
  fclose(newFile);
  return;
}

void query2(treeADT trees,  char ** hoodVec, int totalHoods){
  FILE * newFile;
  newFile = fopen("query2.csv", "w");
  if(newFile == NULL)
    exit(5);
  fprintf(newFile,"BARRIO;NOMBRE_CIENTIFICO\n");

  char * name;
  float aux1,aux2; //dos variables que no van a ser usadas

  toBegin(trees,1);
  int i;
  for(i = 0; i<totalHoods; i++){
    if(hasNext(trees,1)){
      name = next(trees,2,&aux1,&aux2);
      fprintf(newFile, "%s;%s\n",hoodVec[i],name);
    }
  }
  fclose(newFile);
  return;
}

void query3(treeADT trees,  char ** hoodVec, int totalHoods){
  FILE * newFile;
  newFile = fopen("query3.csv", "w");
  if(newFile == NULL)
    exit(5);
  fprintf(newFile,"BARRIO;CALLE_CON_MAS_ARBOLES;ARBOLES\n");

  char * name;
  float cant,aux2; //aux2 no va a ser usada

  toBegin(trees,1);
  int i;
  for(i = 0; i<totalHoods; i++){
    if(hasNext(trees,1)){
      name = next(trees,3,&cant,&aux2);
      fprintf(newFile, "%s;%s;%.0f\n",hoodVec[i],name,cant);
    }
  }
  fclose(newFile);
  return;
}

void query4(treeADT trees,  char ** speciesVec, int totalSpecies){
  FILE * newFile;
  newFile = fopen("query4.csv", "w");
  if(newFile == NULL)
    exit(5);
  fprintf(newFile,"NOMBRE_CIENTIFICO;MIN;MAX\n");

  char * name;
  float min,max; //aux2 no va a ser usada

  toBegin(trees,2);
  int i;
  for(i = 0; i<totalSpecies; i++){
    if(hasNext(trees,2)){
      name = next(trees,4,&min,&max);
      fprintf(newFile, "%s;%.2f;%.2f\n",name,min,max);
    }
  }
  fclose(newFile);
  return;
}

void query5(treeADT trees,  char ** speciesVec, int totalSpecies){
  FILE * newFile;
  newFile = fopen("query5.csv", "w");
  if(newFile == NULL)
    exit(5);
  fprintf(newFile,"NOMBRE_CIENTIFICO\n");

  char * name;
  float aux1,aux2; //aux1 y aux2 no van a ser usadas

  toBegin(trees,2);
  int i;
  for(i = 0; i<totalSpecies; i++){
    if(hasNext(trees,2)){
      name = next(trees,5,&aux1,&aux2);
      if(name !=NULL)
        fprintf(newFile, "%s\n",name);
    }
  }
  fclose(newFile);
  return;
}

void query6(treeADT trees,  char ** hoodVec, int totalHoods){
  FILE * newFile;
  newFile = fopen("query6.csv", "w");
  if(newFile == NULL)
    exit(5);
  fprintf(newFile,"BARRIO;ESPECIES_DISTINTAS\n");

  char * name;
  int i;
  float cant,aux2; //aux2 no va a ser usada

  TList fileList = NULL;

  toBegin(trees,1);
  for(i = 0; i<totalHoods; i++){
    if(hasNext(trees,1)){
      name = next(trees,6,&cant,&aux2);
      fileList = addToList(fileList,cant,name);
    }
  }
  TList aux = fileList;
  i=0;
  while (aux!=NULL && i<10){
    fprintf(newFile, "%s;%.0f\n",aux->name,aux->number);
    aux = aux->tail;
    i++;
  }
  freeList(fileList);
  fclose(newFile);
  return;
}
