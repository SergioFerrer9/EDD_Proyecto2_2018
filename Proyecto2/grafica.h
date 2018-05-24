#ifndef GRAFICA_H
#define GRAFICA_H

#include <QMainWindow>

namespace Ui {
class Grafica;
}

class Grafica : public QMainWindow
{
    Q_OBJECT

public:
    explicit Grafica(QWidget *parent = 0);

    void Mostrar_Estacion_Individual();
    void Set_Grafica();

    ~Grafica();

private:
    Ui::Grafica *ui;
};

#endif // GRAFICA_H
