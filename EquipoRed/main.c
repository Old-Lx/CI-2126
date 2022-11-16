#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.h"
#include "gestorDeProductos.h"


int main() {
    printf("¿Eres administrador de la tienda? [S] Sí [N] No\n");
    fflush(stdout);
    fflush(stdin);
    char resp[10];
    scanf("%s", &resp);
    fflush(stdin);

    if (strcmp(resp, "n") == 0 || strcmp(resp, "N") == 0) {
        int k;
        char answer[2];
        do{
        printf("\nBienvenido!\nEstas registrado en nuestra tienda?\n[S] si\n[N] no\nIngrese su respuesta:  \n");
        fflush(stdout);
        fgets(answer, 2, stdin);
        fflush(stdin);
        //system ("cls");

        if (strcmp(answer, "S") == 0 || strcmp(answer, "s") == 0) {
            do{
            printf("Quieres Iniciar Sesion?\n[S] si\n[N] no\nIngrese su respuesta:  ");
            fflush(stdout);
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
            fflush(stdout);
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
    } else if (strcmp(resp, "s") == 0 || strcmp(resp, "S") == 0) {

        printf("Ingrese clave de administrador:\n");
        fflush(stdout);
        fflush(stdin);
        char clave_adm[10];
        scanf("%s", &clave_adm);
        fflush(stdin);

        if (strcmp(clave_adm, "admin") == 0 || strcmp(clave_adm, "admin") == 0) {

            ingresarAdmin();
            
        }

    }else {
        printf("Opción Invalida");
    }
    return 0;
}
