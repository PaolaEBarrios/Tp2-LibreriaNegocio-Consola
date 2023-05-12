#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

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


void Menu_Cliente()
{
    int     opc;
    bool    bandera=true;

    while(bandera != false)
    {
        Borrar();
        MsjMenuCliente();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                AgregarCliente();
            break;
            case 2:
                Modificar_Cliente();
            break;
            case 3:
                EliminarCliente();
            break;
            case 4:
                ListarClientes();
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

int TraerCodigoAnterior()
{

    int cod;


    int x=Contar_Clientes();

    Cliente reg;

    reg.leer_en_disco(x-1);

    cod=reg.getCodCliente();

    if(cod != -1)
    {
        return cod;
    }
    return -1;
}

void Cliente::Grabar_en_disco()
{
    FILE *p;
    p=fopen(cli,"ab");
    if(p == NULL)
    {
        cout<<"  ERROR AL GRABAR CLIENTE"<<endl;
        pausita();
        return;
    }



    fwrite(this,sizeof(Cliente),1,p);
    fclose(p);

}


int Cliente::leer_en_disco(int pos)
{

    int x;

    FILE *p;
    p=fopen(cli,"rb");
    if(p == NULL)return -1;



    fseek(p,pos*sizeof*this,0);
    x=fread(this,sizeof(Cliente),1,p);
    fclose(p);
    return x;

}

bool Cliente::Modificar_en_disco(int pos)
{
    FILE *p;

    p=fopen(cli,"rb+");
    if(p == NULL)return false;


    fseek(p,pos*sizeof*this,0);
    fwrite(this,sizeof(Cliente),1,p);
    fclose(p);
    return true;
}

void Cliente::Mostrar()
{
    LineasLargas();
    cout<<"  CODIGO DEL CLIENTE: "<<CodCliente<<endl;
    cout<<"  NOMBRE DEL CLIENTE: "<<Nombre<<endl;
    cout<<"  EMAIL DEL CLIENTE:  "<<Email<<endl;
    cout<<"  NUMERO DE TELEFONO: "<<NroTelefono<<endl;
    if(Estado == true)
    {
        cout<<"  DISPONIBLE"<<endl;
    }
    else
    {
        cout<<"  DADO DE BAJA"<<endl;
    }

}

int Cliente::Cargar()
{

    cout<<"  INGRESE LOS DATOS DEL CLIENTE"<<endl;
    LineasLargas();

    int x=Contar_Clientes();

    if(x == -1  || x == 0)
    {
        CodCliente=1000;
        cout<<"  NOMBRE DEL CLIENTE: ";
        cin.ignore();
        cin.getline(Nombre,30);
        strupr(Nombre);
        cout<<"  EMAIL: ";
        cin.getline(Email,50);
        cout<<"  TELEFONO/CELULAR: ";
        cin.getline(NroTelefono,20);

        while(strlen(NroTelefono)<10)
        {
            cout<<"  EL NUMERO DEBE TENER UN MINIMO DE 10 DIGITOS"<<endl;
            cout<<"  TELEFONO/CELULAR: ";
            cin.getline(NroTelefono,20);
        }

        Estado=true;
        return 1;
    }
    else
    {
        int x;
        x=TraerCodigoAnterior();

        if(x == -1)
        {
            cout<<"  ERROR AL ASIGNAR CODIGO"<<endl;
            pausita();
            return -1;
        }

        CodCliente=x+1;

        cout<<"  NOMBRE DEL CLIENTE: ";
        cin.ignore();
        cin.getline(Nombre,30);
        strupr(Nombre);
        cout<<"  EMAIL: ";
        cin.getline(Email,50);
        cout<<"  TELEFONO/CELULAR: ";
        cin.getline(NroTelefono,20);

        while(strlen(NroTelefono)<10)
        {
            cout<<"  EL NUMERO DEBE TENER UN MINIMO DE 10 DIGITOS"<<endl;
            cout<<"  TELEFONO/CELULAR: ";
            cin.getline(NroTelefono,20);
        }

        Estado=true;
        return 1;
    }
}


int buscarClienteXid(int cod)
{
    int pos=0;
    Cliente reg;

    while(reg.leer_en_disco(pos))
    {
        if(reg.getCodCliente() == cod)
        {
            return pos;
        }
        pos++;
    }

    return -1;

}

int Contar_Clientes()
{
    int  regs=0;
    long bytes=0;


    FILE *p;
    p=fopen(cli,"rb");
    if(p ==  NULL)return -1;


    fseek(p,0,2);
    bytes=ftell(p);
    fclose(p);

    regs=bytes/sizeof(Cliente);

    return regs;

}

void AgregarCliente()
{
    Borrar();

    Cliente reg;

//    int cant=Contar_Clientes();

    int x=reg.Cargar();

    if(x != -1)
    {
        reg.Grabar_en_disco();
        cout<<endl;
        LineasLargas();
        cout<<"   EL CLIENTE FUE AÑADIDO CON EXITO"<<endl;

    }
    else
    {
        cout<<"  ERROR AL AÑADIR AL CLIENTE"<<endl;

    }

    Pausa();
}


void Modificar_Cliente()
{

    int  opc;
    bool Bandera=1;


    while(Bandera != 0)
    {
        Borrar();

        cout<<"  MODIFICAR LOS DATOS DEL CLIENTE"<<endl;
        LineasLargas();
        cout<<"  1 - MODIFICAR NOMBRE"<<endl;
        cout<<"  2 - MODIFICAR TELEFONO"<<endl;
        cout<<"  3 - MODIFICAR EMAIL"<<endl;
        LineasLargas();
        cout<<" 0 -  VOLVER AL MENU CLIENTES"<<endl;
        LineasLargas();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                Modificar_Nombre();
            break;
            case 2:
                Modificar_Tel();
            break;
            case 3:
                Modificar_Email();
            break;
            case 0:
                Bandera=0;
            break;
            default:
                OpcionError();
                pausita();
            break;
        }


    }


}


void Modificar_Nombre()
{
    int cod;
    Borrar();

    cout<<"  MODIFICAR NOMBRE DEL CLIENTE"<<endl;
    LineasLargas();
    cout<<"  INGRESAR CODIGO DEL CLIENTE: ";
    cin>>cod;

    while(cod < 1000)
    {
        cout<<"  INGRESAR CODIGO DEL CLIENTE(mayor de 1000): ";
        cin>>cod;
    }
    LineasLargas();
    int pos=buscarClienteXid(cod);



    if(pos != -1)
    {
        // VERIFICAR QUE ESTE ESTADO TRUE
        Cliente reg;
        reg.leer_en_disco(pos);

        if(reg.getEstado()== true)
        {
            char nom[30];
            cout<<"  NUEVO NOMBRE: ";
            cin.ignore();
            cin.getline(nom,30);
            strupr(nom);
            reg.setNombre(nom);

            bool x=reg.Modificar_en_disco(pos);
            if(x == true)
            {
                LineasLargas();
                cout<<"  EL NOMBRE FUE MODIFICADO CON EXITO"<<endl;
                LineasLargas();
                pausita();
            }
            else
            {
                cout<<"  ERROR AL MODIFICAR NOMBRE"<<endl;
                pausita();
            }

        }
        else
        {
            cout<<"  EL CLIENTE NO ESTA DISPONIBLE"<<endl;
            cout<<"  ERROR AL MODIFICAR"<<endl;
            pausita();
        }

    }
    else
    {
        cout<<"  EL CLIENTE NO EXISTE"<<endl;
        cout<<"  INTENTE CON OTRO CODIGO DE CLIENTE"<<endl;
        LineasLargas();
        pausita();
    }


}

void Modificar_Tel()
{
    int cod;
    Borrar();

    cout<<"  MODIFICAR EL TELEFONO DEL CLIENTE "<<endl;
    LineasLargas();
    cout<<"  INGRESE EL CODIGO DEL CLIENTE: ";
    cin>>cod;
    LineasLargas();

    int x=buscarClienteXid(cod);

    if(x != -1)
    {
        Cliente reg;
        reg.leer_en_disco(x);

        if(reg.getEstado()== true)
        {
            char num[20];
            cout<<"  INGRESE EL NUEVO N° DE TELEFONO: ";
            cin.ignore();
            cin.getline(num,20);

            while(strlen(num)<10)
            {
                cout<<"  EL NUMERO DEBE TENER UN MINIMO DE 10 DIGITOS"<<endl;
                cout<<"  TELEFONO/CELULAR: ";
                cin.getline(num,20);
            }


            reg.setTelefono(num);
            reg.Modificar_en_disco(x);


            cout<<endl;
            cout<<"  N° DE TELEFONO MODIFICADO CON EXITO"<<endl;
            pausita();

        }
        else
        {
            cout<<endl;
            cout<<"  EL CLIENTE NO ESTA DISPONIBLE"<<endl;
            cout<<"  EL CLIENTE NO EXISTE O FUE DADO DE BAJA"<<endl;
            LineasLargas();
            pausita();
        }


    }
    else
    {
        cout<<endl;
        cout<<"  EL CLIENTE NO EXISTE"<<endl;
        cout<<"  INGRESE OTRO CODIGO"<<endl;
        LineasCortas();
        pausita();
    }

}


void Modificar_Email()
{
    Borrar();

    int cod;


    cout<<"  MODIFICAR EMAIL DEL CLIENTE"<<endl;
    LineasLargas();

    cout<<"  INGRESE EL CODIGO DEL CLIENTE: ";
    cin>>cod;
    LineasLargas();

    int pos=buscarClienteXid(cod);


    if(pos != -1)
    {
        Cliente reg;

        reg.leer_en_disco(pos);

        if(reg.getEstado()== true )
        {
            char e[50];
            cout<<"  INGRESE EL NUEVO EMAIL: ";
            cin.ignore();
            cin.getline(e,50);

            reg.setEmail(e);

            reg.Modificar_en_disco(pos);


            cout<<"  EL EMAIL FUE MODIFICADO CON EXITO"<<endl;
            LineasLargas();
            pausita();
        }
        else
        {
            LineasLargas();
            cout<<"  EL CLIENTE NO ESTA DISPONIBLE"<<endl;
            cout<<"  ERROR AL INTENTAR MODIFICAR"<<endl;
            pausita();
        }

    }
    else
    {
        cout<<endl;
        cout<<"  EL CODIGO DEL CLIENTE NO EXISTE"<<endl;
        cout<<"  CLIENTE NO ENCONTRADO"<<endl;
        LineasLargas();
        pausita();
    }

}

void EliminarCliente()
{
    int opc;
    bool Bandera=true;


    while(Bandera != false)
    {
        Borrar();
        cout<<"  DAR BAJA/ELIMINAR AL CLIENTE"<<endl;
        LineasLargas();
        cout<<"  1 - ELIMINAR CLIENTE(ARCHIVO)"<<endl;
        cout<<"  2 - DAR DE BAJA (LOGICO)"<<endl;
        LineasLargas();
        cout<<"  0 - VOLVER AL MENU DE CLIENTES"<<endl;
        LineasLargas();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                Fisico_Cliente();
            break;
            case 2:
                Baja_Cliente();
            break;
            case 0:
                Bandera=false;
            break;
            default:
                OpcionError();
                pausita();
            break;

        }



    }


}


