#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QFileDialog>
#include <QDebug>
#include "AnimationForm.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setAttribute(Qt::WA_TranslucentBackground, true); // ÉèÖÃÍ¸Ã÷±³¾°
 //   ui->centralwidget->setAutoFillBackground(true);
    ui->centralwidget->LoadAnimationFile("C:\\Users\\37436\\Downloads\\home.json");
    ui->centralwidget->StartPlayAnimation();
    connect(ui->actionopenfile,&QAction::triggered,this,[=]{
       QString  fileName = QFileDialog::getOpenFileName(this,
            tr("Open Image"), "C:\\Users\\37436\\Downloads\\", tr("Json Files (*.json)"));
       qDebug()<<"file_name:"<<fileName;
       ui->centralwidget->LoadAnimationFile(fileName);
       ui->centralwidget->StartPlayAnimation();

       AnimationForm* form = new AnimationForm();
       form->LoadAnimationFile(fileName);
       form->StartPlayAnimation();
       form->move(0, 0);
       form->show();

    });
}

MainWindow::~MainWindow()
{

    delete ui;
}

