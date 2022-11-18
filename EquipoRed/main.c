#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Login.h"
#include "gestorDeProductos.h"
#include "gestorDeOrdenes.h"




int main() {
    char ClaveAdmin[10] = "admin" ;
    int menuPrincipal,menu2,resp;

    do
    {
        printf("Eres administrador de la tienda? \n [1] Si \n [2] No\nIngrese su respuesta: ");
        fflush(stdout);
        fflush(stdin);
        scanf("%i", &resp);
        fflush(stdin);
        switch (resp)
        {
        case 1:
            printf("\nIngrese clave de administrador: ");
            fflush(stdout);
            fflush(stdin);
            char clave_adm[10];
            scanf("%s", &clave_adm);
            fflush(stdin);

            if (strcmp(clave_adm, ClaveAdmin) == 0 ) {
                ingresarAdmin();
                menuPrincipal = 2;
            }else {
                printf("\n \nClave invalida\n \n");
                menuPrincipal = 0;
            };
            break;
        case 2:
        do{
            printf("\nBienvenido!\nEstas registrado en nuestra tienda?\n [1] Si\n [2] No\nIngrese su respuesta:  \n");
            scanf("%i", &resp);
            fflush(stdin);
            switch (resp)
            {
            case 1:
                do{
                    printf("\nQuieres Iniciar Sesion?\n[1] Si\n[2] No\nIngrese su respuesta:  ");
                    scanf("%i", &resp);
                    fflush(stdin);
                   switch (resp)
                   {
                   case 1: ingresar(); menuPrincipal=2; break;
                   case 2: printf("*****Ingresaste como Invitado*****"); menuPrincipal=2; break;
                   default: printf("\n\nOpcion invalida, intente de nuevo\n\n"); menuPrincipal=0; break;
                   }
                } while (menuPrincipal == 0);
                break;
            case 2:
                do{
                    printf("Quieres Registrarte?\n[1] Si\n[2] No\nIngrese su respuesta:  ");
                    scanf("%i", &resp);
                    fflush(stdin);
                   switch (resp)
                   {
                   case 1: guardarCliente(nuevoCliente()); ingresar(); menuPrincipal = 2; break;
                   case 2: printf("\n*****Ingresaste como Invitado*****\n"); menuPrincipal = 2; break;
                   default: printf("\n\nOpcion invalida, intente de nuevo\n\n"); menuPrincipal=0; break;
                   }
                } while (menuPrincipal == 0);
                break;
            default:
                printf("\n\nOpcion invalida, intente de nuevo\n\n"); menuPrincipal = 0; break;
            }
        }while (menuPrincipal == 0);break;
        
        default: printf("\n\nOpcion invalida, intente de nuevo\n\n"); menuPrincipal=0; break;

        }
    }while (menuPrincipal == 0);
}
