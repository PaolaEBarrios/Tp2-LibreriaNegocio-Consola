#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED

void Alta_libro();
void Listar_todos();
int  Buscar_LibroXid(int );

void Modificar_Libro();
void Modificar_Stock();
void Modificar_Precio();
void Modificar_Titulo();

bool Eliminar_Archivolibro(int );
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


void Menu_Libro()
{
    int opc;
    bool bandera=1;


    while(bandera != 0)
    {
        Borrar();
        MsjMenuLibro();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                Alta_libro();
            break;
            case 2:
                Modificar_Libro();
            break;
            case 3:
                Borrar_libro();
            break;
            case 4:
                Buscar_Listar_Libros();
            break;
            case 0:
                bandera=0;
            break;
            default:
                OpcionError();
                Pausa();
            break;
        }


    }

}

int Libros::Cargar()
{
    cout<<"  CODIGO DEL LIBRO: ";
    cin>>CodLibro;
    while(CodLibro < 100)
    {
        cout<<" EL CODIGO DEBE SER NAYOR A 100(CIEN)"<<endl;
        cout<<"  CODIGO DEL LIBRO: ";
        cin>>CodLibro;
    }

    int x=Buscar_LibroXid(CodLibro);

    if(x == -1)
    {

        cout<<"  TITULO: ";
        cin.ignore();
        cin.getline(Titulo,30);
        strupr(Titulo);
        cout<<"  AUTOR: ";
        cin.getline(Autor,15);
        strupr(Autor);
        cout<<"  PAGINAS: ";
        cin>>Pags;

        while(Pags < 1)
        {
            cout<<"  LA CANTIDAD DEBE SER MAYOR A 0"<<endl;
            cout<<"  PAGINAS: ";
            cin>>Pags;
        }

      //  cout<<"  AÑO: ";
        //cin>>Anio;

        cout<<"  STOCK:  ";
        cin>>Stock;

        while(Stock < 1)
        {
            cout<<"  EL STOCK DEBE SER MAYOR A 0"<<endl;
            cout<<"  STOCK:  ";
            cin>>Stock;
        }

        cout<<"  PRECIO: ";
        cin>>Precio;

        while(Precio < 1.0)
        {
            cout<<"  EL PRECIO DEBE SER MAYOR A 0"<<endl;
            cout<<"  PRECIO: ";
            cin>>Precio;
        }

        Estado=true;

        return 1;

    }

    return -1;

}


void Libros::Mostrar()
{
    cout<<"   CODIGO LIBRO:  "<< CodLibro<<endl;
    cout<<"   TITULO:        "<<Titulo<<endl;
    cout<<"   AUTOR:         "<<Autor<<endl;
    cout<<"   PAGINAS:       "<<Pags<<endl;
    cout<<"   STOCK:         "<<Stock<<endl;
    cout<<"   PRECIO:       $"<<Precio<<endl;
//    cout<<" AÑO:           "<<Anio<<endl;
    if(Estado == true)
    {
        cout<<"   ESTADO:   DISPONIBLE "<<endl;
    }
    else{
        cout<<"   ESTADO:   NO DISPONIBLE"<<endl;
    }

    //FALTA ESTADO
    LineasCortas();
    LineasLargas();

}

void Libros::Grabar_en_disco()
{
    FILE *p;
    p=fopen(lib,"ab");
    if(p == NULL)
    {
        Error_al_agregar();
        return;
    }

    fwrite(this,sizeof(Libros),1,p);
    fclose(p);

}

int Libros::leer_en_disco(int pos)
{
    int x;

    FILE *p;
    p=fopen(lib,"rb");
    if(p == NULL)return 0;

    fseek(p,pos*sizeof*this,0);
    x=fread(this,sizeof(Libros),1,p);
    fclose(p);
    return x;
}

int Libros::modificar_en_disco(int pos)
{

    FILE *p;
    p=fopen(lib,"rb+");
    if(p == NULL)return -1;

    fseek(p,pos*sizeof*this,0);
    fwrite(this,sizeof(Libros),1,p);
    fclose(p);
    return 1;
}

void Alta_libro()
{
    Borrar();

    Libros l;

    cout<<"  INGRESE DATOS DEL LIBRO"<<endl;
    LineasLargas();

    int x=l.Cargar();
        Borrar();
    if(x != -1)
    {
        l.Grabar_en_disco();
        //Borrar();
        cout<<" LIBRO GRABADO EN DISCO  "<<endl;
    }
    else{
        cout<<" EL LIBRO YA EXISTE "<<endl;
    }
    Pausa();
}

void Listar_todos()
{
    Libros reg;
    int pos=0;
    int cont=0;

    while(reg.leer_en_disco(pos))
    {
        cont++;
        reg.Mostrar();
        pos++;
    }
    Pausa();
}


