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
    cout<<" ___________________________ "<<endl;
    cout<<"|                           |"<<endl;
    cout<<"|       MENU PRINCIPAL      |"<<endl;
    cout<<"|___________________________|"<<endl;
    cout<<"|                           |"<<endl;
    cout<<"|1 - Crea Archivo           |"<<endl;
    cout<<"|2 - Inserta Linea          |"<<endl;
    cout<<"|3 - Mostrar Texto          |"<<endl;
    cout<<"|4 - Borra Linea            |"<<endl;
    cout<<"|5 - Borra Archivo          |"<<endl;
    cout<<"|0 - Salir                  |"<<endl;
    cout<<"|___________________________|"<<endl<<endl;
    cout<<"Inserte Opcion:";
}

tipoRet mostrarTexto(Archivo a){
    tipoRet ret;
    if(a!=NULL){
        
        Linea l = ObtenerPrimLi(a); //Obtiene la primer linea del archivo
        int contaLi=0;
        if(!isEmptyArch(a)){
            cout<<headArch(a)<<endl<<endl;
            while(!isEmptyLi(l)){
                headLi(l);
                contaLi++;
                cout<<contaLi<<"\t"<<headLi(l)<<endl;
                l=tailLiSig(l);
            }
            cout<<endl;
            ret= OK;
        }
        else{
            cout<<headArch(a)<<endl<<endl;
            cout<<"No contiene lineas"<<endl<<endl;
        }
    }
    else
    {
        cout<<"ERROR: Existe archivo"<<endl<<endl;
    }
    
    
    return ret;
}

int main(){
    Archivo a=NULL;
    tipoRet ins, imp, delli, delarch;
    char nom[20], line[50];
    char * error;
    int opc;
    int nroli; 
    string arch="curriculum.txt";
    string lin;

    menu();    
    cin>>opc;
    limpiar_pantalla();
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
            cout<<endl<<endl;
            ins=insertarLinea(a, line, nroli, error);
            if(ins == OK){
                cout<<error<<endl;

            }
            else{
                cout<<error<<endl;

            }
            
        }
        if(opc == 3){
            mostrarTexto(a);
        }
        if(opc == 4){
           
                cout<<"BORRAR LINEA\n\n";
                cout<<"Nro de Linea: ";
                cin>>nroli;
                cout<<endl<<endl;
                delli= borrarLinea(a, nroli, error); 
                if(delli==OK)
                {
                    cout<<error<<endl;
                }       
                else
                    cout<<error<<endl;
           
                
            }
  
        if(opc == 5){
            delarch= borrarArchivo(a);
        }
        menu();    
        cin>>opc;
        limpiar_pantalla();   
    }
    return 0;
}