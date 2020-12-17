#include <stdio.h>
#include <stdlib.h>
#include "arbolesADT.h"
#define MAX 1000

// usando el arbolesBUE.csv y barriosBUE.csv
enum head {NRO_REGISTRO=1, TIPO_ACTIV, COMUNA, MANZANA, CALLE_NOMBRE, CALLE_ALTURA, DIRECCION_NORMALIZADA, NOMBRE_CIENTIFICO, ESTADO_PLANTERA, UBICACION_PLANTERA, NIVEL_PLANTERA, DIAMETRO_ALTURA_PECHO, ALTURA_ARBOL};

void fillHoods(treeADT trees, FILE * neighbourhoods);
void fillSpecies(treeADT trees, FILE * treeFile);
int checkQuery(void);

int main(int argc, char const *argv[]){
  if(argc!=3){
    fprintf(stderr, "ERROR: Cantidad incorrecta de argumentos\n");
    exit(2);
  }
  if(strstr(argv[1], "arbolesBUE.csv") == NULL || strstr(argv[2], "barriosBUE.csv") == NULL){
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


  freeTreeList(trees);
  return 0;
}

void fillHoods(treeADT trees, FILE * neighbourhoods){
	char fileLine[MAX];
  fgets(fileLine, MAX, neighbourhoods);//como no quiero usar la primera linea, le hago un fgets para pasarla de largo

  int population, flag;
  char * name;
  char * aux;
	while (fgets(fileLine, MAX, neighbourhoods) != NULL) {
		aux = strtok(fileLine, ";");
    name = aux;
		aux = strtok(NULL, "\n");
    population = atoi(aux);
		flag = addNeighbourhood(trees,name,population);
		if (flag==0){
			fprintf(stderr, "ERROR: No se pudieron agregar todos los barrios\n");
			exit(1);
		}
	}
}

//  COMUNA=3   CALLE=5  NOMBRE-CIEN=8    DIAMETRO=12
void fillSpecies(treeADT trees, FILE * treeFile){
  char fileLine[MAX];
  fgets(fileLine, MAX, treeFile);
  char * hood;
  char * specie;
  char * road;
  int diameter, flag;
  char * aux;
  while (fgets(fileLine, MAX, treeFile) != NULL){ //para otras bases de dato, se utiliza el ultimo header como limite
    for (int i = 1; i <= ALTURA_ARBOL; i++){
      if(i==ALTURA_ARBOL)
        aux = strtok(NULL, "\n");
      else if(i==NRO_REGISTRO)
        aux = strtok(fileLine, ";");
      else
        aux = strtok(NULL, ";");
      switch(i){  //para otras bases de datos, se utilizan los headers para barrio, calle, nombre_cientifico, DIAMETRO_ALTURA_PECHO
        case COMUNA:
          hood = aux;
          break;
        case CALLE_NOMBRE:
          road = aux;
          break;
        case NOMBRE_CIENTIFICO:
          specie = aux;
          break;
        case DIAMETRO_ALTURA_PECHO:
          diameter = atoi(aux);
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

int checkQuery(void){
  if(fopen("query1.csv", "r") != NULL || fopen("query2.csv", "r") != NULL || fopen("query3.csv", "r") != NULL || fopen("query4.csv", "r") != NULL || fopen("query5.csv", "r") != NULL || fopen("query4.csv", "r") != NULL)
    return 1;
  return 0;
}
