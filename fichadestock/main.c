#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <string.h>
#include <ctype.h>
#define fila 100
#define col 70

typedef struct
{
    int codigo;
    char nombre[col];
    float precio;
    int cantidad;

} producto;

typedef struct
{
    char accion;// (I O E) (ingreso o egreso)
    char fecha[11]; //(9999/12/31);
    char nombre [col];
    float precio;
    int cantidad;
} stock ;

char nombresArchivos[fila][col];
char archivoProductos[] = "productos.bin";
char archivoStock[] = "fichastock.bin";
void CargarProducto(char archivito[]);
void NuevoProducto(producto *productoNuevo, char producto[]);
void mostrarProductos(char archivito[]);
void mostrarUnProducto(producto aux);
void cargaStock(stock *aux,char producto[]);
void CargarFichaStock(char rutaArchivo[], char producto[]);
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
void CrearArchivo (char nuevoArchivo[col]);
void MatrizAArchivo(char matrix[fila][col],char modo[]);
int contarMatriz(char matriz[fila][col]);
void mostrarArchivosRangos(char rutaArchivo[]);
int crearCodigo();
int buscarXcodigo(char archivito[], int codigoBuscado);
int buscarXcantidad(char nombreArchivo[], int cantidadBuscada);
int buscarXnombre(char nombreArchivo[], char nombrebuscado[]);
void mostrarXposicion(char nombreArchivo[], int posicion);
void pasarAPila(char nombreArchivo[], Pila *pilaOrdenadora );
void imprimirPila(Pila *pilaOrdenadora);
void mostrarCambioStockProducto(char rutaArchivo[]);
void stockCantidadProducto(stock aux,int posicion);
void stockPrecioProducto(stock aux,int posicion);

