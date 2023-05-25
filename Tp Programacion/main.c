#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <string.h>

typedef struct {

int codigo;
char nombre[20];
int precio;
int costo;

}producto;

void CargarProducto(producto arr[],int validos,int *cantProductos);
producto NuevoProducto();

int main()
{
producto productos[100];
int cantProductos = 0;
int eleccion;


do{
    printf("\nIngrese la opcion que desea realizar \n");
    printf(" 0.Terminar el programa\n");
    printf(" 1. Cargar un producto\n");
    printf(" 2.\n");
    printf(" 3.\n");
    printf(" 4. \n");
    printf(" 5.\n");
    printf(" 6.\n");
    printf(" 7.\n");
    printf(" 8.\n");
    printf(" 9.\n");
    printf(" 10.\n");

    fflush(stdin);
    scanf("%i",&eleccion);

    switch(eleccion)
    {
        case 1:
            CargarProducto(productos,100,&cantProductos);


            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        default:
            printf("Esa opcion no existe\n");
            break;

}

    } while (eleccion != 0);

}


void CargarProducto(producto arr[],int validos,int *cantProductos){

char eleccion = 's';

while(*cantProductos<validos && eleccion == 's'){

arr[*cantProductos] = NuevoProducto();

*cantProductos++;

printf("si desea seguir cargando escriba 's'\n");
fflush(stdin);
scanf("%c",&eleccion);

}

}


producto NuevoProducto(){

producto productoNuevo;

printf("Codigo de producto:\n");
fflush(stdin);
scanf("%i",&productoNuevo.codigo);

printf("Nombre del producto:\n");
fflush(stdin);
gets(productoNuevo.nombre);

printf("Precio de Venta:\n");
fflush(stdin);
scanf("%i",&productoNuevo.precio);

printf("Costo de produccion:\n"); //Este por ahi despues lo cambiamos por una funcion de calculo de costos.
fflush(stdin);
scanf("%i",&productoNuevo.costo);

return productoNuevo;
}



