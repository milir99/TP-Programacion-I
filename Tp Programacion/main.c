#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <string.h>

typedef struct
{

    int codigo;
    char nombre[30];
    float precio;
    int cantidad;

} producto;

typedef struct
{
    char accion;// (I O E) (ingreso o egreso)
    char fecha[11]; //(01/01/2000);
    char nombre [30];
    float precio;
    int cantidad;
} stock ;

void CargarProducto(char archivito[]);
void NuevoProducto(producto *productoNuevo);
void mostrarProductos(char archivito[]);
void mostrarUnProducto(producto aux);
void cargastock(stock *aux);
void CargarFichaStock(char rutaArchivo[]);
void mostrarUnCambioStock (stock aux);
void mostrarCambioStock(char rutaArchivo[]);
void archivoAarreglo(char rutaArchivo[], producto arr[],int *validos);
void ordenacionSeleccionCodigo (producto arr[], int validos);
int posicionMenorCodigo (producto arr[], int pos, int validos);
void ordenarPorCodigo (char rutaArchivo[]);                     // por codigo
int posicionMenorNombre (producto arr[], int pos, int validos);
void ordenacionSeleccionNombre (producto arr[], int validos);
void ordenarPornombre (char rutaArchivo[]);                     //por nombre
void ordenacionSeleccionCantidad (producto arr[], int validos);
int posicionMenorCantidad (producto arr[], int pos, int validos);
void ordenarPorCantidad (char rutaArchivo[]);                   // por cantidad




int main()
{

    int eleccion;
    int Ordenarpor=0;


    do
    {
        printf("\nIngrese la opcion que desea realizar \n");
        printf(" 0. Terminar el programa\n");
        printf(" 1. Cargar un producto \n");
        printf(" 2. cargar ficha de stock \n");
        printf(" 3. mostrar productos y archivo de stock\n");
        printf(" 4.\n");
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
            printf(" Ordenar por(:\n");
            printf(" 1. Codigo.\n");
            printf(" 2. Nombre.\n");
            printf(" 3. Cantidad.\n");
            fflush(stdin);
            scanf("%i",&Ordenarpor);
            switch(Ordenarpor)
            {
            case 1:
                puts("----------------------------");
                printf(" ORDENADO POR CODIGO.\n");
                ordenarPorCodigo ("productos.bin");
                mostrarProductos("productos.bin");
                puts("----------------------------");
                break;
            case 2:
                puts("----------------------------");
                printf(" ORDENADO POR NOMBRE.\n");
                ordenarPornombre ("productos.bin");
                mostrarProductos("productos.bin");
                puts("----------------------------");
                break;
            case 3:
                puts("----------------------------");
                printf(" ORDENADO POR CANTIDAD.\n");
                ordenarPorCantidad ("productos.bin");
                mostrarProductos("productos.bin");
                puts("----------------------------");
                break;

            }

            break;
        case 5:
            ordenarPorCodigo ("productos.bin");

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
                printf("Esa funcion no existe\n");
            }
            break;

        }

    }
    while (eleccion != 0);
    return 0;

}




