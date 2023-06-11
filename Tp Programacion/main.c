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

char nombresArchivos[100][30];


void CargarProducto(char archivito[]);
void NuevoProducto(producto *productoNuevo);
void mostrarProductos(char archivito[]);
void mostrarUnProducto(producto aux);
void cargaStock(stock *aux);
void CargarFichaStock(char rutaArchivo[]);
void mostrarUnCambioStock (stock aux);
void mostrarCambioStock(char rutaArchivo[]);
void archivoAarreglo(char rutaArchivo[], producto arr[],int *validos);
void ordenacionSeleccionCodigo (producto arr[], int validos);
int posicionMenorCodigo (producto arr[], int pos, int validos);
void ordenarPorCodigo (char rutaArchivo[]);                     // por codigo
int posicionMenorNombre (producto arr[], int pos, int validos);
void ordenacionSeleccionNombre (producto arr[], int validos);
void ordenarPorNombre (char rutaArchivo[]);                     //por nombre
void ordenacionSeleccionCantidad (producto arr[], int validos);
int posicionMenorCantidad (producto arr[], int pos, int validos);
void ordenarPorCantidad (char rutaArchivo[]);                   // por cantidad
void cambiarProducto(producto *aux);
void modificarDatosProducto(char rutaArchivo[], char nombre[]);
void cambiarStock (stock *aux);
void modificarDatosStock(char rutaArchivo[], char nombre[],char fecha[] );
void RangoFechas (char rutaArchivo[]);
void CrearArchivo (char nuevoArchivo[30]);
int contarMatriz();
void MatrizAArchivo();

// mi parte: buscar prod por codigo nombre y cantidad, funcion para pasar a una pila el precio de un articulo q ingreso su cantidad
int buscarXcodigo(char archivito[], int codigoBuscado);
int buscarXcantidad(char nombreArchivo[], int cantidadBuscada);
int buscarXnombre(char nombreArchivo[], char nombrebuscado[]);
void mostrarXposicion(char nombreArchivo[], int posicion);

void pasarAPila(char nombreArchivo[], Pila *pilaOrdenadora );