void Fisico_Cliente()
{
    //DAR LA OPCION DE SALIR DE ESTO

    Borrar();
    int cod;

    cout<<"   ELIMINAR EL ARCHIVO DEL CLIENTE"<<endl;
    cout<<"  ----------------------------------"<<endl;
    cout<<"   INGRESE EL CODIGO DEL CLIENTE: ";
    cin>>cod;

    int pos= buscarClienteXid(cod);

    if(pos != -1)
    {
        bool x=DieARCHIVOCliente(cod);

        if(x == true)
        {

            CopiarClientes();
            cout<<endl;
            cout<<"  CLIENTE ELIMINADO CON EXITO"<<endl;
            LineasLargas();
        }
        else
        {
            cout<<endl;
            cout<<"  ERROR AL ELIMINAR EL ARCHIVO CLIENTE: "<<cod<<endl;
            LineasLargas();

        }


    }
    else
    {
        cout<<"  EL CLIENTE NO EXISTE"<<endl;
        cout<<"  ERROR AL ELIMINAR"<<endl;
        LineasLargas();
        pausita();

    }

    Pausa();
}

void CopiarClientes()
{
    FILE *p,*p2;

    p=fopen(cli,"wb");
    if(p == NULL)
    {
        cout<<"  ERROR AL ABRIR EL ARCHIVO"<<endl;
        pausita();
        exit(1);
    }
    p2=fopen(cli2,"rb");
    if(p== NULL )
    {
        cout<<"  ERROR AL ABRIR EL ARCHIVO"<<endl;
        pausita();
        exit(1);
    }

    Cliente reg,reg2;
    //int pos=0;

    while(fread(&reg2,sizeof(Cliente),1,p2))
    {
        reg.setCodCliente(reg2.getCodCliente());
        reg.setEmail(reg2.getEmail());
        reg.setestado(reg2.getEstado());
        reg.setNombre(reg2.getNombre());
        reg.setTelefono(reg2.getTelefono());

        fwrite(&reg,sizeof(Cliente),1,p);

//        pos++;
    }

    fclose(p);
    fclose(p2);

}

