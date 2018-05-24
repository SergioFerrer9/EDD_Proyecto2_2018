#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "estructuras.h"
#include "grafica.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QString>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <fstream>
#include "QMessageBox"


using namespace std;
using std::cout;
using std::endl;

int Transaccion=1;
int Estado=0;   //Estado 1 = Autobuses
                //Estado 2 = Pilotos
                //Estado 3 = Estaciones
                //Estado 4 = Grafos
                //Estado 5 = Matriz
                //Estado 6 = Usuarios
                //Estado 7 = Bloques
                //Estado 8 = BloquesDB
                //Estado 9 = Transacciones

int EstadoB=0;  //EstadoB 1 = Autobus.
                //EstadoB 2 = Piloto.
                //EstadoB 3 = Rutas.

Estructuras *estructuras = new Estructuras();
QString TextoSalida="";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    estructuras->Inicializar_TablaHash_Autobuses();
    estructuras->Inicializar_TablaHash_Pilotos();
    estructuras->Iniciar_Lista_Lexicografica();

}

MainWindow::~MainWindow()
{
    delete ui;
}


/// Cargar Archivo................
void MainWindow::on_actionCargar_Archivo_triggered()
{
    Cargar_Autobuses();
}



///Boton Cargar Pilotos..............................
void MainWindow::on_actionPilotos_triggered()
{
    Cargar_Pilotos();
}

///Boton Cargar Estaciones..............................
void MainWindow::on_actionEstaciones_triggered()
{
    Cargar_Estaciones();

}

///Boton Cargar Rutas..............................
void MainWindow::on_actionRutas_triggered()
{
    Cargar_Rutas();
}

///Boton Cargar Parqueos..............................
void MainWindow::on_actionParqueos_triggered()
{
    Cargar_Parqueos();
}

///Boton Cargar Usuarios..............................
void MainWindow::on_actionUsuarios_triggered()
{
    Cargar_Usuarios();
}

///Boton Cargar Transacciones..........................
void MainWindow::on_actionTransacciones_triggered()
{
    Cargar_Transacciones();

}


//Mostrar Autobuses.................
void MainWindow::Mostrar_Autobuses(){
    QPixmap pixv("./TablaHash1.png");
    ui->label->setPixmap(pixv);}


//Mostrar Pilotos....................
void MainWindow::Mostrar_Pilotos(){
    QPixmap pixv("./TablaHash2.png");
    ui->label_7->setPixmap(pixv);
}


//Mostrar Estaciones.................
void MainWindow::Mostrar_Estaciones(){
    QPixmap pixv("./Lista_Estaciones.png");
    ui->label_8->setPixmap(pixv);
}


//Mostrar Rutas......................
void MainWindow::Mostrar_Rutas(){
    QPixmap pixv("./Lista_Grafos.png");
    ui->label_9->setPixmap(pixv);
}


//Mostrar Parqueos....................
void MainWindow::Mostrar_Parqueos(){
    QPixmap pixv("./Lista_Matrices.png");
    ui->label_10->setPixmap(pixv);
}


//Mostrar Usuarios.....................
void MainWindow::Mostrar_Usuarios(){
    QPixmap pixv("./Lista_Lexico.png");
    ui->label_11->setPixmap(pixv);
}

//Mostrar Bloque.......................
void MainWindow::Mostrar_Bloque(){
    QPixmap pixv("./Bloques.png");
    ui->label_12->setPixmap(pixv);
}

void MainWindow::Mostrar_Bloque_Individual(){
    QPixmap pixv("./Bloques_Individual.png");
    ui->label_12->setPixmap(pixv);
}

void MainWindow::Mostrar_Estacion_Individual(){
    QPixmap pixv("./Estacion_Individual.png");
    ui->label_12->setPixmap(pixv);
}

///Cargar Autobuses....................................
void MainWindow::Cargar_Autobuses(){
    TextoSalida.append(">>> ******Carga de Archivo de Autobuses******\n");
    TextoSalida.append(">>> Insertar en Tabla Hash.\n");
    QString ruta=QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "",tr("Archivos CSV (*.csv)"));


    QString Arch=ruta;
    Arch=Arch.replace("-","");
    const std::string& path=Arch.toStdString();

    char *path2 =new char[path.length()+1];
    strcpy(path2, path.c_str());
    char *ptr;
    char *archivo;

     ptr=strtok(path2,"/");
     if(ptr==NULL){
         cout<<"Termino"<<endl;
     }
     while(ptr!=NULL){
          ptr=strtok(NULL,"/");
          if(ptr!=NULL){
              archivo=ptr;
          }

     }

           if (ruta != NULL) {
               ifstream archivo (ruta.toLocal8Bit().data());
               if (archivo.is_open()){
                   string linea;

                   while(getline (archivo,linea)){
                       QString linea2=QString::fromLocal8Bit(linea.data());

                       QStringList listado=linea2.split(',');
                       if(listado.length()==3){  //Cantidad de Columnas...

                           QString Placa=listado[0];

                          const std::string& modelo=listado[1].toStdString();
                          char *Mod=new char[modelo.length()+1];
                          strcpy(Mod, modelo.c_str());

                          QString estado=listado[2];
                          estado =estado.replace("\r\n", "").replace("\n", "").replace("\r", "");
                          const std::string& Estado=estado.toStdString();

                          char *Esta=new char[Estado.length()+1];
                          strcpy(Esta, Estado.c_str());
                         // nota=strtok(nota,"\n");

                          if(Placa.compare("Placa")==0 |strcmp(Mod,"Modelo")==0 | strcmp(Esta,"Estado")==0){
                               cout<<"Error en la Linea del Archivo csv"<<endl;
                          }else{

                              estructuras->LLave_Ascii(Placa,Mod,Esta);
                              TextoSalida.append(">>> Se inserto Autobus   Placa: ").append(Placa).append("  Modelo: ").append(Mod).append("  Estado: ").append(Esta).append("\n");


                          }


                       }else{
                           QMessageBox::information(NULL,"Advertencia","Error al leer línea");
                       }
                   }

                   archivo.close();

               }else{
                   QMessageBox::information(NULL,"Advertencia","No se puede abrir el archivo");
               }

           }

       estructuras->Graficar_TablaHash_Autobuses();
       TextoSalida.append(">>> Se Grafico Tabla Hash de Autobuses.\n");
       Mostrar_Autobuses();
       TextoSalida.append(">>> Se Muestra en Pantalla Tabla Hash de Autobuses.\n");

       ui->textEdit->setText(TextoSalida);
}

