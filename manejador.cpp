#include <stdlib.h>
#include <iostream>
#include "manejador.h"
#include <ctype.h>
#include <string.h>
using namespace std;

struct str_Archivo
{
    char nombre[20];
    struct str_Lineas *primeraLinea;
    struct str_Lineas *ultimaLinea;
};

struct str_Lineas
{
    char linea[50];
    struct str_Lineas *anterior;
    struct str_Lineas *siguiente;
};

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

//Pre: n/a.
//Post: Crea un Archivo vacio.
Archivo crearArchivo(char nom[20])
{
    Archivo aux = new struct str_Archivo;
    strcpy(aux->nombre, nom);
    aux->primeraLinea = NULL;
    aux->ultimaLinea = NULL;
    return aux;
}


//Pre: Debe existir Archivo.
//Post: Crea una linea.
Linea crearLineas(char line[50])
{
    Linea l = new struct str_Lineas;
    strcpy(l->linea, line);
    l->anterior = NULL;
    l->siguiente = NULL;
    return l;
}

//Pre: Debe existir el Archivo y Lineas.
//Post: Delvuelve True si las linea son Vacias.
bool isEmptyLi(Linea l)
{
    return l == NULL;
}

//Pre: Debe existir Archivo.
//Post: Delvuelve True si el archivo es Vacio.
bool isEmptyArch(Archivo a)
{
    if (a->primeraLinea == NULL && a->ultimaLinea == NULL)
        return true;
    else
    {
        return false;
    }
}

//Pre: Debe existir Archivo y al menos un valor en la Linea.
//Post: Devuelve el contenido o el valor *Char de una Linea.
char *headLi(Linea l)
{
    return l->linea;
}

//Pre: Debe existir Archivo
//Post: Devuelve el Nombre o el valor *Char del archivo
char *headArch(Archivo a)
{
    return a->nombre;
}

//Pre: Deben tener mas de una creada
//Post: Devuelve todos los elemenos menos el primero de una Linea
Linea tailLiSig(Linea l)
{
    return l->siguiente;
}

//Pre: Debe existir el Archivo con al menos una Linea Insertada
//Post: Devuelve todos los elemenos menos el primero del archivo
Linea ObtenerPrimLi(Archivo a)
{
    return a->primeraLinea;
}

//Pre: Recibe un Archivo existente
//Post: Devuelve el total de Lineas
int contarLineas(Archivo a)
{
    int cont = 0;
    Linea l = a->primeraLinea;
    if (!isEmptyArch(a))
    {
        Linea l = ObtenerPrimLi(a);
        while (l->linea != NULL)
        {
            cont++;
            l = l->siguiente;
        }
    }
    return cont;
}

//Pre: Recibe un Archivo ya creado
//Post: Inserta un elemento al inicio de una Linea
void insertarAlInicio(Archivo &a, char ver, char line[50])
{
    Linea l = crearLineas(line);
    l->siguiente = a->primeraLinea;
    l->anterior = NULL;
    a->primeraLinea = l;
    if (a->ultimaLinea == NULL)
    {
        a->ultimaLinea = l;
    }
    if (!isEmptyLi(a->primeraLinea->siguiente))
    {
        a->primeraLinea->siguiente->anterior = a->primeraLinea;
    }


    /*     Linea l=crearLineas(line);
    if(a->primeraLinea==NULL){
        a->primeraLinea=l;
        a->ultimaLinea=l;
    }
    else{
        l->siguiente=a->primeraLinea;
        a->primeraLinea->anterior=l;
        a->primeraLinea=l;
    } */
}


//Pre: Recibe un Archivo ya creado
//Post: Inserta un elemento al final de una linea
void insertarAlFinal(Archivo &a, char ver, char line[50], unsigned int nroLinea)
{

    if (a->ultimaLinea != NULL)
    {
        Linea l = crearLineas(line);
        l->anterior = a->ultimaLinea;
        a->ultimaLinea->siguiente = l;
        a->ultimaLinea = l;
    }
    else
    {
        insertarAlInicio(a, ver, line);
    }
}

