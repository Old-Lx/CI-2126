#include <stdio.h>


void main(){
    struct fecha
    {
        int dia;
        int mes;
        int year;
    };
    
    struct clientes
    {   char nombre[20];
        char correo[20];
        char direccion[30];
        int telefono;
        char contactof[20];
        char username[15];
        char clave[10];
        struct fecha fnacimiento;
        char lnacimiento[20];
        char genero[10];

    };
    struct clientes primero;
    printf("Ingrese día de nacimiento:\n");
    scanf("%d", &primero.fnacimiento.dia);
    printf("Ingreso el día: %d", primero.fnacimiento.dia);
    printf("\nIngrese mes de nacimiento:\n");
    scanf("%d", &primero.fnacimiento.mes);
    printf("Ingreso el mes: %d", primero.fnacimiento.mes);
    printf("\nIngrese año de nacimiento:\n");
    scanf("%d", &primero.fnacimiento.year);
    printf("Ingreso el año: %d", primero.fnacimiento.year);
    printf("\n\nExcelente, su fecha de nacimiento es: %d / %d / %d", primero.fnacimiento.dia, 
    primero.fnacimiento.mes, primero.fnacimiento.year);
}