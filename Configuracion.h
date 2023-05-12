#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGURACION_H_INCLUDED

//ELIMINAR ARCHIVOS
  // LIBRO
  // CLIENTES
  // VENTAS
  // TODOS

  void Menu_Configuracion();
  void EliminarArchivos();

  bool ChauChauAdiosTodos();

  void BackUp();
  bool bkpclientes();
  bool bkplibros();
  bool bkpventas();
  bool BKPtodos();

  void regs_dados_baja();

  void CargarDatos();
  int  cargarBack();

  void cargarbackclientes();
  void cargarbackventas();

  void Menu_Configuracion()
  {
      int opc;
      bool bandera=true;


      while(bandera != false)
      {
          Borrar();

          cout<<"  MENU CONFIGURACION"<<endl;
          LineasLargas();
          cout<<"  1 - REALIZAR BACK UP"<<endl;
          cout<<"  2 - ELIMINAR ARCHIVOS"<<endl;
          cout<<"  3 - ACTIVAR REGISTROS DADOS DE BAJA"<<endl;
          cout<<"  4 - CARGAR DATOS DE BACK UP"<<endl;
          LineasLargas();
          cout<<"  0 - VOLVER AL MENU PRINCIPAL"<<endl;
          LineasLargas();
          MsjOpcion();
          cin>>opc;

          switch(opc)
          {
            case 1:
                BackUp();
            break;
            case 2:
                EliminarArchivos();
            break;
            case 3:
                regs_dados_baja();
            break;
            case 4:
                CargarDatos();
            break;
            case 0:
                bandera=false;
            break;
            default:
                OpcionError();
                pausita();
            break;
          }
      }
  }

void EliminarArchivos()
{

    int opc;
    bool bandera=true;

    while(bandera!= false)
    {
        Borrar();
        cout<<"  ¿DESEA ELIMINAR TODOS LOS ARCHIVOS?"<<endl;
        cout<<"  -----------------------------------"<<endl;
        cout<<"  1 - SI"<<endl;
        cout<<"  0 - CANCELAR"<<endl;
        LineasCortas();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                {
                    bool x= ChauChauAdiosTodos();
                    if(x == true)
                    {
                        cout<<"  ARCHIVOS ELIMINADOS CON EXITO"<<endl;
                        LineasLargas();
                        pausita();
                        bandera=false;
                    }
                }

            break;
            case 0:
                bandera=false;
            break;
            default:
                OpcionError();
                pausita();
            break;
        }

    }



}

bool ChauChauAdiosTodos()
{
    Cliente reg;
    Venta   reg2;
    Libros reg3;

    FILE *p,*p2,*p3;


    p=fopen(cli,"wb");
    p2=fopen(lib,"wb");
    p3=fopen(ven," wb");

    if(p == NULL || p2== NULL || p3== NULL)return false;



    fwrite(&reg,sizeof(Cliente),0,p);
    fwrite(&reg2,sizeof(Venta),0,p3);
    fwrite(&reg3,sizeof(Libros),0,p2);

    fclose(p);
    fclose(p2);
    fclose(p3);
    return true;
}

//BACKUP
    // LIBROS
    // CLIENTES
    // VENTAS
    // TODOS


void BackUp()
{
    int opc;
    bool bandera=true;


    while(bandera != false)
    {
        Borrar();
        cout<<"  BACK UP DE LOS ARCHIVOS"<<endl;
        LineasLargas();
        cout<<"  1 - BACK UP LIBROS"<<endl;
        cout<<"  2 - BACK UP CLIENTES"<<endl;
        cout<<"  3 - BACK UP VENTAS"<<endl;
        cout<<"  4 - BACK UP TODOS"<<endl;
        LineasLargas();
        cout<<"  0 - VOLVER AL MENU CONFIGURACION"<<endl;
        LineasLargas();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                bkplibros();
            break;
            case 2:
                bkpclientes();
            break;
            case 3:
                bkpventas();
            break;
            case 4:
                BKPtodos();
            break;
            case 0:
                bandera=false;
            break;
            default:
                OpcionError();
                pausita();
            break;
        }

    }


}

