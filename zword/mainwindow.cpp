
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QImage>
#include <QPushButton>
#include <QMenu>
#include <QLineEdit>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("zword");
    resize(500, 400);
//    QLabel* imageLabel = new QLabel(this);
//    imageLabel->setPixmap(QPixmap(":/images/apple.png"));
//    setCentralWidget(imageLabel);

    QPushButton* btn1 = new QPushButton(this);
    btn1->setText("Click One");
    QPushButton* btn2 = new QPushButton(this);
    btn2->setText("Click Two");
    QPushButton* btn3 = new QPushButton(this);
    btn3->setText("Click Three");
    QPushButton* btn4 = new QPushButton(this);
    btn4->setText("Click Four");
    QWidget* widget = new QWidget;
    this->setCentralWidget(widget);

    QHBoxLayout* hbox = new QHBoxLayout(this);
    widget->setLayout(hbox);

    hbox->addWidget(btn1);
    hbox->addWidget(btn2);
    hbox->addWidget(btn3);
    hbox->addWidget(btn4);
//    button->setGeometry(30, 60, 200, 100);
//    button->setFont(QFont("Times", 15));
//    button->setIcon(QIcon(":/images/apple.png"));
//    button->setIconSize(QSize(36,36));

//    QMenu* menu = new QMenu();
//    menu->setFont(QFont("Sanserif",14));
//    menu->setStyleSheet("background-color:yellow");
//    menu->addAction("Copy");
//    menu->addAction("Cut");
//    button->setMenu(menu);

//    QLineEdit* lineEdit = new QLineEdit(this);
//    lineEdit->setGeometry(200, 200, 250, 250);
//    lineEdit->setFont(QFont("Times", 14));
//    //lineEdit->setEnabled(false);
//    lineEdit->setEchoMode(QLineEdit::EchoMode::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

