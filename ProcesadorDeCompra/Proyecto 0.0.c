#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*#include <csv.h>*/

/*Declaramos una struct para almacenar fechas*/
struct fecha {
    int dia;
    int mes;
    int year;
};

/*Declaramos un struct para guardar clientes*/
struct cliente {   
        char nombre[20];
        char correo[20];
        char direccion[30];
        int telefono;
        char contactof[20];
        char username[15];
        char clave[10];
        struct fecha fechaNacimiento;
        char lugarNacimiento[20];
        char genero[10];
};

/*Arreglo dinámico que guarda a los clientes*/
struct baseDeDatos {
    double *datos;
    size_t size;
    size_t capacidad;
};

struct baseDeDatos *bddNueva(size_t N) {
    struct baseDeDatos *BDD = (struct baseDeDatos *) malloc(sizeof(struct baseDeDatos));
    BDD->size = N;
    BDD->capacidad = N;
    return BDD;
}


/*Crea un nuevo cliente*/
void nuevoCliente() {
    
}
/*
    struct clientes primero;
    printf("Ingrese día de nacimiento:\n");
    scanf("%d", &primero.fechaNacimiento.dia);
    printf("Ingreso el día: %d", primero.fechaNacimiento.dia);
    printf("\nIngrese mes de nacimiento:\n");
    scanf("%d", &primero.fechaNacimiento.mes);
    printf("Ingreso el mes: %d", primero.fechaNacimiento.mes);
    printf("\nIngrese año de nacimiento:\n");
    scanf("%d", &primero.fechaNacimiento.year);
    printf("Ingreso el año: %d", primero.fechaNacimiento.year);
    printf("\n\nExcelente, su fecha de nacimiento es: %d / %d / %d", primero.fechaNacimiento.dia, 
    primero.fechaNacimiento.mes, primero.fechaNacimiento.year);*/

