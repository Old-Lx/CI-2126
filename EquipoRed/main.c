#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.c"
#include "gestorDeProductos.h"


int main() {
    print("Si eres administrador inserte clave si no, inserte [n]\n");
    fflush(stdin);
    char clave_adm[1];
    scanf("%s", clave_adm);

    if (strcmp(clave_adm, "n") || strcmp(clave_adm, "N")) {
        int k;
        char answer[2];
        do{
        printf("\nBienvenido!\nEstas registrado en nuestra tienda?\n[S] si\n[N] no\nIngrese su respuesta:  \n");
        fgets(answer, 2, stdin);
        fflush(stdin);
        //system ("cls");

        if (strcmp(answer, "S") == 0 || strcmp(answer, "s") == 0) {
            do{
            printf("Quieres Iniciar Sesion?\n[S] si\n[N] no\nIngrese su respuesta:  ");
            fgets(answer, 2, stdin);
            fflush(stdin);
            //system ("cls");
            if (strcmp(answer, "S") == 0 || strcmp(answer, "s") == 0){
                ingresar();
                k=2;
                }
            else if (strcmp(answer, "N") == 0 || strcmp(answer, "n") == 0)
            {printf("*****Ingresaste como Invitado*****");
                k=2;
            }
            else {
                printf("Opción invalida, intente de nuevo");
                k=0;
            };
            }while (k<1);

        }
        else if (strcmp(answer, "N") == 0 || strcmp(answer, "n") == 0){
            do{
            printf("Quieres Registrarte?\n[S] si\n[N] no\nIngrese su respuesta:  ");
            fgets(answer, 2, stdin);
            fflush(stdin);
            //system ("cls");
            if (strcmp(answer, "S") == 0 || strcmp(answer, "s") == 0){
                guardarCliente(nuevoCliente());
                k=2;
                }
            else if (strcmp(answer, "N") == 0 || strcmp(answer, "n") == 0)
            {printf("*****Ingresaste como Invitado*****");
                k=2;
            }
            else {
                printf("Opción invalida, intente de nuevo");
                k=0;
            };
            }while (k<1);

        }else {
            printf("Opción invalida, intente de nuevo");
            k=0;
        }}while (k<1);

        return 0;
    } else if (strcmp(clave_adm, "n") || strcmp(clave_adm, "N")) {

        printf("¿Que desea hacer?\n[1] Agregar producto al inventario\n[2] Actualizar informacion de un producto\n");
        fflush(stdout);
        int acc_adm;
        scanf("%d", acc_adm);
        switch (acc_adm)
        {
        case 1:
            guardarProducto(nuevoProducto());
            break;

        case 2:
            modificarProducto();
            break;
        default:
            printf("Opcion invalida");
            break;
        }

    }
    return 0;
}
