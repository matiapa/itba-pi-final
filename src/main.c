#include "transporteADT.h"
#include "lectura.h"
#include "queries.h"

#include <stdio.h>

int main(int argc, char **argv) {

	if(argc!=3){
		printf("Uso: ./transporte archivo_estaciones archivo_molinetes\n");
		return 1;
	}

	transporteADT trans = newTransporte();


	// Carga de datos

	printf("> Cargando datos\n");

	cargarEstaciones(trans, argv[1]);
	if(get_cant_lineas(trans)==0){
		printf("No se agrego ninguna estacion\n");
		freeTransporte(trans);
		return 1;
	}

	cargarMolinetes(trans, argv[2]);

	printf("> Carga completada\n");


	// Procesamiento de datos

	ordenarLineasDesc(trans);
	calcularMaxPorLinea(trans);

	printf("> Procesamiento completado\n");


	// Ejecucion de consultas

	query1(trans);
	printf("> Query 1 terminado \n");

	query2(trans);
	printf("> Query 2 terminado \n");

	query3(trans);
	printf("> Query 3 terminado \n");

	query4(trans);
	printf("> Query 4 terminado \n");


	// Liberacion de memoria

	freeTransporte(trans);
	printf("> Completado\n");

}