bool DieARCHIVOCliente(int cod)
{
    FILE *p;

    p=fopen(cli2,"wb");
    if(p == NULL)return -1;

    Cliente reg,reg2;

    int pos=0;


    while(reg.leer_en_disco(pos))
    {
        if(reg.getCodCliente()!=cod)
        {

            reg2.setCodCliente(reg.getCodCliente());
            reg2.setNombre(reg.getNombre());
            reg2.setEmail(reg.getEmail());
            reg2.setTelefono(reg.getTelefono());
            reg2.setestado(reg.getEstado());

            fwrite(&reg2,sizeof(Cliente),1,p);
        }
        pos++;
    }


    fclose(p);
    return 1;

}

void Baja_Cliente()
{

    Borrar();
    int cod;

    cout<<"  DAR DE BAJA CLIENTE"<<endl;
    LineasLargas();

    cout<<"  INGRESE CODIGO DE CLIENTE: ";
    cin>>cod;


    int x=buscarClienteXid(cod);

    if(x != -1)
    {
        Cliente reg;
        reg.leer_en_disco(x);

        if(reg.getEstado() == true)
        {

            reg.setestado(false);
            reg.Modificar_en_disco(x);
            cout<<endl;
            cout<<"  EXITO AL DAR DE BAJA AL CLIENTE: "<<cod<<endl;
            LineasLargas();

        }
        else
        {
            cout<<"  EL CLIENTE YA ESTA DADO DE BAJA"<<endl;
            cout<<"  ERROR AL DAR DE BAJA"<<endl;
            LineasLargas();
           // pausita();
        }

    }
    else
    {
        cout<<"  EL CODIGO DE CLIENTE NO EXISTE"<<endl;

    }

    Pausa();

}


