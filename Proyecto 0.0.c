
#include <stdio.h>


void main(){
    struct clientes
    {   int cedula;
        char Nombre[20];
        char direccion[30];    
    };
    int i=0;
    struct clientes primero ={26739819,"gustavo"};
    printf("%d\n\n\n\n",primero.cedula);    
    printf("hola Compañeritos, ingresen nuevo usuario:\n");
    scanf("%d",&primero.cedula);
    printf("%d\n\n\n\n",primero.cedula);
    for(i=0;i<5;i++){
        printf("*");
    }
}