#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

void pausita()
{
    system("pause>null");
}

void LineasCortas()
{
    cout << " ----------------------" << endl;
}

void LineasLargas()
{
    cout << " ----------------------------" << endl;
}

void Pausa()
{
    system("pause");
}

void Borrar()
{
    system("cls");
}

void MsjOpcion()
{
    cout << "  OPCION: ";
}

void Error_al_agregar()
{
    cout<<"  ERROR AL AGREGAR"<<endl;
}

void OpcionError()
{
    cout << "  OPCION INCORRECTA" << endl;
}

void MsjMenuPrincipal()
{
    cout << "  MENU PRINCIPAL " << endl;
    LineasCortas();
    cout << "  1 - LIBROS FISICOS" << endl;
    cout << "  2 - CLIENTES" <<endl;
    cout << "  3 - VENTAS" <<endl;
    cout << "  4 - CONFIGURACION"<<endl;
    LineasLargas();
    cout << "  0 - SALIR DEL PROGRAMA " << endl;
    LineasLargas();

}

void MsjMenuLibro()
{
    cout<<"   LIBROS FISICOS"<<endl;
    LineasCortas();
    cout<<"  1 - AGREGAR NUEVO LIBRO"<<endl;
    cout<<"  2 - MODIFICAR LIBRO"<<endl;
    cout<<"  3 - ELIMINAR/DAR DE BAJA LIBRO"<<endl;
    cout<<"  4 - MOSTRAR/BUSCAR LIBROS"<<endl;
    LineasLargas();
    cout<<"  0 - VOLVER AL MENU PRINCIPAL"<<endl;
    LineasLargas();
}



void MsjModificar_Libro()
{
    cout<<"  MODIFICAR LIBRO"<<endl;
    LineasCortas();
    cout<<"  1 - MODIFICAR STOCK"<<endl;
    cout<<"  2 - MODIFICAR PRECIO"<<endl;
    cout<<"  3 - MODIFICAR TITULO"<<endl;
    LineasLargas();
    cout<<"  0 - VOLVER AL MENU LIBRO"<<endl;
    LineasLargas();

}

void MsjEliminar_Libro()
{
    cout<<"  ELIMINAR/DAR DE BAJA LIBRO"<<endl;
    LineasLargas();
    cout<<"  1 - ELIMINAR LIBRO(ARCHIVO)"<<endl;
    cout<<"  2 - DAR DE BAJA(LOGICO)"<<endl;
    LineasLargas();
    cout<<"  0 - VOLVER AL MENU LIBRO"<<endl;
    LineasLargas();

}


void MsjMenuCliente()
{

    cout<<"  MENU CLIENTES"<<endl;
    LineasCortas();
    cout<<"  1 - AGREGAR NUEVO CLIENTE"<<endl;
    cout<<"  2 - MODIFICAR DATOS CLIENTE"<<endl;
    cout<<"  3 - ELIMINAR/DAR DE BAJA CLIENTE"<<endl;
    cout<<"  4 - MOSTRAR/BUSCAR CLIENTE"<<endl;
    LineasLargas();
    cout<<"  0 - VOLVER AL MENU PRINCIPAL"<<endl;
    LineasLargas();

}

void MsjMenuVentas()
{
    cout<<"   MENU VENTAS"<<endl;
    LineasLargas();
    cout<<"   1 - AGREGAR NUEVA VENTA"<<endl;
    cout<<"   2 - MODIFICAR VENTA"<<endl;
    cout<<"   3 - ELIMINAR/DAR DE BAJA VENTA"<<endl;
    cout<<"   4 - MOSTRAR/BUSCAR VENTA"<<endl;
    LineasLargas();
    cout<<"   0 - VOLVER AL MENU PRINCIPAL"<<endl;
    LineasLargas();
}

#endif // MENUS_H_INCLUDED
