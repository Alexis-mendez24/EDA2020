#include <stdlib.h>
#include <iostream>
#include "manejador.h"
#include <ctype.h>
#include <string.h>
using namespace std;

void limpiar_pantalla()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void menu(){
    cout<<"MENU PRINCIPAL"<<endl<<endl;
    cout<<"1 - Crea Archivo"<<endl;
    cout<<"2 - Inserta Linea"<<endl;
    cout<<"3 - Mostrar Texto"<<endl;
    cout<<"4 - Borra Linea"<<endl;
    cout<<"5 - Borra Archivo"<<endl<<endl;
    cout<<"0 - Salir"<<endl<<endl;
    cout<<"Inserte Opcion: ";
}

tipoRet mostrarTexto(Archivo a, char ver){
    tipoRet ret;
    Linea l =ObtenerPrimLi(a); //Obtiene la primer linea del archivo
    int contaLi=0;

    if(!isEmptyArch(a)){
        cout<<headArch(a)<<" - "<<ver<<endl<<endl;
        while(!isEmptyLi(l)){
            headLi(l);
            contaLi++;
            cout<<contaLi<<"\t"<<headLi(l)<<endl;
            l=tailLiSig(l);
        }
        cout<<"\n\n";
        ret= OK;
    }
    else{
        cout<<headArch(a)<<" - "<<ver<<endl<<endl;
        cout<<"No contiene lineas"<<endl<<endl;
    }
    
    return ret;
}

int main(){
    Archivo a;
    tipoRet ins, imp, delli, delarch;
    char nom[20], line[50];
    int opc;
    int nroli; 
    string arch="curriculum.txt";
    string lin;

    menu();    
    cin>>opc;
    system("clear");
    while(opc!=0){
        
        if(opc == 1){
            strcpy(nom,arch.c_str());
            a= crearArchivo(nom);
            
        }
        if( opc == 2){
            cout<<"INSERTAR LINEA"<<endl<<endl;
            cout<<"Nro de Linea: ";
            
            cin>>nroli;
            cout<<"Ingrese Linea: ";
            cin>>lin;
            cout<<"\n\n";
            strcpy(line,lin.c_str());
            ins=insertarLinea(a, '1', line, nroli, 'k');
            if(ins==OK){
                cout<<"Linea insertada"<<endl<<endl;
            }
            else {
                if(ins==ERROR){
                    cout<<"No se puede insertar linea"<<endl<<endl;
                }
            }
        }
        if(opc == 3){
            mostrarTexto(a, '1');
        }
        if(opc == 4){
            cout<<"BORRAR LINEA\n\n";
            cout<<"Nro de Linea: ";
            cin>>nroli;
            cout<<"\n\n";
            delli= borrarLinea(a, '1', nroli, 'k');
        }

        if(opc == 5){
            delarch= borrarArchivo(a);
        }
        menu();    
        cin>>opc;
        system("clear");    
    }







    return 0;
}