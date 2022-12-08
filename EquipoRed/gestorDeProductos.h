///
///Gestor de productos
///

#ifndef _gestorDeProductos_h_
#define _gestorDeProductos_h_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Login.h"


/*Declaramos un struct para guardar productos*/
typedef struct {
        char codigo[20];
        char descripcion[145];
        float precio;
        int stock;
        int posProd;
}producto;

int count_p[1];
producto productos[100];

/*Abre una base de datos de personas guardada en un archivo csv*/
producto *abrirBDDProductos() ;

/*Devuelve un producto agregado*/
producto nuevoProducto();

/*Devuelve el índice de un producto*/
int buscarProducto(const char codigo[20], producto productoL[100]);

/*Guarda un producto en la base de datos*/
int guardarProducto(producto nuevo);

/*Modifica un producto existente*/
int modificarProducto();

/*Muestra base de datos del producto*/
void mostrarBDDProductos() ;

/*Muestra base de datos de Clientes*/
void mostrarBDDClientes();

/*Ejecuta una operación para un administrador*/
void operacionProductos() ;

/*Ingresa como administrador*/
void ingresarAdmin();

/*Actualiza la base de datos de productos*/
int actualizarBDProductos();

/*Muestra productos de 10 en 10*/
void mostrar10Productos();
#endif