void ListarClientes()
{
    int  opc;
    bool bandera=true;

    while(bandera != false)
    {
        Borrar();


        cout<<"  BUSCAR/LISTAR CLIENTES"<<endl;
        LineasLargas();
        cout<<"  1  - BUSCAR Y LISTAR CLIENTE POR CODIGO"<<endl;
        cout<<"  2  - BUSCAR Y LISTAR CLIENTE POR LETRA"<<endl;
        cout<<"  3  - LISTAR TODOS "<<endl;
        LineasLargas();
        cout<<"  0  - VOLVER AL MENU CLIENTES"<<endl;
        LineasLargas();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                ClienteXcodigo();
            break;
            case 2:
                ClienteXNombre();
            break;
            case 3:
                ClienteTodosMostrar();
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


void ClienteXcodigo()
{
    int cod;
    Borrar();

    cout<<"  BUSCAR CLIENTE MEDIANTE SU CODIGO"<<endl;
    LineasLargas();
    cout<<"  CODIGO CLIENTE: ";
    cin>>cod;


    int pos=buscarClienteXid(cod);

    if(pos != -1)
    {

        Cliente reg;
        reg.leer_en_disco(pos);

        if(reg.getEstado() == true)
        {

            reg.Mostrar();

        }
        else
        {
            cout<<" EL CLIENTE NO EXISTE"<<endl;
            LineasLargas();
        }

    }
    else
    {
            cout<<" EL CLIENTE NO EXISTE"<<endl;
            LineasLargas();
    }

    Pausa();

}

void ClienteXNombre()
{
    Borrar();
    char Letra[3];
    bool bandera;
    int cont=0;
    int pos=0;

    cout<<"  BUSCAR/LISTAR CLIENTES POR LETRA"<<endl;
    LineasLargas();
    cout<<"  SOLO ACEPTA EL INGRESO DE 2 LETRAS"<<endl;
    cout<<"  INGRESE LA LETRA QUE DESEA VER: ";
    cin.ignore();
    cin.getline(Letra,3);

    strupr(Letra);

    //COMPROBAR QUE EL ARCHIVO EXISTE
    FILE *p;
    p=fopen(cli,"rb");
    if(p == NULL)bandera=false;
    if(p)
    {
        fclose(p);
        bandera=true;
    }
    else
    {
        bandera=false;
    }

    if(bandera != false)
    {
        Cliente reg;

        while(reg.leer_en_disco(pos))
        {
            if(reg.getEstado()== true)
            {
                char l[30];
                strcpy(l,reg.getNombre());
                strupr(l);

                if(l[0]== Letra[0])
                {
                    cont++;
                    //CONTAR ANTES ASI AGREGO LOS RESULTADOS ENCONTRADOS
                    //cout<<"  RESULTADOS ENCONTRADOS: "<<cont<<endl;
                    reg.Mostrar();
                    cout<<endl;
                    LineasLargas();
                    pausita();
                }

            }
            pos++;
        }

        if(cont == 0)
        {
            LineasLargas();
            cout<<"  NO HAY CLIENTES CON LA LETRA/S: "<<Letra<<endl;
            LineasLargas();
        }

    }
    else
    {
        LineasLargas();
        cout<<"  NO HAY CLIENTES AGREGADOS"<<endl;
        cout<<"  CARGUE CLIENTES PARA USAR ESTA OPCION"<<endl;
        LineasLargas();
    }

    Pausa();

}

void ClienteTodosMostrar()
{
    Borrar();
    int pos=0,cont=0;
    Cliente reg;

    int x=reg.leer_en_disco(pos);

    cout<<"  TODOS LOS CLIENTES CARGADOS"<<endl;

    if(x!=-1)
    {


        while(reg.leer_en_disco(pos))
        {
            if(reg.getEstado()== true)
            {
                cont++;

                LineasLargas();
                reg.Mostrar();
                pausita();
            }
            pos++;
        }
        if(cont== 0)
        {
            cout<<endl;
            cout<<"  NO HAY CLIENTES QUE MOSTRAR"<<endl;
            LineasLargas();
        }

    }
    else
    {
        cout<<endl;
        cout<<"  NO HAY CLIENTES QUE MOSTRAR"<<endl;
        LineasLargas();
    }

    Pausa();
}

#endif // CLIENTES_H_INCLUDED