///Cargar Pilotos.................................................
void MainWindow::Cargar_Pilotos(){
    TextoSalida.append(">>> ******Carga de Archivo de Pilotos******\n");
    TextoSalida.append(">>> Insertar en Tabla Hash.\n");
    QString ruta=QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "",tr("Archivos CSV (*.csv)"));


    QString Arch=ruta;
    Arch=Arch.replace("-","");
    const std::string& path=Arch.toStdString();

    char *path2 =new char[path.length()+1];
    strcpy(path2, path.c_str());
    char *ptr;
    char *archivo;

     ptr=strtok(path2,"/");
     if(ptr==NULL){
         cout<<"Termino"<<endl;
     }
     while(ptr!=NULL){
          ptr=strtok(NULL,"/");
          if(ptr!=NULL){
              archivo=ptr;
          }

     }

           if (ruta != NULL) {
               ifstream archivo (ruta.toLocal8Bit().data());
               if (archivo.is_open()){
                   string linea;
                   while(getline (archivo,linea)){
                       QString linea2=QString::fromLocal8Bit(linea.data());

                       QStringList listado=linea2.split(',');
                       if(listado.length()==4){  //Cantidad de Columnas...

                        QString DPI=listado[0];

                       QString Nombre=listado[1];

                         int Edad=listado[2].toInt(0,10);
                         QString EDAD=listado[2];


                          QString Genero=listado[3];
                          Genero =Genero.replace("\r\n", "").replace("\n", "").replace("\r", "");
                          const std::string& Gen=Genero.toStdString();

                          char *genero=new char[Gen.length()+1];
                          strcpy(genero, Gen.c_str());


                          if(DPI.compare("DPI")==0 |Nombre.compare("Nombre")==0 | strcmp(genero,"Edad")==0 | EDAD.compare("Edad")==0){
                               cout<<"Error en la Linea del Archivo csv"<<endl;
                          }else{

                              estructuras->LLave_Ascii_Pilotos(DPI,Nombre,Edad,genero);
                              TextoSalida.append(">>> Se inserto Piloto   DPI: ").append(DPI).append("  Nombre: ").append(Nombre).append("  Edad: ").append(QString::number(Edad)).append("  Genero: ").append(genero).append("\n");


                          }


                       }else{
                           cout<<"Error en la Linea del Archivo csv..."<<endl;
                       }
                   }

                   archivo.close();

               }else{
                   QMessageBox::information(NULL,"Advertencia","No se puede abrir el archivo");
               }

           }

    estructuras->Graficar_TablaHash_Pilotos();
    TextoSalida.append(">>> Se Grafico Tabla Hash de Pilotos.\n");
    Mostrar_Pilotos();
    TextoSalida.append(">>> Se Muestra en Pantalla Tabla Hash de Pilotos.\n");
    ui->textEdit->setText(TextoSalida);

}

void MainWindow::Cargar_Estaciones(){
    TextoSalida.append(">>> ******Carga de Archivo de Estaciones******\n");
    TextoSalida.append(">>> Insertar en Lista Simple.\n");
    QString ruta=QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "",tr("Archivos CSV (*.csv)"));


    QString Arch=ruta;
    Arch=Arch.replace("-","");
    const std::string& path=Arch.toStdString();

    char *path2 =new char[path.length()+1];
    strcpy(path2, path.c_str());
    char *ptr;
    char *archivo;

     ptr=strtok(path2,"/");
     if(ptr==NULL){
         cout<<"Termino"<<endl;
     }
     while(ptr!=NULL){
          ptr=strtok(NULL,"/");
          if(ptr!=NULL){
              archivo=ptr;
          }

     }

           if (ruta != NULL) {
               ifstream archivo (ruta.toLocal8Bit().data());
               if (archivo.is_open()){
                   string linea;
                   while(getline (archivo,linea)){
                       QString linea2=QString::fromLocal8Bit(linea.data());

                       QStringList listado=linea2.split(',');
                       if(listado.length()==3){  //Cantidad de Columnas...

                           const std::string& codigo=listado[0].toStdString();
                           char *Codigo=new char[codigo.length()+1];
                           strcpy(Codigo, codigo.c_str());

                          const std::string& nombre=listado[1].toStdString();
                          char *Nombre=new char[nombre.length()+1];
                          strcpy(Nombre, nombre.c_str());

                          QString ubicacion=listado[2];
                          ubicacion =ubicacion.replace("\r\n","").replace("\n", "").replace("\r", "");
                          const std::string& Estado=ubicacion.toStdString();

                          char *Ubicacion=new char[Estado.length()+1];
                          strcpy(Ubicacion, Estado.c_str());
                         // nota=strtok(nota,"\n");

                          if(strcmp(Codigo,"Codigo")==0 |strcmp(Nombre,"Nombre")==0 | strcmp(Ubicacion,"Ubicacion")==0){
                               cout<<"Error en la Linea del Archivo csv"<<endl;
                          }else{

                              estructuras->Insertar_Lista_Estaciones(Codigo,Nombre,Ubicacion);
                              TextoSalida.append(">>> Se inserto Estacion   Codigo: ").append(Codigo).append("  Nombre: ").append(Nombre).append("  Ubicacion: ").append(Ubicacion).append("\n");


                          }


                       }else{
                          cout<<"Error en la Linea del Archivo csv..."<<endl;
                       }
                   }

                   archivo.close();

               }else{
                   QMessageBox::information(NULL,"Advertencia","No se puede abrir el archivo");
               }

           }

        estructuras->Graficar_Lista_Estaciones();
        TextoSalida.append(">>> Se Grafico Lista de Estaciones.\n");
        Mostrar_Estaciones();
        TextoSalida.append(">>> Se Muestara en Pantalla Lista de Estaciones.\n");
        ui->textEdit->setText(TextoSalida);
}

