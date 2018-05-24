#include "estructuras.h"
#include "QMessageBox"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QString>

using namespace std;
using std::cout;
using std::endl;

///Punteros Tabla Hash de Autobuses...................
typedef struct Nodo_TablaHash_A NodoTH_A;
NodoTH_A *PrimeroTH_A=NULL;
NodoTH_A *UltimoTH_A=NULL;
typedef struct NodoListaHash NodoLH;

///Punteros Tabla Hash de Pilotos......................
typedef struct Nodo_TablaHash_P NodoTH_P;
NodoTH_P *PrimeroTH_P=NULL;
NodoTH_P *UltimoTH_P=NULL;
typedef struct NodoAVLHash NodoAVLH;

///Punteros Lista Simple de Estaciones.................
typedef struct NodoListaEstacion NodoLE;
NodoLE *PrimeroE;
NodoLE *UltimoE;

///Punteros Lista Doble de Grafos......................
typedef struct NodoListaDoble NodoLD;
NodoLD *PrimeroLD;
NodoLD *UltimoLD;
typedef struct NodoGrafo NodoG;

///Punteros de Lista de Matrices........................
typedef struct NodoListaDobleM NodoLDM;
NodoLDM *PrimeroLDM;
NodoLDM *ULtimoLDM;
typedef struct NodoFila NodoF;
typedef struct NodoColumna NodoC;
typedef struct NodoMatriz NodoM;

///Punteros de Lista de Usuario.........................
typedef struct NodoListaLexicografica NodoLX;
NodoLX *PrimeroLX;
NodoLX *UltimoLX;
int TopeLX=37;

typedef struct NodoListaAux NodoLAux;
NodoLAux *PrimeroLAux;
NodoLAux *UltimoLAux;

///Punteros Lista de Bloques............................
typedef struct NodoBloque NodoB;
NodoB *PrimeroB;
NodoB *UltimoB;
int IDB=1;

typedef struct NodoLDobleB NodoLDB;
typedef struct NodoGrafoB NodoGB;
typedef struct NodoAVLBloque NodoAVLB;

int correlativo=1;
int correlativoB=0;
int contadorRuta=1;

//Encrypt...
QString Krip="";


Estructuras::Estructuras(QObject *parent) : QObject(parent)
{

}

void Estructuras::LLave_Ascii(QString clave, char *modelo, char *estado){

    int llave = 0;
    for (int i = 0; i < clave.length(); i++) {
         llave += (int)clave.at(i).toLatin1();
    }

    const std::string& Clave=clave.toStdString();
    char *Placa=new char[Clave.length()+1];
    strcpy(Placa,Clave.c_str());

    int indice = llave % 37;

    Agregar_TablaHash_Autobuses(indice,llave,Placa,modelo,estado);

}

void Estructuras::LLave_Ascii_Pilotos(QString DPI, QString Nombre, int Edad, char *Genero){
    int llaveK = 0;
    for (int i = 0; i < DPI.length(); i++) {
         llaveK += (int)DPI.at(i).toLatin1();
    }

    int llavek = 0;
    for (int i = 0; i < Nombre.length(); i++) {
         llavek += (int)Nombre.at(i).toLatin1();
    }

    const std::string& dpi=DPI.toStdString();
    char *Dpi=new char[dpi.length()+1];
    strcpy(Dpi,dpi.c_str());

    int indice = llaveK % 37;

    const std::string& nom=Nombre.toStdString();
    char *nombre=new char[nom.length()+1];
    strcpy(nombre,nom.c_str());

    Agregar_TablaHash_Pilotos(indice, llaveK, Dpi, nombre, llavek,  Edad, Genero);

}

void Estructuras::Agregar_TablaHash_Autobuses(int indice, int Clave, char *Placa, char *Modelo, char *Estado){
    NodoTH_A *aux=PrimeroTH_A;
    if(aux!=NULL && indice<37){
        while(aux!=NULL){
            if(aux->indice==indice){
                NodoLH *nuevo;
                nuevo=(NodoLH*)malloc(sizeof(struct NodoListaHash));
                nuevo->Clave=Clave;
                nuevo->Placa=Placa;
                nuevo->Modelo=Modelo;
                nuevo->Estado=Estado;
                nuevo->sig=NULL;
                nuevo->ant=NULL;

                if(aux->Primero==NULL){
                    nuevo->sig=NULL;
                    nuevo->ant=NULL;
                    aux->Primero=nuevo;
                    aux->Ultimo=nuevo;
                }else{
                    nuevo->sig=NULL;
                    nuevo->ant=aux->Ultimo;
                    aux->Ultimo->sig=nuevo;
                    aux->Ultimo=nuevo;
                }
            }
         aux=aux->sig;
        }
    }

    Graficar_TablaHash_Autobuses();
}

void Estructuras::Inicializar_TablaHash_Autobuses(){

    if(PrimeroTH_A==NULL){
        for(int i=0; i<37; i++){
            NodoTH_A *nuevo;
            nuevo=(NodoTH_A*)malloc(sizeof(struct Nodo_TablaHash_A));
            nuevo->indice=i;
            nuevo->sig=NULL;
            nuevo->ant=NULL;
            nuevo->Primero=NULL;
            nuevo->Ultimo=NULL;

            if(PrimeroTH_A==NULL){
                nuevo->sig=NULL;
                nuevo->ant=NULL;
                PrimeroTH_A=nuevo;
                UltimoTH_A=nuevo;

            }else{
                nuevo->sig=NULL;
                nuevo->ant=UltimoTH_A;
                UltimoTH_A->sig=nuevo;
                UltimoTH_A=nuevo;
            }
        }

        Graficar_TablaHash_Autobuses();
    }
}


void Estructuras::Agregar_TablaHash_Pilotos(int indice, int clave, char *DPI, char *Nombre, int llavek, int Edad, char *Genero){

    cout<<"indice: "<<indice<<" clave: "<<clave<<" DPI: "<<DPI<<" Nombre: "<<Nombre<<" Edad: "<<Edad<<" Genero: "<<Genero<<endl;

    NodoTH_P *aux=PrimeroTH_P;
    if(aux!=NULL && indice<37){
        while(aux!=NULL){
            if(aux->indice==indice){

            NodoAVLH *nuevo;
            nuevo=(NodoAVLH*)malloc(sizeof(struct NodoAVLHash));
            nuevo->Clave=clave;
            nuevo->DPI=DPI;
            nuevo->Nombre=Nombre;
            nuevo->llavek=llavek;
            nuevo->Edad=Edad;
            nuevo->Genero=Genero;
            nuevo->Altura=0;
            nuevo->fe=0;
            nuevo->Nivel=0;
            nuevo->izq=NULL;
            nuevo->der=NULL;
            nuevo->Contador=correlativo++;
            aux->RAIZ=Insertar(nuevo,aux->RAIZ);
            Ajustar_Fe(aux->RAIZ,0);

            break;
            }
         aux=aux->sig;
        }

      }


}

void Estructuras::Inicializar_TablaHash_Pilotos(){

        if(PrimeroTH_P==NULL){
            for(int i=0; i<37; i++){
                NodoTH_P *nuevo;
                nuevo=(NodoTH_P*)malloc(sizeof(struct Nodo_TablaHash_P));
                nuevo->indice=i;
                nuevo->sig=NULL;
                nuevo->ant=NULL;
                nuevo->RAIZ=NULL;

                if(PrimeroTH_P==NULL){
                    nuevo->sig=NULL;
                    nuevo->ant=NULL;
                    PrimeroTH_P=nuevo;
                    UltimoTH_P=nuevo;

                }else{
                    nuevo->sig=NULL;
                    nuevo->ant=UltimoTH_P;
                    UltimoTH_P->sig=nuevo;
                    UltimoTH_P=nuevo;
                }
            }

            Graficar_TablaHash_Pilotos();
        }

}

////********************* Arbol AVL HASH...................................................
int Estructuras::Altura(NodoAVLHash *actual){
    if(actual==NULL){
        return 0;
    }else{
        return actual->Altura;
    }
}

int Estructuras::Mayor(int num1, int num2){
    if(num1>num2){
        return num1;
    }else{
        return num2;
    }
}


///****************ROTACIONES*************************************
NodoAVLH *Estructuras::Izquierda(NodoAVLH *n1){
    NodoAVLH *n2 =n1->izq;
    n1->izq=n2->der;
    n2->der=n1;
    n1->Altura=Mayor(Altura(n1->izq),Altura(n1->der)) +1;
    n2->Altura=Mayor(Altura(n2->izq), n1->Altura) +1;
    return n2;
}

NodoAVLH *Estructuras::Derecha(NodoAVLH *n1){
    NodoAVLH *n2 =n1->der;
    n1->der=n2->izq;
    n2->izq=n1;
    n1->Altura=Mayor(Altura(n1->izq), Altura(n1->der)) +1;
    n2->Altura=Mayor(Altura(n2->der), n1->Altura) +1;
    return n2;
}

NodoAVLH *Estructuras::IzquierdaDerecha(NodoAVLH *n1){
    n1->izq=Derecha(n1->izq);
    return Izquierda(n1);
}

NodoAVLH *Estructuras::DerechaIzquierda(NodoAVLH *n1){
    n1->der=Izquierda(n1->der);
    return Derecha(n1);
}

///***********INSERTAR EN EL ARBOL AVL****************************
NodoAVLH *Estructuras::Insertar(NodoAVLH *nuevo, NodoAVLH *actual){

   if(actual == NULL){
       actual = nuevo;

   }else if(nuevo->llavek < actual->llavek){
       actual->izq=Insertar(nuevo,actual->izq);

       if((Altura(actual->der)-Altura(actual->izq))==-2){

           if(nuevo->llavek < actual->izq->llavek){
               actual=Izquierda(actual);

           }else{

               actual=IzquierdaDerecha(actual);
           }

       }

   }else if(nuevo->llavek > actual->llavek){
       actual->der=Insertar(nuevo,actual->der);

       if((Altura(actual->der) - Altura(actual->izq))==2){

           if(nuevo->llavek > actual->der->llavek){

               actual=Derecha(actual);

           }else{

               actual = DerechaIzquierda(actual);
           }
       }
   }else{

       cout<<"Valores Repetidos...  "<<endl;
       //cout<<nuevo->Nombre<<endl;
   }

       actual->Altura = Mayor(Altura(actual->izq), Altura(actual->der)) + 1;
       return actual;

}

///********METODO PARA OBTENER EL NODO REEMPLAZO****************
NodoAVLH *Estructuras::Obtener_Reemplazo(NodoAVLH *reemp){
    NodoAVLH *reemplazarPadre=reemp;
    NodoAVLH *reemplazo=reemp;
    NodoAVLH *auxiliar=reemp->der;
    while(auxiliar!=NULL){
        reemplazarPadre=reemplazo;
        reemplazo=auxiliar;
        auxiliar=auxiliar->izq;
    }
    if(reemplazo!=reemp->der){
        reemplazarPadre->izq=reemplazo->der;
        reemplazo->der=reemp->der;
    }
    cout<<"El Nodo Reemplazo es "<<reemplazo->Nombre<<endl;
    return reemplazo;
}

///*********EQUILIBRAR ARBOL AVL********************************
void Estructuras::Ajustar_Fe(NodoAVLH *actual, int Nivel){

        if(actual!=NULL){
           actual->fe=Altura(actual->der)-Altura(actual->izq);
           actual->Altura = Mayor(Altura(actual->izq), Altura(actual->der)) + 1;
           actual->Nivel=Nivel;
              if(actual->izq!=NULL){

               Ajustar_Fe(actual->izq, Nivel+1);

           }
           if(actual->der!=NULL){

            Ajustar_Fe(actual->der, Nivel+1);

           }

         }
}

void Estructuras::Graficar_TablaHash_Autobuses(){
    FILE *gra;
    gra=fopen("TablaHash1.dot","wt");
    fputs("digraph structs {\n ",gra);
    fputs("rankdir=LR;\n",gra);
    fputs("node [shape=record];" ,gra);
    NodoTH_A *aux=PrimeroTH_A;
    if(aux!=NULL){

    fputs("\n subgraph cluster_1 {\n",gra);
    fputs("node [style=filled];\n",gra);

    fputs("hashTable [label=\"",gra);
    for(int i=0;i<37;i++){
        fputs("{",gra);
        if(i<10){
             fputs("0",gra);
             fprintf(gra, "%d",i);
             fputs("&#92;n",gra);
             fputs("&#92;n",gra);
             fputs("&#92;n",gra);
             fputs(".",gra);
        }else{
             fprintf(gra, "%d",i);
             fputs("&#92;n",gra);
             fputs("&#92;n",gra);
             fputs("&#92;n",gra);
             fputs(".",gra);
        }
        fputs("|<f",gra);
        fprintf(gra, "%d",i);
        fputs(">}|",gra);
    }
     fputs("\",fillcolor=cyan];",gra);


     NodoTH_A *aux=PrimeroTH_A;
     if(aux!=NULL){
         int i=0;
         while(aux!=NULL){
             if(aux->Primero!=NULL){
                 fputs("\"",gra);
                 fputs("NodoL",gra);
                 fprintf(gra,"%s",aux->Primero->Placa);
                 fputs("\"",gra);
                 fputs("\n[ ",gra);
                 fprintf(gra, "label=\" " );
                 fputs("K: ",gra);
                 fprintf(gra, "%d",aux->Primero->Clave);
                 fputs("&#92;n",gra);
                 fputs("Placa: ",gra);
                 fprintf(gra, "%s",aux->Primero->Placa);
                 fputs("&#92;n",gra);
                 fputs("Modelo: ",gra);
                 fprintf(gra, "%s",aux->Primero->Modelo);
                 fputs("&#92;n",gra);
                 fputs("Estado: ",gra);
                 fprintf(gra, "%s",aux->Primero->Estado);
                 fputs("\"];\n",gra);

                 NodoLH *auxL=aux->Primero;
                 if(auxL!=NULL){
                     while (auxL!=NULL) {
                         fputs("\"",gra);
                         fputs("NodoL",gra);
                         fprintf(gra,"%s",auxL->Placa);
                         fputs("\"",gra);
                         fputs("\n[ ",gra);
                         fprintf(gra, "label=\" " );
                         fputs("K: ",gra);
                         fprintf(gra, "%d",auxL->Clave);
                         fputs("&#92;n",gra);
                         fputs("Placa: ",gra);
                         fprintf(gra, "%s",auxL->Placa);
                         fputs("&#92;n",gra);
                         fputs("Modelo: ",gra);
                         fprintf(gra, "%s",auxL->Modelo);
                         fputs("&#92;n",gra);
                         fputs("Estado: ",gra);
                         fprintf(gra, "%s",auxL->Estado);
                         fputs("\"];\n",gra);
                      auxL=auxL->sig;
                     }

                 }



                 fputs("hashTable:f",gra);
                 fprintf(gra,"%d",i);
                 fputs(" -> NodoL",gra);
                 fprintf(gra,"%s",aux->Primero->Placa);
                 fputs(";",gra);

             }
          i++;
          aux=aux->sig;
         }
     }

     aux=PrimeroTH_A;
     if(aux!=NULL){
         while(aux!=NULL){
             if(aux->Primero!=NULL){
                 NodoLH *auxL=aux->Primero;
                 if(auxL!=NULL){
                     while (auxL!=NULL) {
                         if(auxL!=aux->Ultimo){
                         fputs("\"NodoL",gra);
                         fprintf(gra,"%s",auxL->Placa);
                         fputs("\"-> \"NodoL",gra);
                         fprintf(gra,"%s",auxL->sig->Placa);
                         fputs( "\";\n",gra);
                         }
                      auxL=auxL->sig;
                     }

                 }
             }
          aux=aux->sig;
         }
     }



     fputs("color=\"orange\"\n",gra);
     fputs("style =\"filled, bold\"\n",gra);
     fputs("label =\"Tabla Hash Autobuses\"\n",gra);
     fputs("}\n",gra);

 }
 fputs("}",gra);
 fclose(gra);
 system("dot -Tpng TablaHash1.dot -o TablaHash1.png");

}