int Buscar_LibroXid(int id)
{

    Libros l;
    int pos=0;

    while(l.leer_en_disco(pos ))
    {
        if(id == l.getCod())
        {
            return pos;
        }
        pos++;
    }

    return -1;

}

void Modificar_Libro()
{
    int     opc;
    bool    bandera=1;

    while(bandera != 0)
    {
        Borrar();

        MsjModificar_Libro();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:

                Borrar();
                Modificar_Stock();

            break;
            case 2:
                Borrar();
                Modificar_Precio();

            break;
            case 3:
                Borrar();
                Modificar_Titulo();

            break;
            case 0:
                bandera=0;
            break;
            default:
                OpcionError();
                Pausa();
            break;
        }

    }
}


void Modificar_Stock()
{
    int num;
    Borrar();

    cout<<"  MODIFICAR STOCK"<<endl;
    LineasLargas();

    cout<<"  CODIGO DEL LIBRO A MODIFICAR: ";
    cin>>num;

    int x=Buscar_LibroXid(num);
    cout<<endl;



    if(x != -1)
    {
        Libros reg;

        reg.leer_en_disco(x);

        if(reg.getestado()== true)
        {



            int cant;

            cout<<"  STOCK: ";
            cin>>cant;

            while(cant < 1)
            {
                cout<<"  STOCK: ";
                cin>>cant;
            }

            reg.setstock(cant);
            reg.modificar_en_disco(x);

            LineasLargas();
            cout<<" EXITO AL MODIFICAR STOCK"<<endl;
        }
        else
        {
            cout<<"  EL LIBRO NO EXISTE"<<endl;
            cout<<"  ERROR AL MODIFICAR"<<endl;
        }
    }
    else
    {
        cout<<"  EL LIBRO NO EXISTE"<<endl;
        cout<<"  ERROR AL MODIFICAR"<<endl;
    }

    LineasLargas();
    Pausa();
}

void Modificar_Precio()
{

    int num;//VARIABLE DE CODIGO LIBRO

    cout<<"  MODIFICAR PRECIO"<<endl;
    LineasCortas();

    cout<<"  CODIGO DEL LIBRO A MODIFICAR: ";
    cin>>num;
    LineasLargas();

    int x=Buscar_LibroXid(num);
    cout<<endl;

    if(x != -1)
    {
        Libros reg;
        reg.leer_en_disco(x);

        if(reg.getestado()== true)
        {

            float p;//VARIABLE FLOAT PRECIO
            cout<<"  NUEVO PRECIO: ";
            cin>>p;

            while(p <= 0.00)
            {
                cout<<"  NUEVO PRECIO: ";
                cin>>p;
            }

            reg.setprecio(p);
            reg.modificar_en_disco(x);

            LineasLargas();

            cout<<"  EXITO AL MODIFICAR PRECIO"<<endl;
        }
        else
        {
            cout<<"  EL LIBRO NO EXISTE"<<endl;
            cout<<"  ERROR AL MODIFICAR"<<endl;
        }
    }
    else
    {
            cout<<"  EL LIBRO NO EXISTE"<<endl;
            cout<<"  ERROR AL MODIFICAR"<<endl;
    }

    LineasLargas();
    Pausa();
}

void Modificar_Titulo()
{
    int num;

    cout<<"  MODIFICAR TITULO "<<endl;
    LineasLargas();

    cout<<"  CODIGO DEL LIBRO A MODIFICAR: ";
    cin>>num;

    int x=Buscar_LibroXid(num);//VARIABLE QUE GUARDA LA POSICION
    cout<<endl;

    if(x != -1)
    {
        Libros reg;
        reg.leer_en_disco(x);

        if(reg.getestado()==true)
        {


            char t[30];
            cout<<"  TITULO: ";
            cin.ignore();
            cin.getline(t,30);
            strupr(t);
            reg.settitulo(t);
            reg.modificar_en_disco(x);

            cout<<"  EXITO AL MODIFICAR"<<endl;
        }
        else
        {
            cout<<"  EL LIBRO NO EXISTE"<<endl;
            cout<<"  ERROR AL MODIFICAR"<<endl;
        }
    }
    else
    {
        cout<<"  EL LIBRO NO EXISTE"<<endl;
        cout<<"  ERROR AL MODIFICAR"<<endl;
    }

    LineasLargas();
    Pausa();
}

///////////////////////////////


////ELIMINAR TODOS LOS ARCHIVOS
bool Eliminar_libros()
{
    Libros reg;

    FILE *p;
    p=fopen(lib,"wb");
    if(p==NULL)return false;


    fwrite(&reg,sizeof(Libros),0,p);
    fclose(p);
    return true;

}