bool bkplibros()
{
    int pos=0;

    Libros reg,reg2;

    FILE *p2;
    //p=fopen(lib,"rb");
    p2=fopen(libBKP," wb");
    if(p2 == NULL)return false;

    while(reg.leer_en_disco(pos))
    {

        reg2.setAutor(reg.getautor());
        reg2.setCodLibro(reg.getCod());
        reg2.setEstado(reg.getestado());
        reg2.setpaginas(reg.getpags());
        reg2.setprecio(reg.getprecio());
        reg2.setstock(reg.getstock());
        reg2.settitulo(reg.gettitulo());
        fwrite(&reg2,sizeof(Libros),1,p2);

        pos++;
    }

    fclose(p2);

    return true;
}


bool bkpclientes()
{
    int pos=0;

    Cliente reg,reg2;

    FILE *p2;
    //p=fopen(lib,"rb");
    p2=fopen(clibkp," wb");
    if(p2 == NULL)return false;

    while(reg.leer_en_disco(pos))
    {

        reg2.setCodCliente(reg.getCodCliente());
        reg2.setEmail(reg.getEmail());
        reg2.setestado(reg.getEstado());
        reg2.setNombre(reg.getNombre());
        reg2.setTelefono(reg.getTelefono());

        fwrite(&reg2,sizeof(Cliente),1,p2);

        pos++;
    }

    fclose(p2);

    return true;
}


bool bkpventas()
{
    int pos=0;

    Venta reg,reg2;

    FILE *p2;
    //p=fopen(lib,"rb");
    p2=fopen(venbkp," wb");
    if(p2 == NULL)return false;

    while(reg.leer_En_disco(pos))
    {

        reg2.setanio(reg.getAnio());
        reg2.setCantidad(reg.getCantidad());
        reg2.setCodCliente(reg.getEstado());
        reg2.setcodlibro(reg.getCodlibro());
        reg2.setCodventa(reg.getcodVenta());
        reg2.setdia(reg.getdia());
        reg2.setEstado(reg.getEstado());
        reg2.setmes(reg.getmes());
        reg2.setPago(reg.getPago());
        reg2.setTotal(reg.getTotal());

        fwrite(&reg2,sizeof(Venta),1,p2);

        pos++;
    }

    fclose(p2);

    return true;

}

bool BKPtodos()
{
    Borrar();
    cout<<"  BACK UP TODOS LOS ARCHIVOS"<<endl;
    LineasLargas();

    bool x,x2,x3;

    x=bkpclientes();
    x2=bkpventas();
    x3=bkplibros();


    if(x == true && x2== true && x3== true)
    {
        cout<<"  BACK UP REALIZADO CON EXITO"<<endl;
        LineasLargas();
        pausita();
        return true;
    }
    else
    {
        cout<<"  ERROR BACK UP FALLO"<<endl;
        pausita();
                return false;
    }

}

///////////ACTIVAR REGS DADOS DE BAJA


void regs_dados_baja()
{
    Borrar();


    Cliente reg;
    Venta   reg2;
    Libros reg3;
    int pos=0;


    cout<<"  ACTIVAR REGISTROS DADOS DE BAJA"<<endl;
    LineasLargas();
    cout<<"  PRESIONE ENTER PARA CONTINUAR"<<endl;
    pausita();

    while(reg.leer_en_disco(pos))
    {
        if(reg.getEstado()== false)
        {
            reg.setestado(true);
            reg.Modificar_en_disco(pos);
        }
        pos++;
    }

    pos=0;


    while(reg2.leer_En_disco(pos))
    {
        if(reg2.getEstado() == false)
        {
            reg2.setEstado(true);
            reg2.modificar_en_disco(pos);
        }
        pos++;
    }

    while(reg3.leer_en_disco(pos))
    {
        if(reg3.getestado()== false)
        {
            reg3.setEstado(true);
            reg3.modificar_en_disco(pos);
        }
        pos++;
    }


    cout<<"   SE ACTIVARON LOS REGISTROS"<<endl;
    cout<<"  ------------------------------"<<endl;
    Pausa();

}


