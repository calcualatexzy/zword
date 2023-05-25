
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QSplitter>
#include <QLabel>
#include "customDocument.h"
#include "nodedata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    Ui::MainWindow *ui;

    QString z_styleSheet;
    QPushButton *z_trashButton;
    QPushButton *z_dotsButton;
    QPushButton *z_newNoteButton;
    QPushButton *z_styleEditorButton;
    QLineEdit *z_searchEdit;
    QToolButton *z_clearButton;
    CustomDocument *z_textEdit;
    NodeData* z_currentNodeData;
    QSplitter *z_splitter;
    QWidget *z_foldersWidget;
    QWidget *z_noteListWidget;

    QString z_displayFont;

    int z_currentCharsLimit;
    QString z_currentFontFamily;
    int z_currentFontPointSize;
    QFont z_currentSelectedFont;

    QLabel *z_editorDateLabel;
    void setupMainWindow();
    void setupFonts();
    /* setting EventFilters */
    void setupNewNoteButtonAndTrashButton();
    void setupRightFrame();
    void setupSignalsSlots();
    void setupSearchEdit();
    void setupEditorLogic();
    void setupSplitter();
    void resetEditorSettings();

private slots:
    // void InitData();

    void onNewNoteButtonPressed();
    void onNewNoteButtonClicked();
    void onTrashButtonPressed();
    void onTrashButtonClicked();
    void onDotsButtonPressed();
    void onDotsButtonClicked();
    void onStyleEditorButtonClicked();
    // void onClearButtonClicked();

    // void createNewNote();
};

#endif // MAINWINDOW_H
