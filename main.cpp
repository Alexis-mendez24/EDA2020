#include <stdlib.h>
#include <iostream>
#include "manejador.h"
#include <ctype.h>
#include <string.h>
using namespace std;

void limpiar_Pantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void menuPrincipal()
{
    cout << " ___________________________ " << endl;
    cout << "|                           |" << endl;
    cout << "|       MENU PRINCIPAL      |" << endl;
    cout << "|___________________________|" << endl;
    cout << "|                           |" << endl;
    cout << "|1 - Crea Archivo           |" << endl;
    cout << "|2 - Inserta Linea          |" << endl;
    cout << "|3 - Mostrar Texto          |" << endl;
    cout << "|4 - Borra Linea            |" << endl;
    cout << "|5 - Borra Archivo          |" << endl;
    cout << "|0 - Salir                  |" << endl;
    cout << "|___________________________|" << endl;
    cout << endl;
    cout << "Inserte Opcion:";
}

void subMenu(){
    cout << "El archivo Existe" << endl
        << endl;
    cout << "1 - Cambiar Nombre del archivo" << endl;
    cout << "2 - Remplazar archivo por uno nuevo Vacio" << endl;
    cout << "0 - Volver" << endl;
    cout << "Inserte Opcion: ";
}

tipoRet mostrarTexto(Archivo a)
{
    tipoRet ret;
    if (fileExists(a))
    {
        Linea l = ObtenerPrimLi(a);
        int contaLi = 0;
        if (!isEmptyArch(a))
        {   
            cout << "----------------------------------------------------" << endl;
            cout << headArch(a) << endl
                 << endl;
            while (!isEmptyLi(l))
            {
                headLi(l);
                contaLi++;
                cout << contaLi << "\t" << headLi(l) << endl;
                l = tailLiSig(l);
            }
            cout << "----------------------------------------------------" << endl;
            ret = OK;
        }
        else
        {   
            cout << "----------------------------------------------------" << endl;
            cout << headArch(a) << endl
                 << endl;
            cout << "No contiene lineas" << endl
                 << endl;
            cout << "----------------------------------------------------" << endl;
            ret = OK;
        }
    }
    else
    {
        ret = NO_IMPLEMENTADA;
        cout << "NO_IMPLEMENTADA: No existe archivo" << endl
             << endl;
    }
    return ret;
}

int main()
{
    Archivo a = NULL;
    tipoRet ret;
    int opc, nroli;
    char nom[20], line[50];
    char *error = new char[30];
    string arch;
    string lin;

    menuPrincipal();
    cin >> opc;
    limpiar_Pantalla();
    while (opc != 0)
    {
        if (opc == 1)
        {
            cout << "INSERTAR ARCHIVO" << endl
                 << endl;
            if (!fileExists(a))
            {
                cout << "Ingrese nombre del archivo: ";
                getline(cin, arch);
                getline(cin, arch);
                strcpy(nom, arch.c_str());
                a = crearArchivo(nom);
                cout << "Archivo creado." << endl
                     << endl;
                mostrarTexto(a);
            }
            else
            {
                subMenu();
                cin >> opc;
                if (opc == 1)
                {
                    cout << "CAMBIAR NOMBRE DEL ARCHIVO" << endl
                         << endl;
                    getline(cin, arch);
                    getline(cin, arch);
                    strcpy(nom, arch.c_str());
                    cambiarNombreArchivo(a, nom);
                }
                if (opc == 2)
                {
                    ret = borrarArchivo(a);
                    cout << "OK" << endl;
                    cout << "Ingrese nombre del archivo: ";
                    getline(cin, arch);
                    getline(cin, arch);
                    strcpy(nom, arch.c_str());
                    a = crearArchivo(nom);
                    cout << "Archivo creado." << endl
                         << endl;
                    mostrarTexto(a);
                    menuPrincipal();
                    cin >> opc;
                    limpiar_Pantalla();
                }
                if (opc == 0)
                {
                    limpiar_Pantalla();
                }
            }
        }
        if (opc == 2)
        {
            cout << "INSERTAR LINEA" << endl
                 << endl;
            cout << "Nro de Linea: ";
            cin >> nroli;
            cout << "Ingrese Linea: ";
            getline(cin, lin);
            getline(cin, lin);
            strcpy(line, lin.c_str());
            cout << endl;
            ret = insertarLinea(a, line, nroli, error);
            if (ret == OK)
            {
                cout << "OK" << endl;
            }
            else
            {
                cout << error << endl;
            }
        }
        if (opc == 3)
        {
            mostrarTexto(a);
        }
        if (opc == 4)
        {
            cout << "BORRAR LINEA\n\n";
            cout << "Nro de Linea: ";
            cin >> nroli;
            cout << endl
                 << endl;
            ret = borrarLinea(a, nroli, error);
            if (ret == OK)
            {
                cout << "OK" << endl;
            }
            else
            {
                cout << error << endl;
            }
        }
        if (opc == 5)
        {
            ret = borrarArchivo(a);
            if (ret == OK)
            {
                cout << "OK" << endl;
            }
            else
            {
                cout << "ERROR: Archivo Inexistente" << endl;
            }
        }
        menuPrincipal();
        cin >> opc;
        limpiar_Pantalla();
    }
    return 0;
}