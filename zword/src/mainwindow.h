
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QSplitter>
#include <QLabel>
#include <qpushbutton.h>
#include <vector>
#include <QListView>
#include <QStringListModel>
#include "customDocument.h"
#include "nodedata.h"
#include "theme.h"
#include "highlighter.h"
#include "searchIterator.h"

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
    QPushButton *z_ExpendReplaceButton;
    QLineEdit *z_searchEdit;
    QLineEdit *z_replaceEdit;
    QToolButton *z_searchButton;
    QToolButton *z_replaceButton;
    long long z_lastSearchIndex;
    bool z_ReplaceExpand;
    bool z_isSearching;
    bool z_isReplacing;
    QString z_search;
    QString z_replace;
    QString *z_searchingText;
    QToolButton *z_searchClearButton;
    QToolButton *z_replaceClearButton;
    CustomDocument *z_textEdit;
    Highlighter *z_highlighter;
    vector<NodeData*> z_vNodeData;
    NodeData* z_currentNodeData;
    QStringListModel *z_listModel;
    QListView *z_listView;
    QSplitter *z_splitter;
    QWidget *z_foldersWidget;
    QWidget *z_noteListWidget;

    SearchIterator z_searchIterator;

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
    void setupSearchAndReplace();
    void setupSearchEdit();
    void setupReplaceEdit();
    void setupEditorLogic();
    void setupSplitter();
    void setupNodeData();
    void setupKeyboardShortcuts();
    void setupNodeList();
    void resetEditorSettings();
    void setTextStyle();

private slots:
    // void InitData();

    void onNewNoteButtonPressed();
    void onNewNoteButtonClicked();
    void onTrashButtonPressed();
    void onTrashButtonClicked();
    void onDotsButtonPressed();
    void onDotsButtonClicked();
    void onStyleEditorButtonClicked();
    void onExpendReplaceButtonClicked();
    void onSearchButtonClicked();
    void onReplaceButtonClicked();
    void onSearchClearButtonClicked();
    void onReplaceClearButtonClicked();
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


signals:
    void signalReplace();
};

#endif // MAINWINDOW_H