int main()
{
    int eleccion;
    int buscarPor=0;
    int flag=0;
    int opcion=0;
    char carga;
    int cambio=0;
    char nombre[col];
    char fecha[col];
    char continuar = 's';
    int ordenacionEleccion=0;
    char productoCargar [col];
    char nombreBuscado[fila];
    int posicionNombre;
    int codigoBuscado;
    int posicionCodigo;
    int i=0;
    char usuarioCorrecto[] = "milagros";
    char contraseniaCorrecta[] = "1234";
    Pila pilaOrdenadora;
    inicpila(&pilaOrdenadora);
   do{
    char usuario[20];
    char contrasenia[20];
    printf("Usuario: ");
    scanf("%s", usuario);
    printf("clave: ");
    scanf("%s", contrasenia);
    if (strcmp(usuario, usuarioCorrecto) == 0 && strcmp(contrasenia, contraseniaCorrecta) == 0)
    {

       i=-1;
        printf("******************************\n");
        printf("*        BIENVENIDO          *\n");
        printf("******************************\n");

        do
        {

            printf("\n\n\n----- Ficha de Stock -----\n");
            printf("\nIngrese la opcion que desea realizar:\n");
            printf(" 1. Cargar un Nuevo producto.\n");
            printf(" 2. Cargar Ficha de Stock.\n");
            printf(" 3. Mostrar stock de productos.\n");
            printf(" 4. Mostrar Ficha de stock. \n");
            printf(" 5. Cambiar datos.\n");
            printf(" 6. Buscar.\n");
            printf(" 7. Archivos. \n");
            printf(" 0. Terminar el programa.\n");
            fflush(stdin);
            scanf("%i",&eleccion);

            switch(eleccion)
            {
            case 1:
                CargarProducto(archivoProductos);
                break;
            case 2:
                do
                {
                    printf("Ingrese el nombre del producto a cargar stock: ");
                    fflush(stdin);
                    gets(productoCargar);

                    flag = buscarXnombre(archivoProductos, productoCargar);
                    if(flag==-1)
                    {
                        printf("El producto no se encuentra cargado\n");

                    }
                    else
                    {
                        CargarFichaStock(archivoStock,productoCargar);
                        puts("-----------------------------------");
                        printf("Producto cargado exitosamente!\n");
                        puts("-----------------------------------");
                    }
                    printf("Ingrese 's' si desea seguir cargando\n");
                    fflush(stdin);
                    scanf("%c",&carga);
                }
                while( carga=='s');

                break;
            case 3:
                printf("Mostrar productos organizados por: \n");
                printf(" 1. Codigo.\n");
                printf(" 2. Nombre.\n");
                printf(" 3. Cantidad.\n");
                fflush(stdin);
                scanf("%i",&opcion);
                switch(opcion)
                {
                case 1:
                    puts("----------------------------");
                    printf(" ORDENANDO POR CODIGO.\n");
                    while(ordenacionEleccion!=1 && ordenacionEleccion!=2)
                    {
                        printf(" 1. Ordenar de menor a mayor \n");
                        printf(" 2. Ordenar de mayor a menor\n");
                        fflush(stdin);
                        scanf("%i", &ordenacionEleccion);
                        if(ordenacionEleccion==1)
                        {
                            puts("----------------------------");
                            printf(" ORDENADO DE MENOR A MAYOR.\n");
                            ordenarPorCodigo (archivoProductos);
                            mostrarProductos(archivoProductos);
                        }
                        else if(ordenacionEleccion==2)
                        {
                            puts("----------------------------");
                            printf(" ORDENADO DE MAYOR A MENOR.\n");
                            ordenarPorCodigo(archivoProductos);
                            pasarAPila(archivoProductos, &pilaOrdenadora);
                            imprimirPila(&pilaOrdenadora);
                        }
                        else
                        {
                            printf("No ha ingresado una opcion correcta, Intentelo otra vez.\n");
                        }
                    }
                    ordenacionEleccion=0;

                    puts("----------------------------");

                    break;
                case 2:
                    puts("----------------------------");
                    printf(" ORDENADO POR NOMBRE.\n");
                    ordenarPorNombre(archivoProductos);
                    mostrarProductos(archivoProductos);
                    puts("----------------------------");
                    break;
                case 3:
                    puts("----------------------------");
                    printf(" ORDENADO POR CANTIDAD.\n");
                    ordenarPorCantidad(archivoProductos);
                    mostrarProductos(archivoProductos);
                    puts("----------------------------");
                    break;
                default:
                    printf("Esa opcion no existe, intente otra vez.\n");
                    break;
                }
                break;
            case 4:
                printf("Ingrese el numero de la opcion que desea realizar:\n");
                printf("1. Mostrar todos los cambios de stock\n");
                printf("2. Ver ficha de stock en cierto rango de fechas\n");
                printf("3. Ver ficha de stock por producto\n");
                fflush(stdin);
                scanf("%i",&opcion);
                switch (opcion)
                {
                case 1:

                    printf("----- Stock -----\n");
                    mostrarCambioStock(archivoStock);

                    break;

                case 2:
                    continuar = 's';
                    while (continuar == 's')
                    {
                        RangoFechas (archivoStock);
                        printf("Presione 's' si desea continuar buscando rangos\n");
                        fflush(stdin);
                        scanf("%c",&continuar);
                    }
                    MatrizAArchivo(nombresArchivos,"ab");

                    break;

                case 3:

                    mostrarCambioStockProducto(archivoStock);

                    break;

                default:

                    printf("Esa opcion no existe\n");

                    break;

                }

                break;

            case 5:
                do
                {
                    printf("Desea realizar un cambio en: \n");
                    printf(" 1.La lista de productos.\n");
                    printf(" 2.La ficha de stock.\n");
                    fflush(stdin);
                    scanf("%i",&cambio);
                    if (cambio == 1)
                    {
                        printf("Ingrese el nombre del producto al cual desea cambiarle un dato.\n");
                        fflush(stdin);
                        gets(nombre);
                        modificarDatosProducto(archivoProductos, nombre);

                    }
                    else if(cambio==2)
                    {
                        printf("Ingrese la fecha ingresada en la ficha de stock.\n");
                        fflush(stdin);
                        gets(fecha);
                        printf("Ingrese el producto.\n");
                        fflush(stdin);
                        gets(nombre);
                        modificarDatosStock(archivoStock, nombre,fecha );
                    }
                    else
                    {
                        printf("Opcion ingresada incorrecta, intentelo otra vez\n");
                    }
                }
                while(cambio!=1 && cambio!=2);
                break;
            case 6:
                printf(" Buscar por:\n");
                printf(" 1. Codigo.\n");
                printf(" 2. Nombre.\n");
                fflush(stdin);
                scanf("%i",&buscarPor);
                switch(buscarPor)
                {
                case 1:
                    puts("----------------------------");
                    printf(" BUSCAR POR CODIGO.\n");
                    puts("----------------------------");
                    printf(" Ingrese el codigo a buscar:\n");
                    fflush(stdin);
                    scanf("%i", &codigoBuscado);

                    posicionCodigo=buscarXcodigo(archivoProductos,codigoBuscado);
                    if (posicionCodigo!=-1)
                    {
                        mostrarXposicion(archivoProductos,posicionCodigo);
                    }
                    else
                    {
                        puts("----------------------------");
                        printf("Ese codigo no existe.\n");
                        puts("----------------------------");
                    }

                    puts("----------------------------");
                    break;
                case 2:
                    puts("----------------------------");
                    printf(" BUSCAR POR NOMBRE.\n");
                    puts("----------------------------");
                    printf(" Ingrese el nombre a buscar:\n");
                    fflush(stdin);
                    gets(nombreBuscado);
                    posicionNombre=buscarXnombre(archivoProductos,nombreBuscado);
                    if (posicionNombre!=-1)
                    {
                        mostrarXposicion(archivoProductos,posicionNombre);
                    }
                    else
                    {
                        puts("----------------------------");
                        printf("Ese producto no existe.\n");
                        puts("----------------------------");
                    }

                    puts("----------------------------");
                    break;
                }
                break;


                break;

            case 7:

                mostrarArchivosRangos("ArchivoRangos.bin");

                break;

            default:
                if (eleccion != 0)
                {
                    printf("Esa opcion no existe, intente otra vez.\n");
                }
                break;


            }

        }
        while (eleccion != 0);
    }
    else
    {
        i++;
        if(i<3)
    {  puts("-------------------------------------------");
       printf("Nombre de usuario o clave incorrecto/a.\n");
       puts("--------------------------------------------");
        printf("Intentelo otra vez.\n");
    }
    else
    {
        puts("---------------------------------------------------------------");
        printf("Clave o usuario ingresado incorrectamente demasiadas veces.\n");
        puts("---------------------------------------------------------------");
    }

    }
   } while (i<3&&i!=-1);

    return 0;

}


