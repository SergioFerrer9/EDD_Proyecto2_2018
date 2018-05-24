#include "grafica.h"
#include "ui_grafica.h"

Grafica::Grafica(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Grafica)
{
    ui->setupUi(this);
}

Grafica::~Grafica()
{
    delete ui;
}

void Grafica::Mostrar_Estacion_Individual(){
    QPixmap pixv("./Estacion_Individual.png");
    ui->label->setPixmap(pixv);
}

void Grafica::Set_Grafica(){
    Mostrar_Estacion_Individual();
}
