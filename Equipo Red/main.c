#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.h"
/*#include <csv.h>*/


int main() {
    int k;
    char answer[2];
    do{
    printf("\nBienvenido!\n�Estas registrado en nuestra tienda?\n[S] si\n[N] no\nIngrese su respuesta:  \n");
    fgets(answer, 2, stdin);
    fflush(stdin);

    if (strcmp(answer, "S") == 0 || strcmp(answer, "s") == 0) {
        do{
        printf("Quieres Iniciar Sesion?\n[S] si\n[N] no\nIngrese su respuesta:  ");
        fgets(answer, 2, stdin);
        fflush(stdin);
        if (strcmp(answer, "S") == 0 || strcmp(answer, "s") == 0){
            //ingresar();
            printf("****Funci�n en Mantenimiento, intente de nuevo m�s tarde****");
            k=2;
            }
         else if (strcmp(answer, "N") == 0 || strcmp(answer, "n") == 0)
         {printf("*****Ingresaste como Invitado*****");
            k=2;
        }
        else {
            printf("Opci�n invalida, intente de nuevo");
            k=0;
        };
        }while (k<1);

    }
    else if (strcmp(answer, "N") == 0 || strcmp(answer, "n") == 0){
        do{
        printf("Quieres Registrarte?\n[S] si\n[N] no\nIngrese su respuesta:  ");
        fgets(answer, 2, stdin);
        fflush(stdin);
        if (strcmp(answer, "S") == 0 || strcmp(answer, "s") == 0){
            nuevoCliente();
            k=2;
            }
         else if (strcmp(answer, "N") == 0 || strcmp(answer, "n") == 0)
         {printf("*****Ingresaste como Invitado*****");
            k=2;
        }
        else {
            printf("Opci�n invalida, intente de nuevo");
            k=0;
        };
        }while (k<1);

    }else {
        printf("Opci�n invalida, intente de nuevo");
        k=0;
    }}while (k<1);

    scanf("%s");
    return 0;
}