void MainWindow::Cargar_Rutas(){
    TextoSalida.append(">>> ******Carga de Archivo de Rutas******\n");
    TextoSalida.append(">>> Insertar en Lista de Grafos.\n");
    QString ruta=QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "",tr("Archivos CSV (*.csv)"));
    QString Arch=ruta;
    Arch=Arch.replace("-","");
    const std::string& path=Arch.toStdString();

    char *path2 =new char[path.length()+1];
    strcpy(path2, path.c_str());
    char *ptr;
    char *Archivo;
    char *nombre;

     ptr=strtok(path2,"/");
     if(ptr==NULL){
         cout<<"Termino"<<endl;
     }
     while(ptr!=NULL){
          ptr=strtok(NULL,"/");
          if(ptr!=NULL){
              Archivo=ptr;
          }

     }

     nombre=strtok(Archivo,".");
        if(estructuras->Buscar_Archivo_Ruta(Archivo)==false){
            TextoSalida.append(">>> Se Inserto Ruta: ").append(Archivo).append("\n");

           if (ruta != NULL) {
               ifstream archivo (ruta.toLocal8Bit().data());
               if (archivo.is_open()){
                   string linea;
                   int line=0;
                   while(getline (archivo,linea)){

                       QString linea2=QString::fromLocal8Bit(linea.data());
                       QStringList listado=linea2.split(',');
                     //  cout<<"linea "<<line<<endl;
                       for(int i=0;i<listado.length();i++){

                           QString ruta1=listado[i];
                           ruta1 =ruta1.replace("\r\n","").replace("\n","").replace("\r","").replace(" ","");


                           const std::string& ruta=ruta1.toStdString();
                           char *Ruta=new char[ruta.length()+1];
                           strcpy(Ruta, ruta.c_str());
                           if(line>0){
                           estructuras->Agregar_En_Grafo(Archivo,Ruta,line);                           
                           TextoSalida.append(">>> Se inserto Estacion en Ruta: ").append(Archivo).append("  Estacion: ").append(Ruta).append("\n");

                           }

                       }


                    line++;

                   }

                   archivo.close();

               }else{
                   QMessageBox::information(NULL,"Advertencia","No se puede abrir el archivo");
               }

           }
        }else{
            QMessageBox::information(NULL,"Advertencia","El Archivo ya existe...");
        }

    estructuras->Graficar_ListaGrafos();
    TextoSalida.append(">>> Se Grafico Lista de Grafos.\n");
    Mostrar_Rutas();
    TextoSalida.append(">>> Se Muestra en Pantalla Lista de Grafos.\n");
    ui->textEdit->setText(TextoSalida);
}

void MainWindow::Cargar_Parqueos(){
    TextoSalida.append(">>> ******Carga de Archivo de Parqueo******\n");
    TextoSalida.append(">>> Insertar en Lista de Matrices.\n");
    QString ruta=QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "",tr("Archivos CSV (*.csv)"));

    QString Arch=ruta;
    Arch=Arch.replace("-","");
    const std::string& path=Arch.toStdString();

    char *path2 =new char[path.length()+1];
    strcpy(path2, path.c_str());
    char *ptr;
    char *Archivo;
    char *nombre;

     ptr=strtok(path2,"/");
     if(ptr==NULL){
         cout<<"Termino"<<endl;
     }
     while(ptr!=NULL){
          ptr=strtok(NULL,"/");
          if(ptr!=NULL){
              Archivo=ptr;
          }

     }

     nombre=strtok(Archivo,".");
        if(estructuras->Buscar_Archivo_Matriz(Archivo)==false){
            TextoSalida.append(">>> Se Crea el Aputador de la Matriz: ").append(Archivo).append("\n");
           if (ruta != NULL) {
               ifstream archivo (ruta.toLocal8Bit().data());
               if (archivo.is_open()){
                   string linea;
                   int fila=0;
                   while(getline (archivo,linea)){

                       QString linea2=QString::fromLocal8Bit(linea.data());
                       QStringList listado=linea2.split(',');
                       int columna=1;
                       for(int i=0;i<listado.length();i++){
                           const std::string& placa=listado[i].toStdString();
                           char *Placa=new char[placa.length()+1];
                           strcpy(Placa, placa.c_str());


                             if(fila>0){
                              estructuras->Agregar_En_Matriz(Archivo,Placa,fila,columna);
                              TextoSalida.append(">>> Se Inserta en la Matriz: ").append(Archivo).append("  Con Placa: ").append(Placa).append("  En la posicion: Fila").append(QString::number(fila)).append(" Columna: ").append(QString::number(columna)).append("\n");

                             }
                              columna++;
                       }


                    fila++;

                   }

                   archivo.close();

               }else{
                   QMessageBox::information(NULL,"Advertencia","No se puede abrir el archivo");
               }

           }
        }else{
            QMessageBox::information(NULL,"Advertencia","El Archivo ya existe...");
        }

        estructuras->Graficar_Lista_Matrices();
        TextoSalida.append(">>> Se Grfica Lista de Matrices de Estacionamientos.\n");
        Mostrar_Parqueos();
        TextoSalida.append(">>> Se Muestra en Pantalla Lista de Matrices de Estacionamientos.\n");
        ui->textEdit->setText(TextoSalida);
}

