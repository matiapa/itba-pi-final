#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA_CSV 200


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
	char c;
	do{
		char str[MAX_LINEA_CSV]={0};
		for(int i=0; (c=fgetc(archEstacion))!='\n' && c!=EOF && i<MAX_LINEA_CSV; i++)
			str[i]=c;

		const char d[2] = ",";
		char *id=strtok(str, d); char *linea=strtok(NULL, d); char * estacion=strtok(NULL, d);

		if(id!=NULL && linea!=NULL && estacion!=NULL)
			addEstacion(trans, atoi(id), linea, estacion);

	}while(c != EOF);

	fclose(archEstacion);

}


void cargarMolinetes(transporteADT trans, const char *archivo_molinetes){

	FILE * archMol = fopen(archivo_molinetes, "r");

	if (archMol == NULL) {
		printf("No se pudo abrir el archivo de molinetes\n");
		exit(1);
	}

	// Solo se leera la hora de finalizacion del intervalo, que es la utilizada para determinar el periodo (diurno/nocturno) del viaje
	unsigned int min, hrs, cant, d, m, y, id; char c;
	do{
		if(fscanf(archMol, "%u/%u/%u,%*[^,],%u:%u,%u,%u", &d, &m, &y, &hrs, &min, &id, &cant) == 7)
			addPasajero(trans, d, m, y, hrs*100+min, id, cant);
		c=fgetc(archMol);
	}
	while(c != EOF);

	fclose(archMol);

}
