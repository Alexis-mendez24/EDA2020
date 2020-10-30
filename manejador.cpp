#include <stdlib.h>
#include "manejador.h"
#include <ctype.h>
#include <string.h>

struct str_Archivo
{
    char *nombre;
    struct str_Lineas *primeraLinea;
    struct str_Lineas *ultimaLinea;
};

struct str_Lineas
{
    char linea[50];
    struct str_Lineas *anterior;
    struct str_Lineas *siguiente;
};

//Pre: n/a.
//Post: Crea un Archivo vacio.
Archivo crearArchivo(char *nom)
{
    Archivo aux = new struct str_Archivo;
    aux->nombre = nom;
    aux->primeraLinea = NULL;
    aux->ultimaLinea = NULL;
    return aux;
}
//Pre:Recibe un archivo
//Post:Cambia el nombre de la posicion actual
void cambiarNombreArchivo(Archivo a,char * nom){
    a->nombre = nom;
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

//Pre: n/a.
//Post: Verifica si el archivo fue creado o si existe
bool fileExists(Archivo a)
{
    return a != NULL;
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
//Post: Devuelve el primer valor de la lista
Linea ObtenerPrimLi(Archivo a)
{
    return a->primeraLinea;
}

//Pre: Debe existir el Archivo con al menos una Linea Insertada
//Post: Devuelve el ultimo valor de la lista
Linea ObtenerUltiLi(Archivo a)
{
    return a->ultimaLinea;
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
void insertarAlInicio(Archivo &a, char *linea)
{
    Linea l = crearLineas(linea);
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
}

//Pre: Recibe un Archivo ya creado
//Post: Inserta un elemento al final de una linea
void insertarAlFinal(Archivo &a, char *linea, unsigned int nroLinea)
{

    if (a->ultimaLinea != NULL)
    {
        Linea l = crearLineas(linea);
        l->anterior = a->ultimaLinea;
        a->ultimaLinea->siguiente = l;
        a->ultimaLinea = l;
    }
    else
    {
        insertarAlInicio(a, linea);
    }
}

//Pre: Recibe un Archivo ya creado
//Post: Inserta un elemento al final de una linea
void insertarAlMedio(Archivo &a, char *linea, unsigned int nroLinea)
{
    int nromaxli = contarLineas(a);
    Linea l = crearLineas(linea);

    if (nromaxli == nroLinea)
    {
        l->siguiente = a->ultimaLinea;
        l->anterior = a->ultimaLinea->anterior;
        a->ultimaLinea->anterior->siguiente = l;
        a->ultimaLinea->anterior = l;
    }
    else
    {
        int cont = 1;
        Linea laux = a->primeraLinea;

        while (cont < nroLinea)
        {
            laux = laux->siguiente;
            cont++;
        }
        l->anterior = laux->anterior;
        l->siguiente = laux;
        laux->anterior->siguiente = l;
        laux->anterior = l;
    }
}

//Pre: Recibe un Archivo creado
//Post: Devuelve OK si inserta correcto
tipoRet insertarLinea(Archivo &a, char *linea, unsigned int nroLinea, char *error)
{
    tipoRet ret;
    if (fileExists(a))
    {
        int nromaxli = contarLineas(a);
        if (nroLinea != 0 && nroLinea <= nromaxli + 1)
        {
            if (isEmptyArch(a) || nroLinea == 1)
            {
                insertarAlInicio(a, linea);
            }
            else
            {
                if (nromaxli < nroLinea)
                {
                    insertarAlFinal(a, linea, nroLinea);
                }
                else
                {
                    insertarAlMedio(a, linea, nroLinea);
                }
            }
            ret = OK;
        }
        else
        {
            ret = ERROR;
            strcpy(error, "ERROR: Numero de Linea Invalido");
        }
    }
    else
    {
        ret = NO_IMPLEMENTADA;
        strcpy(error, "NO_IMPLEMENTADA: Archivo no existe");
    }
    return ret;
}

//Pre: Recibe un archivo no Vacio
//Post:Elimina primer linea
void borrarAlInicio(Archivo &a, int nroLinea)
{

    if (a->primeraLinea == a->ultimaLinea)
    {
        delete a->primeraLinea;
        a->primeraLinea = NULL;
        a->ultimaLinea = NULL;
    }
    else
    {
        a->primeraLinea = a->primeraLinea->siguiente;
        delete a->primeraLinea->anterior;
        a->primeraLinea->anterior = NULL;
    }
}

//Pre: Recibe un archivo no Vacio
//Post:Elimina la ultima
void borrarAlFinal(Archivo &a, int nroLinea)
{
    if (a->primeraLinea == a->ultimaLinea)
    {
        delete a->ultimaLinea;
        a->primeraLinea = NULL;
        a->ultimaLinea = NULL;
    }
    else
    {
        a->ultimaLinea = a->ultimaLinea->anterior;
        delete a->ultimaLinea->siguiente;
        a->ultimaLinea->siguiente = NULL;
    }
}

//Pre: Recibe un archivo no Vacio
//Post: Busca y elimina una linea definida por el usuario
void borrarAlMedio(Archivo &a, int nroLinea)
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
tipoRet borrarLinea(Archivo &a, unsigned int nroLinea, char *error)
{
    tipoRet ret;
    if (fileExists(a))
    {
        if (!isEmptyArch(a))
        {
            int nromaxli = contarLineas(a);
            if (nroLinea == 1)
            {
                borrarAlInicio(a, nroLinea);
                ret = OK;
            }
            else
            {
                if (nroLinea == nromaxli)
                {
                    borrarAlFinal(a, nroLinea);
                    ret = OK;
                }
                else
                {
                    if (nroLinea < nromaxli && nroLinea != 0)
                    {
                        borrarAlMedio(a, nroLinea);
                        ret = OK;
                    }
                    else
                    {
                        ret = ERROR;
                        strcpy(error, "ERROR: Numero de Linea Invalido");
                    }
                }
            }
        }
        else
        {
            ret = ERROR;
            strcpy(error, "ERROR: Archivo vacio");
        }
    }
    else
    {
        ret = NO_IMPLEMENTADA;
        strcpy(error, "NO_IMPLEMENTADA: Archivo no existe");
    }
    return ret;
}

//Pre:Recibe un archivo
//Post:Devuleve un archivo Vacio.
tipoRet borrarArchivo(Archivo &a)
{
    tipoRet ret;
    if (fileExists(a))
    {
        Linea l = ObtenerPrimLi(a);
        int nromaxli = contarLineas(a);
        if (!isEmptyArch(a))
        {
            while (a->primeraLinea->siguiente != NULL)
            {
                borrarAlInicio(a, nromaxli);
                nromaxli--;
                l = l->siguiente;
            }
            delete a;
            a = NULL;
        }
        else
        {
            delete a;
            a = NULL;
        }
        ret = OK;
    }
    else
    {
        ret = NO_IMPLEMENTADA;
    }
    return ret;
}