void MainWindow::Cargar_Usuarios(){
    TextoSalida.append(">>> ******Carga de Archivo de Usuarios******\n");
    TextoSalida.append(">>> Insertar en Tabla Hash de Usuarios.\n");
    QString ruta=QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "",tr("Archivos CSV (*.csv)"));

    QString Arch=ruta;
    Arch=Arch.replace("-","");
    const std::string& path=Arch.toStdString();

    char *path2 =new char[path.length()+1];
    strcpy(path2, path.c_str());
    char *ptr;
    char *archivo;

     ptr=strtok(path2,"/");
     if(ptr==NULL){
         cout<<"Termino"<<endl;
     }
     while(ptr!=NULL){
          ptr=strtok(NULL,"/");
          if(ptr!=NULL){
              archivo=ptr;
          }

     }

           if (ruta != NULL) {
               ifstream archivo (ruta.toLocal8Bit().data());
               if (archivo.is_open()){
                   string linea;
                   int line=0;
                   while(getline (archivo,linea)){
                       QString linea2=QString::fromLocal8Bit(linea.data());

                       QStringList listado=linea2.split(',');
                       if(listado.length()==4){  //Cantidad de Columnas...

                          QString DPI=listado[0];

                          const std::string& tarjeta=listado[1].toStdString();
                          char *Tarjeta=new char[tarjeta.length()+1];
                          strcpy(Tarjeta, tarjeta.c_str());

                          const std::string& nombre=listado[2].toStdString();
                          char *Nombre=new char[nombre.length()+1];
                          strcpy(Nombre, nombre.c_str());

                          QString edad=listado[3];
                          edad =edad.replace("\r\n", "").replace("\n", "").replace("\r", "");
                          int Edad= edad.toInt(0,10);



                          if(DPI.compare("DPI")==0 | strcmp(Tarjeta,"Tarjeta")==0 | strcmp(Nombre,"Nombre")==0 | edad.compare("Edad")==0 | line<1){
                               cout<<"Error en la Linea del Archivo csv"<<endl;
                          }else{

                              //cout<<"DPI: "<<DPI.toStdString()<<" Tarjeta:"<<Tarjeta<<" Nombre:"<<Nombre<<" Edad:"<<Edad<<endl;
                              estructuras->LLave_Ascii_Lista_Lexicografica(DPI,Tarjeta,Nombre,Edad);
                              TextoSalida.append(">>> Se el Inserto el Usuario: DPI ").append(DPI).append("  Tarjeta: ").append(Tarjeta).append("   Nombre: ").append(Nombre).append("  Edad: ").append(QString::number(Edad)).append("\n");

                          }


                       }else{
                          cout<<"Error en la Linea del Archivo csv..."<<endl;
                       }

                       line++;
                   }

                   archivo.close();

               }else{
                   QMessageBox::information(NULL,"Advertencia","No se puede abrir el archivo");
               }

           }

        estructuras->Graficar_Lista_Lexicografica();
        TextoSalida.append(">>> Se Grafica Tabla Hash de Usuarios.\n");
        Mostrar_Usuarios();
        TextoSalida.append(">>> Se Muestra en Pantalla Tabla Hash de Usuarios.\n");
        ui->textEdit->setText(TextoSalida);
}


void MainWindow::Cargar_Transacciones(){
    TextoSalida.append(">>> ******Carga de Archivo de Transacciones******\n");
    QString ruta=QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "",tr("Archivos CSV (*.csv)"));


    QString Arch=ruta;
    Arch=Arch.replace("-","");
    const std::string& path=Arch.toStdString();

    char *path2 =new char[path.length()+1];
    strcpy(path2, path.c_str());
    char *ptr;
    char *archivo;

     ptr=strtok(path2,"/");
     if(ptr==NULL){
         cout<<"Termino"<<endl;
     }
     while(ptr!=NULL){
          ptr=strtok(NULL,"/");
          if(ptr!=NULL){
              archivo=ptr;
          }

     }
            int t=0;
           if (ruta != NULL) {
               ifstream archivo (ruta.toLocal8Bit().data());

               if (archivo.is_open()){
                   string linea;
                   int line=0;
                   while(getline (archivo,linea)){
                       QString linea2=QString::fromLocal8Bit(linea.data());

                       QStringList listado=linea2.split(',');
                       cout<<"Linea: "<<line<<endl;
                       for(int i=0;i<listado.length();i++){  //Cantidad de Columnas...


                          QString edad=listado[i];
                          edad =edad.replace("\r\n","").replace("\n","").replace("\r","");
                          const std::string& dpi=edad.toStdString();
                          char *DPI=new char[dpi.length()+1];
                          strcpy(DPI, dpi.c_str());

                          if(line>0){
                               int Bloque=ui->lineEdit_5->text().toInt(0,10);
                               char *Ruta=strdup(ui->lineEdit_6->text().toUtf8().constData());

                               if(Bloque>0 && strcmp(Ruta,"")!=0){

                                   estructuras->Agregar_Transacciones(Bloque,Ruta,line,DPI);
                                   TextoSalida.append(">>> Agregar Transacciones a Bloque: ").append(QString::number(Bloque)).append("  Ruta: ").append(Ruta).append("   Usuario con DPI: ").append(DPI).append("\n");

                               }else{
                                   t=1;
                               }

                          }


                       }

                     line++;
                   }

                   archivo.close();

               }else{
                   QMessageBox::information(NULL,"Advertencia","No se puede abrir el archivo");
               }


            Transaccion++;
           }

           if(t==1){
               QMessageBox::information(NULL,"ERROR","Error en el Bloque o Ruta.");
           }
       estructuras->Graficar_Bloque();
       TextoSalida.append(">>> Graficar Bloques Con Transacciones.\n");
       Mostrar_Bloque();
       TextoSalida.append(">>> Mostrar Lista de Bloques Con Transacciones.\n");
       ui->textEdit->setText(TextoSalida);

}


