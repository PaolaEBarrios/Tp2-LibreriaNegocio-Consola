#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

////CLASES UTILIZADAS: LIBRO, LIBROLECTRONICO, CLIENTE, VENTAS


class Libros
{

    //ATRIBUTOS
    protected:
        int     CodLibro;
        char    Titulo[30];
        char    Autor[15];
        int     Pags;
        int     Stock;
        float   Precio;
   //     char    Editorial[20];
       // int     Anio;
        bool    Estado;

    //METODOS
    public:

        int     Cargar();
        void    Mostrar();
        void    Grabar_en_disco();
        int     leer_en_disco(int );
        int     modificar_en_disco(int );

        //SETTERS
        void setCodLibro(int cod){CodLibro=cod;}
        void settitulo(char *tit){strcpy(Titulo,tit);}
        void setAutor(char *a){strcpy(Autor,a);}
        void setpaginas(int pag){Pags=pag;}
        void setstock(int s){Stock=s;};
        void setprecio(float p){Precio=p;}
        void setEstado(bool e){Estado=e;}
     //   void setEditorial(char *e){strcpy(Editorial,e);}
      //  void setanio(int a){Anio=a;}

        //GETTERS
        int    getCod(){return CodLibro;}
        char  *gettitulo(){return Titulo;}
        char  *getautor(){return Autor;}
        int    getpags(){return Pags;}
        int    getstock(){return Stock;}
        float  getprecio(){return Precio;}
        bool   getestado(){return Estado;}
       // char   *getEditorial(){return Editorial;}
        //int    getanio(){return Anio;}
};



class Cliente
{
    private:

        int     CodCliente;
        char    Nombre[30];
        char    Email[50];
        char    NroTelefono[20];
        bool    Estado;

    public:

            int     Cargar();
            void    Mostrar();
            void    Grabar_en_disco();
            int     leer_en_disco(int );
            bool     Modificar_en_disco(int );

        //GETTERS
            int     getCodCliente(){return CodCliente;}
            char    *getNombre(){return Nombre;}
            char    *getEmail(){return Email;}
            char     *getTelefono(){return NroTelefono;}
            bool    getEstado(){return Estado;}

        //SETTERS

            void    setCodCliente(int cod){CodCliente=cod;}
            void    setNombre(char *n){strcpy(Nombre,n);}
            void    setEmail(char *e){strcpy(Email,e);}
            void    setTelefono(char *t){strcpy(NroTelefono,t);}
            void    setestado(bool e){Estado=e;}

};


class Venta//PEDIDOS-VENTAS
{
    private:

        int     codLibro;
        int     codCliente;
        int     codVenta;
        int     Cantidad;
        float   Total;
        int     dia, mes, anio;
        bool    Estado;//PARA BAJA LOGICA
        int     Pago;//CONCRETADO/PENDIENTE Y CANCELADO(ESTADO DEL PEDIDO)


    public:

        int     Cargar();
        void    Mostrar();
        void    grabar_en_disco();
        int     leer_En_disco(int );
        int     modificar_en_disco(int );

        //GETTERS
        int     getCodlibro(){return codLibro;}
        int     getCodcliente(){return codCliente;}
        int     getcodVenta(){return codVenta;}
        int     getCantidad(){return Cantidad;}
        float   getTotal(){return Total;}
        int     getdia(){return dia;}
        int     getmes(){return mes;}
        int     getAnio(){return anio;}
        bool    getEstado(){return Estado;}
        int     getPago(){return Pago;}

        //SETTERS

        void    setcodlibro(int codL){codLibro=codL;}
        void    setCodCliente(int codC){codCliente=codC;}
        void    setCodventa(int codV){codVenta=codV;}
        void    setCantidad(int cant){Cantidad=cant;}
        void    setTotal(float tot){Total=tot;}
        void    setdia(int d){dia=d;}
        void    setmes(int m){mes=m;}
        void    setanio(int a){anio=a;}
        void    setEstado(bool e){Estado=e;}
        void    setPago(int p){Pago=p;}
};




#endif // CLASES_H_INCLUDED
