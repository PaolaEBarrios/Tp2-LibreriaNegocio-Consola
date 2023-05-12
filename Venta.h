#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED

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
void  VentasXmes();//
void  VentasCliente();//
void  VentaXLibro();
void  ListarAllVentas();//MUESTRA TODAS LAS VENTAS GUARDADAS

int VentasMes();
int VentasMesMayor();




void Menu_Ventas()
{
    int opc;
    bool bandera=true;


    while(bandera != false)
    {
        Borrar();

        MsjMenuVentas();
        MsjOpcion();
        cin>>opc;


        switch(opc)
        {
            case 1:
                AgregarVenta();
            break;
            case 2:
                Modificar_Venta();
            break;
            case 3:
                EliminarVenta();
            break;
            case 4:
                ListarVentas();
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

void Venta::grabar_en_disco()
{
    FILE *p;
    p=fopen(ven,"ab");
    if(p == NULL)
    {
        cout<<"  ERROR AL GRABAR VENTA"<<endl;
        pausita();
        return;
    }



    fwrite(this,sizeof(Venta),1,p);
    fclose(p);

}

int contarVentas()
{
    int  regs=0;
    long bytes=0;

    FILE *p;
    p=fopen(ven,"rb");
    if(p == NULL)return -1;


    fseek(p,0,2);
    bytes=ftell(p);
    fclose(p);

    regs=bytes/sizeof(Venta);
    return regs;

}

int Venta::leer_En_disco(int pos)
{
    int x;

    FILE *p;
    p=fopen(ven,"rb");
    if(p == NULL)return -1;



    fseek(p,pos*sizeof*this,0);
    x=fread(this,sizeof(Venta),1,p);
    fclose(p);
    return x;
}

int  Venta::modificar_en_disco(int pos)
{

    FILE *p;
    p=fopen(ven,"rb+");
    if(p == NULL)return -1;



    fseek(p,pos*sizeof*this,0);
    fwrite(this,sizeof(Venta),1,p);
    fclose(p);
    return -1;

}

void Venta::Mostrar()
{
    cout<<endl;
    LineasLargas();
    cout<<"  CODIGO VENTA:   "<<codVenta<<endl;
    cout<<"  CODIGO CLIENTE: "<<codCliente<<endl;
    cout<<"  CODIGO LIBRO:   "<<codLibro<<endl;
    cout<<"  CANTIDAD:       "<<Cantidad<<endl;
    cout<<"  FECHA DE VENTA: "<<dia<<"/"<<mes<<"/"<<anio<<endl;
    cout<<"  TOTAL :        $"<<Total<<endl;
    cout<<"  PAGO:           ";
    if(Pago == 1)
    {
        cout<<"CONCRETADO"<<endl;
    }
    else
    {
        cout<<"DEBE"<<endl;
    }

}

int Venta::Cargar()
{
    //VERIFICAR QUE EXISTEN CODCLIENTE Y CODLIBRO//
    cout<<"  INGRESE EL CODIGO DE CLIENTE: ";
    cin>>codCliente;
    cout<<endl;
    int ex=buscarClienteXid(codCliente);
    if(ex == -1)
    {
        LineasLargas();
        cout<<"  EL CLIENTE NO EXISTE"<<endl;
        pausita();
        return -1;
    }

    //PREGUNTAR SI ESTA ACTIVO
    Cliente c;
    c.leer_en_disco(ex);



    if(c.getEstado()== false)
    {
        LineasLargas();
        cout<<"  EL CLIENTE NO EXISTE"<<endl;
        pausita();
        return -1;
    }


    cout<<"  INGRESE EL CODIGO DE LIBRO:   ";
    cin>>codLibro;
    ex=Buscar_LibroXid(codLibro);
    if(ex == -1)
    {
        LineasLargas();
        cout<<" EL LIBRO NO EXISTE"<<endl;
        pausita();
        return -1;
    }

    Libros obj;

    obj.leer_en_disco(ex);
    if(obj.getestado()== false)
    {
        LineasLargas();
        cout<<" EL LIBRO NO EXISTE"<<endl;
        pausita();
        return -1;
    }

    //AGREGAR EL CODVENTA AUTONUMERICO
    int registros=contarVentas();

    //SI LA CANTIDAD DE REG ES -1 O CERO ES PORQUE NO HAY ARCHIVO O ESTA VACIO
    //IF CONTAR REGISTRO
    if( registros == -1 || registros == 0)
    {
        codVenta=1;

        cout<<"  CANTIDAD DE LIBROS:  ";
        cin>>Cantidad;
        while(Cantidad<0)
        {//WHILE CANTIDAD <0
            cout<<"  LA CANTIDAD DEBE SER MAYOR A CERO"<<endl;
            cout<<"  CANTIDAD DE LIBROS:  ";
            cin>>Cantidad;
        }//WHILE CANTIDAD <0 FIN


        //COMPROBAR QUE EL STOCK ALCANZA


        if(obj.getstock()>= Cantidad)
        {

        }
        else
        {
            cout<<"  STOCK INSUFICIENTE: "<<obj.getstock()<<endl;
            LineasLargas();
            return -1;
        }

        //GUARDAR FECHA
        //DIA,MES Y ANIO SE TOMA DEL SISTEMA

        int d,m,a;

        time_t tiempo;
        struct tm *tmPtr;
        tiempo = time(NULL);
        tmPtr = localtime(&tiempo);
        a=tmPtr->tm_year+1900;
        m=tmPtr->tm_mon+1;
        d=tmPtr->tm_mday;


        dia=d;//SE GUARDA D EN DIA
        mes=m;//" "
        anio=a;// SE TERMINA POR GUARDAR EL ANIO DEL SISTEMA

        Estado=true;//ESTADO ES TRUE PORQUE ESTA DISPONIBLE/BAJA LOGICA
        int pagar;//VARIABLE PARA SELECCIONAR PAGO DE LIBROS
        int bandera=true;//FIN DEL WHILE DE PAGO

        Libros reg;

        //SE BUSCA EL LIBRO EN REGISTRO LIBRO
        int existe=Buscar_LibroXid(codLibro);
            reg.leer_en_disco(existe);

            //SE SACA EL TOTAL
        Total=Cantidad*reg.getprecio();

        while(bandera != false)//INICIO WHILE PAGO
        {
            cout<<endl;
            cout<<"   PAGO  ";
            LineasLargas();
            cout<<"  1 - CONCRETAR VENTA"<<endl;
            cout<<"  2 - PENDIENTE/DEUDA"<<endl;
            cout<<"  0 - CANCELAR VENTA"<<endl;
            LineasLargas();
            MsjOpcion();
            cin>>pagar;

            switch(pagar)
            {
                case 1:
                    {
                        obj.setstock(obj.getstock()-Cantidad);
                        obj.modificar_en_disco(ex);
                        Pago=1;//// 1 ES PAGO CONCRETADO
                        return 1;
                    }

                break;
                case 2:
                    {
                        obj.setstock(obj.getstock()-Cantidad);
                        obj.modificar_en_disco(ex);
                        Pago=2; ////2 - PENDIENTE DE PAGO
                        return 1;

                    }
                break;
                case 0:
                    bandera=false;//SE CAMBIA EL VALOR PARA QUE CIERRE EL WHILE
                break;
                default:
                    OpcionError();
                    pausita();
                break;
            }//FIN SWITCH
        }//FIN WHILE PAGO
        return -1;
    }//FIN IF REGISTRO
    else
    {
        codVenta=1+contarVentas();

        cout<<"  CANTIDAD DE LIBROS:  ";
        cin>>Cantidad;
        while(Cantidad<0)
        {
            cout<<"  LA CANTIDAD DEBE SER MAYOR A CERO"<<endl;
            cout<<"  CANTIDAD DE LIBROS:  ";
            cin>>Cantidad;
        }

        //COMPROBAR QUE EL STOCK ALCANZA


        if(obj.getstock()>= Cantidad)
        {
            //obj.setstock(obj.getstock()-Cantidad);
            //obj.modificar_en_disco(ex);
        }
        else
        {
            cout<<"  STOCK INSUFICIENTE: "<<obj.getstock()<<endl;
            LineasLargas();
            return -1;
        }

        //GUARDAR FECHA
        //DIA,MES Y ANIO SE TOMA DEL SISTEMA

        int d,m,a;

        time_t tiempo;
        struct tm *tmPtr;
        tiempo = time(NULL);
        tmPtr = localtime(&tiempo);
        a=tmPtr->tm_year+1900;
        m=tmPtr->tm_mon+1;
        d=tmPtr->tm_mday;


        dia=d;
        mes=m;
        anio=a;

        Estado=true;
        int pagar;
        int bandera=true;

        Libros reg;

        int existe=Buscar_LibroXid(codLibro);
            reg.leer_en_disco(existe);
        Total=Cantidad*reg.getprecio();

        while(bandera != false)
        {
            cout<<"   PAGO  ";
            LineasLargas();
            cout<<"  1 - CONCRETAR VENTA"<<endl;
            cout<<"  2 - PENDIENTE/DEUDA"<<endl;
            cout<<"  0 - CANCELAR VENTA"<<endl;
            LineasLargas();
            MsjOpcion();
            cin>>pagar;

            switch(pagar)
            {
                case 1:
                    {
                        obj.setstock(obj.getstock()-Cantidad);
                        obj.modificar_en_disco(ex);
                        Pago=1;
                        return 1;

                    }
                break;
                case 2:
                    {
                        obj.setstock(obj.getstock()-Cantidad);
                        obj.modificar_en_disco(ex);
                        Pago=2;
                        return 1;
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
        cout<<"  SE CANCELO LA VENTA"<<endl;
        LineasCortas();
        pausita();
        return -1;
    }


}

void AgregarVenta()
{
    Borrar();
    //VENTA O PEDIDOS? RENOMBRAR VENTA A PEDIDOS Y QUE LAS VENTAS SEAN DATOS POR LOS PEDIDOS(REPORTES)1¿?
    cout<<"  AGREGAR NUEVA VENTA"<<endl;
    LineasLargas();

    Venta reg;

    int x=reg.Cargar();

    cout<<endl;
    if(x != -1)
    {
        reg.grabar_en_disco();
        cout<<"   NUEVA VENTA AÑADIDA CON EXITO"<<endl;
        LineasLargas();
    }
    else
    {
        cout<<"  ERROR AL AGREGAR NUEVA VENTA"<<endl;
        LineasLargas();
    }

    Pausa();
}

void Modificar_Venta()
{

    int opc;
    bool bandera=true;


    while(bandera!= false)
    {
        Borrar();
        cout<<"  MODIFICAR VENTA"<<endl;
        LineasLargas();
        cout<<"  1 -  MODIFICAR CANTIDAD COMPRADA"<<endl;
        cout<<"  2 -  MODIFICAR ESTADO DE PAGO"<<endl;
        LineasLargas();
        cout<<"  0 -  VOLVER AL MENU DE VENTAS"<<endl;
        LineasLargas();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                Modificar_cantidad();
            break;
            case 2:
                Modificar_Pago();
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


void Modificar_cantidad()
{
    Borrar();
    int cod;

    cout<<"  MODIFICAR CANTIDAD DE LA COMPRA "<<endl;
    LineasLargas();

    cout<<"  INGRESE EL CODIGO DE LA VENTA: ";
    cin>>cod;
    //SE BUSCA POSICION DE VENTA
    int x=BuscarVentaXcod(cod);
//SI ES POSITIVO SE ENTRA
    if(x != -1)
    {
        Venta reg;//SE ABRE UN OBJETO VENTA
        //LEO EL OBJETO EN DISCO EN POSICION X
        reg.leer_En_disco(x);

        if(reg.getEstado() == true)
        {
            int cant;

            int cant2=reg.getCantidad();

            cout<<" EL LIBRO A COMPRAR, SU CODIGO ES: "<<reg.getCodlibro()<<endl;
            cout<<" INGRESE LA NUEVA CANTIDAD: ";
            cin>>cant;

            while(cant<0)
            {
                cout<<endl;
                cout<<"  INGRESE UN VALOR POSITIVO"<<endl;
                cout<<"  CANTIDAD: ";
                cin>>cant;
            }


            if(cant<cant2)
            {

                int Diferencia=cant2-cant;

                Libros l;

                int libpos=Buscar_LibroXid(reg.getCodlibro());
                l.leer_en_disco(libpos);



                int stock=Diferencia+l.getstock();
                cout<<"  stock: "<<stock<<endl;
                pausita();
                l.setstock(stock);
                l.modificar_en_disco(libpos);

                int tot=cant*l.getprecio();
                reg.setTotal(tot);
                reg.setCantidad(cant);
                reg.modificar_en_disco(x);// X ES LA POSICION DE LA VENTA A MODIFICAR

                LineasLargas();
                cout<<"  VENTA MODIFICADA CON EXITO"<<endl;
                cout<<"  CANTIDAD MODIFICADA"<<endl;
                LineasLargas();
            }
            else
            {
                Libros l2;

                int Posbook=Buscar_LibroXid(reg.getCodlibro());

                l2.leer_en_disco(Posbook);
                int stock2=l2.getstock();

                if(stock2== 0 || stock2 < cant)
                {
                    cout<<"  STOCK INSUFICIENTE"<<endl;
                    pausita();
                    return;
                }
                else
                {

                    Libros l;

                    int libpos=Buscar_LibroXid(reg.getCodlibro());
                    l.leer_en_disco(libpos);
                    int stock=l.getstock();
                    int acu=stock-cant;

                    l.setstock(acu);
                    l.modificar_en_disco(libpos);

                    int tot=cant*l.getprecio();
                    reg.setTotal(tot);
                    reg.setCantidad(cant);
                    reg.modificar_en_disco(x);// X ES LA POSICION DE LA VENTA A MODIFICAR

                    LineasLargas();
                    cout<<"  VENTA MODIFICADA CON EXITO"<<endl;
                    cout<<"  CANTIDAD MODIFICADA"<<endl;
                    LineasLargas();

                }

            }

        }
        else
            {
                cout<<"  LA VENTA "<<cod<<" NO EXISTE"<<endl;
                cout<<"  INGRESE OTRO CODIGO "<<endl;
                LineasLargas();
            }
}
else
{
            LineasLargas();
            cout<<"  LA VENTA "<<cod<<"  NO EXISTE"<<endl;
            cout<<"  INGRESE OTRO CODIGO"<<endl;
}

        Pausa();
}


void Modificar_Pago()
{
    Borrar();

    cout<<"  MODIFICAR ESTADO DE VENTA"<<endl;
    LineasLargas();

    int cod;

    cout<<"  INGRESE EL NUMERO DE VENTA: ";
    cin>>cod;

    int x=BuscarVentaXcod(cod);

    if(x != -1)
    {
        Venta reg;

        reg.leer_En_disco(x);


        if(reg.getEstado()== true)
        {
            //SI ESTA PAGO NO SE PUEDE VOLVER A PAGAR Y SI ESTA EN DEUDA NO SE PUEDE VOLVER A ADEUDAR.
            int pago;
            bool bandera=true;

           while(bandera != false)
           {


                cout<<"  INGRESE LA OPCION QUE DESEA"<<endl;
                LineasLargas();
                cout<<"  1 - CAMBIAR ESTADO A PAGADO"<<endl;
                cout<<"  2 - CAMBIAR ESTADO A DEUDA"<<endl;
                cout<<"  0 - CANCELAR Y SALIR AL MENU"<<endl;
                MsjOpcion();
                cin>>pago;

                switch(pago)
                {
                    case 1:
                        reg.setPago(1);
                        reg.modificar_en_disco(x);

                        cout<<"   PAGADA"<<endl;
                        cout<<"   VENTA CONFIRMADA"<<endl;
                        pausita();
                        bandera=false;
                    break;
                    case 2:
                        reg.setPago(2);
                        reg.modificar_en_disco(x);
                        cout<<"   ADEUDA"<<endl;
                        cout<<"   VENTA PENDIENTE"<<endl;
                        pausita();
                        bandera=false;
                    break;
                    case 0:
                        bandera=false;
                        return;
                    break;
                    default:
                        OpcionError();
                        pausita();
                    break;
                }

           }

        }
        else
        {
            cout<<"  EL CODIGO INGRESADO NO EXISTE"<<endl;
            cout<<"  INTENTE CON OTRO CODIGO<<"<<endl;
            LineasLargas();
        }

    }
    else
    {
        cout<<"   VENTA NO EXISTE"<<endl;
        cout<<"   VERIFIQUE QUE ESTE CARGADA LA VENTA"<<endl;
        LineasLargas();
    }

    Pausa();
}

int BuscarVentaXcod(int cod)
{
    Venta reg;

    int pos=0;

    while(reg.leer_En_disco(pos))
    {
        if(cod == reg.getcodVenta())
        {
            return pos;
        }

        pos++;
    }

    return -1;
}


void EliminarVenta()
{
    int opc;
    bool bandera=true;


    while(bandera != false)
    {
        Borrar();

        cout<<"  DAR BAJA/ELIMINAR VENTA"<<endl;
        LineasLargas();
        cout<<"  1 -  ELIMINAR VENTA (ARCHIVO)"<<endl;
        cout<<"  2 -  DAR BAJA VENTA (LOGICO)"<<endl;
        LineasLargas();
        cout<<"  0 - VOLVER AL MENU VENTAS"<<endl;
        LineasLargas();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                Fisico_Venta();
            break;
            case 2:
                Baja_Venta();
            break;
            case 0:
                bandera = false;
            break;
            default:
                OpcionError();
                pausita();
            break;
        }

    }

}

bool Die_Archivo_Venta(int cod)
{
    FILE *p;

    p=fopen(ven2,"wb");
    if(p == NULL)return -1;

    Venta reg,reg2;

    int pos=0;


    while(reg.leer_En_disco(pos))
    {
        if(reg.getcodVenta() != cod)
        {
            reg2.setanio(reg.getAnio());
            reg2.setCantidad(reg.getCantidad());
            reg2.setCodCliente(reg.getCodcliente());
            reg2.setcodlibro(reg.getCodlibro());
            reg2.setCodventa(reg.getcodVenta());
            reg2.setdia(reg.getdia());
            reg2.setEstado(reg.getEstado());
            reg2.setmes(reg.getmes());
            reg2.setPago(reg.getPago());
            reg2.setTotal(reg.getTotal());

            fwrite(&reg2,sizeof(Venta),1,p);
        }
        pos++;
    }


    fclose(p);
    return 1;
}

void Copiar_Ventas()
{
    FILE *p,*p2;

    p=fopen(ven,"wb");
    if(p == NULL)
    {
        cout<<"  ERROR AL ABRIR ARCHIVO"<<endl;
        pausita();
        exit(1);
    }
    p2=fopen(ven2,"rb");
    if(p == NULL)
    {
        cout<<"  ERROR AL ABRIR ARCHIVO"<<endl;
        pausita();
        exit(1);
    }

    Venta reg,reg2;


    while(fread(&reg2,sizeof(Venta),1,p2))
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

        fwrite(&reg,sizeof(Venta),1,p);
    }

    fclose(p);
    fclose(p2);


}

void Fisico_Venta()
{
    Borrar();
    int cod;

    cout<<"  ELIMINAR VENTA (ARCHIVO)"<<endl;
    LineasLargas();
    cout<<"  INGRESE EL CODIGO DE VENTA: ";
    cin>>cod;

    LineasLargas();

    int pos=BuscarVentaXcod(cod);

    if(pos != -1)
    {
        Venta reg;

        reg.leer_En_disco(pos);

        if(reg.getEstado()== true)
        {
            bool x=Die_Archivo_Venta(cod);

            if( x != false)
            {

                Copiar_Ventas();
                cout<<"  VENTA ELIMINADA CON EXITO"<<endl;
                cout<<"  ARCHIVO ELIMINADO"<<endl;
            }
        }
        else
        {
            cout<<"  VENTA NO EXISTE"<<endl;
            cout<<"  VERIFIQUE QUE EL CODIGO EXISTA"<<endl;
        }

    }
    else
    {
        cout<<"  VENTA NO EXISTE"<<endl;
        cout<<"  VERIFIQUE QUE EL CODIGO EXISTA"<<endl;
    }

    LineasLargas();
    Pausa();
}

void Baja_Venta()
{
    Borrar();

    int cod;

    cout<<"   DAR DE BAJA VENTA "<<endl;
    LineasCortas();
    cout<<"  INGRESE CODIGO DE VENTA: ";
    cin>>cod;


    int pos=BuscarVentaXcod(cod);


    if(pos != -1)
    {
        Venta reg;
        reg.leer_En_disco(pos);

        if(reg.getEstado()== true)
        {
            reg.setEstado(false);
            reg.modificar_en_disco(pos);

            cout<<endl;
            cout<<"  EXITO AL DAR DE BAJA VENTA"<<endl;
            cout<<"  VENTA "<<cod<<"  DADA DE BAJA"<<endl;


        }
        else
        {
            cout<<endl;
            cout<<"  ERROR A DAR DE BAJA LA VENTA"<<endl;
            cout<<"  LA VENTA YA ESTA DADA DE BAJA"<<endl;
        }

    }
    else
    {
        cout<<endl;
        cout<<"  ERROR AL DAR DE BAJA"<<endl;
        cout<<"  NO SE ENCONTRO LA VENTA"<<endl;

    }

    LineasLargas();
    Pausa();

}


void ListarVentas()
{
    int opc;
    bool bandera=true;


    while(bandera != false)
    {
        Borrar();

        cout<<"   BUSCAR/LISTAR VENTAS"<<endl;
        LineasLargas();
        cout<<"  1 - BUSCAR/LISTAR VENTA POR CLIENTE"<<endl;
        cout<<"  2 - BUSCAR/LISTAR VENTA POR LIBRO"<<endl;
        cout<<"  3 - BUSCAR/LISTAR VENTA POR MES"<<endl;
        cout<<"  4 - LISTAR TODAS LAS VENTAS"<<endl;
        LineasLargas();
        cout<<"  0 - VOLVER AL MENU VENTAS"<<endl;
        LineasLargas();
        MsjOpcion();
        cin>>opc;


        switch(opc)
        {
            case 1:
                VentasCliente();
            break;
            case 2:
                VentaXLibro();
            break;
            case 3:
                VentasXmes();
            break;
            case 4:
                ListarAllVentas();
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



void VentasCliente()
{
    Borrar();
    int cod;
    int pos=0;
    int x;
    int cont=0;

    cout<<"  VENTAS POR N° DE CLIENTE"<<endl;
    LineasLargas();
    cout<<"  INGRESE CODIGO CLIENTE: ";
    cin>>cod;

    x=buscarClienteXid(cod);
    ////PREGUNTA SI EXISTE
    if(x != -1)
    {
        Cliente cliente;

        cliente.leer_en_disco(x);

            Venta reg;

            while(reg.leer_En_disco(pos))
            {
                if(cod==reg.getCodcliente())
                {


                    cont++;
                    LineasLargas();
                    cout<<endl;

                    cout<<"  NOMBRE DEL CLIENTE: "<<cliente.getNombre()<<endl;
                    cout<<"  ESTADO DE CLIENTE:  ";
                    if( cliente.getEstado()== true)
                    {
                        cout<<"  ACTIVO"<<endl;
                    }
                    else
                    {
                        cout<<"  NO DISPONIBLE"<<endl;
                    }
                    reg.Mostrar();
                    pausita();
                }
                pos++;
            }

            if(cont == 0)
            {
                cout<<"  EL CLIENTE NO REALIZO COMPRAS"<<endl;
                pausita();
            }
            else
            {
                LineasLargas();
                cout<<endl;
                cout<<"  EL CLIENTE REALIZO "<<cont<<" COMPRAS"<<endl;
                pausita();

            }

    }
    else
    {
        cout<<"  EL CLIENTE INGRESADO NO EXISTE"<<endl;

    }

    LineasLargas();
    Pausa();
}

void VentaXLibro()
{
    Borrar();
    cout<<"  LIBRO MAS VENDIDO"<<endl;
    LineasLargas();

    int pos=0;

    int contLibros=Contar_libros();

    int *vLibros=new int[contLibros];
    int *VcontLibros=new int [contLibros];

    Libros reg;

    for(int i=0;i<contLibros;i++)
    {
        vLibros[i]=0;

        VcontLibros[i]=0;
    }

    while(reg.leer_en_disco(pos))
    {

        vLibros[pos]=reg.getCod();
        pos++;
    }

    Venta v;
    pos=0;
    int pos2=0;

    while(v.leer_En_disco(pos))
    {

        while(reg.leer_en_disco(pos2))
        {
            if(vLibros[pos2]== v.getCodlibro())
            {
                VcontLibros[pos2]+=v.getCantidad();

            }

            pos2++;
        }

        pos++;
        pos2=0;
    }

    int mayor=0,poslibro=0;

    for(int x=0;x<contLibros;x++)
    {
        if(VcontLibros[x]>mayor)
        {
            mayor=VcontLibros[x];
            poslibro=x;
        }
    }

    cout<<"  EL LIBRO MAS VENDIDO FUE: "<<vLibros[poslibro]<<endl;
    cout<<"  CANTIDADES VENDIDAS:      "<<VcontLibros[poslibro]<<endl;
    cout<<endl;
    LineasLargas();
    Pausa();

    delete[]VcontLibros;
    delete[]vLibros;

}

void VentasXmes()
{
    int opc;
    bool bandera=true;



    while(bandera != false)
    {
        Borrar();
        cout<<"  BUSCAR/LISTAR VENTAS POR MES"<<endl;
        LineasLargas();
        cout<<"  1 - BUSCAR VENTA POR MES"<<endl;
        cout<<"  2 - LISTAR MES CON MÁS VENTAS"<<endl;
        LineasLargas();
        cout<<"  0 - VOLVER AL MENU ANTERIOR"<<endl;
        LineasLargas();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                VentasMes();
            break;
            case 2:
                VentasMesMayor();
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
int VentasMes()
{
    int vMes[12];

    int mes;
    Borrar();


    cout<<"  INGRESE EL NUMERO DEL MES: ";
    cin>>mes;

    while(mes < 0 && mes > 12)
    {
        cout<<"  INGRESE EL NUMERO DEL MES: ";
        cin>>mes;
    }
    int pos=0;

    Venta reg;
    float vTotal[12];


    for(int i=0;i<12;i++)
    {
        vMes[i]=0;
        vTotal[i]=0.0;
    }

    while(reg.leer_En_disco(pos))
    {

        vMes[reg.getmes()-1]+=1;
        vTotal[reg.getmes()-1]+=reg.getTotal();
        pos++;

    }

    cout<<"  EL MES: "<<mes<<endl;
    cout<<"  VENTAS: "<<vMes[mes-1]<<endl;
    cout<<"  TOTAL: $"<<vTotal[mes-1]<<endl;
    LineasLargas();
    Pausa();
    return 1;
}

int VentasMesMayor()
{
    Borrar();
    int mes[12];
    float vTotal[12];
    int pos=0;

    for(int i=0;i<12;i++)
    {
        mes[i]=0;
        vTotal[i]=0.0;
    }


    cout<<"  CANTIDAD DE VENTAS POR MES"<<endl;
    LineasLargas();

    Venta reg;

    while(reg.leer_En_disco(pos))
    {

        mes[reg.getmes()-1]+=1;
        vTotal[reg.getmes()-1]+=reg.getTotal();
        pos++;

    }

    int mayor=0,y=0;
    //12,15,3, 7
    for(int x=0;x<12;x++)
    {
        if(mes[x]>mayor)
        {
            y=x;
            mayor=mes[x];
        }

    }

    cout<<"  MES CON MAYOR VENTAS"<<endl;
    LineasLargas();
    cout<<" MES               "<<y+1<<endl;
    cout<<" VENTAS:           "<<mayor<<endl;
    cout<<" TOTAL FACTURADO: $"<<vTotal[y]<<endl;
    LineasLargas();
    Pausa();

    return 1;
}

void ListarAllVentas()
{
    Borrar();
    int pos=0;

    Venta reg;
    cout<<endl;
    cout<<"  TODAS LAS VENTAS REGISTRADAS"<<endl;
    LineasLargas();
    int x=contarVentas();
    if(x != -1)
    {
        while(reg.leer_En_disco(pos))
        {
            if(reg.getEstado()== true)
            {
                reg.Mostrar();
                pausita();
            }
            pos++;
        }

    }
    else
    {
        cout<<"  NO HAY NADA QUE MOSTRAR"<<endl;
    }
    Pausa();

}


#endif // VENTA_H_INCLUDED
