#ifndef MANEJADOR_H
#define MANEJADOR_H

enum retorno{
OK, ERROR, NO_IMPLEMENTADA
};

typedef enum retorno tipoRet;
typedef struct str_Archivo * Archivo;
typedef struct str_Lineas * Linea;
//Pre:n/a
//Post:Crea un archivo vacio

//Funciones Axileares
bool isEmptyLi(Linea l);
bool isEmptyArch(Archivo a);
char* headLi(Linea l);
char* headArch(Archivo a);
Linea tailLiSig(Linea l);
Linea ObtenerPrimLi(Archivo a);
int contarLineas(Archivo a);

//Constructoras
Archivo crearArchivo(char nom[10]);
tipoRet insertarLinea(Archivo &a, char ver, char line[50],unsigned int nroLinea, char error);
tipoRet mostrarTexto(Archivo a, char ver);
tipoRet borrarLinea(Archivo &a, char ver, int nroLinea, char error);
tipoRet borrarArchivo(Archivo &a);

#endif //MANEJADOR_H