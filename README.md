# Programacion
trabajo practico programacion 1
Done:
---------------------------------
Estructura Productos
Cargar productos-- void CargarProducto(char archivito[]);
funcion cargar un  producto-- void NuevoProducto(producto productoNuevo);
mostrar productos -- void mostrarProductos(char archivito[]);
funcion mostrar un producto -- void mostrarUnProducto( producto aux);
---------------------------------
Estructuras:
Productos
Stock (cantidad, fecha, producto,precio)
Funciones:
-Ordenar por : Codigo
              Nombre
              Cantidad
-Edicion de dato del producto.
- Buscar producto : Codigo
                    Nombre
                    cantidad
 Sacar ganacias por producto.
 Sacar ganancias del mes/año.
 sacar ingresos del mes/año.
 sacar costos del mes/año.
 cargar impuestos.
 -Cargar stock.
 -Sacar stock.
 -Cambios en el stock (por fecha, por producto)
 - pasar datos de stock del periodo deseado  a un nuevo archivo con el nombre que quiers en ususariio y poner ese nombre en una matriz.
 Matrices:
 -Guardar nombres de archivos que crea el usuario para guardar ciertos datos en el cambio de la ficha de stock.
 Punteros:
 RECORDAR USARLOS EN PILAS O VER OTRO LUGAR DONDE NOS SIRVA.
 
COSAS QUE VAN EN EL SWITCH:
-1.Cargar Productos/ cargar producto nuevo.
-2. Mostrar productos ordenados ( EN EL CASE VA OTRO SWITCH PARA ELEGIR COMO QUIERE QUE ESTE ORDENADO.)
-3. Cambio de stock:( SWITCH PARA CARGA Y DESCARGA)
-4. Cambio de datos de producto: ( ver sie s para todos o solo para precio)
-5. Buscar cambios en el stock.
-6. Resultados del periodo deseado (ingrese rango para el periodo que quiere)
Ideas generales:
usar pilas para sacar costo de mercaderia vendida modo LIFO,o sea que hay que hacer una pila por producto para cargar el precio cada vez que se cambia y cuando se saca el costo de usa esta pila (contabilidad)
 
Stock:
tracking de delivery (si se mando algo, si fue entregado y eso)