void Borrar_libro()
{
    int opc;
    bool bandera=false;


    while(bandera!= true)
    {
        Borrar();

        MsjEliminar_Libro();
        MsjOpcion();
        cin>>opc;

        switch(opc)
        {
            case 1:
                FISICO_Libro();
            break;
            case 2:
                Baja_libro();
            break;
            case 0:
                bandera=true;
            break;
            default:
                OpcionError();
                Pausa();
            break;
        }


    }

}

void FISICO_Libro()
{
    int cod;
    Borrar();

    cout<<"  ELIMINAR 1 LIBRO DEL ARCHIVO"<<endl;
    LineasLargas();
    cout<<"  INGRESE EL CODIGO DEL LIBRO: ";
    cin>>cod;

    int x=Buscar_LibroXid(cod);

    if(x != -1)
    {
        bool borrar=Eliminar_Archivolibro(cod);

        if(borrar == true )
        {
            copiarArchivosLibros();
            cout<<"  LIBRO ELIMINADO/BORRADO CON EXITO"<<endl;
        }
        else
        {
            cout<<"  ERROR AL ELIMINAR EL ARCHIVO"<<endl;
        }

    }
    else
    {
        cout<<"  EL LIBRO INGRESADO NO EXISTE"<<endl;
    }
    Pausa();
}


bool Eliminar_Archivolibro(int cod)
{

    Libros reg,reg2;

    ////COPIAR ARCHIVOS MENOS EL QUE QUIERO BORRAR
    FILE *p,*p2;

    p=fopen(lib,"rb");
    if(p == NULL)return false;
    p2=fopen(lib2,"wb");
    if(p2 == NULL)return false;


    while(fread(&reg,sizeof(Libros),1,p))
    {
        if(cod != reg.getCod())
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
    }

    fclose(p);
    fclose(p2);

    return true;
    ////////////////FIN

}


void copiarArchivosLibros()
{

    Libros reg,reg2;

    FILE *p,*p2;

    p=fopen(lib,"wb");
    if(p == NULL)exit(1);

    p2=fopen(lib2,"rb");
    if(p2 == NULL)exit(2);

    while(fread(&reg,sizeof(Libros),1,p2))
    {
            reg2.setCodLibro(reg.getCod());
            reg2.settitulo(reg.gettitulo());
            reg2.setAutor(reg.getautor());
            reg2.setpaginas(reg.getpags());
            reg2.setstock(reg.getstock());
            reg2.setprecio(reg.getprecio());
//            reg2.setanio(reg.getanio());
            reg2.setEstado(reg.getestado());

            fwrite(&reg2,sizeof(Libros),1,p);
    }

    fclose(p);
    fclose(p2);
}


void Baja_libro()
{
    int cod;
    Borrar();

    cout<<"  DAR DE BAJA LIBRO "<<endl;
    LineasLargas();
    cout<<"  INGRESE EL CODIGO DEL LIBRO: ";
    cin>>cod;

    int x=Buscar_LibroXid(cod);

    if(x != -1)
    {
        Libros reg;
        if(reg.getestado()== true)
        {
            reg.leer_en_disco(x);
            reg.setEstado(false);
            reg.modificar_en_disco(x);
            cout<<"  EXITO AL DAR DE BAJA LIBRO: "<<cod<<endl;
            LineasLargas();
        }
        else
        {
            LineasLargas();
            cout<<"  ERROR AL DAR DE BAJA"<<endl;
            cout<<"  PORQUE EL LIBRO YA ESTA DADO DE BAJA"<<endl;
            LineasLargas();
        }
    }
    else
    {
        LineasLargas();
        cout<<"  ERROR AL DAR DE BAJA"<<endl;
        cout<<"  COMPRUEBE QUE EL CODIGO EXISTA"<<endl;
        LineasLargas();
    }
    Pausa();
}

