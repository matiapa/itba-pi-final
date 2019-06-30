#ifndef TRANSPORTEADT_H

#define TRANSPORTEADT_H

typedef struct transporteCDT * transporteADT;

transporteADT newTransporte();

void addEstacion(transporteADT trans, unsigned int id, char * nombre_linea, char * nombre_estacion);

void addPasajero(transporteADT trans, unsigned int d, unsigned int m, unsigned int y, unsigned int hora, unsigned int id, unsigned int cant);

void ordenarLineasDesc(transporteADT trans);
void calcularMaxPorLinea(transporteADT trans);


#endif

typedef struct tEstacion_favorita
{
	char * nombre_estacion;
	char * nombre_linea;
	long int pasajeros;
}tEstacion_favorita;

// estructura de intercambio entre el TAD y el front end del query 4.

typedef struct tLinea_con_pasajeros
{
	char * nombre_linea;
	long int pasajeros;
}tLinea_con_pasajeros;

//estructura de intercambio entre el TAD y el fron end del query 3.