void Estructuras::Graficar_TablaHash_Pilotos(){
    gra2=fopen("TablaHash2.dot","wt");
    fputs("digraph structs {\n ",gra2);
    fputs("rankdir=LR;\n",gra2);
    fputs("node [shape=record,fontsize=9];" ,gra2);

    if(PrimeroTH_P!=NULL){

    fputs("\n subgraph cluster_1 {\n",gra2);
    fputs("node [style=filled];\n",gra2);

    fputs("hashTable [label=\"",gra2);
    for(int i=0;i<37;i++){
        fputs("{",gra2);
        if(i<10){
             fputs("0",gra2);
             fprintf(gra2, "%d",i);
             fputs("&#92;n",gra2);
             fputs("&#92;n",gra2);
             fputs("&#92;n",gra2);
             fputs(".",gra2);
        }else{
             fprintf(gra2, "%d",i);
             fputs("&#92;n",gra2);
             fputs("&#92;n",gra2);
             fputs("&#92;n",gra2);
             fputs(".",gra2);
        }
        fputs("|<f",gra2);
        fprintf(gra2, "%d",i);
        fputs(">}|",gra2);
    }
     fputs("\",fillcolor=cyan];",gra2);

     NodoTH_P *aux=PrimeroTH_P;
     if(aux!=NULL){
         int i=0;
         while(aux!=NULL){
             if(aux->RAIZ!=NULL){

                 Graficar_AVL(aux->RAIZ);

                 fputs("hashTable:f",gra2);
                 fprintf(gra2,"%d",i);
                 fputs(" -> NodoL",gra2);
                 fprintf(gra2,"%d",aux->RAIZ->Contador);

                 fputs(";",gra2);

             }
          i++;
          aux=aux->sig;
         }
     }



     fputs("color=\"orange\"\n",gra2);
     fputs("style =\"filled, bold\"\n",gra2);
     fputs("label =\"Tabla Hash Pilotos\"\n",gra2);
     fputs("}\n",gra2);

 }
 fputs("}",gra2);
 fclose(gra2);
 system("dot -Tpng TablaHash2.dot -o TablaHash2.png");
}


void Estructuras::Graficar_AVL(NodoAVLH *actual){
    if(actual != NULL)
    {
        if(actual->izq ==NULL && actual->der==NULL){
            fputs("\"",gra2);
            fputs("NodoL",gra2);
            fprintf(gra2,"%d",actual->Contador);
            fputs("\"",gra2);
            fputs("[ ",gra2);
            fprintf(gra2, "label=\" " );
            fputs("K: ",gra2);
            fprintf(gra2, "%d",actual->llavek);
            fputs("&#92;n",gra2);
            fputs("DPI: ",gra2);
            fprintf(gra2, "%s",actual->DPI);
            fputs("&#92;n",gra2);
            fputs("Nombre: ",gra2);
            fprintf(gra2, "%s",actual->Nombre);
            fputs("&#92;n",gra2);
            fputs("Edad: ",gra2);
            fprintf(gra2, "%d",actual->Edad);
            fputs("\"];\n",gra2);

        }else{
            fputs("\"",gra2);
            fputs("NodoL",gra2);
            fprintf(gra2,"%d",actual->Contador);
            fputs("\"",gra2);
            fputs("[ ",gra2);
            fprintf(gra2, "label=\"<C1>| " );
            fputs("K: ",gra2);
            fprintf(gra2, "%d",actual->llavek);
            fputs("&#92;n",gra2);
            fputs("DPI: ",gra2);
            fprintf(gra2, "%s",actual->DPI);
            fputs("&#92;n",gra2);
            fputs("Nombre: ",gra2);
            fprintf(gra2, "%s",actual->Nombre);
            fputs("&#92;n",gra2);
            fputs("Edad: ",gra2);
            fprintf(gra2, "%d",actual->Edad);
            fputs("|<C0>\"];\n",gra2);

        }
        if(actual->izq!=NULL){
            Graficar_AVL(actual->izq);
            fputs("NodoL",gra2);
            fprintf(gra2,"%d",actual->Contador);
            fputs(":C0->NodoL",gra2);
            fprintf(gra2,"%d",actual->izq->Contador);
            fputs("\n",gra2);

        }
        if(actual->der!=NULL){
            Graficar_AVL(actual->der);
            fputs("NodoL",gra2);
            fprintf(gra2,"%d",actual->Contador);
            fputs(":C1->NodoL",gra2);
            fprintf(gra2,"%d",actual->der->Contador);
            fputs("\n",gra2);
        }

    }
}

void Estructuras::Insertar_Lista_Estaciones(char *Codigo, char *Nombre, char *Ubicacion){
    NodoLE *nuevo;
    nuevo=(NodoLE*)malloc(sizeof(struct NodoListaEstacion));
    nuevo->Codigo=Codigo;
    nuevo->Nombre=Nombre;
    nuevo->Ubicacion=Ubicacion;
    nuevo->sig=NULL;
    nuevo->ant=NULL;

    if(PrimeroE==NULL){
        nuevo->sig=NULL;
        nuevo->ant=NULL;
        PrimeroE=nuevo;
        UltimoE=nuevo;

    }else{
        nuevo->sig=NULL;
        nuevo->ant=UltimoE;
        UltimoE->sig=nuevo;
        UltimoE=nuevo;

    }

}

