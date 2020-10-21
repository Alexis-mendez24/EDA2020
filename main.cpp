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
    Linea l = ObtenerPrimLi(a); //Obtiene la primer linea del archivo
    int contaLi=0;

    if(!isEmptyArch(a)){
        cout<<headArch(a)<<endl<<endl;
        while(!isEmptyLi(l)){
            headLi(l);
            contaLi++;
            cout<<contaLi<<"\t"<<headLi(l)<<endl<<endl;
            l=tailLiSig(l);
        }
        ret= OK;
    }
    else{
        cout<<headArch(a)<<endl<<endl;
        cout<<"No contiene lineas"<<endl<<endl;
    }
    
    return ret;
}

int main(){
    Archivo a;
    tipoRet ins, imp, delli, delarch;
    char nom[20], line[50];
    char * error;
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
            getline(cin, lin);
            getline(cin, lin);
            strcpy(line,lin.c_str());
            ins=insertarLinea(a, '1', line, nroli, error);
            
        }
        if(opc == 3){
            mostrarTexto(a, '1');
        }
        if(opc == 4){
            if(!isEmptyArch(a)){
                cout<<"BORRAR LINEA\n\n";
                cout<<"Nro de Linea: ";
                cin>>nroli;
                cout<<"\n";
                delli= borrarLinea(a, '1', nroli, error);        
                cout<<error<<endl;
                cout<<"\n";
            }else{
                cout<<"Archivo no contiene lineas"<<endl<<endl;
            }
  
        
            
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