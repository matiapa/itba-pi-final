#include <stdio.h>
#define DIAS_SEMANA 7

funciones que necesito:
cant_lineas
get_total_pasajeros
get_linea
get_pasajeros_dia
get_pasajeros_por_linea_vec
get_favourite_vec

int main()
{

	

}
void query1(transporteADT trans)
{
	char * nombre_linea;
        long int pasajeros;
	int cant_lineas=cant_lineas(trans);
	//conseguir cantidad de lineas de subte para saber cuantas lineas agregar al archivo.
	
	FILE *fptr=fopen("./query1.csv","w");
	//generar el archivo

	for (int i=0;i<cant_lineas;i++){
		get_linea(&nombre_linea,&pasajeros,i,trans);
		fprintf(fptr,"%s,%ld\n", nombre_linea, pasajeros);
		}
	//agregar linea por linea los dats al archivo
	
	fclose(fptr);
	//cerrar el archivo
	

}
void query2(transporteADT trans)
{
	char ** dias={"domingo","lunes","martes","miercoles","jueves","viernes","sabado"};
	long int dia,noche;
	

	FILE *fptr=fopen("./query2.csv","w");
	         //generar el archivo
	for (int i=0;i<DIAS_SEMANA;i++){
		get_pasajeros_dia(&dia,&noche,i,trans);
		fprintf(ftpr,"%s,%ld,%ld,%ld \n",dias[i],dia,noche,dia+noche);
	}
	//agregar cada linea al archivo
	fclose(fptr);
	//cerrar el archivo
}

void query3(transporteADT trans){
	tLinea_con_pasajeros ** vec=get_pasageros_por_linea_vec(trans);
	tLinea_con_pasajeros * linea;
	//recibe vecor de punteros a estructuras con la linea y cantidad de pasajeros en cada estructura a la que apunta cada elemento del vector.
	
	long int total_pasajeros=get_total_pasajeros(trans);
	int cant_lineas=cant_lineas(trans);
	//consigue la cantidad de lineas del subterraneo para saber cuantas iteraciones hacer y la cantidad de pasageros totales para hacer los calculos.
	
	FILE *fptr=fopen("./query3.csv","w");
	//generar el archivo a escribir.
	
	for (int i=0;i<cant_lineas;i++){
		linea=vec[i]
		fprintf(fptr,"%s,%ld% \n",linea->nombre_linea,(linea->pasajeros/total_pasajeros)*100);

	}
	// agrega los valores al archivo
	
	fclose(fptr);
	//cierra el archivo

}




void query4(transporteADT trans){

	//recibe un vector de punteros a estructuras con la linea, estacion y cantidad de pasajeros en cada estructura a la que aunta cada elemento del vector.
	tEstacion_favorita ** vec=get_favourite_vec(trans);
	tEstacion_favorita * estacion_fav;
	
	
	int cant_lineas=cant_lineas(trans);
	//consigue la cantidad de lineas de subterraneo para saber cuantas iteraciones hacer.
	

	FILE *fptr=fopen("./query4.csv","w");
	//generar el archivo
	
	for (int i=0;i<cant_lineas;i++){
		estacion_fav=vec[i];
		fprintf(fptr,"%s,%s,%ld \n",estacion_fav.nombre_estacion,estacon_fav.nombre_linea,estacion_fav.pasajeros);
	}
	//agregar los valores de las estructuras al archivo, iterando en el vector
	
	fclose(fptr);
	//cerrar el archivo
}




