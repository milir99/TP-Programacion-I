#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <string.h>
#include <ctype.h>


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
    char fecha[11]; //(9999/12/31);
    char nombre [30];
    float precio;
    int cantidad;
} stock ;

char nombresArchivos[100][30];
char archivoProductos[] = "productos.bin";
char archivoStock[] = "fichastock.bin";


void CargarProducto(char archivito[]);
void NuevoProducto(producto *productoNuevo);
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
void CrearArchivo (char nuevoArchivo[30]);
void MatrizAArchivo(char matrix[100][30],char modo[]);
int contarMatriz(char matriz[100][30]);
void mostrarArchivosRangos(char rutaArchivo[]);
int crearCodigo();
int buscarXcodigo(char archivito[], int codigoBuscado);
int buscarXcantidad(char nombreArchivo[], int cantidadBuscada);
int buscarXnombre(char nombreArchivo[], char nombrebuscado[]);
void mostrarXposicion(char nombreArchivo[], int posicion);
void pasarAPila(char nombreArchivo[], Pila *pilaOrdenadora );
void imprimirPila(Pila *pilaOrdenadora);


int main()
{
    int eleccion;
    int buscarPor=0;
    int flag=0;
    int opcion=0;
    char carga;
    int cambio=0;
    char nombre[30];
    char fecha[30];
    char continuar = 's';
    int ordenacionEleccion=0;
    char productoCargar [30];

    char usuarioCorrecto[] = "milagros";
    char contraseniaCorrecta[] = "1234";
    Pila pilaOrdenadora;
    inicpila(&pilaOrdenadora);

    char usuario[20];
    char contrasenia[20];
    printf("Usuario: ");
    scanf("%s", usuario);
    printf("clave: ");
    scanf("%s", contrasenia);
    if (strcmp(usuario, usuarioCorrecto) == 0 && strcmp(contrasenia, contraseniaCorrecta) == 0)
    {


        printf("******************************\n");
        printf("*        BIENVENIDO          *\n");
        printf("******************************\n");

        do
        {

            printf("\n----- Ficha de Stock -----\n");
            printf("\nIngrese la opcion que desea realizar:\n");
            printf(" 1. Cargar un Nuevo producto.\n");
            printf(" 2. Cargar Ficha de Stock.\n");//chequear si queremos que cargue al stock igual o solo al producto
            printf(" 3. Mostrar stock.\n");// MOSTRAR ARCH PROD POR CODIGO POR NOMBRE Y POR CANTIDAD
            printf(" 4. Mostrar Ficha de stock. \n");// MOSTRAR ARCH stock  POR articulo
            printf(" 5. Cambiar datos.\n"); // opcion para que sea en la ficha de stock o en la ficha de productos
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
                printf("Ingrese el nombre del producto a cargar stock: ");
                fflush(stdin);
                gets(productoCargar);

                flag = buscarXnombre(archivoProductos, productoCargar);
                if(flag==-1)
                {
                    printf("El producto no se encuentra cargado\n");
                    printf("Ingres 's' si desea cargarlo\n");
                    fflush(stdin);
                    scanf("%c",&carga);
                    if (carga == 's')
                    {
                        CargarProducto(archivoProductos);
                    }
                }
                else
                {
                    CargarFichaStock(archivoStock,productoCargar);
                }
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
                printf("----- Stock -----\n");
                mostrarCambioStock(archivoStock);
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
                        printf("Opcion inresada incorrecta, intentelo otra vez");
                    }
                }
                while(cambio!=1 && cambio!=2);
                break;
            case 6:
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
                    posicionCodigo=buscarXcodigo(archivoProductos,codigoBuscado);
                    mostrarXposicion(archivoProductos,posicionCodigo);
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
                    posicionNombre=buscarXnombre(archivoProductos,nombreBuscado);
                    mostrarXposicion(archivoProductos,posicionNombre);
                    puts("----------------------------");
                    break;
                }
                break;


            break;
        case 7:
            printf("Ingrese el numero de la opcion que desea realizar:\n");
            printf(" 1. Ver ficha de stock en cierto rango de fechas\n");
            printf(" 2. Mostrar archivos guardados\n");
            printf(" 3. \n");
            fflush(stdin);
            scanf("%i",&opcion);
            switch (opcion){

                case 1:
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

                case 2:

                    mostrarArchivosRangos("ArchivoRangos.bin");

                    break;

                case 3:



                    break;
                }

                break;
            case 10:

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
        printf("Nombre de usuario o clave incorrecto/a.\n");
    }

    return 0;

}

