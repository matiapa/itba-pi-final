#include "transporteADT.h"
#include "lectura.h"
#include "queries.h"

#include <stdio.h>

int main(int argc, char **argv) {

	if(argc!=3){
		printf("Uso: ./transporte archivo_estaciones archivo_molinetes");
		return 1;
	}

	printf("> Procesando datos\n");

	transporteADT trans = newTransporte();

	// Carga de datos
	cargarEstaciones(trans, argv[1]);
	cargarMolinetes(trans, argv[2]);

	// Procesamiento de datos
	ordenarLineasDesc(trans);
	calcularMaxPorLinea(trans);

	printf("> Procesamiento completado\n");


	query1(trans);
	printf("> Query 1 terminado \n");

	query2(trans);
	printf("> Query 2 terminado \n");

	query3(trans);
	printf("> Query 3 terminado \n");

	query4(trans);
	printf("> Query 4 terminado \n");
}
