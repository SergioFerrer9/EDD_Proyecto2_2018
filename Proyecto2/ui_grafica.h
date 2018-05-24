/********************************************************************************
** Form generated from reading UI file 'grafica.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAFICA_H
#define UI_GRAFICA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Grafica
{
public:
    QWidget *centralwidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QMenuBar *menubar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *Grafica)
    {
        if (Grafica->objectName().isEmpty())
            Grafica->setObjectName(QStringLiteral("Grafica"));
        Grafica->resize(800, 600);
        centralwidget = new QWidget(Grafica);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(10, 10, 781, 551));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 779, 549));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);
        Grafica->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Grafica);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        Grafica->setMenuBar(menubar);
        toolBar = new QToolBar(Grafica);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        Grafica->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(Grafica);

        QMetaObject::connectSlotsByName(Grafica);
    } // setupUi

    void retranslateUi(QMainWindow *Grafica)
    {
        Grafica->setWindowTitle(QApplication::translate("Grafica", "Grafica", nullptr));
        label->setText(QString());
        toolBar->setWindowTitle(QApplication::translate("Grafica", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Grafica: public Ui_Grafica {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAFICA_H
