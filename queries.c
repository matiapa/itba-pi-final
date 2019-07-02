#include <stdio.h>
#include <stdlib.h>
#include "transporteADT.h"


void query1(transporteADT trans){
 	long int pasajeros=0;

  // Conseguir cantidad de lineas de subte para saber cuantas lineas agregar al archivo.
	int cant_lineas=get_cant_lineas(trans);

  // Generar el archivo
	FILE *fptr=fopen("query1.csv","w");
  if (fptr == NULL) {
		printf("No se pudo crear el archivo query1.csv\n");
		exit(1);
	}

	fprintf(fptr,"Línea,Pasajeros \n");

  // Agregar linea por linea los datos al archivo

	for (int i=0;i<cant_lineas;i++){
		char * nombre_linea;
    get_linea(&nombre_linea, &pasajeros,i,trans);
		/* si la cantidad de pasajero es 0 entonces no la imprime */
		if (pasajeros >= 1) {
			fprintf(fptr,"%s,%ld\n", nombre_linea, pasajeros);
		}
		free(nombre_linea);
	}

	fclose(fptr);

}


void query2(transporteADT trans){
	char * dias[]={"domingo","lunes","martes","miercoles","jueves","viernes","sabado"};
	long int dia,noche;

  // Generar el archivo
	FILE *fptr=fopen("query2.csv","w");
  if (fptr == NULL) {
    printf("No se pudo crear el archivo query2.csv\n");
    exit(1);
  }

	fprintf(fptr,"Día,Diurnos,Nocturnos,Total \n");

  // Agregar cada linea al archivo

	for (int i=0;i<DIAS_SEMANA;i++){
		get_pasajeros_por_dia(&dia,&noche,i,trans);
		fprintf(fptr,"%s,%ld,%ld,%ld \n",dias[i],dia,noche,dia+noche);
	}

	fclose(fptr);
}


void query3(transporteADT trans){

  // Recibe vector de punteros a estructuras con la linea y cantidad de pasajeros en cada estructura a la que apunta cada elemento del vector.
	tLinea_con_pasajeros ** vec=get_pasajeros_por_linea(trans);
	tLinea_con_pasajeros * linea;

  // Consigue la cantidad de lineas del subterraneo para saber cuantas iteraciones hacer y la cantidad de pasajeros totales para hacer los calculos.
	long int total_pasajeros=get_total_pasajeros(trans);
	int cant_lineas=get_cant_lineas(trans);

  // Genera el archivo a escribir.
	FILE *fptr=fopen("query3.csv","w");
  if (fptr == NULL) {
    printf("No se pudo crear el archivo query3.csv\n");
    exit(1);
  }

	fprintf(fptr,"Línea,Porcentaje \n");

  // Imprime las lineas al archivo

	for (int i=0;i<cant_lineas;i++){
		linea=vec[i];

		if (total_pasajeros!=0){
      int long perc = linea->pasajeros * 100 /  total_pasajeros;
			fprintf(fptr,"%s,%ld%% \n",linea->nombre_linea, perc);
		}else
			fprintf(fptr,"%s,0%%\n",linea->nombre_linea);

		free(linea->nombre_linea);
		free(linea);
		//libera la estructura

  }
	free (vec);
	//libera el vector que contenia las estructuras

	fclose(fptr);

}


void query4(transporteADT trans){

	// Recibe un vector de punteros a estructuras con la linea, estacion y cantidad de pasajeros en cada estructura a la que apunta cada elemento del vector.
	tEstacion_favorita ** vec=get_favourite_vec(trans);
	tEstacion_favorita * estacion_fav=NULL;

  // Consigue la cantidad de lineas de subterraneo para saber cuantas iteraciones hacer.
	int cant_lineas=get_cant_lineas(trans);

  // Genera el archivo
	FILE *fptr=fopen("query4.csv","w");
  if (fptr == NULL) {
    printf("No se pudo crear el archivo query3.csv\n");
    exit(1);
  }

	fprintf(fptr,"Estación,Línea,Pasajeros \n");

	for (int i=0;i<cant_lineas;i++){

		estacion_fav=vec[i];

    // Agrega los valores de las estructuras al archivo, iterando en el vector
		fprintf(fptr,"%s,%s,%ld\n", estacion_fav->nombre_estacion, estacion_fav->nombre_linea, estacion_fav->pasajeros);

    // Libera la estructura
		free(estacion_fav->nombre_estacion);
		free(estacion_fav->nombre_linea);
		free(estacion_fav);

  }
	free(vec);

	fclose(fptr);
}