void Estructuras::Graficar_Lista_Estaciones(){
    FILE *gra;
    gra=fopen("Lista_Estaciones.dot","wt");
    fputs("digraph structs {\n ",gra);
    fputs("rankdir=LR;\n",gra);
    fputs("node [shape=record];" ,gra);
    NodoLE *aux=PrimeroE;
    if(aux!=NULL){
        fputs("\n subgraph cluster_1 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=0;
        while (aux!=NULL) {
            fputs("\"",gra);
            fputs("NodoL",gra);
            fprintf(gra,"%d",a);
            fputs("\"",gra);
            fputs("\n[ ",gra);
            fprintf(gra, "label=\" " );
            fputs("Codigo: ",gra);
            fprintf(gra, "%s",aux->Codigo);
            fputs("&#92;n",gra);
            fputs("Nombre: ",gra);
            fprintf(gra, "%s",aux->Nombre);
            fputs("&#92;n",gra);
            fputs("Ubicacion: ",gra);
            fprintf(gra, "%s",aux->Ubicacion);
            fputs("\"];\n",gra);
         a++;
         aux=aux->sig;
        }

        aux=PrimeroE;
        int b=0;
        int c=b+1;
        if(aux!=NULL){
            while (aux->sig!=NULL) {
                fputs("NodoL",gra);
                fprintf(gra,"%d",b);
                fputs(" -> NodoL",gra);
                fprintf(gra,"%d",c);
                fputs(";",gra);
             b++;
             c++;
             aux=aux->sig;
            }
        }

        fputs("color=\"orange\"\n",gra);
        fputs("style =\"filled, bold\"\n",gra);
        fputs("label =\"Lista_Estaciones\"\n",gra);
        fputs("}\n",gra);

    }
    fputs("}",gra);
    fclose(gra);
    system("dot -Tpng Lista_Estaciones.dot -o Lista_Estaciones.png");


}

///*******Incertar en Lista Doble de las Rutas************************
void Estructuras::Agregar_ListaDoble(char *archivo){

    NodoLD *nuevo;
    nuevo=(NodoLD*)malloc(sizeof(struct NodoListaDoble));
    nuevo->Archivo=archivo;
    nuevo->sig=NULL;
    nuevo->ant=NULL;
    nuevo->PrimeroG=NULL;
    nuevo->UltimoG=NULL;

    if(PrimeroLD==NULL){
        nuevo->sig=NULL;
        nuevo->ant=NULL;
        PrimeroLD=nuevo;
        UltimoLD=nuevo;

    }else{
        nuevo->sig=NULL;
        nuevo->ant=UltimoLD;
        UltimoLD->sig=nuevo;
        UltimoLD=nuevo;
    }

}

bool Estructuras::Buscar_Archivo_Ruta(char *archivo){
    int dato =0;
    NodoLD *aux=PrimeroLD;
    if(aux!=NULL){
        while(aux!=NULL){
            if(strcmp(aux->Archivo,archivo)==0){
                 dato=1;
                 break;
            }

         aux=aux->sig;
        }
    }

    if(dato==0){
        Agregar_ListaDoble(archivo);
        return false;
    }else{
        return true;
    }

}

void Estructuras::Eliminar_Ultimo(char *Archivo){
    NodoLD *aux=PrimeroLD;
    if(aux!=NULL){
        while(aux!=NULL){
            if(strcmp(aux->Archivo,Archivo)==0){
                 aux->UltimoG->ant->sig=NULL;
                 aux->UltimoG=aux->UltimoG->ant;
                 break;
            }

         aux=aux->sig;
        }
    }

}

void Estructuras::Agregar_En_Grafo(char *archivo, char *Ruta, int dir){
    NodoLD *aux=PrimeroLD;
    if(aux!=NULL){
        while(aux!=NULL){
            if(strcmp(aux->Archivo,archivo)==0){
                 NodoG *nuevo;
                 nuevo=(NodoG*)malloc(sizeof(struct NodoGrafo));
                 nuevo->Codigo=Ruta;
                 nuevo->dir=dir;
                 nuevo->sig=NULL;
                 nuevo->ant=NULL;

                 if(aux->PrimeroG==NULL){
                     nuevo->sig=NULL;
                     nuevo->ant=NULL;
                     aux->PrimeroG=nuevo;
                     aux->UltimoG=nuevo;
                 }else{
                     nuevo->sig=NULL;
                     nuevo->ant=aux->UltimoG;
                     aux->UltimoG->sig=nuevo;
                     aux->UltimoG=nuevo;
                 }

                 break;
            }

         aux=aux->sig;
        }
    }
}


void Estructuras::Graficar_ListaGrafos(){
    FILE *gra;
    gra=fopen("Lista_Grafos.dot","wt");
    fputs("digraph structs {\n ",gra);
    fputs("rankdir=LR;\n",gra);
    fputs("node [shape=record];" ,gra);
    NodoLD *aux=PrimeroLD;
    if(aux!=NULL){
        fputs("\n subgraph cluster_1 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=0;
        while (aux!=NULL) {
            fputs("\"",gra);
            fputs("NodoL",gra);
            fprintf(gra,"%d",a);
            fputs("\"",gra);
            fputs("\n[ ",gra);
            fprintf(gra, "label=\" " );
            fputs("Codigo: ",gra);
            fprintf(gra, "%s",aux->Archivo);
            fputs("\",fillcolor=cyan];",gra);

            NodoG *auxG=aux->PrimeroG;
            if(auxG!=NULL){
                while(auxG!=NULL){
                    fputs("\"",gra);
                    fputs("NodoG",gra);
                    fprintf(gra,"%s",aux->Archivo);
                    fprintf(gra,"%s",auxG->Codigo);
                    fputs("\"",gra);
                    fputs("\n[ ",gra);
                    fprintf(gra, "label=\" " );
                    fputs("Ruta: ",gra);
                    fprintf(gra, "%s",auxG->Codigo);
                    fputs("&#92;n",gra);
                    fputs("dir: ",gra);
                    fprintf(gra, "%d",auxG->dir);
                    fputs("\"];\n",gra);
                 auxG=auxG->sig;
                }
            }



         a++;
         aux=aux->sig;
        }

        aux=PrimeroLD;
        int b=0;
        int c=b+1;
        if(aux!=NULL){
            while (aux!=NULL){
                if(aux!=UltimoLD){
                fputs("NodoL",gra);
                fprintf(gra,"%d",b);
                fputs(" -> NodoL",gra);
                fprintf(gra,"%d",c);
                fputs(";",gra);

                fputs("NodoL",gra);
                fprintf(gra,"%d",c);
                fputs(" -> NodoL",gra);
                fprintf(gra,"%d",b);
                fputs(";",gra);

                NodoG *auxG=aux->PrimeroG;
                if(auxG!=NULL){
                    fputs("NodoL",gra);
                    fprintf(gra,"%d",b);
                    fputs(" -> NodoG",gra);
                    fprintf(gra,"%s",aux->Archivo);
                    fprintf(gra,"%s",aux->PrimeroG->Codigo);
                    fputs(";",gra);
                    while (auxG!=NULL) {

                        if(auxG!=aux->UltimoG){
                            fputs("NodoG",gra);
                            fprintf(gra,"%s",aux->Archivo);
                            fprintf(gra,"%s",auxG->Codigo);
                            fputs(" -> NodoG",gra);
                            fprintf(gra,"%s",aux->Archivo);
                            fprintf(gra,"%s",auxG->sig->Codigo);
                            fputs(";",gra);
                        }

                     auxG=auxG->sig;
                    }

                }


                }else{

                    NodoG *auxG=aux->PrimeroG;
                    if(auxG!=NULL){
                        fputs("NodoL",gra);
                        fprintf(gra,"%d",b);
                        fputs(" -> NodoG",gra);
                        fprintf(gra,"%s",aux->Archivo);
                        fprintf(gra,"%s",aux->PrimeroG->Codigo);
                        fputs(";",gra);
                        while (auxG!=NULL) {

                            if(auxG!=aux->UltimoG){
                                fputs("NodoG",gra);
                                fprintf(gra,"%s",aux->Archivo);
                                fprintf(gra,"%s",auxG->Codigo);
                                fputs(" -> NodoG",gra);
                                fprintf(gra,"%s",aux->Archivo);
                                fprintf(gra,"%s",auxG->sig->Codigo);
                                fputs(";",gra);
                            }

                         auxG=auxG->sig;
                        }

                    }

                }

             b++;
             c++;
             aux=aux->sig;
          }


          }

        fputs("color=\"orange\"\n",gra);
        fputs("style =\"filled, bold\"\n",gra);
        fputs("label =\"Lista de Grafos\"\n",gra);
        fputs("}\n",gra);

    }
    fputs("}",gra);
    fclose(gra);
    system("dot -Tpng Lista_Grafos.dot -o Lista_Grafos.png");

}

///****************Lista Doble de Matrices***********************************

///***************Agregar Lista Doble....
void Estructuras::Agregar_Lista_Matrices(char *Archivo){
    NodoLDM *nuevo;
    nuevo=(NodoLDM*)malloc(sizeof(struct NodoListaDobleM));
    nuevo->Archivo=Archivo;
    nuevo->sig=NULL;
    nuevo->ant=NULL;
    nuevo->PrimeroC=NULL;
    nuevo->UltimoC=NULL;
    nuevo->PrimeroF=NULL;
    nuevo->UltimoF=NULL;

    if(PrimeroLDM==NULL){
        nuevo->sig=NULL;
        nuevo->ant=NULL;
        PrimeroLDM=nuevo;
        ULtimoLDM=nuevo;

    }else{

        nuevo->sig=NULL;
        nuevo->ant=ULtimoLDM;
        ULtimoLDM->sig=nuevo;
        ULtimoLDM=nuevo;
    }


}


////***************Agregar en Fila...
void Estructuras::Agregar_En_Fila(NodoListaDobleM *Actual, int Fila){
    NodoF *nuevo;
    nuevo=(NodoF*)malloc(sizeof(struct NodoFila));
    nuevo->Fila=Fila;
    nuevo->Abajo=NULL;  //*sig
    nuevo->Arriba=NULL; //*ant
    nuevo->PrimeroM=NULL;
    nuevo->UltimoM=NULL;

    if(Actual->PrimeroF==NULL){
        nuevo->Abajo=NULL;
        nuevo->Arriba=NULL;
        Actual->PrimeroF=nuevo;
        Actual->UltimoF=nuevo;

    }else{
        NodoF *aux=Actual->PrimeroF;
        int d=0;
        if(aux!=NULL){
            while (aux!=NULL) {
                if(aux->Fila==Fila){
                    d=1;
                    break;
                }
             aux=aux->Abajo;
            }

            if(d==0){
                nuevo->Abajo=NULL;
                nuevo->Arriba=Actual->UltimoF;
                Actual->UltimoF->Abajo=nuevo;
                Actual->UltimoF=nuevo;
            }

        }


    }

}

///***************Agregar en Columna...
void Estructuras::Agregar_En_Columna(NodoListaDobleM *Actual, int Columna){
    NodoC *nuevo;
    nuevo=(NodoC*)malloc(sizeof(struct NodoColumna));
    nuevo->Columna=Columna;
    nuevo->Izq=NULL; //*sig
    nuevo->Der=NULL; //*ant
    nuevo->PrimeroM=NULL;
    nuevo->UltimoM=NULL;

    if(Actual->PrimeroC==NULL){
        nuevo->Der=NULL;
        nuevo->Izq=NULL;
        Actual->PrimeroC=nuevo;
        Actual->UltimoC=nuevo;

    }else{
        NodoC *aux=Actual->PrimeroC;
        int d=0;
        if(aux!=NULL){
            while (aux!=NULL) {
                if(aux->Columna==Columna){
                    d=1;
                    break;
                }
             aux=aux->Izq;
            }

            if(d==0){
                nuevo->Izq=NULL;
                nuevo->Der=Actual->UltimoC;
                Actual->UltimoC->Izq=nuevo;
                Actual->UltimoC=nuevo;
            }

        }

    }

}

///**************Agrgar en Matriz....
void Estructuras::Agregar_En_Matriz(char *Archivo, char *placa, int Fila, int Columna){
    NodoLDM *aux=PrimeroLDM;
    if(aux!=NULL){
        while(aux!=NULL){
            if(strcmp(aux->Archivo,Archivo)==0){
                Agregar_En_Fila(aux,Fila); ///Agregar Fila...

                Agregar_En_Columna(aux,Columna); ///Agregar Columna...

               //Declarar Nodo Matriz....
                NodoM *nuevo;
                nuevo=(NodoM*)malloc(sizeof(struct NodoMatriz));
                nuevo->Placa=placa;
                nuevo->Fila=Fila;
                nuevo->Columna=Columna;
                nuevo->arriba==NULL;
                nuevo->abajo=NULL;
                nuevo->izq=NULL;
                nuevo->der=NULL;

                ///Insertar para Filas......
                NodoF *auxF=aux->PrimeroF;
                if(auxF!=NULL){
                    while (auxF!=NULL) {
                        if(auxF->Fila==Fila){

                            if(auxF->PrimeroM==NULL){
                                nuevo->izq=NULL;
                                nuevo->der=NULL;
                                auxF->PrimeroM=nuevo;
                                auxF->UltimoM=nuevo;
                            }else{
                                nuevo->izq=NULL;
                                nuevo->der=auxF->UltimoM;
                                auxF->UltimoM->izq=nuevo;
                                auxF->UltimoM=nuevo;
                            }

                         break;
                        }
                    auxF=auxF->Abajo;
                    }
                }

                ///Insertar para Columnas....
                 NodoC *auxC=aux->PrimeroC;
                if(auxC!=NULL){
                    while (auxC!=NULL) {
                        if(auxC->Columna==Columna){

                            if(auxC->PrimeroM==NULL){
                                nuevo->abajo=NULL;
                                nuevo->arriba=NULL;
                                auxC->PrimeroM=nuevo;
                                auxC->UltimoM=nuevo;
                            }else{
                                nuevo->abajo=NULL;
                                nuevo->arriba=auxC->UltimoM;
                                auxC->UltimoM->abajo=nuevo;
                                auxC->UltimoM=nuevo;
                            }

                         break;
                        }
                     auxC=auxC->Izq;
                    }
                }

             break;
            }



         aux=aux->sig;
        }
    }


}

bool Estructuras::Buscar_Archivo_Matriz(char *Archivo){
    int dato =0;
    NodoLDM *aux=PrimeroLDM;
    if(aux!=NULL){
        while(aux!=NULL){
            if(strcmp(aux->Archivo,Archivo)==0){
                 dato=1;
                 break;
            }

         aux=aux->sig;
        }
    }

    if(dato==0){
        Agregar_Lista_Matrices(Archivo);
        return false;
    }else{
        return true;
    }
}


void Estructuras::Graficar_Lista_Matrices(){
    FILE *gra;
    gra=fopen("Lista_Matrices.dot","wt");
    fputs("digraph structs {\n ",gra);
   // fputs("rankdir=LR;\n",gra);
    fputs("node [shape=record];" ,gra);
    NodoLDM *aux=PrimeroLDM;
    if(aux!=NULL){
        fputs("\n subgraph cluster_1 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=0;
        while (aux!=NULL) {
            //Nodo Lista Doble...
            fputs("\"",gra);
            fputs("NodoL",gra);
            fprintf(gra,"%d",a);
            fputs("\"",gra);
            fputs("\n[ ",gra);
            fprintf(gra, "label=\" " );
            fputs("Parqueo: ",gra);
            fprintf(gra, "%s",aux->Archivo);
             fputs("\",fillcolor=cyan];",gra);

            fputs("\"",gra);
            fputs("Nodo",gra);
            fprintf(gra,"%d",a);
            fputs("\"",gra);
            fputs("\n[ ",gra);
            fprintf(gra, "label=\" " );
            fprintf(gra,"%s",aux->Archivo);
             fputs("\",fillcolor=cyan];",gra);

            //Nodo Columnas....
            NodoC *auxC=aux->PrimeroC;
            if(auxC!=NULL){
                while(auxC!=NULL){
                    fputs("\"",gra);
                    fputs("NodoC",gra);
                    fprintf(gra,"%s",aux->Archivo);
                    fprintf(gra,"%d",auxC->Columna);
                    fputs("\"",gra);
                    fputs("\n[ ",gra);
                    fprintf(gra, "label=\" " );
                    fputs("C: ",gra);
                    fprintf(gra, "%d",auxC->Columna);
                    fputs("\"];\n",gra);
                auxC=auxC->Izq;
                }
            }

            //Nodo Filas...
            NodoF *auxF=aux->PrimeroF;
            if(auxF!=NULL){
                while(auxF!=NULL){
                    fputs("\"",gra);
                    fputs("NodoF",gra);
                    fprintf(gra,"%s",aux->Archivo);
                    fprintf(gra,"%d",auxF->Fila);
                    fputs("\"",gra);
                    fputs("\n[ ",gra);
                    fprintf(gra, "label=\" " );
                    fputs("F: ",gra);
                    fprintf(gra, "%d",auxF->Fila);
                    fputs("\"];\n",gra);

                    //Modo Matriz...
                    NodoM *auxM=auxF->PrimeroM;
                    if(auxM!=NULL){
                        while(auxM!=NULL){
                            fputs("\"",gra);
                            fputs("NodoM",gra);
                            fprintf(gra,"%s",aux->Archivo);
                            fprintf(gra,"%d",auxM->Fila);
                            fprintf(gra,"%d",auxM->Columna);
                            fputs("\"",gra);
                            fputs("\n[ ",gra);
                            fprintf(gra, "label=\" " );
                           // fputs("F: ",gra);
                            fprintf(gra, "%s",auxM->Placa);
                            fputs("\"];\n",gra);

                         auxM=auxM->izq;
                        }
                    }




                 auxF=auxF->Abajo;
                }
            }

         ////Rank......
         /// Rank Columnas...
         auxC=aux->PrimeroC;
         if(auxC!=NULL){
             fputs("{rank = same; ",gra);
             fputs("\"",gra);
             fputs("Nodo",gra);
             fprintf(gra,"%d",a);
             fputs("\"",gra);
             fputs(";",gra);
             while(auxC!=NULL){
                 fputs("\"",gra);
                 fputs("NodoC",gra);
                 fprintf(gra,"%s",aux->Archivo);
                 fprintf(gra,"%d",auxC->Columna);
                 fputs("\"",gra);
                 fputs(";",gra);
              auxC=auxC->Izq;
             }
             fputs("}\n",gra);
         }

         ///Rank Filas...
         auxF=aux->PrimeroF;
         if(auxF!=NULL){
             while(auxF!=NULL){
                 fputs("{rank = same; ",gra);
                 fputs("\"",gra);
                 fputs("NodoF",gra);
                 fprintf(gra,"%s",aux->Archivo);
                 fprintf(gra,"%d",auxF->Fila);
                 fputs("\"",gra);
                 fputs(";",gra);

                        NodoM *auxM=auxF->PrimeroM;
                        if(auxM!=NULL){
                            while(auxM!=NULL){
                                fputs("\"",gra);
                                fputs("NodoM",gra);
                                fprintf(gra,"%s",aux->Archivo);
                                fprintf(gra,"%d",auxM->Fila);
                                fprintf(gra,"%d",auxM->Columna);
                                fputs("\"",gra);
                                fputs(";",gra);
                             auxM=auxM->izq;
                            }
                        }
               fputs("}\n",gra);
              auxF=auxF->Abajo;
             }
         }


         a++;
         aux=aux->sig;
        }

        ///Enleces..........................................
        aux=PrimeroLDM;
        int b=0;
        int c=b+1;
        if(aux!=NULL){
            while (aux!=NULL){
                if(aux!=ULtimoLDM){
                fputs("NodoL",gra);
                fprintf(gra,"%d",b);
                fputs(" -> NodoL",gra);
                fprintf(gra,"%d",c);
                fputs(";",gra);

                fputs("NodoL",gra);
                fprintf(gra,"%d",c);
                fputs(" -> NodoL",gra);
                fprintf(gra,"%d",b);
                fputs(";",gra);

                fputs("NodoL",gra);
                fprintf(gra,"%d",b);
                fputs(" -> Nodo",gra);
                fprintf(gra,"%d",b);
                fputs(";",gra);

                fputs("Nodo",gra);
                fprintf(gra,"%d",b);
                fputs(" -> NodoC",gra);
                fprintf(gra,"%s",aux->Archivo);
                fprintf(gra,"%d",aux->PrimeroC->Columna);
                fputs(";",gra);

                fputs("Nodo",gra);
                fprintf(gra,"%d",b);
                fputs(" -> NodoF",gra);
                fprintf(gra,"%s",aux->Archivo);
                fprintf(gra,"%d",aux->PrimeroF->Fila);
                fputs(";",gra);


                NodoC *auxC=aux->PrimeroC;
                if(auxC!=NULL){
                    while(auxC!=NULL){
                        if(auxC!=aux->UltimoC){
                            fputs("NodoC",gra);
                            fprintf(gra,"%s",aux->Archivo);
                            fprintf(gra,"%d",auxC->Columna);
                            fputs(" -> NodoC",gra);
                            fprintf(gra,"%s",aux->Archivo);
                            fprintf(gra,"%d",auxC->Izq->Columna);
                            fputs(";",gra);
                        }
                     auxC=auxC->Izq;
                    }
                }

                fputs("\n\n",gra);
                NodoF *auxF=aux->PrimeroF;
                if(auxF!=NULL){
                    while(auxF!=NULL){
                        fputs("NodoF",gra);
                        fprintf(gra,"%s",aux->Archivo);
                        fprintf(gra,"%d",auxF->Fila);
                        fputs(" ->",gra);
                        NodoM *auxM=auxF->PrimeroM;
                        if(auxM!=NULL){
                            while(auxM!=NULL){
                                if(auxM!=auxF->UltimoM){
                                    fputs("\"NodoM",gra);
                                    fprintf(gra,"%s",aux->Archivo);
                                    fprintf(gra,"%d",auxM->Fila);
                                    fprintf(gra,"%d",auxM->Columna);
                                    fputs("\" ->",gra);
                                }else{
                                    fputs("\"NodoM",gra);
                                    fprintf(gra,"%s",aux->Archivo);
                                    fprintf(gra,"%d",auxM->Fila);
                                    fprintf(gra,"%d",auxM->Columna);
                                    fputs( "\"[dir=both,color=\"blue:black\"];\n",gra);
                                }

                             auxM=auxM->izq;
                            }
                        }

                     auxF=auxF->Abajo;
                    }
                }
                //...........................
                auxF=aux->PrimeroF;
                if(auxF!=NULL){
                    while(auxF->Abajo!=NULL){
                        fputs("NodoF",gra);
                        fprintf(gra,"%s",aux->Archivo);
                        fprintf(gra,"%d",auxF->Fila);
                        fputs(" ->",gra);
                        fputs("NodoF",gra);
                        fprintf(gra,"%s",aux->Archivo);
                        fprintf(gra,"%d",auxF->Abajo->Fila);
                        fputs(";",gra);
                     auxF=auxF->Abajo;
                    }
                }

                auxC=aux->PrimeroC;
                if(auxC!=NULL){
                    while(auxC!=NULL){
                        fputs("NodoC",gra);
                        fprintf(gra,"%s",aux->Archivo);
                        fprintf(gra,"%d",auxC->Columna);
                        fputs(" ->",gra);
                            NodoM *auxM=auxC->PrimeroM;
                            if(auxM!=NULL){
                                while(auxM!=NULL){
                                    if(auxM!=auxC->UltimoM){
                                        fputs("\"NodoM",gra);
                                        fprintf(gra,"%s",aux->Archivo);
                                        fprintf(gra,"%d",auxM->Fila);
                                        fprintf(gra,"%d",auxM->Columna);
                                        fputs("\" ->",gra);
                                    }else{
                                        fputs("\"NodoM",gra);
                                        fprintf(gra,"%s",aux->Archivo);
                                        fprintf(gra,"%d",auxM->Fila);
                                        fprintf(gra,"%d",auxM->Columna);
                                        fputs( "\"[dir=both,color=\"blue:black\"];\n",gra);
                                    }
                                 auxM=auxM->abajo;
                                }
                            }

                     auxC=auxC->Izq;
                    }
                }



                }else{///Else..............

                    fputs("NodoL",gra);
                    fprintf(gra,"%d",b);
                    fputs(" -> Nodo",gra);
                    fprintf(gra,"%d",b);
                    fputs(";",gra);

                    fputs("Nodo",gra);
                    fprintf(gra,"%d",b);
                    fputs(" -> NodoC",gra);
                    fprintf(gra,"%s",aux->Archivo);
                    fprintf(gra,"%d",aux->PrimeroC->Columna);
                    fputs(";",gra);

                    fputs("Nodo",gra);
                    fprintf(gra,"%d",b);
                    fputs(" -> NodoF",gra);
                    fprintf(gra,"%s",aux->Archivo);
                    fprintf(gra,"%d",aux->PrimeroF->Fila);
                    fputs(";",gra);

                    NodoC *auxC=aux->PrimeroC;
                    if(auxC!=NULL){
                        while(auxC!=NULL){
                            if(auxC!=aux->UltimoC){
                                fputs("NodoC",gra);
                                fprintf(gra,"%s",aux->Archivo);
                                fprintf(gra,"%d",auxC->Columna);
                                fputs(" -> NodoC",gra);
                                fprintf(gra,"%s",aux->Archivo);
                                fprintf(gra,"%d",auxC->Izq->Columna);
                                fputs(";",gra);
                            }
                         auxC=auxC->Izq;
                        }
                    }

                    fputs("\n\n",gra);
                   NodoF *auxF=aux->PrimeroF;
                   if(auxF!=NULL){
                       while(auxF!=NULL){
                           fputs("NodoF",gra);
                           fprintf(gra,"%s",aux->Archivo);
                           fprintf(gra,"%d",auxF->Fila);
                           fputs(" ->",gra);
                           NodoM *auxM=auxF->PrimeroM;
                           if(auxM!=NULL){
                               while(auxM!=NULL){
                                   if(auxM!=auxF->UltimoM){
                                       fputs("\"NodoM",gra);
                                       fprintf(gra,"%s",aux->Archivo);
                                       fprintf(gra,"%d",auxM->Fila);
                                       fprintf(gra,"%d",auxM->Columna);
                                       fputs("\" ->",gra);
                                   }else{
                                       fputs("\"NodoM",gra);
                                       fprintf(gra,"%s",aux->Archivo);
                                       fprintf(gra,"%d",auxM->Fila);
                                       fprintf(gra,"%d",auxM->Columna);
                                       fputs( "\"[dir=both,color=\"blue:black\"];\n",gra);
                                   }

                                auxM=auxM->izq;
                               }
                           }

                        auxF=auxF->Abajo;
                       }
                   }

                   //...........................
                   auxF=aux->PrimeroF;
                   if(auxF!=NULL){
                       while(auxF->Abajo!=NULL){
                           fputs("NodoF",gra);
                           fprintf(gra,"%s",aux->Archivo);
                           fprintf(gra,"%d",auxF->Fila);
                           fputs(" ->",gra);
                           fputs("NodoF",gra);
                           fprintf(gra,"%s",aux->Archivo);
                           fprintf(gra,"%d",auxF->Abajo->Fila);
                           fputs(";",gra);
                        auxF=auxF->Abajo;
                       }
                   }

                   auxC=aux->PrimeroC;
                   if(auxC!=NULL){
                       while(auxC!=NULL){
                           fputs("NodoC",gra);
                           fprintf(gra,"%s",aux->Archivo);
                           fprintf(gra,"%d",auxC->Columna);
                           fputs(" ->",gra);
                               NodoM *auxM=auxC->PrimeroM;
                               if(auxM!=NULL){
                                   while(auxM!=NULL){
                                       if(auxM!=auxC->UltimoM){
                                           fputs("\"NodoM",gra);
                                           fprintf(gra,"%s",aux->Archivo);
                                           fprintf(gra,"%d",auxM->Fila);
                                           fprintf(gra,"%d",auxM->Columna);
                                           fputs("\" ->",gra);
                                       }else{
                                           fputs("\"NodoM",gra);
                                           fprintf(gra,"%s",aux->Archivo);
                                           fprintf(gra,"%d",auxM->Fila);
                                           fprintf(gra,"%d",auxM->Columna);
                                           fputs( "\"[dir=both,color=\"blue:black\"];\n",gra);
                                       }
                                    auxM=auxM->abajo;
                                   }
                               }

                        auxC=auxC->Izq;
                       }
                   }


                }
             b++;
             c++;
             aux=aux->sig;
            }

            fputs("NodoL",gra);
            fprintf(gra,"%d",0);
            fputs(" -> NodoL",gra);
            fprintf(gra,"%d",b-1);
            fputs(";",gra);

            fputs("NodoL",gra);
            fprintf(gra,"%d",b-1);
            fputs(" -> NodoL",gra);
            fprintf(gra,"%d",0);
            fputs(";",gra);
        }

        fputs("color=\"orange\"\n",gra);
        fputs("style =\"filled, bold\"\n",gra);
        fputs("label =\"Lista_Matrices\"\n",gra);
        fputs("}\n",gra);

    }
    fputs("}",gra);
    fclose(gra);
    system("dot -Tpng Lista_Matrices.dot -o Lista_Matrices.png");


}


///***********Lista Mapeada Lexicograficamente************************
void Estructuras::LLave_Ascii_Lista_Lexicografica(QString DPI, char *Tarjeta, char *Nombre, int edad){
    int llaveK = 0;
    for (int i = 0; i < DPI.length(); i++) {
         llaveK += (int)DPI.at(i).toLatin1();
    }

    const std::string& dpi=DPI.toStdString();
    char *Dpi=new char[dpi.length()+1];
    strcpy(Dpi,dpi.c_str());

    int indice = llaveK % TopeLX;

    Agregar_En_Lista_Lexicografica(indice,llaveK,Dpi,Tarjeta,Nombre,edad);
    Calcular_Porcentaje();
}

void Estructuras::Agregar_En_Lista_Lexicografica(int indice, int Clave, char *DPI, char *Tarjeta, char *Nombre, int Edad){
    NodoLX *aux=PrimeroLX;
    if(aux!=NULL){
        while(aux!=NULL){
            if(aux->indice==indice){
                if(aux->Clave==0){
                    aux->Clave=Clave;
                    aux->DPI=DPI;
                    aux->Nombre=Nombre;
                    aux->Tarjeta=Tarjeta;
                    aux->Edad=Edad;
                }else{

                    NodoLX *aux2=PrimeroLX;
                    if(aux2!=NULL){
                        while (aux2!=NULL){
                            if(aux2->Clave==0){
                                aux2->Clave=Clave;
                                aux2->DPI=DPI;
                                aux2->Nombre=Nombre;
                                aux2->Tarjeta=Tarjeta;
                                aux2->Edad=Edad;

                             break;
                            }
                         aux2=aux2->sig;
                        }
                    }

                }
             break;
            }
         aux=aux->sig;
        }
    }

}

void Estructuras::Calcular_Porcentaje(){
    int Total = TopeLX;
    int cant =0;
    NodoLX *aux=PrimeroLX;
    if(aux!=NULL){
        while (aux!=NULL) {
            if(aux->Clave!=0){
                cant++;
            }
         aux=aux->sig;
        }
    }

    float porcentaje = (float)cant/(float)Total;
    if(porcentaje>0.8){
        cout<<"Rehashing"<<TopeLX<<endl;
        int aumentar=Total*0.15;
        TopeLX+=aumentar;
        Rehashing();
        cout<<TopeLX<<endl;
        QMessageBox::information(NULL,"Rehashing de 15%",QString("Tamaño Inicial: %1 \nTamaño Aumentado: %2").arg(QString::number(Total)).arg(QString::number(TopeLX)));
    }


}

void Estructuras::Rehashing(){
    NodoLX *aux=PrimeroLX;
    if(aux!=NULL){
        while(aux!=NULL){
            if(aux->Clave!=0){
                Agregar_En_Lista_Aux(aux->indice,aux->Clave,aux->DPI,aux->Tarjeta,aux->Nombre,aux->Edad);
            }
         aux=aux->sig;
        }
    }

    PrimeroLX=UltimoLX=NULL;

    Iniciar_Lista_Lexicografica();

    NodoLAux *auxX=PrimeroLAux;
    if(auxX!=NULL){
        while (auxX!=NULL) {
            Agregar_En_Lista_Lexicografica(auxX->indice,auxX->Clave,auxX->DPI,auxX->Tarjeta,auxX->Nombre,auxX->Edad);
         auxX=auxX->sig;
        }
    }

    PrimeroLAux=UltimoLAux=NULL;
}

void Estructuras::Iniciar_Lista_Lexicografica(){

    for(int i=0; i<TopeLX; i++){
        NodoLX *nuevo;
        nuevo=(NodoLX*)malloc(sizeof(struct NodoListaLexicografica));
        nuevo->indice=i;
        nuevo->Clave=0;
        nuevo->DPI="";
        nuevo->Tarjeta="";
        nuevo->Nombre="";
        nuevo->Edad=0;
        nuevo->sig=NULL;
        nuevo->ant=NULL;

        if(PrimeroLX==NULL){
            nuevo->sig=NULL;
            nuevo->ant=NULL;
            PrimeroLX=nuevo;
            UltimoLX=nuevo;

        }else{
            nuevo->sig=NULL;
            nuevo->ant=UltimoLX;
            UltimoLX->sig=nuevo;
            UltimoLX=nuevo;
        }

    }
}

void Estructuras::Agregar_En_Lista_Aux(int indice, int Clave, char *DPI, char *Tarjeta, char *Nombre, int edad){
    NodoLAux *nuevo;
    nuevo=(NodoLAux*)malloc(sizeof(struct NodoListaAux));
    nuevo->indice=indice;
    nuevo->Clave=Clave;
    nuevo->DPI=DPI;
    nuevo->Tarjeta=Tarjeta;
    nuevo->Nombre=Nombre;
    nuevo->Edad=edad;

    if(PrimeroLAux==NULL){
        nuevo->sig=NULL;
        nuevo->ant=NULL;
        PrimeroLAux=nuevo;
        UltimoLAux=nuevo;

    }else{
        nuevo->sig=NULL;
        nuevo->ant=UltimoLAux;
        UltimoLAux->sig=nuevo;
        UltimoLAux=nuevo;
    }
}

void Estructuras::Graficar_Lista_Lexicografica(){
    FILE *gra;
    gra=fopen("Lista_Lexico.dot","wt");
    fputs("digraph structs {\n ",gra);
    //fputs("rankdir=LR;\n",gra);
    fputs("node [shape=record];" ,gra);
    NodoLX *aux=PrimeroLX;
    if(aux!=NULL){
        fputs("\n subgraph cluster_1 {\n",gra);
        fputs("node [style=filled];\n",gra);
        int a=0;
        while (aux!=NULL) {

            fputs("\"",gra);
            fputs("NodoL",gra);
            fprintf(gra,"%d",a);
            fputs("\"",gra);
            fputs("\n[ ",gra);
            fprintf(gra, "label=\" " );
            fprintf(gra, "%d",a);
            fputs("|",gra);
            if(aux->Clave!=0){
                fprintf(gra, "%d",aux->Clave);
                fputs("&#92;n",gra);
                fputs("DPI: ",gra);
                fprintf(gra, "%s",aux->DPI);
                fputs("&#92;n",gra);
                fputs("Tarjeta: ",gra);
                fprintf(gra, "%s",aux->Tarjeta);
                fputs("&#92;n",gra);
                fputs("Nombre: ",gra);
                fprintf(gra, "%s",aux->Nombre);
                fputs("&#92;n",gra);
                fputs("Edad: ",gra);
                fprintf(gra, "%d",aux->Edad);
            }else{
                fputs("NULL",gra);
            }
            fputs("\"];\n",gra);

         a++;
         aux=aux->sig;
        }

        aux=PrimeroLX;
        int b=0;
        int c=b+1;
        if(aux!=NULL){
            while (aux->sig!=NULL) {
                fputs("NodoL",gra);
                fprintf(gra,"%d",b);
                fputs(" -> NodoL",gra);
                fprintf(gra,"%d",c);
                fputs(";",gra);
             b++;
             c++;
             aux=aux->sig;
            }
        }

        fputs("color=\"orange\"\n",gra);
        fputs("style =\"filled, bold\"\n",gra);
        fputs("label =\"Lista Lexicografica\"\n",gra);
        fputs("}\n",gra);

    }
    fputs("}",gra);
    fclose(gra);
    system("dot -Tpng Lista_Lexico.dot -o Lista_Lexico.png");

}

///********************Crear Bloque********************************
void Estructuras::Crear_Bloque(){
     cout<<"INsertando bloque"<<endl;
     NodoB *nuevo;
     nuevo=(NodoB*)malloc(sizeof(struct NodoBloque));
     nuevo->ID=IDB;
     nuevo->Piloto=NULL;
     nuevo->Autobus=NULL;
     nuevo->Fecha="";
     nuevo->sig=NULL;
     nuevo->ant=NULL;
     nuevo->Primero=NULL;
     nuevo->Ultimo=NULL;
     IDB++;

     if(PrimeroB==NULL){
          nuevo->sig=NULL;
          nuevo->ant=NULL;
          PrimeroB=nuevo;
          UltimoB=nuevo;

     }else{
          nuevo->sig=NULL;
          nuevo->ant=UltimoB;
          UltimoB->sig=nuevo;
          UltimoB=nuevo;
     }

}

///Agregar Piloto.....
void Estructuras::Agregar_Piloto_Bloque(QString DPI, int Bloque){
    int llaveK = 0;
    for (int i = 0; i < DPI.length(); i++) {
         llaveK += (int)DPI.at(i).toLatin1();
    }

    const std::string& d=DPI.toStdString();
    char *dpi=new char[d.length()+1];
    strcpy(dpi,d.c_str());

     int indice = llaveK % 37;/// Buscar Piloto con el Indice...

     NodoTH_P *aux=PrimeroTH_P;
     if(aux!=NULL){
         while (aux!=NULL) {
             if(aux->indice==indice){

                Buscar_Piloto(dpi,aux->RAIZ, Bloque);

              break;
             }
          aux=aux->sig;
         }
     }
}

///Buscar Piloto..........
void Estructuras::Buscar_Piloto(char *DPI, NodoAVLHash *actual, int Bloque){

    if(actual!=NULL){
        if(strcmp(actual->DPI,DPI)==0){
           NodoB *aux=PrimeroB;
           if(aux!=NULL){
               while (aux!=NULL) {
                   if(aux->ID==Bloque){
                       aux->Piloto=actual;
                   }
                aux=aux->sig;
               }
           }
           QMessageBox::information(NULL,"Advertencia","Piloto Encontrado");
          }
         if(actual->izq!=NULL){
             Buscar_Piloto(DPI,actual->izq, Bloque);
         }

         if(actual->der!=NULL){
             Buscar_Piloto(DPI,actual->der, Bloque);
         }
    }


}

///Agregar Autobus.....
void Estructuras::Agregar_Autobus_Bloque(QString Placa, int Bloque){
    int llaveK = 0;
    for (int i = 0; i < Placa.length(); i++) {
         llaveK += (int)Placa.at(i).toLatin1();
    }

    const std::string& d=Placa.toStdString();
    char *placa=new char[d.length()+1];
    strcpy(placa,d.c_str());

    int indice = llaveK % 37;/// Buscar Autobus con el Indice...

    NodoTH_A *aux=PrimeroTH_A;
    if(aux!=NULL){
        while (aux!=NULL) {
            if(aux->indice==indice){
                NodoLH *auxH=aux->Primero;
                if(auxH!=NULL){
                    while (auxH!=NULL) {
                        if(strcmp(auxH->Placa,placa)==0){
                            NodoB *auxB =PrimeroB;
                            if(auxB!=NULL){
                                while (auxB!=NULL) {
                                    if(auxB->ID==Bloque){
                                        auxB->Autobus=auxH;
                                     break;
                                    }
                                 auxB=auxB->sig;
                                }
                            }
                            QMessageBox::information(NULL,"Advertencia","Autobus Encontrado");
                         break;
                        }
                     auxH=auxH->sig;
                    }
                }
             break;
            }
         aux=aux->sig;
        }
    }
}






///Agrear Ruta.....
void Estructuras::Agregar_Ruta_Bloque(int IDB, char *Ruta){
    NodoB *aux=PrimeroB;
    if(aux!=NULL){
        while (aux!=NULL) {
            if(aux->ID==IDB){

                Buscar_Ruta(aux,Ruta);

             break;
            }
         aux=aux->sig;
        }
    }
}

void Estructuras::Buscar_Ruta(NodoB *auxB, char *Ruta){
    NodoLD *aux =PrimeroLD;
    if(aux!=NULL){
        while(aux!=NULL){
            if(strcmp(aux->Archivo,Ruta)==0){
                NodoLDB *nuevoLB;
                nuevoLB=(NodoLDB*)malloc(sizeof(struct NodoLDobleB));
                nuevoLB->Archivo=Ruta;
                nuevoLB->carga=contadorRuta++;
                nuevoLB->sig=NULL;
                nuevoLB->ant=NULL;
                nuevoLB->PrimeroG=NULL;
                nuevoLB->UltimoG=NULL;

                if(auxB->Primero==NULL){
                    nuevoLB->sig=NULL;
                    nuevoLB->ant=NULL;
                    auxB->Primero=nuevoLB;
                    auxB->Ultimo=nuevoLB;

                    NodoG *auxG=aux->PrimeroG;
                    if(auxG!=NULL){
                        int contador=1;
                        while (auxG!=NULL) {

                            NodoGB *nuevo;
                            nuevo=(NodoGB*)malloc(sizeof(struct NodoGrafoB));
                            nuevo->Codigo=auxG->Codigo;
                            nuevo->contador=contador;
                            nuevo->dir=auxG->dir;
                            nuevo->RAIZ=NULL;
                            nuevo->sig=NULL;
                            nuevo->ant=NULL;

                            if(auxB->Primero->PrimeroG==NULL){
                                nuevo->sig=NULL;
                                nuevo->ant=NULL;
                                auxB->Primero->PrimeroG=nuevo;
                                auxB->Primero->UltimoG=nuevo;
                            }else{
                                nuevo->sig=NULL;
                                nuevo->ant=auxB->Primero->UltimoG;
                                auxB->Primero->UltimoG->sig=nuevo;
                                auxB->Primero->UltimoG=nuevo;
                            }
                         contador++;
                         auxG=auxG->sig;
                        }
                    }

                }else{
                    nuevoLB->sig=NULL;
                    nuevoLB->ant=auxB->Ultimo;
                    auxB->Ultimo->sig=nuevoLB;
                    auxB->Ultimo=nuevoLB;

                    NodoG *auxG=aux->PrimeroG;
                    if(auxG!=NULL){
                        int contador=1;
                        while (auxG!=NULL) {

                            NodoGB *nuevo;
                            nuevo=(NodoGB*)malloc(sizeof(struct NodoGrafoB));
                            nuevo->Codigo=auxG->Codigo;
                            nuevo->contador=contador;
                            nuevo->dir=auxG->dir;
                            nuevo->RAIZ=NULL;
                            nuevo->sig=NULL;
                            nuevo->ant=NULL;

                            if(auxB->Ultimo->PrimeroG==NULL){
                                nuevo->sig=NULL;
                                nuevo->ant=NULL;
                                auxB->Ultimo->PrimeroG=nuevo;
                                auxB->Ultimo->UltimoG=nuevo;
                            }else{
                                nuevo->sig=NULL;
                                nuevo->ant=auxB->Primero->UltimoG;
                                auxB->Ultimo->UltimoG->sig=nuevo;
                                auxB->Ultimo->UltimoG=nuevo;
                            }
                         contador++;
                         auxG=auxG->sig;
                        }
                    }
                }
              cout<<"Encontrado..."<<endl;
             break;
            }
         aux=aux->sig;
        }
    }
}

void Estructuras::Agregar_Transacciones(int Bloque, char *Ruta, int Grafo, char *DPI){

    NodoB *auxB=PrimeroB;
    if(auxB!=NULL){
        while (auxB!=NULL) {
            if(auxB->ID==Bloque){

                NodoLDB *auxLD=auxB->Primero;
                if(auxLD!=NULL){
                    while (auxLD!=NULL) {
                        if(strcmp(auxLD->Archivo,Ruta)==0){

                            NodoGB *auxGB=auxLD->PrimeroG;
                            if(auxGB!=NULL){
                                while (auxGB!=NULL){
                                    if(auxGB->contador==Grafo){

                                        NodoLX *auxLX=PrimeroLX;
                                        if(auxLX!=NULL){
                                            while (auxLX!=NULL){

                                                if(strcmp(auxLX->DPI,DPI)==0){                                                   
                                                    NodoAVLB *nuevo;
                                                    nuevo=(NodoAVLB*)malloc(sizeof(struct NodoAVLBloque));
                                                    nuevo->DPI=DPI;
                                                    nuevo->Nombre=auxLX->Nombre;
                                                    nuevo->Tarjeta=auxLX->Tarjeta;
                                                    nuevo->Edad=auxLX->Edad;
                                                    nuevo->Contador=correlativoB++;
                                                    nuevo->Altura=0;
                                                    nuevo->fe=0;
                                                    nuevo->Nivel=0;
                                                    nuevo->izq=NULL;
                                                    nuevo->der=NULL;
                                                    auxGB->RAIZ=Insertar2(nuevo,auxGB->RAIZ);
                                                    Ajustar_Fe2(auxGB->RAIZ,0);

                                                 break;
                                                }
                                             auxLX=auxLX->sig;
                                            }
                                        }
                                     break;
                                    }
                                 auxGB=auxGB->sig;
                                }
                            }

                         break;
                        }
                     auxLD=auxLD->sig;
                    }
                }
             break;
            }
         auxB=auxB->sig;
        }
    }
}

/// AVL del Bloque.........................
int Estructuras::Altura2(NodoAVLB *actual){
    if(actual==NULL){
        return 0;
    }else{
        return actual->Altura;
    }
}

int Estructuras::Mayor2(int num1, int num2){
    if(num1>num2){
        return num1;
    }else{
        return num2;
    }
}

///****************ROTACIONES*************************************
NodoAVLB *Estructuras::Izquierda2(NodoAVLB *n1){
    NodoAVLB *n2 =n1->izq;
    n1->izq=n2->der;
    n2->der=n1;
    n1->Altura=Mayor2(Altura2(n1->izq),Altura2(n1->der)) +1;
    n2->Altura=Mayor2(Altura2(n2->izq), n1->Altura) +1;
    return n2;
}

NodoAVLB *Estructuras::Derecha2(NodoAVLB *n1){
    NodoAVLB *n2 =n1->der;
    n1->der=n2->izq;
    n2->izq=n1;
    n1->Altura=Mayor2(Altura2(n1->izq), Altura2(n1->der)) +1;
    n2->Altura=Mayor2(Altura2(n2->der), n1->Altura) +1;
    return n2;
}

NodoAVLB *Estructuras::IzquierdaDerecha2(NodoAVLB *n1){
    n1->izq=Derecha2(n1->izq);
    return Izquierda2(n1);
}

NodoAVLB *Estructuras::DerechaIzquierda2(NodoAVLB *n1){
    n1->der=Izquierda2(n1->der);
    return Derecha2(n1);
}

///***********INSERTAR EN EL ARBOL AVL****************************
NodoAVLB *Estructuras::Insertar2(NodoAVLB *nuevo, NodoAVLB *actual){


   if(actual == NULL){

       actual = nuevo;

   }else if(strcmp(nuevo->DPI,actual->DPI)<0){
       actual->izq=Insertar2(nuevo,actual->izq);

       if((Altura2(actual->der)-Altura2(actual->izq))==-2){

           if(strcmp(nuevo->DPI,actual->izq->DPI)<0){
               actual=Izquierda2(actual);

           }else{

               actual=IzquierdaDerecha2(actual);
           }

       }

   }else if(strcmp(nuevo->DPI,actual->DPI)>0){

       actual->der=Insertar2(nuevo,actual->der);

       if((Altura2(actual->der) - Altura2(actual->izq))==2){

           if(strcmp(nuevo->DPI,actual->der->DPI)>0){

               actual=Derecha2(actual);

           }else{

               actual = DerechaIzquierda2(actual);
           }
       }
   }else{

       cout<<"Valores Repetidos...  "<<endl;
       //cout<<nuevo->Nombre<<endl;
   }

       actual->Altura = Mayor2(Altura2(actual->izq), Altura2(actual->der)) + 1;
       return actual;

}

///********METODO PARA OBTENER EL NODO REEMPLAZO****************
NodoAVLB *Estructuras::Obtener_Reemplazo2(NodoAVLB *reemp){
    NodoAVLB *reemplazarPadre=reemp;
    NodoAVLB *reemplazo=reemp;
    NodoAVLB *auxiliar=reemp->der;
    while(auxiliar!=NULL){
        reemplazarPadre=reemplazo;
        reemplazo=auxiliar;
        auxiliar=auxiliar->izq;
    }
    if(reemplazo!=reemp->der){
        reemplazarPadre->izq=reemplazo->der;
        reemplazo->der=reemp->der;
    }

    return reemplazo;
}

///*********EQUILIBRAR ARBOL AVL********************************
void Estructuras::Ajustar_Fe2(NodoAVLB *actual, int Nivel){

        if(actual!=NULL){
           actual->fe=Altura2(actual->der)-Altura2(actual->izq);
           actual->Altura = Mayor2(Altura2(actual->izq), Altura2(actual->der)) + 1;
           actual->Nivel=Nivel;
              if(actual->izq!=NULL){

               Ajustar_Fe2(actual->izq, Nivel+1);

           }
           if(actual->der!=NULL){

            Ajustar_Fe2(actual->der, Nivel+1);

           }

         }
}


void Estructuras::Graficar_Bloque(){

    gra3=fopen("Bloques.dot","wt");
    fputs("digraph structs {\n ",gra3);

    fputs("node [shape=record];" ,gra3);
    NodoB *auxB=PrimeroB;
    if(auxB!=NULL){
        fputs("\n subgraph cluster_1 {\n",gra3);
        fputs("node [style=filled];\n",gra3);
        int a=0;
        while (auxB!=NULL) {

            fputs("\"",gra3);
            fputs("NodoB",gra3);
            fprintf(gra3,"%d",a);
            fputs("\"",gra3);
            fputs("\n[ ",gra3);
            fprintf(gra3, "label=\" " );
            fputs("Bloque: ",gra3);
            fprintf(gra3, "%d",auxB->ID);
                if(auxB->Piloto!=NULL){
                    fputs("&#92;n",gra3);
                    fputs("******PILOTO******",gra3);
                    fputs("&#92;n",gra3);
                    fputs("Nombre: ",gra3);
                    fprintf(gra3, "%s",auxB->Piloto->Nombre);
                    fputs("&#92;n",gra3);
                    fputs("DPI: ",gra3);
                    fprintf(gra3, "%s",auxB->Piloto->DPI);
                    fputs("&#92;n",gra3);
                    fputs("Edad: ",gra3);
                    fprintf(gra3, "%d",auxB->Piloto->Edad);
                    fputs("&#92;n",gra3);
                    fputs("Genero: ",gra3);
                    fprintf(gra3, "%s",auxB->Piloto->Genero);
                }
                if(auxB->Autobus!=NULL){
                    fputs("&#92;n",gra3);
                    fputs("******AUTOBUS******",gra3);
                    fputs("&#92;n",gra3);
                    fputs("Placa: ",gra3);
                    fprintf(gra3, "%s",auxB->Autobus->Placa);
                    fputs("&#92;n",gra3);
                    fputs("Modelo: ",gra3);
                    fprintf(gra3, "%s",auxB->Autobus->Modelo);
                    fputs("&#92;n",gra3);
                    fputs("Estado: ",gra3);
                    fprintf(gra3, "%s",auxB->Autobus->Estado);
                }
            fputs("\",shape=box3d,fillcolor=cyan];\n",gra3);

            NodoLDB *auxLD=auxB->Primero;
            if(auxLD!=NULL){
                int aa=0;
                while (auxLD!=NULL) {
                    fputs("\"",gra3);
                    fputs("NodoL",gra3);
                    fprintf(gra3,"%d",auxB->ID);
                    fprintf(gra3,"%d",aa);
                    fputs("\"",gra3);
                    fputs("\n[ ",gra3);
                    fprintf(gra3, "label=\" " );
                    fputs("Ruta: ",gra3);
                    fprintf(gra3, "%s",auxLD->Archivo);
                    fputs("&#92;n",gra3);
                    fputs("ID: ",gra3);
                    fprintf(gra3, "%d",auxLD->carga);
                    fputs("\",shape=box,fillcolor=green];\n",gra3);

                        NodoGB *auxG=auxLD->PrimeroG;
                        if(auxG!=NULL){

                            while (auxG!=NULL) {
                                fputs("\"",gra3);
                                fputs("NodoG",gra3);
                                fprintf(gra3,"%d",auxB->ID);
                                fprintf(gra3,"%s",auxLD->Archivo);
                                fprintf(gra3,"%s",auxG->Codigo);
                                fputs("\"",gra3);
                                fputs("\n[ ",gra3);
                                fprintf(gra3, "label=\" " );
                                fprintf(gra3, "%s",auxG->Codigo);
                                fputs("&#92;n",gra3);
                                fputs("dir: ",gra3);
                                fprintf(gra3, "%d",auxG->dir);
                                fputs("\",shape=circle,fillcolor=salmon];\n",gra3);

                                    cout<<"Graficar avl....1"<<endl;
                                    if(auxG->RAIZ!=NULL){
                                        cout<<"Graficar avl...2."<<endl;
                                        Graficar_AVL2(auxG->RAIZ);
                                        cout<<"Graficar avl....3"<<endl;
                                    }

                             auxG=auxG->sig;
                            }
                        }


                 aa++;
                 auxLD=auxLD->sig;
                }
            }

         a++;
         auxB=auxB->sig;
        }

        auxB=PrimeroB;
        int b=0;
        int c=b+1;
        if(auxB!=NULL){
            while (auxB!=NULL) {
             if(auxB!=UltimoB){
                fputs("NodoB",gra3);
                fprintf(gra3,"%d",b);
                fputs(" -> NodoB",gra3);
                fprintf(gra3,"%d",c);
                fputs(";",gra3);

                NodoLDB *auxLD=auxB->Primero;
                if(auxLD!=NULL){
                    int bb=0;
                    int cc=bb+1;
                    fputs("NodoB",gra3);
                    fprintf(gra3,"%d",b);
                    fputs(" -> NodoL",gra3);
                    fprintf(gra3,"%d",auxB->ID);
                    fprintf(gra3,"%d",bb);
                    fputs(";",gra3);


                    while (auxLD!=NULL) {
                         cout<<"AQUI"<<endl;
                        if(auxLD!=auxB->Ultimo){
                            fputs("NodoL",gra3);
                            fprintf(gra3,"%d",auxB->ID);
                            fprintf(gra3,"%d",bb);
                            fputs(" -> NodoL",gra3);
                            fprintf(gra3,"%d",auxB->ID);
                            fprintf(gra3,"%d",cc);
                            fputs(";",gra3);

                            NodoGB *auxG=auxLD->PrimeroG;
                            cout<<"AQUI"<<endl;
                            if(auxG!=NULL){
                                fputs("NodoL",gra3);
                                fprintf(gra3,"%d",auxB->ID);
                                fprintf(gra3,"%d",bb);
                                fputs(" -> NodoG",gra3);
                                fprintf(gra3,"%d",auxB->ID);
                                fprintf(gra3,"%s",auxLD->Archivo);
                                fprintf(gra3,"%s",auxG->Codigo);
                                fputs(";",gra3);
                                while (auxG!=NULL) {
                                    if(auxG!=auxLD->UltimoG){
                                    fputs("NodoG",gra3);
                                    fprintf(gra3,"%d",auxB->ID);
                                    fprintf(gra3,"%s",auxLD->Archivo);
                                    fprintf(gra3,"%s",auxG->Codigo);
                                    fputs(" -> NodoG",gra3);
                                    fprintf(gra3,"%d",auxB->ID);
                                    fprintf(gra3,"%s",auxLD->Archivo);
                                    fprintf(gra3,"%s",auxG->sig->Codigo);
                                    fputs(";",gra3);

                                    if(auxG->RAIZ!=NULL){
                                        fputs("NodoG",gra3);
                                        fprintf(gra3,"%d",auxB->ID);
                                        fprintf(gra3,"%s",auxLD->Archivo);
                                        fprintf(gra3,"%s",auxG->Codigo);
                                        fputs(" -> NodoV",gra3);
                                        fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                        fputs(";",gra3);
                                    }

                                    }else{
                                     ////// Ultimo Grafo
                                        if(auxG->RAIZ!=NULL){
                                            fputs("NodoG",gra3);
                                            fprintf(gra3,"%d",auxB->ID);
                                            fprintf(gra3,"%s",auxLD->Archivo);
                                            fprintf(gra3,"%s",auxG->Codigo);
                                            fputs(" -> NodoV",gra3);
                                            fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                            fputs(";",gra3);
                                        }
                                    }

                                 auxG=auxG->sig;
                                }


                            }



                        }else{
                            NodoGB *auxG=auxLD->PrimeroG;
                            cout<<"AQUI"<<endl;
                            if(auxG!=NULL){
                                fputs("NodoL",gra3);
                                fprintf(gra3,"%d",auxB->ID);
                                fprintf(gra3,"%d",bb);
                                fputs(" -> NodoG",gra3);
                                fprintf(gra3,"%d",auxB->ID);
                                fprintf(gra3,"%s",auxLD->Archivo);
                                fprintf(gra3,"%s",auxG->Codigo);
                                fputs(";",gra3);
                                while (auxG!=NULL) {
                                    if(auxG!=auxLD->UltimoG){
                                    fputs("NodoG",gra3);
                                    fprintf(gra3,"%d",auxB->ID);
                                    fprintf(gra3,"%s",auxLD->Archivo);
                                    fprintf(gra3,"%s",auxG->Codigo);
                                    fputs(" -> NodoG",gra3);
                                    fprintf(gra3,"%d",auxB->ID);
                                    fprintf(gra3,"%s",auxLD->Archivo);
                                    fprintf(gra3,"%s",auxG->sig->Codigo);
                                    fputs(";",gra3);

                                    if(auxG->RAIZ!=NULL){
                                        fputs("NodoG",gra3);
                                        fprintf(gra3,"%d",auxB->ID);
                                        fprintf(gra3,"%s",auxLD->Archivo);
                                        fprintf(gra3,"%s",auxG->Codigo);
                                        fputs(" -> NodoV",gra3);
                                        fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                        fputs(";",gra3);
                                    }

                                    }else{
                                       ////// Ultimo Grafo
                                        if(auxG->RAIZ!=NULL){
                                            fputs("NodoG",gra3);
                                            fprintf(gra3,"%d",auxB->ID);
                                            fprintf(gra3,"%s",auxLD->Archivo);
                                            fprintf(gra3,"%s",auxG->Codigo);
                                            fputs(" -> NodoV",gra3);
                                            fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                            fputs(";",gra3);
                                        }

                                    }

                                 auxG=auxG->sig;
                                }


                            }
                        }
                     bb++;
                     cc++;
                     auxLD=auxLD->sig;
                    }
                }



            }else{
                 NodoLDB *auxLD=auxB->Primero;
                 if(auxLD!=NULL){
                     int bb=0;
                     int cc=bb+1;
                     fputs("NodoB",gra3);
                     fprintf(gra3,"%d",b);
                     fputs(" -> NodoL",gra3);
                     fprintf(gra3,"%d",auxB->ID);
                     fprintf(gra3,"%d",bb);
                     fputs(";",gra3);


                     while (auxLD!=NULL) {
                         if(auxLD!=auxB->Ultimo){
                             fputs("NodoL",gra3);
                             fprintf(gra3,"%d",auxB->ID);
                             fprintf(gra3,"%d",bb);
                             fputs(" -> NodoL",gra3);
                             fprintf(gra3,"%d",auxB->ID);
                             fprintf(gra3,"%d",cc);
                             fputs(";",gra3);

                             NodoGB *auxG=auxLD->PrimeroG;
                             if(auxG!=NULL){
                                 fputs("NodoL",gra3);
                                 fprintf(gra3,"%d",auxB->ID);
                                 fprintf(gra3,"%d",bb);
                                 fputs(" -> NodoG",gra3);
                                 fprintf(gra3,"%d",auxB->ID);
                                 fprintf(gra3,"%s",auxLD->Archivo);
                                 fprintf(gra3,"%s",auxG->Codigo);
                                 fputs(";",gra3);
                                 while (auxG!=NULL) {
                                     if(auxG!=auxLD->UltimoG){
                                     fputs("NodoG",gra3);
                                     fprintf(gra3,"%d",auxB->ID);
                                     fprintf(gra3,"%s",auxLD->Archivo);
                                     fprintf(gra3,"%s",auxG->Codigo);
                                     fputs(" -> NodoG",gra3);
                                     fprintf(gra3,"%d",auxB->ID);
                                     fprintf(gra3,"%s",auxLD->Archivo);
                                     fprintf(gra3,"%s",auxG->sig->Codigo);
                                     fputs(";",gra3);

                                     if(auxG->RAIZ!=NULL){
                                         fputs("NodoG",gra3);
                                         fprintf(gra3,"%d",auxB->ID);
                                         fprintf(gra3,"%s",auxLD->Archivo);
                                         fprintf(gra3,"%s",auxG->Codigo);
                                         fputs(" -> NodoV",gra3);
                                         fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                         fputs(";",gra3);
                                     }

                                     }else{
                                         ////// Ultimo Grafo
                                         if(auxG->RAIZ!=NULL){
                                             fputs("NodoG",gra3);
                                             fprintf(gra3,"%d",auxB->ID);
                                             fprintf(gra3,"%s",auxLD->Archivo);
                                             fprintf(gra3,"%s",auxG->Codigo);
                                             fputs(" -> NodoV",gra3);
                                             fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                             fputs(";",gra3);
                                         }
                                     }

                                  auxG=auxG->sig;
                                 }


                             }

                         }else{
                             cout<<"1111"<<endl;
                             NodoGB *auxG=auxLD->PrimeroG;
                             if(auxG!=NULL){
                                 fputs("NodoL",gra3);
                                 fprintf(gra3,"%d",auxB->ID);
                                 fprintf(gra3,"%d",bb);
                                 fputs(" -> NodoG",gra3);
                                 fprintf(gra3,"%d",auxB->ID);
                                 fprintf(gra3,"%s",auxLD->Archivo);
                                 fprintf(gra3,"%s",auxG->Codigo);
                                 fputs(";",gra3);
                                 while (auxG!=NULL) {
                                     if(auxG!=auxLD->UltimoG){
                                     fputs("NodoG",gra3);
                                     fprintf(gra3,"%d",auxB->ID);
                                     fprintf(gra3,"%s",auxLD->Archivo);
                                     fprintf(gra3,"%s",auxG->Codigo);
                                     fputs(" -> NodoG",gra3);
                                     fprintf(gra3,"%d",auxB->ID);
                                     fprintf(gra3,"%s",auxLD->Archivo);
                                     fprintf(gra3,"%s",auxG->sig->Codigo);
                                     fputs(";",gra3);

                                         if(auxG->RAIZ!=NULL){
                                             fputs("NodoG",gra3);
                                             fprintf(gra3,"%d",auxB->ID);
                                             fprintf(gra3,"%s",auxLD->Archivo);
                                             fprintf(gra3,"%s",auxG->Codigo);
                                             fputs(" -> NodoV",gra3);
                                             fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                             fputs(";",gra3);
                                         }



                                     }else{
                                         ////// Ultimo Grafo
                                         if(auxG->RAIZ!=NULL){
                                             fputs("NodoG",gra3);
                                             fprintf(gra3,"%d",auxB->ID);
                                             fprintf(gra3,"%s",auxLD->Archivo);
                                             fprintf(gra3,"%s",auxG->Codigo);
                                             fputs(" -> NodoV",gra3);
                                             fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                             fputs(";",gra3);
                                         }
                                     }

                                  auxG=auxG->sig;
                                 }
                             }

                         }
                      bb++;
                      cc++;
                      auxLD=auxLD->sig;
                     }
                 }


             }

             b++;
             c++;
             auxB=auxB->sig;
            }
        }

        fputs("color=\"orange\"\n",gra3);
        fputs("style =\"filled, bold\"\n",gra3);
        fputs("label =\"Bloques\"\n",gra3);
        fputs("}\n",gra3);

    }
    fputs("}",gra3);
    fclose(gra3);
    system("dot -Tpng Bloques.dot -o Bloques.png");


}

void Estructuras::Graficar_AVL2(NodoAVLB *actual){

    if(actual != NULL){
        if(actual->izq ==NULL && actual->der==NULL){
            fputs("\"",gra3);
            fputs("NodoV",gra3);
            fprintf(gra3,"%d",actual->Contador);
            fputs("\"",gra3);
            fputs("[ ",gra3);
            fprintf(gra3, "label=\" " );
            fputs("DPI: ",gra3);
            fprintf(gra3, "%s",actual->DPI);
            fputs("\",fillcolor=yellow];\n",gra3);

        }else{
            fputs("\"",gra3);
            fputs("NodoV",gra3);
            fprintf(gra3,"%d",actual->Contador);
            fputs("\"",gra3);
            fputs("[ ",gra3);
            fprintf(gra3, "label=\"<C1>| " );
            fputs("DPI: ",gra3);
            fprintf(gra3, "%s",actual->DPI);
            fputs("|<C0>\",fillcolor=yellow];\n",gra3);

        }
        if(actual->izq!=NULL){
            Graficar_AVL2(actual->izq);
            fputs("NodoV",gra3);
            fprintf(gra3,"%d",actual->Contador);
            fputs(":C0->NodoV",gra3);
            fprintf(gra3,"%d",actual->izq->Contador);
            fputs("\n",gra3);

        }
        if(actual->der!=NULL){
            Graficar_AVL2(actual->der);
            fputs("NodoV",gra3);
            fprintf(gra3,"%d",actual->Contador);
            fputs(":C1->NodoV",gra3);
            fprintf(gra3,"%d",actual->der->Contador);
            fputs("\n",gra3);
        }

    }
}

void Estructuras::Graficar_AVL3(NodoAVLB *actual){

    if(actual != NULL){
        if(actual->izq ==NULL && actual->der==NULL){
            fputs("\"",gra3);
            fputs("NodoV",gra3);
            fprintf(gra3,"%d",actual->Contador);
            fputs("\"",gra3);
            fputs("[ ",gra3);
            fprintf(gra3, "label=\" " );
            fputs("DPI: ",gra3);
            fprintf(gra3, "%s",actual->DPI);
            fputs("&#92;n",gra3);
            fputs("Nombre: ",gra3);
            fprintf(gra3, "%s",actual->Nombre);
            fputs("&#92;n",gra3);
            fputs("Tarjeta: ",gra3);
            fprintf(gra3, "%s",actual->Tarjeta);
            fputs("&#92;n",gra3);
            fputs("Edad: ",gra3);
            fprintf(gra3, "%d",actual->Edad);
            fputs("\",fillcolor=yellow];\n",gra3);

        }else{
            fputs("\"",gra3);
            fputs("NodoV",gra3);
            fprintf(gra3,"%d",actual->Contador);
            fputs("\"",gra3);
            fputs("[ ",gra3);
            fprintf(gra3, "label=\"<C1>| " );
            fputs("DPI: ",gra3);
            fprintf(gra3, "%s",actual->DPI);
            fputs("&#92;n",gra3);
            fputs("Nombre: ",gra3);
            fprintf(gra3, "%s",actual->Nombre);
            fputs("&#92;n",gra3);
            fputs("Tarjeta: ",gra3);
            fprintf(gra3, "%s",actual->Tarjeta);
            fputs("&#92;n",gra3);
            fputs("Edad: ",gra3);
            fprintf(gra3, "%d",actual->Edad);
            fputs("|<C0>\",fillcolor=yellow];\n",gra3);

        }
        if(actual->izq!=NULL){
            Graficar_AVL3(actual->izq);
            fputs("NodoV",gra3);
            fprintf(gra3,"%d",actual->Contador);
            fputs(":C0->NodoV",gra3);
            fprintf(gra3,"%d",actual->izq->Contador);
            fputs("\n",gra3);

        }
        if(actual->der!=NULL){
            Graficar_AVL3(actual->der);
            fputs("NodoV",gra3);
            fprintf(gra3,"%d",actual->Contador);
            fputs(":C1->NodoV",gra3);
            fprintf(gra3,"%d",actual->der->Contador);
            fputs("\n",gra3);
        }

    }
}


void Estructuras::Graficar_Bloque_Individual(int ID){
    gra3=fopen("Bloques_Individual.dot","wt");
    fputs("digraph structs {\n ",gra3);

    fputs("node [shape=record];" ,gra3);
    NodoB *auxB=PrimeroB;
    if(auxB!=NULL){
        fputs("\n subgraph cluster_1 {\n",gra3);
        fputs("node [style=filled];\n",gra3);
        int a=1;
        while (auxB!=NULL){
                cout<<"BUG..1"<<endl;
            if(auxB->ID==ID){
                fputs("\"",gra3);
                fputs("NodoB",gra3);
                fprintf(gra3,"%d",a);
                fputs("\"",gra3);
                fputs("\n[ ",gra3);
                fprintf(gra3, "label=\" " );
                fputs("Bloque: ",gra3);
                fprintf(gra3, "%d",auxB->ID);
                    if(auxB->Piloto!=NULL){

                        fputs("&#92;n",gra3);
                        fputs("******PILOTO******",gra3);
                        fputs("&#92;n",gra3);
                        fputs("Nombre: ",gra3);
                        fprintf(gra3, "%s",auxB->Piloto->Nombre);
                        fputs("&#92;n",gra3);
                        fputs("DPI: ",gra3);
                        fprintf(gra3, "%s",auxB->Piloto->DPI);
                        fputs("&#92;n",gra3);
                        fputs("Edad: ",gra3);
                        fprintf(gra3, "%d",auxB->Piloto->Edad);
                        fputs("&#92;n",gra3);
                        fputs("Genero: ",gra3);
                        fprintf(gra3, "%s",auxB->Piloto->Genero);
                    }
                    if(auxB->Autobus!=NULL){
                        fputs("&#92;n",gra3);
                        fputs("******AUTOBUS******",gra3);
                        fputs("&#92;n",gra3);
                        fputs("Placa: ",gra3);
                        fprintf(gra3, "%s",auxB->Autobus->Placa);
                        fputs("&#92;n",gra3);
                        fputs("Modelo: ",gra3);
                        fprintf(gra3, "%s",auxB->Autobus->Modelo);
                        fputs("&#92;n",gra3);
                        fputs("Estado: ",gra3);
                        fprintf(gra3, "%s",auxB->Autobus->Estado);
                    }
                fputs("\",shape=box3d,fillcolor=cyan];\n",gra3);

                NodoLDB *auxLD=auxB->Primero;
                if(auxLD!=NULL){
                    cout<<"BUG..2"<<endl;
                    int aa=1;
                    while (auxLD!=NULL) {
                        fputs("\"",gra3);
                        fputs("NodoL",gra3);
                        fprintf(gra3,"%d",auxB->ID);
                        fprintf(gra3,"%d",aa);
                        fputs("\"",gra3);
                        fputs("\n[ ",gra3);
                        fprintf(gra3, "label=\" " );
                        fputs("Ruta: ",gra3);
                        fprintf(gra3, "%s",auxLD->Archivo);
                        fputs("&#92;n",gra3);
                        fputs("ID: ",gra3);
                        fprintf(gra3, "%d",auxLD->carga);
                        fputs("\",shape=box,fillcolor=green];\n",gra3);

                            NodoGB *auxG=auxLD->PrimeroG;
                            if(auxG!=NULL){

                                while (auxG!=NULL) {
                                    fputs("\"",gra3);
                                    fputs("NodoG",gra3);
                                    fprintf(gra3,"%d",auxB->ID);
                                    fprintf(gra3,"%s",auxLD->Archivo);
                                    fprintf(gra3,"%s",auxG->Codigo);
                                    fputs("\"",gra3);
                                    fputs("\n[ ",gra3);
                                    fprintf(gra3, "label=\" " );
                                    fprintf(gra3, "%s",auxG->Codigo);
                                    fputs("&#92;n",gra3);
                                    fputs("dir: ",gra3);
                                    fprintf(gra3, "%d",auxG->dir);
                                    fputs("\",shape=circle,fillcolor=salmon];\n",gra3);


                                        if(auxG->RAIZ!=NULL){
                                            Graficar_AVL2(auxG->RAIZ);
                                        }

                                 auxG=auxG->sig;
                                }
                            }


                     aa++;
                     auxLD=auxLD->sig;
                    }
                }

            break;
            }
            a++;
            auxB=auxB->sig;

        }

        auxB=PrimeroB;
        int b=1;
        int c=b+1;
        if(auxB!=NULL){
            while (auxB!=NULL) {
                if(auxB->ID==ID){
                    if(auxB!=UltimoB){

                       NodoLDB *auxLD=auxB->Primero;
                       if(auxLD!=NULL){
                           int bb=1;
                           int cc=bb+1;
                           fputs("NodoB",gra3);
                           fprintf(gra3,"%d",auxB->ID);
                           fputs(" -> NodoL",gra3);
                           fprintf(gra3,"%d",auxB->ID);
                           fprintf(gra3,"%d",bb);
                           fputs(";",gra3);


                           while (auxLD!=NULL) {
                                cout<<"AQUI"<<endl;
                               if(auxLD!=auxB->Ultimo){
                                   fputs("NodoL",gra3);
                                   fprintf(gra3,"%d",auxB->ID);
                                   fprintf(gra3,"%d",bb);
                                   fputs(" -> NodoL",gra3);
                                   fprintf(gra3,"%d",auxB->ID);
                                   fprintf(gra3,"%d",cc);
                                   fputs(";",gra3);

                                   NodoGB *auxG=auxLD->PrimeroG;
                                   cout<<"AQUI"<<endl;
                                   if(auxG!=NULL){
                                       fputs("NodoL",gra3);
                                       fprintf(gra3,"%d",auxB->ID);
                                       fprintf(gra3,"%d",bb);
                                       fputs(" -> NodoG",gra3);
                                       fprintf(gra3,"%d",auxB->ID);
                                       fprintf(gra3,"%s",auxLD->Archivo);
                                       fprintf(gra3,"%s",auxG->Codigo);
                                       fputs(";",gra3);
                                       while (auxG!=NULL) {
                                           if(auxG!=auxLD->UltimoG){
                                           fputs("NodoG",gra3);
                                           fprintf(gra3,"%d",auxB->ID);
                                           fprintf(gra3,"%s",auxLD->Archivo);
                                           fprintf(gra3,"%s",auxG->Codigo);
                                           fputs(" -> NodoG",gra3);
                                           fprintf(gra3,"%d",auxB->ID);
                                           fprintf(gra3,"%s",auxLD->Archivo);
                                           fprintf(gra3,"%s",auxG->sig->Codigo);
                                           fputs(";",gra3);

                                           if(auxG->RAIZ!=NULL){
                                               fputs("NodoG",gra3);
                                               fprintf(gra3,"%d",auxB->ID);
                                               fprintf(gra3,"%s",auxLD->Archivo);
                                               fprintf(gra3,"%s",auxG->Codigo);
                                               fputs(" -> NodoV",gra3);
                                               fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                               if(auxG->dir==1){
                                                   fprintf(gra3, "[label=\"Ida\"];" );
                                               }else if(auxG->dir==2){
                                                   fprintf(gra3, "[label=\"Vuelta\"];" );
                                               }else{
                                                   fputs(";",gra3);
                                               }
                                           }

                                           }else{
                                            ////// Ultimo Grafo
                                               if(auxG->RAIZ!=NULL){
                                                   fputs("NodoG",gra3);
                                                   fprintf(gra3,"%d",auxB->ID);
                                                   fprintf(gra3,"%s",auxLD->Archivo);
                                                   fprintf(gra3,"%s",auxG->Codigo);
                                                   fputs(" -> NodoV",gra3);
                                                   fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                                   if(auxG->dir==1){
                                                       fprintf(gra3, "[label=\"Ida\"];" );
                                                   }else if(auxG->dir==2){
                                                       fprintf(gra3, "[label=\"Vuelta\"];" );
                                                   }else{
                                                       fputs(";",gra3);
                                                   }
                                               }
                                           }

                                        auxG=auxG->sig;
                                       }


                                   }



                               }else{
                                   NodoGB *auxG=auxLD->PrimeroG;
                                   cout<<"AQUI"<<endl;
                                   if(auxG!=NULL){
                                       fputs("NodoL",gra3);
                                       fprintf(gra3,"%d",auxB->ID);
                                       fprintf(gra3,"%d",bb);
                                       fputs(" -> NodoG",gra3);
                                       fprintf(gra3,"%d",auxB->ID);
                                       fprintf(gra3,"%s",auxLD->Archivo);
                                       fprintf(gra3,"%s",auxG->Codigo);
                                       fputs(";",gra3);
                                       while (auxG!=NULL) {
                                           if(auxG!=auxLD->UltimoG){
                                           fputs("NodoG",gra3);
                                           fprintf(gra3,"%d",auxB->ID);
                                           fprintf(gra3,"%s",auxLD->Archivo);
                                           fprintf(gra3,"%s",auxG->Codigo);
                                           fputs(" -> NodoG",gra3);
                                           fprintf(gra3,"%d",auxB->ID);
                                           fprintf(gra3,"%s",auxLD->Archivo);
                                           fprintf(gra3,"%s",auxG->sig->Codigo);
                                           fputs(";",gra3);

                                           if(auxG->RAIZ!=NULL){
                                               fputs("NodoG",gra3);
                                               fprintf(gra3,"%d",auxB->ID);
                                               fprintf(gra3,"%s",auxLD->Archivo);
                                               fprintf(gra3,"%s",auxG->Codigo);
                                               fputs(" -> NodoV",gra3);
                                               fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                               if(auxG->dir==1){
                                                   fprintf(gra3, "[label=\"Ida\"];" );
                                               }else if(auxG->dir==2){
                                                   fprintf(gra3, "[label=\"Vuelta\"];" );
                                               }else{
                                                   fputs(";",gra3);
                                               }
                                           }

                                           }else{
                                              ////// Ultimo Grafo
                                               if(auxG->RAIZ!=NULL){
                                                   fputs("NodoG",gra3);
                                                   fprintf(gra3,"%d",auxB->ID);
                                                   fprintf(gra3,"%s",auxLD->Archivo);
                                                   fprintf(gra3,"%s",auxG->Codigo);
                                                   fputs(" -> NodoV",gra3);
                                                   fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                                   if(auxG->dir==1){
                                                       fprintf(gra3, "[label=\"Ida\"];" );
                                                   }else if(auxG->dir==2){
                                                       fprintf(gra3, "[label=\"Vuelta\"];" );
                                                   }else{
                                                       fputs(";",gra3);
                                                   }
                                               }

                                           }

                                        auxG=auxG->sig;
                                       }


                                   }
                               }
                            bb++;
                            cc++;
                            auxLD=auxLD->sig;
                           }
                       }



                   }else{
                        NodoLDB *auxLD=auxB->Primero;
                        if(auxLD!=NULL){
                            int bb=1;
                            int cc=bb+1;
                            fputs("NodoB",gra3);
                            fprintf(gra3,"%d",auxB->ID);
                            fputs(" -> NodoL",gra3);
                            fprintf(gra3,"%d",auxB->ID);
                            fprintf(gra3,"%d",bb);
                            fputs(";",gra3);


                            while (auxLD!=NULL) {
                                if(auxLD!=auxB->Ultimo){
                                    fputs("NodoL",gra3);
                                    fprintf(gra3,"%d",auxB->ID);
                                    fprintf(gra3,"%d",bb);
                                    fputs(" -> NodoL",gra3);
                                    fprintf(gra3,"%d",auxB->ID);
                                    fprintf(gra3,"%d",cc);
                                    fputs(";",gra3);

                                    NodoGB *auxG=auxLD->PrimeroG;
                                    if(auxG!=NULL){
                                        fputs("NodoL",gra3);
                                        fprintf(gra3,"%d",auxB->ID);
                                        fprintf(gra3,"%d",bb);
                                        fputs(" -> NodoG",gra3);
                                        fprintf(gra3,"%d",auxB->ID);
                                        fprintf(gra3,"%s",auxLD->Archivo);
                                        fprintf(gra3,"%s",auxG->Codigo);
                                        fputs(";",gra3);
                                        while (auxG!=NULL) {
                                            if(auxG!=auxLD->UltimoG){
                                            fputs("NodoG",gra3);
                                            fprintf(gra3,"%d",auxB->ID);
                                            fprintf(gra3,"%s",auxLD->Archivo);
                                            fprintf(gra3,"%s",auxG->Codigo);
                                            fputs(" -> NodoG",gra3);
                                            fprintf(gra3,"%d",auxB->ID);
                                            fprintf(gra3,"%s",auxLD->Archivo);
                                            fprintf(gra3,"%s",auxG->sig->Codigo);
                                            fputs(";",gra3);

                                            if(auxG->RAIZ!=NULL){
                                                fputs("NodoG",gra3);
                                                fprintf(gra3,"%d",auxB->ID);
                                                fprintf(gra3,"%s",auxLD->Archivo);
                                                fprintf(gra3,"%s",auxG->Codigo);
                                                fputs(" -> NodoV",gra3);
                                                fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                                if(auxG->dir==1){
                                                    fprintf(gra3, "[label=\"Ida\"];" );
                                                }else if(auxG->dir==2){
                                                    fprintf(gra3, "[label=\"Vuelta\"];" );
                                                }else{
                                                    fputs(";",gra3);
                                                }
                                            }

                                            }else{
                                                ////// Ultimo Grafo
                                                if(auxG->RAIZ!=NULL){
                                                    fputs("NodoG",gra3);
                                                    fprintf(gra3,"%d",auxB->ID);
                                                    fprintf(gra3,"%s",auxLD->Archivo);
                                                    fprintf(gra3,"%s",auxG->Codigo);
                                                    fputs(" -> NodoV",gra3);
                                                    fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                                    if(auxG->dir==1){
                                                        fprintf(gra3, "[label=\"Ida\"];" );
                                                    }else if(auxG->dir==2){
                                                        fprintf(gra3, "[label=\"Vuelta\"];" );
                                                    }else{
                                                        fputs(";",gra3);
                                                    }
                                                }
                                            }

                                         auxG=auxG->sig;
                                        }


                                    }

                                }else{

                                    NodoGB *auxG=auxLD->PrimeroG;
                                    if(auxG!=NULL){
                                        fputs("NodoL",gra3);
                                        fprintf(gra3,"%d",auxB->ID);
                                        fprintf(gra3,"%d",bb);
                                        fputs(" -> NodoG",gra3);
                                        fprintf(gra3,"%d",auxB->ID);
                                        fprintf(gra3,"%s",auxLD->Archivo);
                                        fprintf(gra3,"%s",auxG->Codigo);
                                        fputs(";",gra3);
                                        while (auxG!=NULL) {
                                            if(auxG!=auxLD->UltimoG){
                                            fputs("NodoG",gra3);
                                            fprintf(gra3,"%d",auxB->ID);
                                            fprintf(gra3,"%s",auxLD->Archivo);
                                            fprintf(gra3,"%s",auxG->Codigo);
                                            fputs(" -> NodoG",gra3);
                                            fprintf(gra3,"%d",auxB->ID);
                                            fprintf(gra3,"%s",auxLD->Archivo);
                                            fprintf(gra3,"%s",auxG->sig->Codigo);
                                            fputs(";",gra3);

                                                if(auxG->RAIZ!=NULL){
                                                    fputs("NodoG",gra3);
                                                    fprintf(gra3,"%d",auxB->ID);
                                                    fprintf(gra3,"%s",auxLD->Archivo);
                                                    fprintf(gra3,"%s",auxG->Codigo);
                                                    fputs(" -> NodoV",gra3);
                                                    fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                                    if(auxG->dir==1){
                                                        fprintf(gra3, "[label=\"Ida\"];" );
                                                    }else if(auxG->dir==2){
                                                        fprintf(gra3, "[label=\"Vuelta\"];" );
                                                    }else{
                                                        fputs(";",gra3);
                                                    }
                                                }



                                            }else{
                                                ////// Ultimo Grafo
                                                if(auxG->RAIZ!=NULL){
                                                    fputs("NodoG",gra3);
                                                    fprintf(gra3,"%d",auxB->ID);
                                                    fprintf(gra3,"%s",auxLD->Archivo);
                                                    fprintf(gra3,"%s",auxG->Codigo);
                                                    fputs(" -> NodoV",gra3);
                                                    fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                                    if(auxG->dir==1){
                                                        fprintf(gra3, "[label=\"Ida\"];" );
                                                    }else if(auxG->dir==2){
                                                        fprintf(gra3, "[label=\"Vuelta\"];" );
                                                    }else{
                                                        fputs(";",gra3);
                                                    }
                                                }
                                            }

                                         auxG=auxG->sig;
                                        }
                                    }

                                }
                             bb++;
                             cc++;
                             auxLD=auxLD->sig;
                            }
                        }


                    }


                 break;
                }

                a++;
                auxB=auxB->sig;

            }

        }

        fputs("color=\"orange\"\n",gra3);
        fputs("style =\"filled, bold\"\n",gra3);
        fputs("label =\"Bloques Individual\"\n",gra3);
        fputs("}\n",gra3);

    }
    fputs("}",gra3);
    fclose(gra3);
    system("dot -Tpng Bloques_Individual.dot -o Bloques_Individual.png");


}


void Estructuras::Graficar_Estacion_Individual(int ID, char *Ruta, char *Estacion){
    gra3=fopen("Estacion_Individual.dot","wt");
    fputs("digraph structs {\n ",gra3);

    fputs("node [shape=record];" ,gra3);

    NodoB *auxB=PrimeroB;
    if(auxB!=NULL){
        while (auxB!=NULL) {
            if(auxB->ID==ID){
               NodoLDB *auxL=auxB->Primero;
               if(auxL!=NULL){
                   while (auxL!=NULL) {
                       if(strcmp(auxL->Archivo,Ruta)==0){
                          NodoGB *auxG=auxL->PrimeroG;
                          if(auxG!=NULL){
                              while (auxG!=NULL) {
                                  if(strcmp(auxG->Codigo,Estacion)==0){
                                      //Grafica.....
                                      fputs("\n subgraph cluster_1 {\n",gra3);
                                      fputs("node [style=filled];\n",gra3);

                                      fputs("\"",gra3);
                                      fputs("NodoG",gra3);
                                      fprintf(gra3,"%d",auxB->ID);
                                      fprintf(gra3,"%s",auxL->Archivo);
                                      fprintf(gra3,"%s",auxG->Codigo);
                                      fputs("\"",gra3);
                                      fputs("\n[ ",gra3);
                                      fprintf(gra3, "label=\" " );
                                      fprintf(gra3, "%s",auxG->Codigo);
                                      fputs("&#92;n",gra3);
                                      fputs("dir: ",gra3);
                                      fprintf(gra3, "%d",auxG->dir);
                                      fputs("\",shape=circle,fillcolor=salmon];\n",gra3);

                                      if(auxG->RAIZ!=NULL){
                                          Graficar_AVL3(auxG->RAIZ);

                                          fputs("NodoG",gra3);
                                          fprintf(gra3,"%d",auxB->ID);
                                          fprintf(gra3,"%s",auxL->Archivo);
                                          fprintf(gra3,"%s",auxG->Codigo);
                                          fputs(" -> NodoV",gra3);
                                          fprintf(gra3,"%d",auxG->RAIZ->Contador);
                                          if(auxG->dir==1){
                                              fprintf(gra3, "[label=\"Ida\"];" );
                                          }else if(auxG->dir==2){
                                              fprintf(gra3, "[label=\"Vuelta\"];" );
                                          }else{
                                              fputs(";",gra3);
                                          }
                                      }

                                      fputs("color=\"orange\"\n",gra3);
                                      fputs("style =\"filled, bold\"\n",gra3);
                                      fputs("label =\"Estacion_Individual\"\n",gra3);
                                      fputs("}\n",gra3);
                                      //Grafica......
                                  }
                               auxG=auxG->sig;
                              }
                          }

                        break;
                       }
                    auxL=auxL->sig;
                   }

               }

             break;
            }
         auxB=auxB->sig;
        }
    }

    fputs("}",gra3);
    fclose(gra3);
    system("dot -Tpng Estacion_Individual.dot -o Estacion_Individual.png");
}

void Estructuras::Recorrer_AVL_Hash(NodoAVLH *aux){
    if(aux!=NULL){
        Krip.append(aux->DPI);
        Krip.append(",");
        Krip.append(aux->Nombre);
        Krip.append(",");
        Krip.append(QString::number(aux->Edad));
        Krip.append(",");
        Krip.append(aux->Genero);
        Krip.append("\n");

        if(aux->izq!=NULL){
            Recorrer_AVL_Hash(aux->izq);
        }
        if(aux->der!=NULL){
            Recorrer_AVL_Hash(aux->der);
        }

    }
}

void Estructuras::Recorrer_AVL_Bloque(NodoAVLB *aux){
    if(aux!=NULL){
        Krip.append(aux->DPI);


        if(aux->izq!=NULL){
            Krip.append(",");
            Recorrer_AVL_Bloque(aux->izq);
        }
        if(aux->der!=NULL){
            Krip.append(",");
            Recorrer_AVL_Bloque(aux->der);
        }

    }
}

void Estructuras::Encryptar(){
    FILE *gra;
    gra=fopen("Encryptado.200915305-log","wt");

    ///Autobuses...............................
    Krip.clear();
    NodoTH_A *auxTHA=PrimeroTH_A;
    if(auxTHA!=NULL){
        Krip.append("$AUTOBUSES$\n");
        while (auxTHA!=NULL) {
            NodoLH *auxLH=auxTHA->Primero;
            if(auxLH!=NULL){
                while (auxLH!=NULL) {
                     Krip.append(auxLH->Placa);
                     Krip.append(",");
                     Krip.append(auxLH->Modelo);
                     Krip.append(",");
                     Krip.append(auxLH->Estado);
                     Krip.append("\n");
                 auxLH=auxLH->sig;
                }
            }
         auxTHA=auxTHA->sig;
        }
    }

    ///Pilotos................................
    NodoTH_P *auxTHP=PrimeroTH_P;
    if(auxTHP!=NULL){
        Krip.append("$PILOTOS$\n");
        while (auxTHP!=NULL) {
            NodoAVLH *auxAVLH=auxTHP->RAIZ;
            if(auxAVLH!=NULL){
                Recorrer_AVL_Hash(auxAVLH);
            }
         auxTHP=auxTHP->sig;
        }
    }

    ///Estaciones...............................
    NodoLE *auxLE=PrimeroE;
    if(auxLE!=NULL){
        Krip.append("$ESTACIONES$\n");
        while (auxLE!=NULL) {
            Krip.append(auxLE->Codigo);
            Krip.append(",");
            Krip.append(auxLE->Nombre);
            Krip.append(",");
            Krip.append(auxLE->Ubicacion);
            Krip.append("\n");
         auxLE=auxLE->sig;
        }
    }

    ///Grafos...................................
    NodoLD *auxLD=PrimeroLD;
    if(auxLD!=NULL){
        Krip.append("$GRAFOS$\n");
        while (auxLD!=NULL) {     
            Krip.append(auxLD->Archivo);
            Krip.append(",");
                NodoG *auxG=auxLD->PrimeroG;
                if(auxG!=NULL){
                    while (auxG!=NULL) {
                        if(auxG!=auxLD->UltimoG){
                            Krip.append(auxG->Codigo);
                            Krip.append("/");
                            Krip.append(QString::number(auxG->dir));
                            Krip.append(",");
                        }else{
                            Krip.append(auxG->Codigo);
                            Krip.append("/");
                            Krip.append(QString::number(auxG->dir));

                        }

                     auxG=auxG->sig;
                    }
                    Krip.append("\n");
                }
         auxLD=auxLD->sig;
        }
    }

    ///Lista de Matrices...........................
    NodoLDM *auxLDM=PrimeroLDM;
    if(auxLDM!=NULL){
         Krip.append("$MATRIZ$\n");
        while (auxLDM) {          
            Krip.append(auxLDM->Archivo);      
            Krip.append(";");
                NodoF *auxF=auxLDM->PrimeroF;
                if(auxF!=NULL){
                    while (auxF!=NULL){
                      if(auxF!=auxLDM->UltimoF){
                        NodoM *auxM=auxF->PrimeroM;
                        if(auxM!=NULL){

                            while (auxM!=NULL) {
                                if(auxM!=auxF->UltimoM){
                                    Krip.append(auxM->Placa);
                                    Krip.append(",");
                                }else{
                                    Krip.append(auxM->Placa);
                                }
                             auxM=auxM->izq;
                            }

                              Krip.append(";");


                        }
                     auxF=auxF->Abajo;
                    }else{
                          NodoM *auxM=auxF->PrimeroM;
                          if(auxM!=NULL){

                              while (auxM!=NULL) {
                                  if(auxM!=auxF->UltimoM){
                                      Krip.append(auxM->Placa);
                                      Krip.append(",");
                                  }else{
                                      Krip.append(auxM->Placa);
                                  }
                               auxM=auxM->izq;
                              }

                         }
                       auxF=auxF->Abajo;
                    }
                    }
                }
          Krip.append("\n");
         auxLDM=auxLDM->sig;
        }
    }

     ///Lista de Usarios.............................
     NodoLX *auxLX=PrimeroLX;
     if(auxLX!=NULL){
         Krip.append("$USUARIOS$\n");
         while (auxLX) {
             if(strcmp(auxLX->DPI,"")!=0){
                 Krip.append(auxLX->DPI);
                 Krip.append(",");
                 Krip.append(auxLX->Nombre);
                 Krip.append(",");
                 Krip.append(auxLX->Tarjeta);
                 Krip.append(",");
                 Krip.append(QString::number(auxLX->Edad));
                 Krip.append("\n");
             }
          auxLX=auxLX->sig;
         }
     }

     ///Lista de Bloques............................
     NodoB *auxB=PrimeroB;
     if(auxB!=NULL){
         Krip.append("$BLOQUE$\n");

         while (auxB!=NULL) {
             if(auxB!=UltimoB){
                 Krip.append(QString::number(auxB->ID));
                 Krip.append(",");
             }else{
                 Krip.append(QString::number(auxB->ID));
                 Krip.append("\n");
             }

          auxB=auxB->sig;
         }

     }

     auxB=PrimeroB;
    if(auxB!=NULL){
        Krip.append("$BLOQUEDB$\n");
        while (auxB!=NULL) {
            Krip.append(QString::number(auxB->ID));
            Krip.append(";");
            if(auxB->Autobus!=NULL){
                Krip.append("$AUTOBUS$");
                Krip.append(",");
                Krip.append(auxB->Autobus->Placa);
                Krip.append(";");
            }
            if(auxB->Piloto!=NULL){
                Krip.append("$PILOTO$");
                Krip.append(",");
                Krip.append(auxB->Piloto->DPI);
                Krip.append(";");
            }
            if(auxB->Primero!=NULL){
                NodoLDB *auxLDB=auxB->Primero;
                if(auxLDB!=NULL){
                    Krip.append("$RUTAS$");
                    Krip.append(",");
                    while (auxLDB!=NULL){
                        if(auxLDB!=auxB->Ultimo){
                         Krip.append(auxLDB->Archivo);
                         Krip.append(",");
                        }else{
                            Krip.append(auxLDB->Archivo);
                        }
                     auxLDB=auxLDB->sig;
                    }
                    Krip.append("\n");
                }
            }


         auxB=auxB->sig;
        }
    }


    auxB=PrimeroB;
    if(auxB!=NULL){
        Krip.append("\n$$TRANSACCION$$\n");
        while (auxB!=NULL){
            NodoLDB *auxLDB=auxB->Primero;
            if(auxLDB!=NULL){
                while (auxLDB!=NULL){
                    Krip.append(QString::number(auxB->ID));
                    Krip.append(";");
                    Krip.append(auxLDB->Archivo);
                    NodoGB *auxGB=auxLDB->PrimeroG;
                    if(auxGB!=NULL){                        
                        while (auxGB!=NULL) {
                            if(auxGB->RAIZ!=NULL){
                                Krip.append(";");
                                if(auxGB!=auxLDB->UltimoG){
                                    Recorrer_AVL_Bloque(auxGB->RAIZ);
                                }else{
                                    Recorrer_AVL_Bloque(auxGB->RAIZ);
                                }

                            }
                         auxGB=auxGB->sig;
                        }
                    }
                    Krip.append("\n");
                 auxLDB=auxLDB->sig;
                }
            }
        auxB=auxB->sig;
       }
   }



    cout<<Krip.toStdString()<<endl;


    for(int i=0;i<Krip.length();i++){
        if(Krip[i]=='A'){
            Krip[i]='D';
        }else if(Krip[i]=='B'){
            Krip[i]='E';
        }else if(Krip[i]=='C'){
            Krip[i]='F';
        }else if(Krip[i]=='D'){
            Krip[i]='G';
        }else if(Krip[i]=='E'){
            Krip[i]='H';
        }else if(Krip[i]=='F'){
            Krip[i]='I';
        }else if(Krip[i]=='G'){
            Krip[i]='J';
        }else if(Krip[i]=='H'){
            Krip[i]='K';
        }else if(Krip[i]=='I'){
            Krip[i]='L';
        }else if(Krip[i]=='J'){
            Krip[i]='M';
        }else if(Krip[i]=='K'){
            Krip[i]='N';
        }else if(Krip[i]=='L'){
            Krip[i]='O';
        }else if(Krip[i]=='M'){
            Krip[i]='P';
        }else if(Krip[i]=='N'){
            Krip[i]='Q';
        }else if(Krip[i]=='O'){
            Krip[i]='R';
        }else if(Krip[i]=='P'){
            Krip[i]='S';
        }else if(Krip[i]=='Q'){
            Krip[i]='T';
        }else if(Krip[i]=='R'){
            Krip[i]='U';
        }else if(Krip[i]=='S'){
            Krip[i]='V';
        }else if(Krip[i]=='T'){
            Krip[i]='W';
        }else if(Krip[i]=='U'){
            Krip[i]='X';
        }else if(Krip[i]=='V'){
            Krip[i]='Y';
        }else if(Krip[i]=='W'){
            Krip[i]='Z';
        }else if(Krip[i]=='X'){
            Krip[i]='A';
        }else if(Krip[i]=='Y'){
            Krip[i]='B';
        }else if(Krip[i]=='Z'){
            Krip[i]='C';
        }else if(Krip[i]=='a'){
            Krip[i]='d';
        }else if(Krip[i]=='b'){
            Krip[i]='e';
        }else if(Krip[i]=='c'){
            Krip[i]='f';
        }else if(Krip[i]=='d'){
            Krip[i]='g';
        }else if(Krip[i]=='e'){
            Krip[i]='h';
        }else if(Krip[i]=='f'){
            Krip[i]='i';
        }else if(Krip[i]=='g'){
            Krip[i]='j';
        }else if(Krip[i]=='h'){
            Krip[i]='k';
        }else if(Krip[i]=='i'){
            Krip[i]='l';
        }else if(Krip[i]=='j'){
            Krip[i]='m';
        }else if(Krip[i]=='k'){
            Krip[i]='n';
        }else if(Krip[i]=='l'){
            Krip[i]='o';
        }else if(Krip[i]=='m'){
            Krip[i]='p';
        }else if(Krip[i]=='n'){
            Krip[i]='q';
        }else if(Krip[i]=='o'){
            Krip[i]='r';
        }else if(Krip[i]=='p'){
            Krip[i]='s';
        }else if(Krip[i]=='q'){
            Krip[i]='t';
        }else if(Krip[i]=='r'){
            Krip[i]='u';
        }else if(Krip[i]=='s'){
            Krip[i]='v';
        }else if(Krip[i]=='t'){
            Krip[i]='w';
        }else if(Krip[i]=='u'){
            Krip[i]='x';
        }else if(Krip[i]=='v'){
            Krip[i]='y';
        }else if(Krip[i]=='w'){
            Krip[i]='z';
        }else if(Krip[i]=='x'){
            Krip[i]='a';
        }else if(Krip[i]=='y'){
            Krip[i]='b';
        }else if(Krip[i]=='z'){
            Krip[i]='c';
        }

    }

    cout<<Krip.toStdString()<<endl;

    fputs(Krip.toUtf8().constData(),gra);

    fclose(gra);
}


void Estructuras::Eliminar_Bloque(int ID){
    NodoB *auxB=PrimeroB;
    if(auxB!=NULL){
        while (auxB!=NULL) {
            if(auxB->ID==ID){

                if(PrimeroB==UltimoB){
                    PrimeroB=NULL;
                    UltimoB=NULL;
                }else if(auxB==PrimeroB){
                    PrimeroB->sig->ant=NULL;
                    PrimeroB=PrimeroB->sig;
                    auxB->sig=NULL;
                }else if(auxB==UltimoB){
                    UltimoB->ant->sig=NULL;
                    UltimoB=UltimoB->ant;
                    auxB->ant=NULL;
                }else{
                    auxB->ant->sig=auxB->sig;
                    auxB->sig->ant=auxB->ant;
                    auxB->sig=NULL;
                    auxB->ant=NULL;
                }

             break;
            }

         auxB=auxB->sig;
        }
    }
}


void Estructuras::Eliminar_Ruta_Bloque(int ID, char *Ruta){
    NodoB *auxB=PrimeroB;
    if(auxB!=NULL){
        while (auxB!=NULL) {
            if(auxB->ID==ID){
                NodoLDB *auxLDB=auxB->Primero;
                if(auxLDB!=NULL){
                    while (auxLDB) {
                        cout<<Ruta<< "  "<<auxLDB->Archivo<<endl;
                        if(strcmp(auxLDB->Archivo,Ruta)==0){
                            cout<<"Encontrado....."<<endl;
                            if(auxB->Primero==auxB->Ultimo){
                                auxB->Primero=NULL;
                                auxB->Ultimo=NULL;

                            }else if(auxLDB==auxB->Primero){
                                auxB->Primero->sig->ant=NULL;
                                auxB->Primero=auxB->Primero->sig;
                                auxLDB->sig;
                            }else if(auxLDB==auxB->Ultimo){
                                auxB->Ultimo->ant->sig=NULL;
                                auxB->Ultimo=auxB->Ultimo->ant;
                                auxLDB->ant=NULL;
                            }else{
                                auxB->ant->sig=auxB->sig;
                                auxB->sig->ant=auxB->ant;
                                auxB->sig=NULL;
                                auxB->ant=NULL;
                            }
                         break;
                        }
                     auxLDB=auxLDB->sig;
                    }
                }
             break;
            }
         auxB=auxB->sig;
        }
    }
}







