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

	/* Paso la primera linea de largo porque no me importa */
	while ((c = fgetc(archEstacion)) != '\n');

	/* Tomo la segunda linea */
	fscanf(archEstacion, "%d,%[^,],%[^,]", &id, linea, estacion);

	/* Agrego la estacion con los datos de la segunda linea */
	addEstacion(trans, id, linea, estacion);

	printf("%d, %s, %s", id, linea, estacion);
}