void MainWindow::Agregar_Ruta(){
    char *Ruta=strdup(ui->lineEdit->text().toUtf8().constData());

}

///Crear Bloque...
void MainWindow::on_pushButton_clicked()
{
    estructuras->Crear_Bloque();
    QMessageBox::information(NULL,"Mensaje","Bloque Creado");
    estructuras->Graficar_Bloque();
    Mostrar_Bloque();
    TextoSalida.append(">>> Crear Un Bloque Nuevo.\n");
    ui->textEdit->setText(TextoSalida);
}

///Agregar Ruta al Bloque...
void MainWindow::on_pushButton_2_clicked()
{
    char *Ruta=strdup(ui->lineEdit->text().toUtf8().constData());
    int ID = ui->lineEdit_5->text().toInt(0,10);
    estructuras->Agregar_Ruta_Bloque(ID,Ruta);
    estructuras->Graficar_Bloque();
    Mostrar_Bloque();
    TextoSalida.append(">>> Agregar Ruta: ").append(Ruta).append("  En Bloque: ").append(QString::number(ID)).append("\n");
    ui->textEdit->setText(TextoSalida);
}

///Agrear Piloto al Bloque...
void MainWindow::on_pushButton_3_clicked()
{
     int ID = ui->lineEdit_5->text().toInt(0,10);
     QString Piloto=ui->lineEdit_3->text();
    estructuras->Agregar_Piloto_Bloque(Piloto, ID);
    estructuras->Graficar_Bloque();
    Mostrar_Bloque();
    TextoSalida.append(">>> Agregar Piloto: ").append(Piloto).append("  En Bloque: ").append(QString::number(ID)).append("\n");
    ui->textEdit->setText(TextoSalida);

}

///Agregar Autobus al Bloque...
void MainWindow::on_pushButton_4_clicked()
{
    int ID = ui->lineEdit_5->text().toInt(0,10);
    QString Autobus=ui->lineEdit_4->text();
    estructuras->Agregar_Autobus_Bloque(Autobus,ID);
    estructuras->Graficar_Bloque();
    Mostrar_Bloque();
    TextoSalida.append(">>> Agregar Autobus: ").append(Autobus).append("  En Bloque: ").append(QString::number(ID).append("\n"));
    ui->textEdit->setText(TextoSalida);

}


///Bloque Individual..................
void MainWindow::on_pushButton_5_clicked()
{
    int ID = ui->lineEdit_5->text().toInt(0,10);
    estructuras->Graficar_Bloque_Individual(ID);
    Mostrar_Bloque_Individual();
    TextoSalida.append(">>> Mostrar Unicamente el BLoque: ").append(QString::number(ID)).append("\n");
    ui->textEdit->setText(TextoSalida);

}

///Mostrar Estacion Individual............
void MainWindow::on_pushButton_6_clicked()
{
     int ID_Bloque = ui->lineEdit_5->text().toInt(0,10);
     char *Ruta=strdup(ui->lineEdit_6->text().toUtf8().constData());
     char *Estacion=strdup(ui->lineEdit_7->text().toUtf8().constData());

     estructuras->Graficar_Estacion_Individual(ID_Bloque,Ruta,Estacion);
     Grafica *graficar=new Grafica();
     graficar->Set_Grafica();
     graficar->show();
     TextoSalida.append(">>> Mostrar Unicamente la Estacion: ").append(Estacion).append("\n");
     ui->textEdit->setText(TextoSalida);

}

void MainWindow::on_actionEncryptar_triggered()
{
    estructuras->Encryptar();
    QMessageBox::information(NULL,"Encryptar","Archivo Encryptado");
    TextoSalida.append(">>> Encriptar Bitacora \n");
    ui->textEdit->setText(TextoSalida);

}

