#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	transporteADT trans = newTransporte();

	// Lectura de estaciones.csv

	FILE * archEstacion = fopen("estaciones.csv", "r");

	// Se saltea el encabezado
	while (fgetc(archEstacion) != '\n');

	int id; char *linea = malloc(30), *estacion = malloc(30);
	do{
		fscanf(archEstacion, "%d,%30[^,],%30[^,\n]", &id, linea, estacion);
		printf("Adding: %d, %s, %s\n", id, linea, estacion);
		addEstacion(trans, id, linea, estacion);
	}while(fgetc(archEstacion)!=EOF);
	

}
