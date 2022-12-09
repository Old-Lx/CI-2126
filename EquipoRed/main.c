#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.h"
#include "gestorDeProductos.h"
#include "gestorDeOrdenes.h"




int main() {
    int aux,n;
    printf("\n\n***Bienvenido a Nuestro Sistema***\n\n");

    do{
        printf("\nQue deseas Realizar? \n");
        printf(" [1] Registrarte\n [2] Iniciar Sesion\n [3] Ingresar como administrador\n [4] Ingresar como invitado\n [5] Salir\n");
        printf(" Ingresa tu opcion:\t");
        fflush(stdout);
        scanf("%d", &aux);
        fflush(stdin);
        switch (aux)
        {
        case 1:
            guardarCliente(nuevoCliente());
            ingresarNuevoRegistro();
            n=0;
            break;
        case 2:
            ingresar();
            n=0;
            break;
        case 3:
            ingresarAdmin();
            n=0;
            break;
        case 4:
            ingresarInvitado();
            n=0;
            break;
        case 5:
            exit(0);
            n=0;
            break;
        default:
            printf("\n\nOpcion Invalida\n\n");
            n=0;
            break;
        }
    }while (n==0);
}