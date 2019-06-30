#ifndef TRANSPORTEADT_H

#define TRANSPORTEADT_H

typedef struct transporteCDT * transporteADT;

transporteADT newTransporte(char *archivo_estaciones, char *archivo_molinetes);


#endif

typedef struct tEstacion_favorita
{
	char * nombre_estacion;
	char * nombre_linea;
	long int pasajeros;
}tEstacion_favorita;
