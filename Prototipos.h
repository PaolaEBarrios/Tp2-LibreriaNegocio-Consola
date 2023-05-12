#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED

void MsjMenuPrincipal();
void MsjMenuLibro();
void MsjMenuVentas();
void MsjMenu_Electronico();
void MsjModificar_Libro();

void Pausa();
void Borrar();////SYSTEM ("CLS")
void MsjOpcion();//// MENSAJE DE OPCION
void OpcionError();////MENSAJE DE OPCION INCORRECTA

void LineasCortas();////LINEAS SEPARADORAS MENUS
void LineasLargas();


//////////////////////////////////////////////////////////////////
//LIBROS
////////////////////////////

void Menu_Libro();
void Alta_libro();

void Modificar_Libro();
void Modificar_Stock();
void Modificar_Precio();
void Modificar_Titulo();

void Borrar_Libro();//MENU INTERACTIVO PARA DAR DE BAJA O ELIMINAR LIBRO
void Eliminar_Libros();//ABRE UN FILE *P, EN WB, PARA BORRAR TODOS LOS ARCHIVOS DE LIBROS
bool Eliminar_Archivolibro(int ); //ABRE FILE, PARA LEER Y OTRO PARA ESCRIBIR
void FISICO_Libro();// FUNSION A OTRAS PARA BORRAR ARCHIVO DESEADO(LIBRO)
void Borrar_libro();
void copiarArchivosLibros();

void Baja_libro();

int BuscarXtitulo(char *);
void Buscar_Listar_Libros();
void MostrarLibroXcod();
void MostrarLibroXtitulo();

int Contar_libros();
void OrdenarLibros();

////////////////////////////////////////////////////////////////////
//FIN LIBRO
/////////////////////////////////////////////////////////////////////

//INICIO Clientes

void Menu_Cliente();
int  Contar_Clientes();

void AgregarCliente();
int TraerCodigoAnterior();

void Modificar_Cliente();
void Modificar_Email();
void Modificar_Tel();
void Modificar_Nombre();


int buscarClienteXid(int );

void  EliminarCliente();
void  Baja_Cliente();
void  Fisico_Cliente();

bool  DieARCHIVOCliente(int );
void  CopiarClientes();


void ListarClientes();
void ClienteXcodigo();
void ClienteXNombre();
void ClienteTodosMostrar();

//FIN CLIENTES
//////////////////////////////////////////////////////////////////

//////INICIO VENTAS

void MsjMenuVentas();
void Menu_Ventas();

void AgregarVenta();
int contarVentas();

void Modificar_Venta();
void Modificar_cantidad();
void Modificar_Pago();

int BuscarVentaXcod(int );

void  EliminarVenta();
void  Baja_Venta();
void  Fisico_Venta();
bool  Die_Archivo_Venta(int );
void  Copiar_Ventas();

void  ListarVentas();//MENU VENTAS
void  VentasXmes();//I
void  VentasCliente();//I
void  VentaXLibro();
void  ListarAllVentas();//MUESTRA TODAS LAS VENTAS GUARDADAS

int VentasMes();
int VentasMesMayor();

#endif // PROTOTIPOS_H_INCLUDED