void MainWindow::on_actionDesencryptar_triggered()
{
    QString ruta=QFileDialog::getOpenFileName(this, tr("Abrir Archivo"), "",tr("Archivos 200915305 (*.200915305-log)"));
    const std::string& path=ruta.toStdString();
    char *path2 =new char[path.length()+1];
    strcpy(path2, path.c_str());
    char *ptr;
    char *archivo;

     ptr=strtok(path2,"/");
     if(ptr==NULL){
         cout<<"Termino"<<endl;
     }
     while(ptr!=NULL){
          ptr=strtok(NULL,"/");
          if(ptr!=NULL){
              archivo=ptr;
          }

     }
            int t=0;
           if (ruta != NULL) {
               ifstream archivo (ruta.toLocal8Bit().data());

               if (archivo.is_open()){
                   string linea;

                   while(getline (archivo,linea)){
                       QString linea2=QString::fromLocal8Bit(linea.data());

                       QString Linea=DesEncryptar(linea2);
                       if(Linea.compare("$AUTOBUSES$")==0){
                           Estado=1;

                       }else if(Linea.compare("$PILOTOS$")==0){
                           Estado=2;

                       }else if(Linea.compare("$ESTACIONES$")==0){
                           Estado=3;

                       }else if(Linea.compare("$GRAFOS$")==0){
                           Estado=4;

                       }else if(Linea.compare("$MATRIZ$")==0){
                           Estado=5;

                       }else if(Linea.compare("$USUARIOS$")==0){
                           Estado=6;

                       }else if(Linea.compare("$BLOQUE$")==0){
                           Estado=7;

                       }else if(Linea.compare("$BLOQUEDB$")==0){
                           Estado=8;

                       }else if(Linea.compare("$$TRANSACCION$$")==0){
                           Estado=9;

                       }else if(Estado==1){
                           ///Autobuses...
                           QStringList listado=Linea.split(',');
                           if(listado.length()==3){
                               QString placa=listado[0];
                               QString modelo=listado[1];
                               QString estado=listado[2];
                               estado=estado.replace("\n","");

                                const std::string& pla=placa.toStdString();
                                char *Placa=new char[pla.length()+1];
                                strcpy(Placa, pla.c_str());

                                const std::string& mod=modelo.toStdString();
                                char *Modelo=new char[mod.length()+1];
                                strcpy(Modelo, mod.c_str());

                                const std::string& est=estado.toStdString();
                                char *Estado=new char[est.length()+1];
                                strcpy(Estado, est.c_str());


                               cout<<"Autobuses: "<<Placa<<" "<<Modelo<<" "<<Estado<<endl;
                               estructuras->LLave_Ascii(placa,Modelo,Estado);
                           }

                       }else if(Estado==2){
                           ///Pilotos...
                           QStringList listado=Linea.split(',');
                           if(listado.length()==4){
                               QString dpi=listado[0];
                               QString nombre=listado[1];
                               QString edad=listado[2];
                               QString genero=listado[3];
                               genero=genero.replace("\n","");

                                const std::string& d=dpi.toStdString();
                                char *DPI=new char[d.length()+1];
                                strcpy(DPI, d.c_str());

                                const std::string& n=nombre.toStdString();
                                char *Nombre=new char[n.length()+1];
                                strcpy(Nombre, n.c_str());

                                int Edad=edad.toInt(0,10);

                                const std::string& g=genero.toStdString();
                                char *Genero=new char[g.length()+1];
                                strcpy(Genero, g.c_str());


                               cout<<"Pilotos: "<<DPI<<" "<<Nombre<<" "<<Edad<<" "<<Genero<<endl;
                               estructuras->LLave_Ascii_Pilotos(dpi,nombre,Edad,Genero);

                           }


                       }else if(Estado==3){
                           ///Estaciones...
                           QStringList listado=Linea.split(',');
                           if(listado.length()==3){
                               QString codigo=listado[0];
                               QString nombre=listado[1];
                               QString ubicacion=listado[2];
                               ubicacion=ubicacion.replace("\n","");

                                const std::string& d=codigo.toStdString();
                                char *Codigo=new char[d.length()+1];
                                strcpy(Codigo, d.c_str());

                                const std::string& n=nombre.toStdString();
                                char *Nombre=new char[n.length()+1];
                                strcpy(Nombre, n.c_str());


                                const std::string& g=ubicacion.toStdString();
                                char *Ubicacion=new char[g.length()+1];
                                strcpy(Ubicacion, g.c_str());


                               cout<<"Estaciones: "<<Codigo<<" "<<Nombre<<" "<<Ubicacion<<endl;
                               estructuras->Insertar_Lista_Estaciones(Codigo,Nombre,Ubicacion);
                           }

                       }else if(Estado==4){
                           ///Grafos
                           QStringList listado=Linea.split(',');
                           QString archivo=listado[0];

                           const std::string& d=archivo.toStdString();
                           char *Archivo=new char[d.length()+1];
                           strcpy(Archivo, d.c_str());

                           cout<<"Archivo: "<<Archivo<<endl;
                           if(estructuras->Buscar_Archivo_Ruta(Archivo)==false){
                               for(int i=1;i<listado.length();i++){
                                   QString estacion=listado[i];
                                   estacion=estacion.replace("\n","");

                                   QStringList lista=estacion.split("/");
                                   QString grafo=lista[0];

                                   const std::string& g=grafo.toStdString();
                                   char *Estacion=new char[g.length()+1];
                                   strcpy(Estacion, g.c_str());

                                   QString dir=lista[1];
                                   int Dir =dir.toInt(0,10);

                                   cout<<"Archivo: "<<Archivo<<" Grafo: "<<Estacion<<" Dir: "<<Dir<<endl;
                                   estructuras->Agregar_En_Grafo(Archivo,Estacion,Dir);
                               }
                            }
                       }else if(Estado==5){
                           ///Matriz...
                           QStringList Fila=Linea.split(';');
                           QString archivo=Fila[0];

                           const std::string& d=archivo.toStdString();
                           char *Archivo=new char[d.length()+1];
                           strcpy(Archivo, d.c_str());

                            if(estructuras->Buscar_Archivo_Matriz(Archivo)==false){
                               for(int i=1;i<Fila.length();i++){

                                   QString fila=Fila[i];
                                   fila=fila.replace("\n","");
                                   QStringList Columna=fila.split(",");

                                   for(int j=0;j<Columna.length();j++){
                                       QString placa=Columna[j];
                                       placa=placa.replace("\n","");

                                       const std::string& g=placa.toStdString();
                                       char *Placa=new char[g.length()+1];
                                       strcpy(Placa, g.c_str());

                                       cout<<"Archivo: "<<Archivo<<" Fila: "<<i<<" Columna:"<<j+1<<" Placa: "<<Placa<<endl;
                                       estructuras->Agregar_En_Matriz(Archivo,Placa,i,j+1);
                                   }

                               }
                            }

                       }else if(Estado==6){
                           ///Usuarios...
                           QStringList listado=Linea.split(',');
                           if(listado.length()==4){
                               QString dpi=listado[0];
                               QString nombre=listado[1];
                               QString tarjeta=listado[2];
                               QString edad=listado[3];
                               edad=edad.replace("\n","");

                                const std::string& d=dpi.toStdString();
                                char *DPI=new char[d.length()+1];
                                strcpy(DPI, d.c_str());

                                const std::string& n=nombre.toStdString();
                                char *Nombre=new char[n.length()+1];
                                strcpy(Nombre, n.c_str());

                                const std::string& g=tarjeta.toStdString();
                                char *Tarjeta=new char[g.length()+1];
                                strcpy(Tarjeta, g.c_str());

                                int Edad=edad.toInt(0,10);


                               cout<<"Usuarios: "<<DPI<<" "<<Nombre<<" "<<Tarjeta<<" "<<Edad<<endl;
                               estructuras->LLave_Ascii_Lista_Lexicografica(dpi,Tarjeta,Nombre,Edad);
                           }


                       }else if(Estado==7){
                           ///Lista Bloques
                           QStringList listado=Linea.split(',');
                           cout<<"Tamaño BLoque:"<<listado.length()<<endl;
                           for(int i=0;i<listado.length();i++){

                               QString Bloque = listado[i];
                               cout<<"Lista Bloque: "<<Bloque.toStdString()<<endl;
                               estructuras->Crear_Bloque();
                           }


                       }else if(Estado==8){
                           QStringList listado=Linea.split(';');
                           QString bloque =listado[0];
                           int Bloque=bloque.toInt(0,10);
                           cout<<"Bloque: "<<Bloque<<endl;
                           for(int i=1;i<listado.length();i++){
                               QString registros=listado[i];                               
                               registros=registros.replace("\n","");
                               QStringList DatosBloque=registros.split(",");

                               QString Dato=DatosBloque[0];
                               if(Dato.compare("$AUTOBUS$")==0){
                                   QString Dato1=DatosBloque[1];
                                   const std::string& d=Dato1.toStdString();
                                   char *Autobus=new char[d.length()+1];
                                   strcpy(Autobus, d.c_str());
                                   cout<<"Autobus: "<<Autobus<<endl;
                                   estructuras->Agregar_Autobus_Bloque(Autobus,Bloque);

                               }else if(Dato.compare("$PILOTO$")==0){
                                   QString Dato1=DatosBloque[1];
                                   const std::string& d=Dato1.toStdString();
                                   char *Piloto=new char[d.length()+1];
                                   strcpy(Piloto, d.c_str());
                                   cout<<"Piloto: "<<Piloto<<endl;
                                   estructuras->Agregar_Piloto_Bloque(Piloto,Bloque);

                               }else if(Dato.compare("$RUTAS$")==0){
                                   cout<<"Rutas: "<<endl;
                                   for(int i=1;i<DatosBloque.length();i++){
                                       QString Dato1=DatosBloque[i];
                                       const std::string& d=Dato1.toStdString();
                                       char *Ruta=new char[d.length()+1];
                                       strcpy(Ruta, d.c_str());
                                       cout<<Ruta<<endl;
                                       estructuras->Agregar_Ruta_Bloque(Bloque,Ruta);
                                   }

                               }


                           }

                       }else if(Estado==9){
                           ///Transacciones...
                           QStringList listado=Linea.split(';');

                           QString bloq=listado[0];
                           int Bloque=bloq.toInt(0,10); //ID Bloque.

                           QString ruta=listado[1];
                           const std::string& d=ruta.toStdString();
                           char *Ruta=new char[d.length()+1];
                           strcpy(Ruta, d.c_str());

                           if(listado.length()>1){
                               for(int i=2;i<listado.length();i++){
                                    QString arbol = listado[i];
                                    QStringList dpi=arbol.split(",");
                                  for(int j=0;j<dpi.length();j++){
                                       QString dp =dpi[j];
                                       const std::string& d=dp.toStdString();
                                       char *DPI=new char[d.length()+1];
                                       strcpy(DPI, d.c_str());

                                       cout<<"Bloque: "<<Bloque<<" Ruta: "<<Ruta<<" G: "<<i-1<<" DPI:"<<DPI<<endl;
                                       estructuras->Agregar_Transacciones(Bloque,Ruta,i-1,DPI);
                                   }

                               }

                           }


                       }

                   }

                   archivo.close();

               }else{
                   QMessageBox::information(NULL,"Advertencia","No se puede abrir el archivo");
               }


            Transaccion++;
           }

           if(t==1){
               QMessageBox::information(NULL,"ERROR","Error en el Bloque o Ruta.");
           }

           estructuras->Graficar_TablaHash_Autobuses();
           Mostrar_Autobuses();

           estructuras->Graficar_TablaHash_Pilotos();
           Mostrar_Pilotos();

           estructuras->Graficar_Lista_Estaciones();
           Mostrar_Estaciones();

           estructuras->Graficar_ListaGrafos();
           Mostrar_Rutas();

           estructuras->Graficar_Lista_Matrices();
           Mostrar_Parqueos();

           estructuras->Graficar_Lista_Lexicografica();
           Mostrar_Usuarios();

           estructuras->Graficar_Bloque();
           Mostrar_Bloque();

           TextoSalida.append(">>> Desencriptar Bitacora \n");
           ui->textEdit->setText(TextoSalida);
}

