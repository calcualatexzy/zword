
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QSplitter>
#include <QLabel>
#include <vector>
#include <QListView>
#include <QStringListModel>
#include "customDocument.h"
#include "nodedata.h"
#include "theme.h"

#define MAX_NODES 20

using std::vector;

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
    QToolButton *z_searchButton;
    QToolButton *z_clearButton;
    CustomDocument *z_textEdit;
    vector<NodeData*> z_vNodeData;
    NodeData* z_currentNodeData;
    QStringListModel *z_listModel;
    QListView *z_listView;
    QSplitter *z_splitter;
    QWidget *z_foldersWidget;
    QWidget *z_noteListWidget;

    QString z_displayFont;

    int z_currentCharsLimit;
    QString z_currentFontFamily;
    int z_currentFontPointSize;
    QFont z_currentSelectedFont;

    QLabel *z_editorDateLabel;

    Theme z_currentTheme;
    QColor z_currentEditorTextColor;
    void setupMainWindow();
    void setupFonts();
    /* setting EventFilters */
    void setupNewNoteButtonAndTrashButton();
    void setupRightFrame();
    void setupSignalsSlots();
    void setupSearchEdit();
    void setupEditorLogic();
    void setupSplitter();
    void setupNodeData();
    void setupKeyboardShortcuts();
    void setupNodeList();
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
    void onSearchButtonClicked();
    void saveNodeData();
    void saveAsNodeData();
    void savePrimateData();
    void openNodeData();
    void insertCurrentNodetoList();
    void setCurrentNodetoText();
    void setTheme(Theme theme);
    // void onClearButtonClicked();

    // void createNewNote();
    void on_listView_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
