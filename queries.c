#include <stdio.h>
#define DIAS_SEMANA 7


typedef struct tEstacion_favorita
{
	char * nombre_estacion;
	char * nombre_linea;
	long int pasajeros;
}tEstacion_favorita;

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

void query4(transporteADT trans){

	//recibe un vector de estructuras con la linea, estacion y cantidad de pasajeros en cada elemento del vector.
	tEstacion_favorita ** vec=get_favourite_vec(trans);
	
	
	int cant_lineas=cant_lineas(trans);
	//consigue la cantidad de lineas de subterraneo para saber cuantas iteraciones hacer.
	

	FILE *fptr=fopen("./query4.csv","w");
	//generar el archivo
	
	for (int i=0;i<cant_lineas;i++){
		vec[0}