QString MainWindow::DesEncryptar(QString Krip){


    for(int i=0;i<Krip.length();i++){

        if(Krip[i]=='D'){
            Krip[i]='A';
        }else if(Krip[i]=='E'){
            Krip[i]='B';
        }else if(Krip[i]=='F'){
            Krip[i]='C';
        }else if(Krip[i]=='G'){
            Krip[i]='D';
        }else if(Krip[i]=='H'){
            Krip[i]='E';
        }else if(Krip[i]=='I'){
            Krip[i]='F';
        }else if(Krip[i]=='J'){
            Krip[i]='G';
        }else if(Krip[i]=='K'){
            Krip[i]='H';
        }else if(Krip[i]=='L'){
            Krip[i]='I';
        }else if(Krip[i]=='M'){
            Krip[i]='J';
        }else if(Krip[i]=='N'){
            Krip[i]='K';
        }else if(Krip[i]=='O'){
            Krip[i]='L';
        }else if(Krip[i]=='P'){
            Krip[i]='M';
        }else if(Krip[i]=='Q'){
            Krip[i]='N';
        }else if(Krip[i]=='R'){
            Krip[i]='O';
        }else if(Krip[i]=='S'){
            Krip[i]='P';
        }else if(Krip[i]=='T'){
            Krip[i]='Q';
        }else if(Krip[i]=='U'){
            Krip[i]='R';
        }else if(Krip[i]=='V'){
            Krip[i]='S';
        }else if(Krip[i]=='W'){
            Krip[i]='T';
        }else if(Krip[i]=='X'){
            Krip[i]='U';
        }else if(Krip[i]=='Y'){
            Krip[i]='V';
        }else if(Krip[i]=='Z'){
            Krip[i]='W';
        }else if(Krip[i]=='A'){
            Krip[i]='X';
        }else if(Krip[i]=='B'){
            Krip[i]='Y';
        }else if(Krip[i]=='C'){
            Krip[i]='Z';
        }else if(Krip[i]=='d'){
            Krip[i]='a';
        }else if(Krip[i]=='e'){
            Krip[i]='b';
        }else if(Krip[i]=='f'){
            Krip[i]='c';
        }else if(Krip[i]=='g'){
            Krip[i]='d';
        }else if(Krip[i]=='h'){
            Krip[i]='e';
        }else if(Krip[i]=='i'){
            Krip[i]='f';
        }else if(Krip[i]=='j'){
            Krip[i]='g';
        }else if(Krip[i]=='k'){
            Krip[i]='h';
        }else if(Krip[i]=='l'){
            Krip[i]='i';
        }else if(Krip[i]=='m'){
            Krip[i]='j';
        }else if(Krip[i]=='n'){
            Krip[i]='k';
        }else if(Krip[i]=='o'){
            Krip[i]='l';
        }else if(Krip[i]=='p'){
            Krip[i]='m';
        }else if(Krip[i]=='q'){
            Krip[i]='n';
        }else if(Krip[i]=='r'){
            Krip[i]='o';
        }else if(Krip[i]=='s'){
            Krip[i]='p';
        }else if(Krip[i]=='t'){
            Krip[i]='q';
        }else if(Krip[i]=='u'){
            Krip[i]='r';
        }else if(Krip[i]=='v'){
            Krip[i]='s';
        }else if(Krip[i]=='w'){
            Krip[i]='t';
        }else if(Krip[i]=='x'){
            Krip[i]='u';
        }else if(Krip[i]=='y'){
            Krip[i]='v';
        }else if(Krip[i]=='z'){
            Krip[i]='w';
        }else if(Krip[i]=='a'){
            Krip[i]='x';
        }else if(Krip[i]=='b'){
            Krip[i]='y';
        }else if(Krip[i]=='c'){
            Krip[i]='z';
        }

    }
     return Krip;
}

void MainWindow::on_actionInfo_triggered()
{
    QMessageBox::information(this,tr("Proyecto 2"),tr("Estructuras de Datos \nSeccion: B \nPrimer Semestre 2018 \nNombre: Sergio Alfonso Ferrer Garcia \nCarne: 200915305\n CUI: 2529952520101"),
                            tr("Continuar"));
}

///Eliminar Bloque...
void MainWindow::on_pushButton_7_clicked()
{
    int ID =ui->lineEdit_9->text().toInt(0,10);
    estructuras->Eliminar_Bloque(ID);
    estructuras->Graficar_Bloque();
    Mostrar_Bloque();
}

///Eliminar Ruta de Bloque...
void MainWindow::on_pushButton_8_clicked()
{
    int ID =ui->lineEdit_9->text().toInt(0,10);
    char *Ruta=strdup(ui->lineEdit_8->text().toUtf8().constData());
    estructuras->Eliminar_Ruta_Bloque(ID,Ruta);
    estructuras->Graficar_Bloque();
    Mostrar_Bloque();

}
