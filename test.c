#include "transporteADT.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE * archEstacion;
	archEstacion = fopen("estaciones.csv", "r");
	unsigned int id;
	char * linea = malloc(20);
	char * estacion = malloc(25);
	transporteADT trans;
	trans = newTransporte();

	int c;
	while ((c = fgetc(archEstacion)) != '\n');
	fscanf(archEstacion, "%d,%[^,],%[^,]", &id, linea, estacion);
	addEstacion(trans, id, linea, estacion);
	printf("%d, %s, %s", id, linea, estacion);
}
