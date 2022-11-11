///
///Gestor de productos
///

#ifndef _gestorDeProductos_h_
#define _gestorDeProductos_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gestorDeProductos.h"


/*Declaramos un struct para guardar productos*/
typedef struct {
        char codigo[20];
        char descripcion[145];
        float precio;
        int stock;
}producto ;

/*Lista de productos*/
producto BDproductos[100];

/*Abre una base de datos de productos guardada en un archivo csv*/
producto *abrirBDDProductos();

/*Agrega un producto nuevo*/
producto nuevoProducto();

/*Guarda un producto en la base de datos*/
int guardarProducto(producto nuevo);

/*Modifica un producto existente*/
int modificarProducto();

#endif