#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <QObject>

///Estructura Tabla Hash de los Autobuses...............................
struct NodoListaHash{
    int Clave;
    char *Placa;
    char *Modelo;
    char *Estado;
    NodoListaHash *sig;
    NodoListaHash *ant;
};

struct Nodo_TablaHash_A{
    int indice;
    Nodo_TablaHash_A *sig;
    Nodo_TablaHash_A *ant;
    NodoListaHash *Primero;
    NodoListaHash *Ultimo;

};

///Estructura Tabla Hash de los Pilotos..................................
struct NodoAVLHash{
    int Clave;
    char *DPI;
    char *Nombre;
    int llavek;
    int Edad;
    char *Genero;
    int Altura;
    int fe;
    int Nivel;
    int Contador;

    NodoAVLHash *izq;
    NodoAVLHash *der;
};

struct Nodo_TablaHash_P{
    int indice;
    Nodo_TablaHash_P *sig;
    Nodo_TablaHash_P *ant;
    NodoAVLHash *RAIZ;
};

///*******************Lista Simple de Estaciones*************************
struct NodoListaEstacion{
    char *Codigo;
    char *Nombre;
    char *Ubicacion;
    NodoListaEstacion *sig;
    NodoListaEstacion *ant;
};

///*************Estructura Lista Doble de Grafos*************************
struct NodoGrafo{
    char *Codigo;
    int dir;
    NodoGrafo *sig;
    NodoGrafo *ant;
};

struct NodoListaDoble{
    char *Archivo;
    NodoListaDoble *sig;
    NodoListaDoble *ant;
    NodoGrafo *PrimeroG;
    NodoGrafo *UltimoG;
};

///************Estructura Lista Doble de Matrices************************

///...........Nodo de la Matriz...
struct NodoMatriz{
    int Fila;
    int Columna;
    char *Placa;
    struct NodoMatriz *izq;
    struct NodoMatriz *der;
    struct NodoMatriz *arriba;
    struct NodoMatriz *abajo;
};

///...........Nodo de las Filas...
struct NodoFila{
    int Fila;
    struct NodoFila *Abajo;  //*Sig
    struct NodoFila *Arriba; //*Ant
    struct NodoMatriz *PrimeroM;
    struct NodoMatriz *UltimoM;
};

///............Nodo de las Columnas...
struct NodoColumna{
    int Columna;
    struct NodoColumna *Izq;
    struct NodoColumna *Der;
    struct NodoMatriz *PrimeroM;
    struct NodoMatriz *UltimoM;
};

///............Nodo Pibote de cada Matriz....
struct NodoListaDobleM{
    char *Archivo;
    NodoListaDobleM *sig;
    NodoListaDobleM *ant;
    NodoFila *PrimeroF;
    NodoFila *UltimoF;
    NodoColumna *PrimeroC;
    NodoColumna *UltimoC;
};

///*********Estructura de la Lista Mapeada Lexicograficamentes************
struct NodoListaLexicografica{
    int indice;
    int Clave;
    char *DPI;
    char *Tarjeta;
    char *Nombre;
    int Edad;
    NodoListaLexicografica *sig;
    NodoListaLexicografica *ant;
};

struct NodoListaAux{
    int indice;
    int Clave;
    char *DPI;
    char *Tarjeta;
    char *Nombre;
    int Edad;
    NodoListaAux *sig;
    NodoListaAux *ant;
};

///*************************BLOQUE***************************************
struct NodoAVLBloque{
    char *DPI;
    char *Tarjeta;
    char *Nombre;
    int Edad;
    int Altura;
    int fe;
    int Contador;
    int Nivel;
    NodoAVLBloque *izq;
    NodoAVLBloque *der;
};

struct NodoGrafoB{
    char *Codigo;
    int contador;
    int dir;
    NodoGrafoB *sig;
    NodoGrafoB *ant;
    NodoAVLBloque *RAIZ;
};

struct NodoLDobleB{
    char *Archivo;
    int carga;
    NodoLDobleB *sig;
    NodoLDobleB *ant;
    NodoGrafoB *PrimeroG;
    NodoGrafoB *UltimoG;
};

struct NodoBloque{
    int ID;
    NodoListaHash *Autobus;
    NodoAVLHash *Piloto;
    char *Fecha;
    NodoBloque *sig;
    NodoBloque *ant;
    NodoLDobleB *Primero;
    NodoLDobleB *Ultimo;

};

///***************************Arbol B************************************




///************************Clase Estructuras*****************************
class Estructuras : public QObject
{
    Q_OBJECT
public:
    explicit Estructuras(QObject *parent = nullptr);
    //Tabla Hash1.
    void LLave_Ascii(QString clave, char *modelo, char *estado);
    void LLave_Ascii_Pilotos(QString DPI, QString Nombre, int Edad, char *Genero);
    void Inicializar_TablaHash_Autobuses();
    void Inicializar_TablaHash_Pilotos();
    void Agregar_TablaHash_Autobuses(int indice, int clave, char *Placa, char *Modelo, char *Estado);
    void Agregar_TablaHash_Pilotos(int indice, int clave, char *DPI, char *Nombre, int llavek, int Edad, char *Genero);
    void Graficar_TablaHash_Autobuses();
    void Graficar_TablaHash_Pilotos();

