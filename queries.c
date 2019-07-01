#include <stdio.h>
#include <stdlib.h>
#include "transporteADT.h"
#define DIAS_SEMANA 7

void query1(transporteADT trans)
{
 	long int pasajeros=0;

	int cant_lineas=get_cant_lineas(trans);
	//conseguir cantidad de lineas de subte para saber cuantas lineas agregar al archivo.

	FILE *fptr=fopen("query1.csv","w");
	//generar el archivo

	fprintf(fptr,"Línea,Pasajeros \n");
	//escribir el header.

	for (int i=0;i<cant_lineas;i++){
		char * nombre_linea = malloc(40);
		get_linea(nombre_linea,&pasajeros,i,trans);
		/* si la cantidad de pasajero es 0 entonces no la imprime */
		if (pasajeros >= 1) {
			fprintf(fptr,"%s,%ld\n", nombre_linea, pasajeros);
		}
		free(nombre_linea);
	}
	//agregar linea por linea los dats al archivo

	fclose(fptr);

}


void query2(transporteADT trans)
{
	char * dias[]={"domingo","lunes","martes","miercoles","jueves","viernes","sabado"};
	long int dia,noche;


	FILE *fptr=fopen("query2.csv","w");
	         //generar el archivo

	fprintf(fptr,"Día,Diurnos,Nocturnos,Total \n");
	//escribir el header del archivo.



	for (int i=0;i<DIAS_SEMANA;i++){
		get_pasajeros_dia(&dia,&noche,i,trans);
		fprintf(fptr,"%s,%ld,%ld,%ld \n",dias[i],dia,noche,dia+noche);
	}
	//agregar cada linea al archivo
	fclose(fptr);
	//cerrar el archivo
}

void query3(transporteADT trans){
	tLinea_con_pasajeros ** vec=get_pasajeros_por_linea_vec(trans);
	tLinea_con_pasajeros * linea;
	//recibe vecor de punteros a estructuras con la linea y cantidad de pasajeros en cada estructura a la que apunta cada elemento del vector.

	long int total_pasajeros=get_total_pasajeros(trans);
	int cant_lineas=get_cant_lineas(trans);
	//consigue la cantidad de lineas del subterraneo para saber cuantas iteraciones hacer y la cantidad de pasageros totales para hacer los calculos.

	FILE *fptr=fopen("query3.csv","w");
	//generar el archivo a escribir.

	fprintf(fptr,"Línea,Porcentaje \n");
	// ecribir el header del archivo.
	for (int i=0;i<cant_lineas;i++){
		linea=vec[i];
		if (total_pasajeros!=0)
			fprintf(fptr,"%s,%ld%% \n",linea->nombre_linea,linea->pasajeros*100/total_pasajeros);
		else 
			fprintf(fptr,"%s,0%%\n",linea->nombre_linea);
		//imprime las lineas al archivo

		free(linea->nombre_linea);
		free(linea);
		//libera la estructura 
	}
	free (vec);
	//libera el vector que contenia las estructuras

	fclose(fptr);
	//cierra el archivo

}




void query4(transporteADT trans){

	//recibe un vector de punteros a estructuras con la linea, estacion y cantidad de pasajeros en cada estructura a la que apunta cada elemento del vector.
	tEstacion_favorita ** vec=get_favourite_vec(trans);
	tEstacion_favorita * estacion_fav=NULL;


	int cant_lineas=get_cant_lineas(trans);
	//consigue la cantidad de lineas de subterraneo para saber cuantas iteraciones hacer.


	FILE *fptr=fopen("query4.csv","w");
	//generar el archivo

	 fprintf(fptr,"Estación,Línea,Pasajeros \n");
	         //escribir el header.

	for (int i=0;i<cant_lineas;i++){
		estacion_fav=vec[i];
		fprintf(fptr,"%s,%s,%ld \n",estacion_fav->nombre_estacion,estacion_fav->nombre_linea,estacion_fav->pasajeros);
		//agregar los valores de las estructuras al archivo, iterando en el vector
	
		free(estacion_fav->nombre_estacion);
		free(estacion_fav->nombre_linea);
		free(estacion_fav);
		//liberando la estructura
	}
	free(vec);
	//liberando el vector

	fclose(fptr);
	//cerrar el archivo
}