// FUNCION PARA ORDENAR
void archivoAarreglo(char rutaArchivo[], producto arr[],int *validos)
{
    int i=0;
    FILE *arch;
    arch = fopen( rutaArchivo,"rb");

    if(arch!=NULL)
    {
        while(fread(&arr[i],sizeof(producto),1,arch)==1
             )
        {
            (*validos)++;
            i++;

        }
        fclose(arch);
    }
    else
    {
        printf("Error al abrir el archivo");
    }
}
//ORDENAR POR Cantidad!
void ordenarPorCantidad (char rutaArchivo[])
{
    producto arr[30];
    producto aux;
    int validos=0;
    int i=0;
    archivoAarreglo(rutaArchivo, arr, &validos);
    ordenacionSeleccionCantidad(arr, validos);
    FILE *arch;
    arch = fopen( rutaArchivo,"wb");
    if(arch!=NULL)
    {
        while(i<validos)
        {
            aux = arr[i];
            i++;
            fwrite(&aux,sizeof(producto),1, arch);
        }
        fclose(arch);
    }
    else
    {
        printf("Error al abrir el archivo");
    }
}
int posicionMenorCantidad (producto arr[], int pos, int validos)
{
    int menor = arr[pos].cantidad;
    int posmenor = pos;
    int i = pos +1;
    while (i<validos)
    {
        if (menor > arr[i].cantidad)
        {
            menor = arr[i].cantidad;
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}
void ordenacionSeleccionCantidad (producto arr[], int validos)
{
    int posmenor;
    producto aux;
    int i = 0;
    while (i<validos-1)
    {
        posmenor = posicionMenorCantidad(arr,i,validos);
        aux = arr[posmenor];
        arr[posmenor]=arr[i];
        arr[i]= aux;
        i++;
    }
}



//ORDENAR POR NOMBRE!
void ordenarPornombre (char rutaArchivo[])
{
    producto arr[30];
    producto aux;
    int validos=0;
    int i=0;
    archivoAarreglo(rutaArchivo, arr, &validos);

    ordenacionSeleccionNombre (arr, validos);
    FILE *arch;
    arch = fopen( rutaArchivo,"w");
    if(arch!=NULL)
    {
        while(i<validos)
        {
            aux = arr[i];
            i++;
            fwrite(&aux,sizeof(producto),1, arch);
        }
        fclose(arch);
    }
    else
    {
        printf("Error al abrir el archivo");
    }
}
void  ordenacionSeleccionNombre (producto arr[], int validos)
{
    int posmenor;
    producto aux;
    int i = 0;
    while (i<validos-1)
    {
        posmenor = posicionMenorNombre(arr,i,validos);
        aux = arr[posmenor];
        arr[posmenor]=arr[i];
        arr[i]= aux;
        i++;
    }
}
int posicionMenorNombre(producto arr[], int pos, int validos)
{
    int posmenor = pos;
    int i = pos + 1;
    while (i < validos)
    {
        if (strcmp(arr[i].nombre, arr[posmenor].nombre) < 0)
        {
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}
//ORDENAR POR CODIGO!
void ordenarPorCodigo (char rutaArchivo[])
{
    producto arr[30];
    producto aux;
    int validos=0;
    int i=0;
    archivoAarreglo(rutaArchivo, arr,&validos);
    ordenacionSeleccionCodigo(arr, validos);
    FILE *arch;
    arch = fopen( rutaArchivo,"wb");
    if(arch!=NULL)
    {
        while(i<validos)
        {
            aux = arr[i];
            i++;
            fwrite(&aux,sizeof(producto),1, arch);
        }
        fclose(arch);
    }
    else
    {
        printf("Error al abrir el archivo");
    }
}
int posicionMenorCodigo (producto arr[], int pos, int validos)
{
    int menor = arr[pos].codigo;
    int posmenor = pos;
    int i = pos +1;
    while (i<validos)
    {
        if (menor > arr[i].codigo)
        {
            menor = arr[i].codigo;
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}
void ordenacionSeleccionCodigo (producto arr[], int validos)
{
    int posmenor;
    producto aux;
    int i = 0;
    while (i<validos-1)
    {
        posmenor = posicionMenorCodigo(arr,i,validos);
        aux = arr[posmenor];
        arr[posmenor]=arr[i];
        arr[i]= aux;
        i++;
    }
}

//Funcion para mostrar stock
void mostrarUnCambioStock (stock aux)
{

    puts("\n-----------------------------------------------\n");
    printf("FECHA: %s\n",aux.fecha);
    printf("Se realizo un: %c\n",aux.accion);
    printf("Producto: %s\n",aux.nombre);
    printf("Precio: %f\n",aux.precio);
    printf("cantidad: %i\n",aux.cantidad);
    puts("\n-----------------------------------------------\n");
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
            scanf("%c",&eleccion);


        }
        fclose(arch);
    }
}
void cargastock(stock *aux)
{
    printf("Fecha(00/00/0000):\n");
    fflush(stdin);
    gets(aux->fecha);

    printf("Tipo de accion Egreso o Ingreso:\n");
    fflush(stdin);
    scanf("%c",&aux->accion);

    printf("Nombre del producto:\n");
    fflush(stdin);
    gets(aux->nombre);

    printf("Precio:\n");
    fflush(stdin);
    scanf("%f.2",&aux->precio);

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

//Funcion para mostrar de a un producto
void mostrarUnProducto (producto aux)
{
    puts("\n-----------------------------------------------\n");
    printf("Codigo del producto: %i\n",aux.codigo);
    printf("Nombre: %s\n",aux.nombre);
    printf("Precio de venta: %.2f\n",aux.precio);
    printf("Stock: %i\n",aux.cantidad);
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
void NuevoProducto(producto *productoNuevo)
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
