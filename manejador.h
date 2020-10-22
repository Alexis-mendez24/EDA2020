#ifndef MANEJADOR_H
#define MANEJADOR_H

enum retorno{
OK, ERROR, NO_IMPLEMENTADA
};

typedef enum retorno tipoRet;
typedef struct str_Archivo * Archivo;
typedef struct str_Lineas * Linea;

//Funciones Axileares


//Pre: n/a.
//Post: Verifica si el archivo fue creado o si existe
bool existArch(Archivo a);

//Pre: Debe existir el Archivo y Lineas.
//Post: Delvuelve True si las linea son Vacias.
bool isEmptyLi(Linea l);

//Pre: Debe existir Archivo.
//Post: Delvuelve True si el archivo es Vacio.
bool isEmptyArch(Archivo a);

//Pre: Debe existir Archivo y al menos un valor en la Linea.
//Post: Devuelve el contenido o el valor *Char de una Linea.
char* headLi(Linea l);

//Pre: Debe existir Archivo
//Post: Devuelve el Nombre o el valor *Char del archivo
char* headArch(Archivo a);

//Pre: Deben tener mas de una creada
//Post: Devuelve todos los elemenos menos el primero de una Linea
Linea tailLiSig(Linea l);

//Pre: Debe existir el Archivo con al menos una Linea Insertada
//Post: Devuelve todos los elemenos menos el primero del archivo
Linea ObtenerPrimLi(Archivo a);

//Pre: Recibe un Archivo existente
//Post: Devuelve el total de Lineas
int contarLineas(Archivo a);

//Constructoras

//Pre:n/a
//Post:Crea un archivo vacio
Archivo crearArchivo(char nom[10]);

//Predicadoras

//Pre: Recibe un Archivo creado
//Post: Devuelve OK si inserta correcto de lo contrario ERROR
tipoRet insertarLinea(Archivo &a, char ver, char line[50],unsigned int nroLinea, char *&error);

//Pre:Recibe un archivo no vacio
//Post:Devuelve el contenido del archivo con sus lineas
tipoRet mostrarTexto(Archivo a, char ver);

//Destructoras

//Pre:Recibe Numero de linea y un archivo
//Post:Devuelve Lineas con el elemento eliminado
tipoRet borrarLinea(Archivo &a, char ver, unsigned int  nroLinea, char *&error);

//Pre:Recibe un archivo
//Post:Devuleve un archivo Vacio.
tipoRet borrarArchivo(Archivo &a);

#endif //MANEJADOR_H