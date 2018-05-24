#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //Cargar Archivos.
    void Cargar_Autobuses();
    void Cargar_Pilotos();
    void Cargar_Estaciones();
    void Cargar_Rutas();
    void Cargar_Parqueos();
    void Cargar_Usuarios();
    void Cargar_Transacciones();

    //Mostrar Graficas.
    void Mostrar_Autobuses();
    void Mostrar_Pilotos();
    void Mostrar_Estaciones();
    void Mostrar_Rutas();
    void Mostrar_Parqueos();
    void Mostrar_Usuarios();
    void Mostrar_Bloque();
    void Mostrar_Bloque_Individual();
    void Mostrar_Estacion_Individual();

    //Bloque.
    void Agregar_Ruta();
    QString DesEncryptar(QString linea);

    ~MainWindow();

private slots:
    void on_actionCargar_Archivo_triggered();

    void on_actionPilotos_triggered();

    void on_actionEstaciones_triggered();

    void on_actionRutas_triggered();

    void on_actionParqueos_triggered();

    void on_actionUsuarios_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionTransacciones_triggered();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_actionEncryptar_triggered();

    void on_actionDesencryptar_triggered();

    void on_actionInfo_triggered();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