//Mostrar ficha stock por producto
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

//Elegir que archivo ver
void elegirArchivo(char matrix[fila][col],int validos)
{
    int eleccionVerEliminar;
    int opcion = -1;
    int i = 0;

    printf("Que desea hacer?\n");
    printf("1. Ver un archivo\n");
    printf("2. Eliminar un archivo\n");
    fflush(stdin);
    scanf("%i",&eleccionVerEliminar);

    switch(eleccionVerEliminar)
    {
    case 1:
        printf("Elija el archivo que desea ver\n");
        fflush(stdin);
        scanf("%i",&opcion);

        if (opcion >= 0 && opcion <= validos)
        {

            mostrarCambioStock(matrix[opcion - 1]);

        }
        else
        {

            puts("--------------------------------");
            printf("Esa opcion no existe\n");
            puts("--------------------------------");
        }
        break;

    case 2:

        printf("Elija el archivo que desea eliminar\n");
        fflush(stdin);
        scanf("%i",&opcion);

        if (opcion >= 0 && opcion <= validos)
        {
            remove(matrix[opcion - 1]);


            for(i = opcion - 1; i< validos; i++)
            {

                strcpy(matrix[i],matrix[i+1]);
                strcpy(matrix[validos -1], "");
                MatrizAArchivo(matrix,"wb");
                puts("--------------------------------");
                printf("Archivo eliminado exitosamente\n");
                puts("--------------------------------");

            }
        }
        else
        {

            puts("--------------------------------");
            printf("Esa opcion no existe\n");
            puts("--------------------------------");

        }

        break;
    default:
        printf("Ingreso una opcion que no existe.\n");
        break;

    }
}

