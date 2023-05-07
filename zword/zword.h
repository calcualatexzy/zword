
#ifndef ZWORD_H
#define ZWORD_H

#include <QMainWindow>
#include <QFont>
#include <QFontComboBox>


QT_BEGIN_NAMESPACE
namespace Ui { class zword; }
QT_END_NAMESPACE

class zword : public QMainWindow

{
    Q_OBJECT

public:
    zword(QWidget *parent = nullptr);
    ~zword();

private slots:
    void newDocument();
    void save();
    void open();
    void saveAs();
    void print();
    void exit();
    void selectFont();
    void selectText();

private:
    Ui::zword *ui;
    QString currentFile;
};

#endif // ZWORD_H
