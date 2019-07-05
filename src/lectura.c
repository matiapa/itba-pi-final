#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void cargarEstaciones(transporteADT trans, const char *archivo_estaciones){

	FILE * archEstacion = fopen(archivo_estaciones, "r");

	if (archEstacion == NULL) {
		printf("No se pudo abrir el archivo de estaciones\n");
		exit(1);
	}

	// Verifica que este el encabezado, y que no corresponda al archivo de molinetes
	char s1[10],s2[10],s3[10];
	if(fscanf(archEstacion,"%9[a-z],%9[a-z],%9[a-z]\n",s1,s2,s3)!=3 || strcmp(s1,"fecha")==0){
		printf("Encabezado faltante o invalido. Recuerde el orden de los archivos: ./transporte archivo_estaciones archivo_molinetes\n");
		exit(1);
	}

	// Lectura de estaciones
	int id; char linea[40], estacion[40], c;
	do{
		if(fscanf(archEstacion, "%d,%30[^,],%30[^,\n]", &id, linea, estacion) == 3)
			addEstacion(trans, id, linea, estacion);
		c=fgetc(archEstacion);
	}while(c != EOF);

	fclose(archEstacion);

}


void cargarMolinetes(transporteADT trans, const char *archivo_molinetes){

	FILE * archMol = fopen(archivo_molinetes, "r");

	if (archMol == NULL) {
		printf("No se pudo abrir el archivo de molinetes\n");
		exit(1);
	}

	// Solo se leera la hora de finalizacion del intervalo, la de inicio no es necesaria
	unsigned int min, hrs, cant, d, m, y, id; char c;
	do{
		if(fscanf(archMol, "%u/%u/%u,%*[^,],%u:%u,%u,%u", &d, &m, &y, &hrs, &min, &id, &cant) == 7)
			addPasajero(trans, d, m, y, hrs*100+min, id, cant);
		c=fgetc(archMol);
	}
	while(c != EOF);

	fclose(archMol);

}
