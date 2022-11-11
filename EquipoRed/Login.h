#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gestorDeProductos.h"


/*Declaramos un struct para guardar clientes*/
typedef struct {   
    char nombre[20];
    char correo[20];
    char direccion[30];
    int telefono;
    char contactof[20];
    char username[15];
    char clave[10];
    char fechaNacimiento[10];
    char lugarNacimiento[20];
    char genero[20];
} cliente ;

/*Declaramos el arreglo de todos los clientes*/
cliente clientes[100];

/*Abre una base de datos de personas guardada en un archivo csv*/
cliente *abrirBDDClientes();

/*Crea un nuevo cliente*/
cliente nuevoCliente();

/*Guarda un cliente en la base de datos*/
int guardarCliente(cliente nuevo);

/*Inicia sesión*/
int ingresar();

/*Modifica datos de un cliente*/
int modificarCliente();


#endif // LOGIN_H_INCLUDED