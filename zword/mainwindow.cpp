
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("zword");
    QLabel* label = new QLabel(this);
    label->setPixmap(QPixmap(":/images/apple.png"));
//    label->setText("This is a label.");
//    label->move(100, 100);
//    label->setFont(QFont("Times", 15));
//    label->setStyleSheet("color:red");
//    label->setGeometry(100, 100, 300, 300);
}

MainWindow::~MainWindow()
{
    delete ui;
}


