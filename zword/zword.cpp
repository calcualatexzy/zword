
#include "zword.h"
#include "./ui_zword.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

zword::zword(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::zword)
{
    ui->setupUi(this);

    connect(ui->actionNew_File, &QAction::triggered, this, &zword::newDocument);
    connect(ui->actionOpen_File, &QAction::triggered, this, &zword::open);
    connect(ui->actionSave_File, &QAction::triggered, this, &zword::save);
    connect(ui->actionSave_As, &QAction::triggered, this, &zword::saveAs);
}

zword::~zword()
{
    delete ui;
}

void zword::newDocument(){
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void zword::open(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file", nullptr, tr("Text files (*.txt);;Zword files (*.zw)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void zword::save(){
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        QFileDialog dialog(this);
        fileName = dialog.getSaveFileName(this, "Save", nullptr, tr("Text files (*.txt);;Zword files (*.zw)"));
        if (fileName.isEmpty())
            return;
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void zword::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}
