#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <string.h>

typedef struct
{

    int codigo;
    char nombre[100];
    float precio;
    int cantidad;

} producto;

typedef struct
{
    char accion[10];// (I O E) (ingreso o egreso)
    char fecha[11]; //(01/01/2000);
    char nombre [100];
    float precio;
    int cantidad;
} stock ;

void CargarProducto(char archivito[]);
void NuevoProducto(producto *productoNuevo);
void mostrarProductos(char archivito[]);
void mostrarUnProducto( producto aux);
void cargastock(stock *aux);
void CargarFichaStock(char rutaArchivo[]);
void mostrarUnCambioStock ( stock aux);
void mostrarCambioStock(char rutaArchivo[]);



int main()
{

    int eleccion;


    do
    {
        printf("\nIngrese la opcion que desea realizar \n");
        printf(" 0. Terminar el programa\n");
        printf(" 1. Cargar un producto \n");
        printf(" 2. cargar ficha de stock \n");
        printf(" 3. mostrar productos y archivo de stock\n");
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
            CargarProducto("productos.bin");


            break;
        case 2:
            CargarFichaStock("fichastock.bin");

            break;
        case 3:
            mostrarProductos("productos.bin");
            puts("\n\n STOCK");
            mostrarCambioStock("fichastock.bin");
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
            if (eleccion != 0)
            {
                printf("Esa opcion no existe\n");
            }
            break;

        }

    }
    while (eleccion != 0);
    return 0;

}
//funcion para mostrar TODOS cambios de stock
void mostrarCambioStock(char rutaArchivo[])
{
    stock aux;
    FILE *arch;

    arch=fopen(rutaArchivo,"rb");

    if(arch!=NULL)
    {
        while(!feof(arch))
        {
            fread(&aux,sizeof(stock),1,arch);
            if(!feof(arch))
            {
                mostrarUnCambioStock(aux);
            }

        }
        fclose(arch);
    }
}
//Funcion para mostrar stock
void mostrarUnCambioStock ( stock aux)
{

    puts("\n-----------------------------------------------\n");
    printf("FECHA: %s\n",aux.fecha);
    printf("Se realizo un: %s\n",aux.accion);
    printf("Producto: %s\n",aux.nombre);
    printf("Precio: %f\n",aux.precio);
    printf("cantidad: %i\n",aux.cantidad);
    puts("\n-----------------------------------------------\n");
}
//Cargar ficha de stock
void CargarFichaStock(char rutaArchivo[])
{
    char eleccion = 's';
    stock aux;
    FILE *arch;

    arch = fopen(rutaArchivo,"ab");

    if(arch != NULL)
    {

        while(eleccion == 's')
        {

            cargastock(&aux);
            fwrite(&aux, sizeof(stock), 1, arch);

            printf("si desea seguir cargando escriba 's'\n");
            fflush(stdin);
            scanf(" %c ",&eleccion);


        }
        fclose(arch);
    }
}
void cargastock(stock *aux)
{
    printf("Tipo de accion Egreso o Ingreso:\n");
    fflush(stdin);
    scanf("%s",&aux->accion);

    printf("Fecha(00/00/0000):\n");
    fflush(stdin);
    scanf("%s",&aux->fecha);

    printf("Nombre del producto:\n");
    fflush(stdin);
    gets(aux->nombre);

    printf("Precio:\n");
    fflush(stdin);
    scanf("%f",&aux->precio);

    printf("Cantidad:\n");
    fflush(stdin);
    scanf("%i",&aux->cantidad);

}

//funcion para mostrar TODOS los productos
void mostrarProductos(char archivito[])
{
    producto aux;
    FILE *arch;

    arch=fopen(archivito,"rb");

    if(arch!=NULL)
    {
        while(!feof(arch))
        {
            fread(&aux,sizeof(producto),1,arch);
            if(!feof(arch))
            {
                mostrarUnProducto(aux);
            }

        }
        fclose(arch);
    }
}
//Funcion para mostrar de aun producto
void mostrarUnProducto ( producto aux)
{

    puts("\n-----------------------------------------------\n");
    printf("El codigo del producto es: %i\n",aux.codigo);
    printf("El nombre del producto es: %s\n",aux.nombre);
    printf("El precio del producto es: %.2f\n",aux.precio);
    printf("El stock del producto es: %i\n",aux.cantidad);
    puts("\n-----------------------------------------------\n");
}
// cargar cantidad deseada de productos
void CargarProducto(char rutaArchivo[])
{

    char eleccion = 's';
    producto aux;
    FILE *arch;

    arch = fopen(rutaArchivo,"ab");

    if(arch != NULL)
    {

        while(eleccion == 's')
        {

            NuevoProducto(&aux);
            fwrite(&aux, sizeof(producto), 1, arch);
            printf("si desea seguir cargando escriba 's'\n");
            fflush(stdin);
            scanf("%c",&eleccion);

        }

        fclose(arch);

    }
}

// Cargar un producto
void NuevoProducto(producto *productoNuevo)  // cargar un producto
{

    printf("Codigo de producto:\n");
    fflush(stdin);
    scanf("%i",&productoNuevo->codigo);

    printf("Nombre del producto:\n");
    fflush(stdin);
    gets(productoNuevo->nombre);

    printf("Precio de Venta:\n");
    fflush(stdin);
    scanf("%f",&productoNuevo->precio);

    printf("Cantidad de producto en stock:\n");
    fflush(stdin);
    scanf("%i",&productoNuevo->cantidad);

}
