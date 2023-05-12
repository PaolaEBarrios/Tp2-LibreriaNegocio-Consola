#ifndef LIBELECTRONICO_H_INCLUDED
#define LIBELECTRONICO_H_INCLUDED

void Agregar_Electronico();

int Contar_Electronicos();
int buscarELectronicoXCod(int );



void Menu_Electronico()
{
    int opc;
    bool bandera=true;

    while(bandera != false)
    {
        Borrar();

        MsjMenu_Electronico();
        MsjOpcion();
        cin>>opc;


        switch(opc)
        {
            case 1:
                Agregar_Electronico();
            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
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

int Contar_Electronicos()
{
    int regs=0;
    long bytes=0;


    FILE *p;
    p=fopen(elec,"rb");
    if(p == NULL)return -1;

    fseek(p,0,2);
    bytes=ftell(p);

    fclose(p);

    regs=bytes/sizeof(LibroElectronico);

    return regs;
}

void Agregar_Electronico()
{

    Borrar();

    cout<<"  AGREGAR NUEVO LIBRO ELECTRONICO"<<endl;
    LineasLargas();
    cout<<"  INGRESE LOS DATOS DEL LIBRO "<<endl;
    LineasLargas();

    LibroElectronico reg;


    int x=reg.CargarElectronico();


    if()
    {

    }
    else
    {

    }

}

int

int LibroElectronico::CargarElectronico()
{
    int x=Contar_Electronicos();

    if(x == -1)
    {
        CodLibro=1;
               CodLibro=x+1;
        cout<<"  TITULO: ";
        cin.ignore();
        cin.getline(Titulo,30);
        strupr(Titulo);
        cout<<"  AUTOR: ";
        cin.ignore(Autor,30);
        strupr(Autor);
        cout<<"  PAGINAS: ";
        cin>>Pags;
        while(pags < 0)
        {
            cout<<"  VERIFIQUE QUE SEA MAYOR A 0"<<endl;
            cout<<"  PAGINAS: ";
            cin>>Pags;
        }

        cout<<"  STOCK DISPONIBLE: ";
        cin>>stock;

        while(stock<0)
        {
            cout<<"  VUELVA A INGRESAR EL STOCK"<<endl;
            cout<<"  STOCK: ";
            cin>>Stock;
        }

        cout<<"  PRECIO: ";
        cin>>Precio;

        while(Precio<0.0)
        {
            cout<<"  EL PRECIO DEBE SER POSITIVO"<<endl;
            cout<<"  PRECIO: ";
            cin>>Precio;
        }

        Estado=true;
        return 1;
    }
    else
    {
        CodLibro=x+1;
        cout<<"  TITULO: ";
        cin.ignore();
        cin.getline(Titulo,30);
        strupr(Titulo);
        cout<<"  AUTOR: ";
        cin.ignore(Autor,30);
        strupr(Autor);
        cout<<"  PAGINAS: ";
        cin>>Pags;
        while(pags < 0)
        {
            cout<<"  VERIFIQUE QUE SEA MAYOR A 0"<<endl;
            cout<<"  PAGINAS: ";
            cin>>Pags;
        }

        cout<<"  STOCK DISPONIBLE: ";
        cin>>stock;

        while(stock<0)
        {
            cout<<"  VUELVA A INGRESAR EL STOCK"<<endl;
            cout<<"  STOCK: ";
            cin>>Stock;
        }

        cout<<"  PRECIO: ";
        cin>>Precio;

        while(Precio<0.0)
        {
            cout<<"  EL PRECIO DEBE SER POSITIVO"<<endl;
            cout<<"  PRECIO: ";
            cin>>Precio;
        }

        Estado=true;
        return 1;
    }


    return -1;

}

int buscarELectronicoXCod(int cod)
{
    int pos=0;
    LibroElectronico reg;

    while(reg.LeerEnDiscoE(pos))
    {

        pos++;
    }


}

#endif // LIBELECTRONICO_H_INCLUDED