int main()
{
    int eleccion;
    int ordenarPor=0;
    int buscarPor=0;
    char nombre[30];
    char fecha[30];
    Pila pilaOrdenadora;
    inicpila(&pilaOrdenadora);

    do
    {
        printf("\nIngrese la opcion que desea realizar \n");
        printf(" 0. Terminar el programa\n");
        printf(" 1. Cargar un producto \n");
        printf(" 2. cargar ficha de stock \n");
        printf(" 3. mostrar productos y archivo de stock\n");
        printf(" 4. ordenar lista de productos\n");
        printf(" 5. cambiar un dato del producto\n");
        printf(" 6. cambiar datos de la ficha de stock\n");
        printf(" 7. Buscar y mostrar productos\n");
        printf(" 8.Crear archivo con rangos\n");
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
            scanf("%i",&ordenarPor);
            switch(ordenarPor)
            {
            case 1:
                puts("----------------------------");
                printf(" ORDENADO POR CODIGO.\n");
                int ordenacionEleccion;
                printf("Elija 1 para ordenar de mayor a menor o 0 para ordenar de menor a mayor");
                fflush(stdin);
                scanf("%i", ordenacionEleccion);
                if(ordenacionEleccion==1)
                {
                ordenarPorCodigo ("productos.bin");
                mostrarProductos("productos.bin");
                }else{
                ordenarPorCodigo("productos.bin");
                pasarAPila("productos.bin", &pilaOrdenadora);
                }

                puts("----------------------------");
                break;
            case 2:
                puts("----------------------------");
                printf(" ORDENADO POR NOMBRE.\n");
                ordenarPorNombre ("productos.bin");
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
            printf("Ingrese el nombre del producto al cual desea cambiarle un dato.\n");
            fflush(stdin);
            gets(nombre);
            modificarDatosProducto("productos.bin", nombre);

            break;
        case 6:
            printf("Ingrese la fecha ingresada en la ficha de stock.\n");
            fflush(stdin);
            gets(fecha);
            printf("Ingrese el producto.\n");
            fflush(stdin);
            gets(nombre);
            modificarDatosStock("fichastock.bin", nombre,fecha );
            break;
        case 7:
            printf(" Buscar por(:\n");
            printf(" 1. Codigo.\n");
            printf(" 2. Nombre.\n");
            fflush(stdin);
            scanf("%i",&buscarPor);
            switch(buscarPor)
            {
            case 1:
                puts("----------------------------");
                printf(" BUSCAR POR CODIGO.\n");
                int codigoBuscado;
                int posicionCodigo;
                printf(" Ingrese el codigo a buscar:\n");
                fflush(stdin);
                scanf("%i", &codigoBuscado);
                posicionCodigo=buscarXcodigo("productos.bin",codigoBuscado);
                mostrarXposicion("productos.bin",posicionCodigo);
                puts("----------------------------");
                break;
            case 2:
                puts("----------------------------");
                printf(" BUSCAR POR NOMBRE.\n");
                char nombreBuscado[20];
                int posicionNombre;
                printf(" Ingrese el nombre a buscar:\n");
                fflush(stdin);
                gets(nombreBuscado);
                posicionNombre=buscarXnombre("productos.bin",nombreBuscado);
                mostrarXposicion("productos.bin",posicionNombre);
                puts("----------------------------");
                break;
            }
            break;
        case 8:
            //while
            RangoFechas ("fichastock.bin");

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

//funcion matriz a archivo
void MatrizAArchivo(){
int validos = contarMatriz();
int i=0;
FILE *arch = fopen("ArchivoRangos.bin","ab");

for( i = 0;i<validos;i++){
   fwrite(&nombresArchivos[i],sizeof(char),1,arch);
}

fclose(arch);

}

//funcion contar elementos matriz
int contarMatriz(){

int flag = 0;
int contador = 0;
int i = 0;
while(flag == 0){

  if(strlen(nombresArchivos[i])>0){

    contador++;

  }else{

     flag = 1;

  }

  i++;

}
return contador;
}

//funcion CrearArchivo
void CrearArchivo (char nuevoArchivo[30]){
int contadorMatriz = contarMatriz();
char extension []=".bin";

printf("Nombre del nuevo archivo\n");
fflush(stdin);
gets(nuevoArchivo);
strcat(nuevoArchivo,extension);

strcpy(nombresArchivos[contadorMatriz],nuevoArchivo);
contadorMatriz++;

printf("Nuevo archivo creado llamado : %s\n",nuevoArchivo);

}
//datos de un determinado periodo
void RangoFechas (char rutaArchivo[]){

stock aux;
char antigua[30];
char reciente[30];
char nuevoArchivo[30];
char eleccion = 's';

printf("Fecha mas antigua YYYY/MM/DD:\n");
fflush(stdin);
gets(antigua);

printf("Fecha mas reciente YYYY/MM/DD:\n");
fflush(stdin);
gets(reciente);

printf("Desea guardar el rango en un archivo?\n");
fflush(stdin);
scanf("%c",&eleccion);
if(eleccion == 's'){

   CrearArchivo(nuevoArchivo);

}

FILE *arch = fopen(rutaArchivo,"rb");
FILE *nuevoArch = fopen(nuevoArchivo,"ab");
if (arch != NULL){

    while (fread(&aux, sizeof(stock), 1, arch) > 0){

           if (aux.fecha > antigua && aux.fecha < reciente){

              mostrarUnCambioStock (aux);

                 if(eleccion == 's'){

                 fwrite(&aux,sizeof(stock),1,nuevoArch);

                 }

           }

    }
fclose(nuevoArch);
fclose(arch);


}

}

//Modificar cantidad de producto en stock
void ModificarCantidadStock (char rutaArchivo[],stock aux){

int posicion = -1;
producto auxProducto;
char nombreProducto[30];
strcpy(nombreProducto,aux.nombre);

posicion = buscarXnombre("productos.bin",nombreProducto);

FILE *arch = fopen("productos.bin","r+b");

if(arch != NULL){

    fseek(arch, posicion * sizeof(producto) , SEEK_SET);
    fread(&auxProducto,sizeof(producto),1,arch);

       if (aux.accion == 'I'){

           auxProducto.cantidad = auxProducto.cantidad + aux.cantidad;

       }else{

          auxProducto.cantidad = auxProducto.cantidad - aux.cantidad;

       }
      fseek(arch, posicion * sizeof(producto) , SEEK_SET);
      fwrite(&auxProducto,sizeof(producto),1,arch);

}else{

   printf("Error: el archivo esta vacio\n");

}

fclose(arch);

}

//fUNCION PARA CAMBIAR CIERTO DATO EN STOCK CARGADO
void modificarDatosStock(char rutaArchivo[], char nombre[],char fecha[] )
{
    FILE *arch;
    stock aux;

    arch = fopen(rutaArchivo, "r+b");
    if (arch == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    while (fread(&aux, sizeof(stock), 1, arch) == 1)
    {
        if (strcasecmp(nombre, aux.nombre) == 0 && strcasecmp(fecha, aux.fecha) == 0)
        {
            cambiarStock(&aux);
            fseek(arch, -sizeof(stock), SEEK_CUR);
            fwrite(&aux, sizeof(stock), 1, arch);
            printf("Registro modificado exitosamente.\n");
            break;
        }
        else
        {
            printf("No se encontro esa fecha y producto en el archivo.\n");
            break;
        }
    }

    fclose(arch);
}

void cambiarStock(stock *aux)
{
    int eleccion;

    printf("\nIngrese el numero de la opcion que desea cambiar o 0 para terminar \n");
    printf(" 1.Fecha.\n");
    printf(" 2.Accion.\n");
    printf(" 3.Nombre producto.\n");
    printf(" 4.Precio.\n");
    printf(" 5.Cantidad.\n");
    fflush(stdin);
    scanf("%i",&eleccion);
    printf("Modificando:\n");
    switch (eleccion)
    {
    case 1:
        printf("Fecha:\n");
        fflush(stdin);
        gets(aux->fecha);
        break;
    case 2:
        printf("Accion('I' para ingreso O 'E' para egreso): \n");
        fflush(stdin);
        scanf("%c", &aux->accion);
        break;
    case 3:
        printf("Nombre producto: \n");
        fflush(stdin);
        gets(aux->nombre);
        break;
    case 4:
        printf("Precio: \n");
        fflush(stdin);
        scanf("%f",&aux->precio);
        break;
    case 5:
        printf("Cantidad: \n");
        fflush(stdin);
        scanf("%i", &aux->cantidad);
        break;


    }


}

//fUNCION PARA CAMBIAR CIERTO DATO EN STOCK CARGADO
void modificarDatosProducto(char rutaArchivo[], char nombre[])
{
    FILE *arch;
    producto aux;

    arch = fopen(rutaArchivo, "r+b");
    if (arch == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    while (fread(&aux, sizeof(producto), 1, arch) == 1)
    {
        if (strcasecmp(nombre, aux.nombre) == 0)
        {
            cambiarProducto(&aux);
            fseek(arch, -sizeof(producto), SEEK_CUR);  // Mover el puntero de lectura/escritura al inicio del registro
            fwrite(&aux, sizeof(producto), 1, arch);
            printf("Registro modificado exitosamente.\n");
            break;
        }
    }

    fclose(arch);
}

void cambiarProducto(producto *aux)
{
    int eleccion;

    printf("\nIngrese el numero de la opcion que desea cambiar o 0 para terminar \n");
    printf(" 1.Codigo.\n");
    printf(" 2.Nombre.\n");
    printf(" 3.precio.\n");
    fflush(stdin);
    scanf("%i",&eleccion);
    switch (eleccion)
    {
    case 1:
        printf("Modificando Codigo\n");
        fflush(stdin);
        scanf("%i", &aux->codigo);
        break;
    case 2:
        printf("Modificando Nombre\n");
        fflush(stdin);
        gets(aux->nombre);
        break;
    case 3:
        printf("Modificando precio\n");
        fflush(stdin);
        scanf("%f",&aux->precio);
        break;
    case 4:
        printf("Modificando cantidad\n");
        fflush(stdin);
        scanf("%i", &aux->cantidad);
        break;

    }


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
void ordenarPorNombre (char rutaArchivo[])
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

void ordenacionSeleccionNombre (producto arr[], int validos)
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

            cargaStock(&aux);
            fwrite(&aux, sizeof(stock), 1, arch);

            ModificarCantidadStock(rutaArchivo,aux);

            printf("si desea seguir cargando escriba 's'\n");
            fflush(stdin);
            scanf("%c",&eleccion);


        }
        fclose(arch);
    }
}

void cargaStock(stock *aux)
{
    printf("Fecha(YYYY/MM/DD):\n");
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

//BUSCAR POR CODIGO DEVUELVE POSICION
int buscarXcodigo(char nombreArchivo[], int codigoBuscado)
{
    FILE *archi=fopen(nombreArchivo,"rb");
                producto aux;
                int flag=0;
                int posicion=-1;
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            if(!feof(archi))
            {
                fread(&aux,sizeof(producto),1,archi);
                if(aux.codigo==codigoBuscado)
                    {
                    flag=1;
                    break;
                    }
            }
        }

        if (flag==1)
        {
            posicion=ftell(archi)/sizeof(producto)-1;
        }
        fclose(archi);

    }
    return posicion;
}

//BUSCAR POR NOMBRE DEVUELVE POSICION
int buscarXnombre(char nombreArchivo[], char nombreBuscado[])
{
    FILE *archi=fopen(nombreArchivo,"rb");
                producto aux;
                int flag=0;
                int posicion=-1;
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            if(!feof(archi))
            {
                fread(&aux,sizeof(producto),1,archi);
                if(strcmp(aux.nombre,nombreBuscado)==0)
                    {
                    flag=1;
                    break;
                    }
            }
        }

        if (flag==1)
        {
            posicion=ftell(archi)/sizeof(producto)-1;
        }
        fclose(archi);

    }
    return posicion;
}

//MOSTRAR POR POSICION
void mostrarXposicion(char nombreArchivo[], int posicion)
{
    FILE *archi=fopen(nombreArchivo,"rb");
    producto aux;

    if(archi!=NULL)
    {
        fseek(archi,sizeof(producto)*posicion,SEEK_SET);
        fread(&aux, sizeof(producto),1,archi);

        mostrarUnProducto(aux);
        fclose(archi);
    }
}

//PASAR DE ARCHIVO A PILA (UNA VEZ ORDENADO)
void pasarAPila(char nombreArchivo[], Pila *pilaOrdenadora)
{

    FILE *archi=fopen(nombreArchivo,"rb");
    producto aux;

    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&aux,sizeof(producto),1,archi);
            apilar(&pilaOrdenadora,aux.codigo);
        }
fclose(archi);

    }
}
void imprimirPila(Pila *pilaOrdenadora)
{
    while(!pilavacia(pilaOrdenadora))
    {
        int posicionCodigo=buscarXcodigo("productos.bin",tope(pilaOrdenadora));
        mostrarXposicion("productos.bin", posicionCodigo);
        desapilar(pilaOrdenadora);
    }
}
