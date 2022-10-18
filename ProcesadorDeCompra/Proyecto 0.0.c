#include <stdio.h>


void main(){
    /*Declaramos una struct para almacenar fechas*/
    struct fecha {
        int dia;
        int mes;
        int year;
    };
    
    /*Declaramos un struct para guardar clientes*/
    struct clientes {   
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

    /*Ahora nos toca definir la función para agregar un nuevo cliente*/
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
    primero.fechaNacimiento.mes, primero.fechaNacimiento.year);
}