//Funcion mostrar arhivo de strings
void mostrarArchivosRangos(char rutaArchivo[])
{
    char matrizAux[fila][col];
    int contador = 0;
    FILE* arch = fopen(rutaArchivo, "rb");

    if (arch == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    else
    {

        size_t longString;
        char aux[fila];
        puts("------------ARCHIVOS-----------");
        while (fread(&longString, sizeof(size_t), 1, arch) == 1)
        {
            fread(aux, sizeof(char), longString, arch);
            aux[longString] = '\0';
            printf("%i:%s\n",(contador + 1),aux);
            strcpy(matrizAux[contador],aux);
            contador ++;
        }
        puts("--------------------------------");
        fclose(arch);
    }
    elegirArchivo(matrizAux,contador);
}

//funcion matriz a archivo
void MatrizAArchivo(char matrix[fila][col],char modo[])
{
    int validos = contarMatriz(matrix);
    int i=0;

    FILE *arch = fopen("ArchivoRangos.bin",modo);

    for(i=0; i<validos; i++)
    {

        size_t longString = strlen(matrix[i]);

        fwrite(&longString, sizeof(size_t), 1, arch);
        fwrite(matrix[i], sizeof(char), longString, arch);

    }

    fclose(arch);

}

//funcion contar elementos matriz
int contarMatriz(char matriz[fila][col])
{

    int flag = 0;
    int contador = 0;
    int i = 0;
    while(flag == 0 && i<fila)
    {

        if(strlen(matriz[i])>0)
        {

            contador++;

        }
        else
        {

            flag = 1;

        }

        i++;

    }

    return contador;

}

//funcion CrearArchivo
void CrearArchivo (char nuevoArchivo[col])
{
    int contadorMatriz = contarMatriz(nombresArchivos);
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
void RangoFechas (char rutaArchivo[])
{

    stock aux;
    char antigua[col];
    char reciente[col];
    char nuevoArchivo[col];
    char eleccionArchivo = 's';
    char eleccionProducto = 's';
    char nombreBuscar[col];

    printf("Fecha mas antigua YYYY/MM/DD:\n");
    fflush(stdin);
    gets(antigua);

    printf("Fecha mas reciente YYYY/MM/DD:\n");
    fflush(stdin);
    gets(reciente);

    printf("Presione 's' si desea filtrar por producto\n");
    fflush(stdin);
    scanf("%c",&eleccionProducto);

    if (eleccionProducto == 's')
    {
        printf("Producto que desea buscar:\n");
        fflush(stdin);
        gets(nombreBuscar);
    }

    printf("Presione 's' si desea guardar el rango en un archivo?\n");
    fflush(stdin);
    scanf("%c",&eleccionArchivo);

    if(eleccionArchivo == 's')
    {

        CrearArchivo(nuevoArchivo);

    }

    FILE *arch = fopen(rutaArchivo,"rb");
    FILE *nuevoArch = fopen(nuevoArchivo,"ab");
    if (arch != NULL)
    {

        while (fread(&aux, sizeof(stock), 1, arch) > 0)
        {
            if (eleccionProducto == 's')
            {

                if ((strcmpi(aux.fecha,antigua) >= 0) && (strcmpi(aux.fecha,reciente) <= 0) && strcmpi(nombreBuscar,aux.nombre) == 0)
                {

                    mostrarUnCambioStock (aux);


                    if(eleccionArchivo == 's')
                    {

                        fwrite(&aux,sizeof(stock),1,nuevoArch);

                    }

                }

            }
            else
            {


                if ((strcmpi(aux.fecha,antigua) >= 0) && (strcmpi(aux.fecha,reciente) <= 0))
                {

                    mostrarUnCambioStock (aux);


                    if(eleccionArchivo == 's')
                    {

                        fwrite(&aux,sizeof(stock),1,nuevoArch);

                    }

                }

            }

        }

        fclose(nuevoArch);
        fclose(arch);

    }

}

//Cambia el precio de productos a partir de entrada/salida de stock
void stockPrecioProducto(stock aux,int posicion){

producto auxProducto;
FILE *arch = fopen(archivoProductos,"r+b");

    if(arch != NULL)
    {

        fseek(arch, posicion * sizeof(producto), SEEK_SET);
        fread(&auxProducto,sizeof(producto),1,arch);
        if (aux.accion == 'I')
        {
            if(auxProducto.precio<(aux.precio*1.21*1.3))
            {


                auxProducto.precio= aux.precio*1.21*1.3;

            }
        }

        fseek(arch, -1* sizeof(producto), SEEK_SET);
        fwrite(&auxProducto,sizeof(producto),1,arch);

    }
    else
    {

        printf("Error: el archivo esta vacio\n");

    }

fclose(arch);






}

//Cambia la cantidad de productos a partir de entrada/salida de stock
void stockCantidadProducto(stock aux,int posicion){

producto auxProducto;
FILE *arch = fopen("productos.bin","r+b");

    if(arch != NULL)
    {

        fseek(arch, posicion * sizeof(producto), SEEK_SET);
        fread(&auxProducto,sizeof(producto),1,arch);

        if (aux.accion == 'I')
        {

            auxProducto.cantidad = auxProducto.cantidad + aux.cantidad;

        }
        else
        {

            auxProducto.cantidad = auxProducto.cantidad - aux.cantidad;

        }
        fseek(arch, posicion * sizeof(producto), SEEK_SET);
        fwrite(&auxProducto,sizeof(producto),1,arch);

    }
    else
    {

        puts("--------------------------------------");
        printf("Error al abrir el archivo\n");
        puts("--------------------------------------");
    }

fclose(arch);

}

//Modificar producto a partir de ficha stock
void ModificarCantidadStock (char rutaArchivo[],stock aux)
{

    int posicion = -1;
    char nombreProducto[col];
    strcpy(nombreProducto,aux.nombre);

    posicion = buscarXnombre("productos.bin",nombreProducto);
    stockCantidadProducto(aux,posicion);
    stockPrecioProducto(aux,posicion);

}

//fUNCION PARA CAMBIAR CIERTO DATO EN STOCK CARGADO
void modificarDatosStock(char rutaArchivo[], char nombre[],char fecha[] )
{
    FILE *arch;
    stock aux;
    int flag=0;

    arch = fopen(rutaArchivo, "r+b");
    if (arch == NULL)
    {
        puts("--------------------------------------");
        printf("Error al abrir el archivo\n");
        puts("--------------------------------------");
        return;
    }

    while (fread(&aux, sizeof(stock), 1, arch) == 1)
    {
        if (strcasecmp(nombre, aux.nombre) == 0 && strcasecmp(fecha, aux.fecha) == 0)
        {
            cambiarStock(&aux);
            fseek(arch, -sizeof(stock), SEEK_CUR);
            fwrite(&aux, sizeof(stock), 1, arch);
            puts("--------------------------------------");
            printf("Registro modificado exitosamente.\n");
            puts("--------------------------------------");
            break;
        }
    }

    fclose(arch);
    if(flag==0)
    {
        puts("--------------------------------------------------");
        printf("No se encontro esa fecha y producto en el archivo.\n");
        puts("--------------------------------------------------");
    }
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

//FUNCION PARA CAMBIAR CIERTO DATO EN STOCK CARGADO
void modificarDatosProducto(char rutaArchivo[], char nombre[])
{
    FILE *arch;
    producto aux;
    int flag=0;

    arch = fopen(rutaArchivo, "r+b");
    if (arch == NULL)
    {
        puts("--------------------------------------");
        printf("Error al abrir el archivo\n");
        puts("--------------------------------------");
        return;
    }

    while (fread(&aux, sizeof(producto), 1, arch) == 1)
    {
        if (strcasecmp(nombre, aux.nombre) == 0)
        {
            cambiarProducto(&aux);
            fseek(arch, -sizeof(producto), SEEK_CUR);
            fwrite(&aux, sizeof(producto), 1, arch);
            puts("--------------------------------------");
            printf("Registro modificado exitosamente.\n");
            puts("--------------------------------------");
            flag=1;
            break;
        }


    }

    fclose(arch);
    if(flag==0)
    {
        puts("--------------------------------------");
        printf("El producto ingresado no existe.\n");
        puts("--------------------------------------");
    }
}

void cambiarProducto(producto *aux)
{
    int eleccion;

    printf("\nIngrese el numero de la opcion que desea cambiar o 0 para terminar \n");
    printf(" 1.Codigo.\n");
    printf(" 2.Nombre.\n");
    printf(" 3.Precio.\n");
    printf(" 4.Cantidad.\n");
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
    default:
         printf("Ingreso una opcion incorrecta.\n");
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
        puts("--------------------------------------");
        printf("Error al abrir el archivo\n");
        puts("--------------------------------------");
    }
}

//ORDENAR POR Cantidad!
void ordenarPorCantidad (char rutaArchivo[])
{
    producto arr[fila];
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
        puts("--------------------------------------");
        printf("Error al abrir el archivo\n");
        puts("--------------------------------------");
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
    producto arr[fila];
    producto aux;
    int validos=0;
    int i=0;
    archivoAarreglo(rutaArchivo, arr, &validos);

    ordenacionSeleccionNombre (arr, validos);
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
        puts("--------------------------------------");
        printf("Error al abrir el archivo\n");
        puts("--------------------------------------");
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
    producto arr[fila];
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
        puts("--------------------------------------");
        printf("Error al abrir el archivo\n");
        puts("--------------------------------------");
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

// MOSTRAR UN STOCK
void mostrarUnCambioStock (stock aux)
{
    puts("\n-----------------------------------------------\n");
    printf("FECHA: %s\n",aux.fecha);
    printf("Se realizo un: %c\n",aux.accion);
    printf("Producto: %s\n",aux.nombre);
    printf("Precio: %.2f\n",aux.precio);
    printf("cantidad: %i\n",aux.cantidad);
    puts("\n-----------------------------------------------\n");
}

//FUNCION PARA MOSTRAR TODOS LOS  DATOS DE STOCK
void mostrarCambioStockProducto(char rutaArchivo[])
{
    stock aux;
    char nombre[fila];
    int flag=0;
    printf("Que producto desea buscar\n");
    fflush(stdin);
    gets(nombre);
    FILE *arch;

    arch=fopen(rutaArchivo,"rb");

    if(arch!=NULL)
    {
        while(!feof(arch))
        {
            fread(&aux,sizeof(stock),1,arch);
            if(!feof(arch))
            {
                if(strcmpi(aux.nombre,nombre)==0)
                {
                    mostrarUnCambioStock(aux);
                    flag=1;
                }
            }

        }
        fclose(arch);
    }
    if(flag==0)
    {
        puts("-----------------------------------------------------------------");
        printf("No se encontro ingresos o egresos en la ficha de ese producto\n");
        puts("-----------------------------------------------------------------");
    }
}

//CARGAR FICHA DE STOCK
void CargarFichaStock(char rutaArchivo[], char producto[])
{

    stock aux;
    FILE *arch;

    arch = fopen(rutaArchivo,"ab");

    if(arch != NULL)
    {

        cargaStock(&aux, producto);
        fwrite(&aux, sizeof(stock), 1, arch);

        ModificarCantidadStock(rutaArchivo,aux);

        fclose(arch);
    }
}

//CARGAR UN DATO DE STOCK
void cargaStock(stock *aux,char nombreProducto[])
{
    printf("Fecha(YYYY/MM/DD):\n");
    fflush(stdin);
    gets(aux->fecha);

    printf("Tipo de accion:\n'E' para egreso\n'I'para ingreso\n");
    fflush(stdin);
    scanf("%c",&aux->accion);
    aux->accion = toupper(aux->accion);


    printf("Nombre del producto: %s\n",nombreProducto);
    strcpy(aux->nombre,nombreProducto);

    if(aux->accion == 'E')
    {

        producto auxiliar;
        FILE *arch = fopen("productos.bin","rb");
        int pos = buscarXnombre("productos.bin",nombreProducto);
        fseek(arch,pos * sizeof(producto),SEEK_SET);
        fread(&auxiliar,sizeof(producto),1,arch);
        aux->precio = auxiliar.precio;
        fclose(arch);
        printf("Precio de venta:%.2f\n",aux->precio);
    }
    else
    {

        printf("Precio de compra:\n");
        fflush(stdin);
        scanf("%f.2",&aux->precio);

    }

    printf("Cantidad:\n");
    fflush(stdin);
    scanf("%i",&aux->cantidad);

}

//FUNCION PARA MOSTRAR TODOS LOS PRODUCTOS
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

//FUNCION PARA MOSTRAR DE A UN PRODUCTO
void mostrarUnProducto (producto aux)
{
    puts("\n-----------------------------------------------\n");
    printf("Codigo del producto: %04i\n",aux.codigo);
    printf("Nombre: %s\n",aux.nombre);
    printf("Precio de venta: %.2f\n",aux.precio);
    printf("Stock: %i\n",aux.cantidad);
    puts("\n-----------------------------------------------\n");
}

// CARGAR CANTIDAD DESEADA DE UN PRODUCTO
void CargarProducto(char rutaArchivo[])
{

    char eleccion = 's';
    producto aux;
    FILE *arch;


    while(eleccion == 's')
    {
        int flag=0;
        char productoCargar[30];

        printf("Ingrese el nombre del producto a cargar: ");
        fflush(stdin);
        gets(productoCargar);
        flag = buscarXnombre(archivoProductos, productoCargar);
        if(flag!=-1)
        {
            puts("--------------------------------------");
            printf("El producto ya existe.\n");
            puts("--------------------------------------");

        }
        else
        {
            arch = fopen(rutaArchivo,"ab");
            if(arch != NULL)

            {
                NuevoProducto(&aux,productoCargar);
                fwrite(&aux, sizeof(producto), 1, arch);
                fclose(arch);
                puts("-----------------------------------");
                printf("Producto cargado exitosamente!\n");
                puts("-----------------------------------");

            }

        }
        printf("si desea seguir cargando escriba 's'\n");
        fflush(stdin);
        scanf("%c",&eleccion);
        eleccion = tolower(eleccion);

    }
}
// CARGAR UN PRODUCTO
void NuevoProducto(producto *productoNuevo, char productoN[])
{

    productoNuevo->codigo = crearCodigo();
    printf("Codigo asignado al producto es: %04i\n", productoNuevo->codigo);

    printf("Nombre del producto:%s\n",productoN);
    strcpy(productoNuevo->nombre,productoN);

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
    FILE *archi = fopen(nombreArchivo,"rb");
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
                if(strcmpi(aux.nombre,nombreBuscado)==0)
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
    FILE *archi;
    archi=fopen(nombreArchivo,"rb");
    producto aux;

    if(archi!=NULL)
    {

        fseek(archi,sizeof(producto)*posicion,SEEK_SET);
        fread(&aux, sizeof(producto),1,archi);
        if(!feof(archi))
        {
            mostrarUnProducto(aux);
        }

        fclose(archi);
    }
    else
    {
        puts("--------------------------------------");
        printf("Error al abrir el archivo\n");
        puts("--------------------------------------");  //lucreciadenisebazan@gmail.com
    }
}

//PASAR DE ARCHIVO A PILA (UNA VEZ ORDENADO)
void pasarAPila(char nombreArchivo[], Pila *pilaOrdenadora)
{

    FILE *archi=fopen(nombreArchivo,"rb");
    producto aux;

    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(producto),1,archi)>0)
        {

            apilar(pilaOrdenadora,aux.codigo);

        }


    }
    fclose(archi);
}

void imprimirPila(Pila *pilaOrdenadora)
{
    while(!pilavacia(pilaOrdenadora))
    {
        int posicionCodigo=buscarXcodigo(archivoProductos,tope(pilaOrdenadora));
        mostrarXposicion(archivoProductos, posicionCodigo);
        desapilar(pilaOrdenadora);
    }
}

//FUNCION QUE CREA EL CODIGO
int crearCodigo()
{
    int codigoNuevo;
    producto aux;
    ordenarPorCodigo(archivoProductos);

    FILE *archi = fopen(archivoProductos, "rb");
    if (archi != NULL)
    {
        fseek(archi, 0, SEEK_END);
        if (ftell(archi) == 0)
        {
            codigoNuevo = 1;
        }
        else
        {
            fseek(archi, -1 *sizeof(producto), SEEK_END);
            fread(&aux, sizeof(producto), 1, archi);
            codigoNuevo = aux.codigo + 1;
        }


    }
    fclose(archi);
    return codigoNuevo;

}