void Buscar_Listar_Libros()
{
    int opc;
    bool bandera=true;


    while(bandera != false)
    {

        Borrar();

        cout<<"  BUSCAR/LISTAR LIBROS"<<endl;
        LineasLargas();
        cout<<"  1 - BUSCAR/LISTAR POR CODIGO"<<endl;
        cout<<"  2 - BUSCAR/LISTAR POR TITULO"<<endl;
        cout<<"  3 - LISTAR EN ORDEN ASCENDENTE"<<endl;
        LineasLargas();
        cout<<"  0 - VOLVER AL MENU LIBROS"<<endl;
        LineasLargas();
        MsjOpcion();
        cin>>opc;


        switch(opc)
        {
            case 1:
                MostrarLibroXcod();
            break;
            case 2:
                MostrarLibroXtitulo();
            break;
            case 3:
                OrdenarLibros();
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


void MostrarLibroXcod()
{
    int cod;

    Borrar();

    cout<<"  BUSCAR LIBRO POR CODIGO"<<endl;
    LineasLargas();
    cout<<"  INGRESE EL CODIGO DEL LIBRO: ";
    cin>>cod;

    int x=Buscar_LibroXid(cod);


    if(x != -1)
    {


        Libros reg;
        reg.leer_en_disco(x);

        if(reg.getestado() != false)
        {
            cout<<endl;
            LineasCortas();
            reg.Mostrar();

        }
        else
        {
            cout<<endl;
            LineasLargas();
            cout<<"  EL LIBRO INGRESADO NO EXISTE : "<<cod<<endl;
            cout<<"  INTENTE NUEVAMENTE CON OTRO CODIGO"<<endl;
            LineasLargas();
        }


    }
    else
    {
        cout<<endl;
        LineasLargas();
        cout<<"  EL LIBRO INGRESADO NO EXISTE : "<<cod<<endl;
        cout<<"  INTENTE NUEVAMENTE CON OTRO CODIGO"<<endl;
        LineasLargas();
    }

    Pausa();
}


void MostrarLibroXtitulo()
{
    Borrar();

    char tit[30];
    int pos=0;
    int cont=0;

    cout<<"  BUSCAR LIBRO POR TITULO"<<endl;
    LineasLargas();
    cout<<"  INGRESE TITULO: ";
    cin.ignore();
    cin.getline(tit,30);

    strupr(tit);

    Libros reg;

    while(reg.leer_en_disco(pos))
    {
        if(reg.getestado()== true)//////////////LIBRO DISPONIBLE
        {
            /////////////////COMPARAR TITULOS
            if(strcmp(reg.gettitulo(),tit)== 0)
            {

                cout<<endl;
                reg.Mostrar();
                Pausa();
                cont++;
            }

        }
        pos++;
    }

    if(cont == 0)
    {
        cout<<"  EL TITULO NO FUE ENCONTRADO"<<endl;
        LineasCortas();
        Pausa();
    }

}


int Contar_libros()
{
    int regs=0;
    long bytes=0;
    FILE *p;


    p=fopen(lib,"rb");
    if(p == NULL )return -1;

    fseek(p,0,2);////0 - inicio 1 - actual 2- final
    bytes=ftell(p);
    fclose(p);

    regs=bytes/sizeof(Libros);

    return regs;

}

int BuscarXtitulo(char *t)
{
    Libros reg;
    int pos=0;


    while(reg.leer_en_disco(pos))
    {
        if(strcmp(reg.gettitulo(),t)==0)
        {
            return pos;
        }
        pos++;
    }

    return -1;
}

void OrdenarLibros()
{

    Borrar();
    cout<<"   LIBROS EN ORDEN ALFABETICO/ MOSTRAR"<<endl;
    cout<<"  ------------------------------------- "<<endl;



    int cant=Contar_libros();

    int filas=cant;
 //   int columnas=30;

    char (*mLibros)[30];
    mLibros=(char (*)[30]) malloc(cant*30*sizeof(char));
    if(mLibros == NULL)exit(1);

    	// Limpiar array
	for(int i=0; i<cant; i++)
    {
		for(int j=0; j<30; j++)
		{
			mLibros[i][j] = '\0';
		}
	}

    Libros reg;

    for(int z=0;z<filas;z++)
    {
        reg.leer_en_disco(z);
        strcpy(mLibros[z] ,reg.gettitulo());

    }



    	for(int x=0; x<cant; x++){
		for(int k=x+1; k<cant; k++) {
			// Comparamos los dos textos
			int result = strcmp(mLibros[x], mLibros[k]);

			// Si [j] es menor alfabeticamente que [i]
			if(result > 0) {
				char aux[30];

				// Copiamos [i] a aux
				memset(aux, '\0', 30);
				strcpy(aux, mLibros[x]);

				// Copiamos lo que estaba en [j] en [i]
				memset(mLibros[x], '\0', 30);
				strcpy(mLibros[x], mLibros[k]);

				// Copiamos el valor original de [i](aux) en [j]
				memset(mLibros[k], '\0', 30);
				strcpy(mLibros[k], aux);
			}
		}
	}


	// Mostrar datos en pantalla
	for(int i=0; i<cant; i++){


        int pos = BuscarXtitulo(mLibros[i]);
        if(pos != -1)
        {
            reg.leer_en_disco(pos);

            reg.Mostrar();
        }

        system("pause>null");
        //cin.get(); // hace que la ejecucíon se detenga hasta que se presione enter


	}

	Pausa();

    free(mLibros);

}



#endif // LIBRO_H_INCLUDED
