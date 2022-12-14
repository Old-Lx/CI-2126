#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestorDeProductos.h"

/*Declaramos un struct para guardar clientes*/
typedef struct {
    char nombre[20];
    char correo[20];
    char direccion[30];
    long unsigned int telefono;
    char contactof[20];
    char username[15];
    char clave[10];
    char fechaNacimiento[10];
    char lugarNacimiento[20];
    char genero[20];
    int posCli;
} cliente ;

int count_c[1];

/*Fila donde se encuentra almacenado el usuario*/
int num_fila[1];

/*Nombre de usuario que ingreso*/
char usuario[20];

/*Struct de datos de clientes*/
cliente clientes[100];

/*Abre una base de datos de personas guardada en un archivo csv*/
cliente *abrirBDDClientes();

/*Crea un nuevo cliente*/
cliente nuevoCliente();

/*Devuelve el índice de un cliente*/
int buscarCliente(const char username[20], cliente clienteL[100]);

/*Guarda un cliente en la base de datos*/
int guardarCliente(cliente nuevo);

/*Modifica datos de un cliente*/
int modificarCliente();

/*Muestra los datos del cliente*/
void mostrarDatosCliente(int filaDelCliente);

/*Ejecuta una operación para un cliente*/
void operacionCliente();

/*Inicia sesión*/
int ingresar();

/*Actualiza la base de datos con datos modificados*/
int actualizarBDClientes();

/*Inicia sesión Invitado*/
int ingresarInvitado();

/*Inicia sesión NuevoRegistro*/
int ingresarNuevoRegistro();

#endif // LOGIN_H_INCLUDED
