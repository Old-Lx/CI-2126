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

/*Struct para guardar productos*/
typedef struct producto;

/*Lista de productos*/
producto BDproducto[100];

/*Abre una base de datos de productos guardada en un archivo csv*/
producto *abrirBDDProductos();

/*Agrega un producto nuevo*/
producto nuevoProducto();

/*Guarda un producto en la base de datos*/
int guardarProducto(producto nuevo);

/*Modifica un producto existente*/
int modificarProducto();




#endif