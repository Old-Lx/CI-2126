///
///Gestor de ordenes
///

#ifndef _gestorDeOrdenes_h_
#define _gestorDeOrdenes_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestorDeOrdenes.h"

/*Declaramos un struct para guardar ordenes*/
typedef struct {
    char codigoCliente[20];
    char codigoProducto[20];
    char codigoOrden[20];
    unsigned int cantidad;
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
int abrirBDDOrdenes() ;

/*Inicializa un arreglo dinámico de órdenes*/
DynaOrden *dynaOrden(orden listaDeOrdenes[100]);

#endif
