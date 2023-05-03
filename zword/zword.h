
#ifndef ZWORD_H
#define ZWORD_H

#include <QMainWindow>



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

private:
    Ui::zword *ui;
    QString currentFile;
};

#endif // ZWORD_H