void CargarDatos()
{
    int opc;
    bool bandera=true;

    while(bandera != false)
    {
        Borrar();

        cout<<"  CARGAR DATOS DE BACK UP"<<endl;
        LineasLargas();
        cout<<"  1 - CARGAR DATOS"<<endl;
        LineasLargas();
        cout<<"  0 - CANCELAR"<<endl;
        LineasCortas();

        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                cargarBack();
            break;
            case 0:
                bandera=false;
            break;
            default:
                OpcionError();
                Pausa();
            break;
        }

    }


}

int cargarBack()
{
    Libros reg,reg2;

    FILE *p,*p2;

    p=fopen(libBKP,"rb");
    if(p == NULL)return false;
    p2=fopen(lib,"wb");
    if(p2 == NULL)return false;


    while(fread(&reg,sizeof(Libros),1,p))
    {
            reg2.setCodLibro(reg.getCod());
            reg2.settitulo(reg.gettitulo());
            reg2.setAutor(reg.getautor());
            reg2.setpaginas(reg.getpags());
            reg2.setstock(reg.getstock());
            reg2.setprecio(reg.getprecio());
//            reg2.setanio(reg.getanio());
            reg2.setEstado(reg.getestado());

            fwrite(&reg2,sizeof(Libros),1,p2);

    }

    fclose(p);
    fclose(p2);

    cargarbackclientes();

    cargarbackventas();

    cout<<"  DATOS CARGADOS EXITOSAMENTE"<<endl;
    LineasLargas();
    pausita();
    return 1;

}

void cargarbackclientes()
{
    FILE *p3,*p4;

    p3=fopen(clibkp,"rb");
    if(p3 == NULL)
    {
        cout<<"  ERROR AL ABRIR EL ARCHIVO"<<endl;
        pausita();
        exit(1);
    }
    p4=fopen(cli,"wb");
    if(p4 == NULL )
    {
        cout<<"  ERROR AL ABRIR EL ARCHIVO"<<endl;
        pausita();
        exit(1);
    }

    Cliente reg,reg2;
    //int pos=0;

    while(fread(&reg2,sizeof(Cliente),1,p3))
    {
        reg.setCodCliente(reg2.getCodCliente());
        reg.setEmail(reg2.getEmail());
        reg.setestado(reg2.getEstado());
        reg.setNombre(reg2.getNombre());
        reg.setTelefono(reg2.getTelefono());

        fwrite(&reg,sizeof(Cliente),1,p4);

//        pos++;
    }

    fclose(p3);
    fclose(p4);


}

void cargarbackventas()
{

    FILE *p7,*p8;

    p7=fopen(venbkp,"rb");
    if(p7 == NULL)
    {
        cout<<"  ERROR AL ABRIR ARCHIVO"<<endl;
        pausita();
        exit(1);
    }
    p8=fopen(ven,"wb");
    if(p8 == NULL)
    {
        cout<<"  ERROR AL ABRIR ARCHIVO"<<endl;
        pausita();
        exit(1);
    }

    Venta reg,reg2;


    while(fread(&reg2,sizeof(Venta),1,p7))
    {

        reg.setanio(reg2.getAnio());
        reg.setCantidad(reg2.getCantidad());
        reg.setCodCliente(reg2.getCodcliente());
        reg.setcodlibro(reg2.getCodlibro());
        reg.setCodventa(reg2.getcodVenta());
        reg.setdia(reg2.getdia());
        reg.setEstado(reg2.getEstado());
        reg.setmes(reg2.getmes());
        reg.setPago(reg2.getPago());
        reg.setTotal(reg2.getTotal());

        fwrite(&reg,sizeof(Venta),1,p8);
    }

    fclose(p7);
    fclose(p8);

}

#endif // CONFIGURACION_H_INCLUDED
