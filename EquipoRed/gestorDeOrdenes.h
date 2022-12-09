///
///Gestor de ordenes
///

#ifndef _gestorDeOrdenes_h_
#define _gestorDeOrdenes_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestorDeProductos.h"
#include "Login.h"

/*Struct de cantidad de productos*/
typedef struct {
    char codigoProd[20][20];
    char cantidad[20][20];
} codigoProducto ;

/*Declaramos un struct para guardar ordenes*/
typedef struct {
    char codigoCliente[20]; ///Hacerlo como struct incluyendo cantidad
    char codigoOrden[20];
    codigoProducto productoOrden;
    unsigned int descuento;
} orden ;

/*Declaramos arreglo dinámico de órdenes*/
typedef struct {
    orden *ordenes;
    unsigned int tamano;
    unsigned int capacidad;
} DynaOrden ;

/*Lista de ordenes*/
orden listaO[100];

/*Número de órdenes*/
int count_o[1];

/*Abre base de datos de órdenes en csv*/
orden *abrirBDOrdenes() ;

/*Inicializa un arreglo dinámico de órdenes*/
DynaOrden *dynaOrden(orden listaDeOrdenes[100]);

/*Carga los codigos de los productos de cada orden*/
const char *abrirProdPorOrd();

/*Devuelve la columna de productos de una orden*/
int columnOrd(DynaOrden *dynaOrden, char *codOrd);

/*Busca la orden de un cliente x*/
int buscarOrden(DynaOrden *listaO, orden buscada);

/*Encuentra el indice de la string que se elija*/
int indOrd(int i, DynaOrden *listaO);

/*Crea orden nueva*/
orden nuevaOrden();

/*Guarda una orden en la base de datos*/
void guardarOrden(orden nueva);

/*Devuelve la orden en el indice i*/
orden valorOrd(int i, const DynaOrden *dynaOrden);

/*Cambia el valor de la orden en el indice i*/
void dynaCambValOrd(int i, DynaOrden *dynaOrden, orden cambio);

/*Esta funcion devuelve todas las ordenes, sólo usar en modo admin*/
orden *ordGuardadas(const DynaOrden *dynaOrden);

/*Devuelve la capacidad de la lista de ordenes*/
int ordCap(const DynaOrden *dynaOrden);

/*Devuelve el tamano de la lista de ordenes*/
int ordTam(const DynaOrden *dynaOrden);

/*Libera memoria ue contiene arreglo dinamico de ordenes*/
void remDynaOrden(DynaOrden **dynaOrden);

/*Inserta ordenes desde el indice del ultimo elemento de la lista de ordenes*/
void dynaInsOrd(DynaOrden *dynaOrden, int N, orden *nueva);

/*Elimina la orden en el indice i de la lista*/
void elimOrden(DynaOrden *dynaOrden, int pos);

/*Encuentra el indice de la string más cercano a la A*/
int indOrdAlfa(int i, int j, const char *a[]);

/*Cambia la posición de dos ordenes*/
void cambOrd(int i, int j, DynaOrden *dynaOrden);

/*Reordena de menor a mayor las ordenes segun su codigo*/
void sortOrd(DynaOrden *dynaOrden);

/*Por si acaso, función para concatenar dos listas de ordenes*/
DynaOrden *unirLisOrd(DynaOrden *dynaOrden1, DynaOrden *dynaOrden2);

/*Crea una orden en la base de datos*/
int crearOrd(orden nuevo);

/*Agrega un producto a la orden determinada*/
void aggProducto(const char *codigoOrden, producto nuevo, DynaOrden *dynaOrden);

#endif
