
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , z_trashButton(nullptr)
    , z_dotsButton(nullptr)
    , z_newNoteButton(nullptr)
    , z_styleEditorButton(nullptr)
    , z_searchEdit(nullptr)
    , z_textEdit(nullptr)
    , z_splitter(nullptr)
    , z_foldersWidget(nullptr)
    , z_noteListWidget(nullptr)
    , z_displayFont((QStringLiteral("Segoe UI")))
    , z_currentCharsLimit(64);
    , z_currentFontFamily(QStringLiteral("Segoe UI"))
    , z_editorDateLabel(nullptr)
{
    ui->setupUi(this);
    setupMainWindow();
    setupFonts();
    setupNewNoteButtonAndTrashButton();
    setupSplitter();
    setupRightFrame();
    resetEditorSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::setupMainWindow(){

    QFile mainWindowStyleFile(QStringLiteral(":/styles/main-windows.css"));
    mainWindowStyleFile.open(QFile::ReadOnly);
    z_styleSheet = QString::fromLatin1(mainWindowStyleFile.readAll());
    setStyleSheet(z_styleSheet);
    /**** Apply the stylesheet for all children we change classes for ****/

    z_newNoteButton = ui->newNoteButton;
    z_trashButton = ui->trashButton;
    z_dotsButton = ui->dotsButton;
    z_styleEditorButton = ui->styleEditorButton;
    z_searchEdit = ui->searchEdit;
    z_textEdit = ui->textEdit;

    ui->frame->installEventFilter(this);
    ui->centralWidget->setMouseTracking(true);
    setMouseTracking(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Window, QColor(248, 248, 248));
    setAutoFillBackground(true);
    setPalette(pal);

    z_newNoteButton->setToolTip(tr("Create New Note"));
    z_trashButton->setToolTip(tr("Delete Selected Note"));
    z_dotsButton->setToolTip(tr("Open Menu"));
    z_styleEditorButton->setToolTip(tr("Style The Editor"));

    z_styleEditorButton->setText(QStringLiteral("Aa"));
    z_styleEditorButton->setFont(QFont(QStringLiteral("Roboto"), 12, QFont::Bold));

    z_splitter = ui->splitter;
    z_foldersWidget = ui->frameLeft;
    z_noteListWidget = ui->frameMiddle;

    z_editorDateLabel = ui->editorDateLabel;

    // don't resize first two panes when resizing
    z_splitter->setStretchFactor(0, 0);
    z_splitter->setStretchFactor(1, 0);
    z_splitter->setStretchFactor(2, 1);

    ui->toggleTreeViewButton->setMaximumSize({ 33, 25 });
    ui->toggleTreeViewButton->setMinimumSize({ 33, 25 });
    ui->toggleTreeViewButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->toggleTreeViewButton->setFocusPolicy(Qt::TabFocus);
    ui->toggleTreeViewButton->setIconSize(QSize(16, 16));
    ui->toggleTreeViewButton->setIcon(QIcon(QString::fromUtf8(":/images/drawer_icon.png")));

    QFont titleFont(z_displayFont, 10, QFont::DemiBold);
    ui->listviewLabel1->setFont(titleFont);
    ui->listviewLabel2->setFont(titleFont);
    ui->listviewLabel1->setText("Opening List...");

    z_editorDateLabel->setText("Welcome!");

    this->setWindowTitle(QStringLiteral("Zword"));
    setWindowIcon(QIcon(QStringLiteral(":/images/zword_icon.png")));
}

void MainWindow::setupFonts()
{
    z_editorDateLabel->setFont(QFont(z_displayFont, 10, QFont::Bold));
    z_searchEdit->setFont(QFont(z_displayFont, 10));
}

/*!
 * \brief MainWindow::setupNewNoteButtonAndTrashButton
 */
void MainWindow::setupNewNoteButtonAndTrashButton()
{
    z_newNoteButton->installEventFilter(this);
    z_trashButton->installEventFilter(this);
    z_dotsButton->installEventFilter(this);
    z_styleEditorButton->installEventFilter(this);
}

/*!
 * \brief MainWindow::setupSplitter
 * Set up the splitter that control the size of the scrollArea and the textEdit
 */
void MainWindow::setupSplitter()
{
    z_splitter->setCollapsible(0, false);
    z_splitter->setCollapsible(1, false);
    z_splitter->setCollapsible(2, false);
}

/*!
 * \brief MainWindow::setupRightFrame
 * Set up a frame above textEdit and behind the other widgets for a unifed background
 * in thet editor section
 */
void MainWindow::setupRightFrame()
{
    ui->frameRightTop->installEventFilter(this);
}


void MainWindow::resetEditorSettings()
{
    z_textEdit->setLineWrapColumnOrWidth(z_currentCharsLimit);
    z_currentFontPointSize = 13;
    z_currentSelectedFont = QFont(z_currentFontFamily, z_currentFontPointSize, QFont::Normal);
    z_textEdit->setFont(z_currentSelectedFont);
    z_textEdit->setWordWrapMode(QTextOption::WordWrap);
    z_textEdit->setLineWrapMode(QTextEdit::FixedColumnWidth);

    //set tab width
    QFontMetrics currentFontMetrics(z_currentSelectedFont);
    z_textEdit->setTabStopDistance(4 * currentFontMetrics.horizontalAdvance(QLatin1Char(' ')));
}

