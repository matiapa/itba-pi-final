#ifndef TRANSPORTEADT_H

#define TRANSPORTEADT_H


typedef struct transporteCDT * transporteADT;

typedef struct tLinea_con_pasajeros{
	char * nombre_linea;
	long int pasajeros;
}tLinea_con_pasajeros;

//estructura de intercambio entre el TAD y el fron end del query 3.

typedef struct tEstacion_favorita{
	char * nombre_estacion;
	char * nombre_linea;
	long int pasajeros;
}tEstacion_favorita;

// estructura de intercambio entre el TAD y el front end del query 4.


transporteADT newTransporte();

void addEstacion(transporteADT trans, const unsigned int id, const char * nombre_linea, const char * nombre_estacion);

void addPasajero(transporteADT trans, unsigned int d, unsigned int m, unsigned int y, unsigned int hora, const unsigned int id, const unsigned int cant);

void ordenarLineasDesc(transporteADT trans);

void calcularMaxPorLinea(transporteADT trans);


int get_cant_lineas(transporteADT trans);

long int get_total_pasajeros(transporteADT trans);

void get_linea(char * nombre_linea,long int * pasajeros,int pos,transporteADT trans);

void get_pasajeros_dia(long int * dia,long int * noche,int i,transporteADT trans);

tLinea_con_pasajeros ** get_pasajeros_por_linea_vec(transporteADT trans);

tEstacion_favorita ** get_favourite_vec(transporteADT trans);

#endif
