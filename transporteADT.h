#ifndef TRANSPORTEADT_H

#define TRANSPORTEADT_H

#define DIAS_SEMANA 7

typedef struct transporteCDT * transporteADT;

typedef struct tLinea_con_pasajeros{
	char * nombre_linea;
	long int pasajeros;
}tLinea_con_pasajeros;

//estructura de intercambio entre el TAD y el fron end del query 3.

typedef struct tEstacion_favorita{
	char * nombre_linea;
	long int pasajeros;
	char * nombre_estacion;
}tEstacion_favorita;

// estructura de intercambio entre el TAD y el front end del query 4.

void *smalloc(int bytes, char *err_msg);

transporteADT newTransporte();

void addEstacion(transporteADT trans, const unsigned int id, const char * nombre_linea, const char * nombre_estacion);

void addPasajero(transporteADT trans, unsigned int d, unsigned int m, unsigned int y, unsigned int hora, const unsigned int id, const unsigned int cant);

void ordenarLineasDesc(transporteADT trans);

void calcularMaxPorLinea(transporteADT trans);


int get_cant_lineas(const transporteADT trans);

void get_linea(char ** nombre_linea, long int * pasajeros, const int pos, const transporteADT trans);

void get_pasajeros_por_dia(long int * dia,long int * noche, const int i, const transporteADT trans);

tLinea_con_pasajeros ** get_pasajeros_por_linea(const transporteADT trans);

long int get_total_pasajeros(const transporteADT trans);

tEstacion_favorita ** get_favourite_vec(const transporteADT trans);

#endif
