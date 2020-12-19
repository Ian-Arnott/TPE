# TPE

Este programa consiste de dos ejecutables que leen archivos en formato
CSV con data de los arboles y los habitantes de las ciudades Buenos
Aires y Vancuver. Los ejecutables crearan archivos en formato CSV y
contendran la respuesta a 6 queries:
  1.Total de  arboles por habitante.
  2.Especie de arbol mas popular por barrio.
  3.Calle con mas arboles por barrio.
  4.Maximo y minimo diametro por especie de arbol.
  5.Especies de árboles que están presentes en todos los barrios.
  6.Top 10 barrios con mayor diversidad de especies

## COMO COMPILAR

Colocandose en el directorio donde estan los archivos, escriba
en la terminal:
  - make all
Este comando genera los dos ejecutables (arbolesADTBUE y arbolesADTVAN).
  - make BUE
  - make VAN
Estos comandos generan los ejecutables de arbolesADTBUE y arbolesADTVAN respectivamente.
  - make clean
Para eliminar los ejecutables generados.

## COMO EJECUTAR

En el mismo directorio donde compilo los archivos (en el caso que los CSV esten en el mismo directorio):

-Para ejecutar el arbolesADTBUE:
  ./arbolesADTBUE arbolesBUE.csv barriosBUE.csv

-Para ejecutar el arbolesADTVAN:
  ./arbolesADTVAN arbolesVAN.csv barriosVAN.csv

Si no estan los archivos CSV en el mismo directorio, introduzca el PATH completo.
Se debe respetar el orden de los archivos CSV como fue indicado.

## DESPUES DE LA EJECUCION

Si no hay error, se crearan seis archivos .csv en el mismo directorio, cada uno
con la data pedida por los queries, y en la salida estandard va haber un
mensaje diciendo "Se hizo lo pedido". En el caso de que haya algun error,
tambien habra un mensaje indicando cual fue el error.

## INDICE DE ERRORES:
  exit 1 : memory allocation error.
  exit 2 : error en la cantidad de argumentos.
  exit 3 : error de introduccion u orden de argumentos.
  exit 4 : archivo pre-existente.
  exit 5 : no se pudieron abrir los archivos.
  exit 6 : se introdujo una opcion incorrecta.