//Pre: Recibe un Archivo ya creado
//Post: Inserta un elemento al final de una linea
void insertarAlMedio(Archivo &a, char ver, char line[50], unsigned int nroLinea)
{
    int nromaxli = contarLineas(a);
    Linea l = crearLineas(line);
    if (nroLinea == 1) {
        insertarAlInicio(a, ver, line);
    }
    else{
        if (nromaxli < nroLinea){
            insertarAlFinal(a, ver, line, nroLinea);
        }else{
            if (nromaxli == nroLinea){
                l->siguiente = a->ultimaLinea;
                l->anterior = a->ultimaLinea->anterior;
                a->ultimaLinea->anterior = l;
            }
            else{
                if (nromaxli > nroLinea){
                    int cont = 1;
                    Linea laux = a->primeraLinea;
                    Linea laux1;
                    while (cont < nroLinea)
                    {
                        laux1 = laux;
                        laux = laux->siguiente;
                        cont++;
                    }
                    l->anterior = laux1;
                    l->siguiente = laux;
                    laux1->anterior = l;
                    laux->anterior = l;
                }
            }
        }
    }
}

    //Pre: Recibe un Archivo creado
    //Post: Devuelve OK si inserta correcto
    tipoRet insertarLinea(Archivo & a, char ver, char line[50], unsigned int nroLinea, char *error)
    {
        tipoRet ret;
        if (isEmptyArch(a))
        {   
            if(nroLinea==1)
            {
                insertarAlInicio(a, ver, line);
                ret = OK;
            }
            else{
                ret=ERROR;
            }
           
        }
        else
        {   
            int nromaxli = contarLineas(a);
            if(nroLinea<=(nromaxli+1))
            {
                insertarAlMedio(a, ver, line, nroLinea);
                ret = OK;
            }
            else{
                ret=ERROR;
            }
        }
        
        return ret;
    }
    //Pre: Recibe un archivo no Vacio
    //Post:Elimina primer linea
    void borrarAlInicio(Archivo & a, char ver, int nroLinea)
    {   
        
        if(a->primeraLinea==a->ultimaLinea){
            Linea aux = a->primeraLinea;
            a->primeraLinea=NULL;
            a->ultimaLinea=NULL;
            delete aux;
        }
        else{
            Linea aux = a->primeraLinea->siguiente;
            a->primeraLinea->siguiente->anterior = NULL;
            delete a->primeraLinea;
            a->primeraLinea = aux;
        }
    }

    //Pre: Recibe un archivo no Vacio
    //Post:Elimina la ultima
    void borrarAlFinal(Archivo & a, char ver, int nroLinea)
    {
        Linea l = a->ultimaLinea->anterior;
        a->ultimaLinea->anterior->siguiente = NULL;
        delete a->ultimaLinea;
        a->ultimaLinea = l;
        
    }
    //Pre: Recibe un archivo no Vacio
    //Post: Busca y elimina una linea definida por el usuario
    void borrarAlMedio(Archivo & a, char ver, int nroLinea)
    {
        Linea l = a->primeraLinea;
        int cont = 1;
        while (cont < nroLinea)
        {
            l = l->siguiente;
            cont++;
        }
        l->anterior->siguiente = l->siguiente;
        l->siguiente->anterior = l->anterior;
        delete l;
    }

    //Pre:Recibe Numero de linea y un archivo
    //Post:Devuelve Lineas con el elemento eliminado
    tipoRet borrarLinea(Archivo & a, char ver, unsigned int  nroLinea, char *&error)
    {
        tipoRet  ret = OK;
        error=new char[1];
        strcpy(error,"");;
       
        if (a!=NULL)
        {
            if (!isEmptyArch(a))
            {
                 int nromaxli = contarLineas(a);
                if (nroLinea == 1)
                {
                    borrarAlInicio(a, ver, nroLinea);
                }else{
                    if (nroLinea == nromaxli)
                    {
                        borrarAlFinal(a, ver, nroLinea);
                    }else{
                        if (nroLinea < nromaxli )
                        {
                            borrarAlMedio(a, ver, nroLinea);
                           
                        }
                        else{
                            ret=ERROR;
                            error=new char[strlen("Numero de Linea Invalido")+1];
                            strcpy(error,"Numero de Linea Invalido");
                        }
                    }
                }
            }
            else{
                 ret=ERROR;
                 error=new char[strlen("Error, archivo vacio")+1];
                 strcpy(error,"Error, archivo vacio");
            }
            
        }
        else
        {
            ret = ERROR;
            error=new char[strlen("Archivo no existe")+1];
            strcpy(error,"Archivo no existe");
            
        }
        return ret;
    }

    void borrarArchivoAux(Archivo a)
    {
        int nromaxli = contarLineas(a);
        int cont = 1;
        Linea l = a->primeraLinea;
        while (cont < nromaxli)
        {
            l = l->siguiente;
            cont++;
        }
    }

    //Pre:Recibe un archivo
    //Post:Devuleve un archivo Vacio.
    tipoRet borrarArchivo(Archivo & a)
    {
        tipoRet ret;
        if (isEmptyArch(a)){
            delete a;
            a=NULL;
        }
        ret = OK;
        return ret;
    }