    //Tabla Hash2.
    int Altura(NodoAVLHash *actual);
    int Mayor(int num1, int num2);
    NodoAVLHash *Insertar(NodoAVLHash *nuevo, NodoAVLHash *actual);
    NodoAVLHash *Buscar(char *nombre, NodoAVLHash *actual);
    void Graficar_AVL(NodoAVLHash *actual);
    void Ajustar_Fe(NodoAVLHash *actual, int Nivel);
    void Equilibrar_AVL(NodoAVLHash *actual);
    NodoAVLHash *Obtener_Reemplazo(NodoAVLHash *reemp);
    NodoAVLHash *Izquierda(NodoAVLHash *actual);
    NodoAVLHash *Derecha(NodoAVLHash *actual);
    NodoAVLHash *IzquierdaDerecha(NodoAVLHash *actual);
    NodoAVLHash *DerechaIzquierda(NodoAVLHash *actual);
    FILE *gra2;
    void Agregar_En_AVL(char *archivo, int carne, char *nombre, char *nota);

    //Lista Estaciones.
    void Insertar_Lista_Estaciones(char *Codigo, char *Nombre, char *Ubicacion);
    void Graficar_Lista_Estaciones();

    //Lsta Grafos.
    void Agregar_ListaDoble(char *archivo);
    bool Buscar_Archivo_Ruta(char *archivo);
    void Graficar_ListaGrafos();
    void Agregar_En_Grafo(char *Archivo, char *Ruta, int dir);
    void Eliminar_Ultimo(char *Archivo);

    ///Lista Matrices.
    void Agregar_Lista_Matrices(char *Archivo);
    void Agregar_En_Matriz(char *Archivo, char *placa, int Fila, int Columna);
    void Agregar_En_Fila(NodoListaDobleM *Actual ,int Fila);
    void Agregar_En_Columna(NodoListaDobleM *Actual, int Columna);
    void Graficar_Lista_Matrices();
    bool Buscar_Archivo_Matriz(char *Archivo);

    ///Lista Mapeada Lexicograficamente.
    void LLave_Ascii_Lista_Lexicografica(QString DPI, char *Tarjeta, char *Nombre, int edad);
    void Agregar_En_Lista_Lexicografica(int indice, int Clave, char *DPI, char *Tarjeta, char *Nombre, int Edad);
    void Iniciar_Lista_Lexicografica();
    void Agregar_En_Lista_Aux(int indice, int Clave, char *DPI, char *Tarjeta, char *Nombre, int edad);
    void Graficar_Lista_Lexicografica();
    void Calcular_Porcentaje();
    void Rehashing();

    ///Bloques.
    void Crear_Bloque();
    void Agregar_Piloto_Bloque(QString DPI, int Bloque);
    void Buscar_Piloto(char *DPI, NodoAVLHash *actual, int Bloque);
    void Agregar_Autobus_Bloque(QString Placa, int Bloque);
    void Buscar_Autobus(char *Placa, int Bloque);
    void Agregar_Ruta_Bloque(int IDB, char *Ruta);
    void Buscar_Ruta(NodoBloque *auxB, char *Ruta);
    void Agregar_Transacciones(int Bloque, char *Ruta, int Grafo, char *DPI);
    void Graficar_Bloque();
    void Graficar_Bloque_Individual(int ID);

    int Altura2(NodoAVLBloque *actual);
    int Mayor2(int num1, int num2);
    NodoAVLBloque *Insertar2(NodoAVLBloque *nuevo, NodoAVLBloque *actual);
    NodoAVLBloque *Buscar2(char *nombre, NodoAVLBloque *actual);
    void Graficar_AVL2(NodoAVLBloque *actual);
    void Graficar_Estacion_Individual(int ID, char* Ruta, char *Estacion);
    void Graficar_AVL3(NodoAVLBloque *actual);
    void Ajustar_Fe2(NodoAVLBloque *actual, int Nivel);
    void Equilibrar_AVL2(NodoAVLBloque *actual);
    NodoAVLBloque *Obtener_Reemplazo2(NodoAVLBloque *reemp);
    NodoAVLBloque *Izquierda2(NodoAVLBloque *actual);
    NodoAVLBloque *Derecha2(NodoAVLBloque *actual);
    NodoAVLBloque *IzquierdaDerecha2(NodoAVLBloque *actual);
    NodoAVLBloque *DerechaIzquierda2(NodoAVLBloque *actual);
    FILE *gra3;
    void Agregar_En_AVL2();
    void Recorrer_AVL_Hash(NodoAVLHash *aux);

    ///Encrypt.....
    void Encryptar();
    void Recorrer_AVL_Bloque(NodoAVLBloque *aux);

    ///Eliminar.....
    void Eliminar_Bloque(int ID);
    void Eliminar_Ruta_Bloque(int ID, char *Ruta);


signals:

public slots:
};

#endif // ESTRUCTURAS_H