//Elegir que archivo ver
void elegirArchivo(char matrix[100][30],int validos)
{
    int eleccionVerEliminar;
    int opcion = -1;
    int i = 0;

    printf("Que desea hacer\n");
    printf("1. Ver un archivo\n");
    printf("2. Eliminar un archivo\n");
    fflush(stdin);
    scanf("%i",&eleccionVerEliminar);
    switch(eleccionVerEliminar){
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


               printf("Esa opcion no existe\n");

          }
       break;

       case 2:

          printf("Elija el archivo que desea eliminar\n");
          fflush(stdin);
          scanf("%i",&opcion);

          if (opcion >= 0 && opcion <= validos)
          {
              remove(matrix[opcion - 1]);


              for(i = opcion - 1;i< validos;i++){

                strcpy(matrix[i],matrix[i+1]);
                strcpy(matrix[validos -1], "");
                MatrizAArchivo(matrix,"wb");


              }
          }
           else
          {


               printf("Esa opcion no existe\n");

          }




        break;





     }
}

//Funcion mostrar arhivo de strings
void mostrarArchivosRangos(char rutaArchivo[])
{
    char matrizAux[100][30];
    int contador = 0;
    FILE* arch = fopen(rutaArchivo, "rb");

    if (arch == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    size_t longString;
    char aux[100];

    while (fread(&longString, sizeof(size_t), 1, arch) == 1)
    {
        fread(aux, sizeof(char), longString, arch);
        aux[longString] = '\0';
        printf("%i:%s\n",(contador + 1),aux);
        strcpy(matrizAux[contador],aux);
        contador ++;
    }
    fclose(arch);
    elegirArchivo(matrizAux,contador);
}

//funcion matriz a archivo
void MatrizAArchivo(char matrix[100][30],char modo[])
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
int contarMatriz(char matriz[100][30])
{

    int flag = 0;
    int contador = 0;
    int i = 0;
    while(flag == 0 && i<100)
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
void CrearArchivo (char nuevoArchivo[30])
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
    char antigua[30];
    char reciente[30];
    char nuevoArchivo[30];
    char eleccionArchivo = 's';
    char eleccionProducto = 's';
    char nombreBuscar[30];

    printf("Fecha mas antigua YYYY/MM/DD:\n");
    fflush(stdin);
    gets(antigua);

    printf("Fecha mas reciente YYYY/MM/DD:\n");
    fflush(stdin);
    gets(reciente);

    printf("Presione 's' si desea filtrar por producto\n");
    fflush(stdin);
    scanf("%c",&eleccionProducto);

    if (eleccionProducto == 's'){
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

                if ((strcmp(aux.fecha,antigua) >= 0) && (strcmp(aux.fecha,reciente) <= 0) && strcmpi(nombreBuscar,aux.nombre) == 0)
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


                if ((strcmp(aux.fecha,antigua) >= 0) && (strcmp(aux.fecha,reciente) <= 0))
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

//Modificar cantidad de producto en stock
void ModificarCantidadStock (char rutaArchivo[],stock aux)
{

    int posicion = -1;
    producto auxProducto;
    char nombreProducto[30];
    strcpy(nombreProducto,aux.nombre);

    posicion = buscarXnombre("productos.bin",nombreProducto);

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

//FUNCION PARA CAMBIAR CIERTO DATO EN STOCK CARGADO
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
        if (strcmpi(arr[i].nombre, arr[posmenor].nombre) < 0)
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

// MOSTRAR UN STOCK
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

//FUNCION PARA MOSTRAR TODOS LOS  DATOS DE STOCK
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
void cargaStock(stock *aux,char producto[])
{
    printf("Fecha(YYYY/MM/DD):\n");
    fflush(stdin);
    gets(aux->fecha);

    printf("Tipo de accion Egreso o Ingreso:\n");
    fflush(stdin);
    scanf("%c",&aux->accion);
    aux->accion = toupper(aux->accion);


    printf("Nombre del producto: %s\n",producto);
    strcpy(aux->nombre,producto);

    printf("Precio:\n");
    fflush(stdin);
    scanf("%f.2",&aux->precio);

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
        arch = fopen(rutaArchivo,"ab");

        if(arch != NULL)
        {

            NuevoProducto(&aux);
            fwrite(&aux, sizeof(producto), 1, arch);
            printf("si desea seguir cargando escriba 's'\n");
            fflush(stdin);
            scanf("%c",&eleccion);
            eleccion = tolower(eleccion);


            fclose(arch);
        }



    }
}

// CARGAR UN PRODUCTO
void NuevoProducto(producto *productoNuevo)
{

    productoNuevo->codigo = crearCodigo();
    printf("Codigo asignado al producto es: %04i\n", productoNuevo->codigo);

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
            apilar(pilaOrdenadora,aux.codigo);
        }
        fclose(archi);

    }
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
