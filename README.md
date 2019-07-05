# Consigna
## Información disponible

estaciones.csv: id, estacion, linea

molinetes.csv: fecha, desde, hasta, estacion_id, pasajeros


## Queries solicitados

Query 1: Pasajeros por línea. Imprime nombre_linea, cant_pasajeros, en orden descendente.

Query 2: Pasajeros por día semanal y por período. Imprime día, diurnos, nocturnos, total, en orden semanal.

Query 3: Porcentaje de pasajeros por línea. Imprime nombre_linea, porcentaje, en orden descendente.

Query 4: Estación con más pasajeros por línea. Imprime estación, línea, pasajeros, en orden alfabético de líneas.



# Solucion desarrollada

## TAD

### transporteCDT
-	tLinea * lineas_ord_alpha;								// Lista de lineas en orden alfabetico
-	tLinea ** lineas_ord_desc;								// Vector de punteros a lineas en orden descendente (por pasajeros)

-	int cant_lineas;
-	tEstacion * estaciones; 									// Arbol binario de busqueda con todas las estaciones
-	unsigned int cant_estaciones;

-	long int pasajeros;												// Total de pasajeros
-	unsigned int vec_diurno[DIAS_SEMANA];			// Cantidad de pasajeros por dia de la semana en periodo diurno, la primer posicion es domingo
-	unsigned int vec_nocturno[DIAS_SEMANA];


### tLinea
- char * nombre;
- long int pasajeros;												// Total de pasajeros en la linea
-	struct tEstacion * max; 									// Puntero a la estacion con mas pasajeros
-	struct tLinea * next;											// Puntero a la proxima linea en la lista de lineas


### tEstacion
- unsigned int id;
-	int pasajeros;														// Total de pasajeros en la estacion
-	char * nombre;
-	tLinea * linea; 														// Puntero a la linea que pertenece
-	struct tEstacion * left;									// Puntero al hijo izquierdo en el arbol binario de busqueda
-	struct tEstacion * right;



## Mapa de Funciones

FRONTEND: main.c, lectura.c, queries.c

BACKEND: transporteADT.c

### main.c

- main
  - cargarEstaciones (lectura.c)
  - cargarMolinetes (lectura.c)
  - ordenarLineasDesc (transporteADT.c)
  - calcularMaxPorLinea (transporteADT.c)
  - query1 (queries.c)
  - query2 (queries.c)
  - query3 (queries.c)
  - query4 (queries.c)


### lectura.c

- cargarEstaciones
  - addEstacion (transporteADT.c)
- cargarMolinetes
  - addPasajero (transporteADT.c)


### queries.c

- query1
  - get_cant_lineas  (transporteADT.c)
  - get_linea (transporteADT.c)

- query2
  - get_pasajeros_dia (transporteADT.c)

- query3
  -  get_pasajeros_por_linea (transporteADT.c)
  - get_total_pasajeros (transporteADT.c)
  - get_cant_lineas (transporteADT.c)

- query4
  - get_favourite_vec (transporteADT.c)
  - get_cant_lineas (transporteADT.c)


### transporteADT.c

- newTransporte

- addEstacion
  - addEstacionRec
  - addLinea

- addPasajero
  - getEstacion

- ordenarLineasDesc
  - compararLineas

- calcularMaxPorLinea
  - postorderExecute
  - calcularMax

- freeTransporte
  - freeEstacion
  - freeLinea
  - postorderExecute

- get_cant_lineas

- get_linea

- get_pasajeros_por_dia

- get_pasajeros_por_linea

- get_total_pasajeros

- get_favourite_vec
