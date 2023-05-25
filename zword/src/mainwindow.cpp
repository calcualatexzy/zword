
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QString>
#include <QDebug>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , z_trashButton(nullptr)
    , z_dotsButton(nullptr)
    , z_newNoteButton(nullptr)
    , z_styleEditorButton(nullptr)
    , z_searchEdit(nullptr)
    , z_clearButton(nullptr)
    , z_textEdit(nullptr)
    , z_currentNodeData(nullptr)
    , z_splitter(nullptr)
    , z_foldersWidget(nullptr)
    , z_noteListWidget(nullptr)
    , z_displayFont((QStringLiteral("Segoe UI")))
    , z_currentCharsLimit(64)
    , z_currentFontFamily(QStringLiteral("Segoe UI"))
    , z_editorDateLabel(nullptr)
{
    ui->setupUi(this);
    setupMainWindow();
    setupFonts();
    // setupKeyboardShortcuts();
    setupNewNoteButtonAndTrashButton();
    setupSplitter();
    setupRightFrame();
    resetEditorSettings();
    setupSignalsSlots();
    setupSearchEdit();
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
    // middle frame
    ui->searchEdit->setStyleSheet(z_styleSheet);
    ui->verticalSpacer_upSearchEdit->setStyleSheet(z_styleSheet);
    ui->verticalSpacer_upSearchEdit2->setStyleSheet(z_styleSheet);
    ui->listviewLabel1->setStyleSheet(z_styleSheet);
    ui->listviewLabel2->setStyleSheet(z_styleSheet);

    // buttons
    // ui->toggleTreeViewButton->setStyleSheet(z_styleSheet);
    ui->styleEditorButton->setStyleSheet(z_styleSheet);
    ui->newNoteButton->setStyleSheet(z_styleSheet);
    ui->trashButton->setStyleSheet(z_styleSheet);
    ui->dotsButton->setStyleSheet(z_styleSheet);

    // right frame (editor)
    ui->textEdit->setStyleSheet(z_styleSheet);
    ui->frameRight->setStyleSheet(z_styleSheet);
    ui->frameRightTop->setStyleSheet(z_styleSheet);


    z_newNoteButton = ui->newNoteButton;
    z_trashButton = ui->trashButton;
    z_dotsButton = ui->dotsButton;
    z_styleEditorButton = ui->styleEditorButton;
    z_searchEdit = ui->searchEdit;
    z_textEdit = ui->textEdit;
    z_editorDateLabel = ui->editorDateLabel;
    z_splitter = ui->splitter;
    // z_foldersWidget = ui->frameLeft;
    z_noteListWidget = ui->frameLeft;
    // don't resize first two panes when resizing
    z_splitter->setStretchFactor(0, 0);
    z_splitter->setStretchFactor(1, 0);
    z_splitter->setStretchFactor(2, 1);

    ui->verticalSpacer->changeSize(0, 7, QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->verticalSpacer_upEditorDateLabel->changeSize(0, 27, QSizePolicy::Fixed, QSizePolicy::Fixed);
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
    z_styleEditorButton->setFont(QFont(QStringLiteral("Roboto"), 16, QFont::Bold));
    z_styleEditorButton->installEventFilter(this);

    // ui->toggleTreeViewButton->setMaximumSize({ 33, 25 });
    // ui->toggleTreeViewButton->setMinimumSize({ 33, 25 });
    // ui->toggleTreeViewButton->setCursor(QCursor(Qt::PointingHandCursor));
    // ui->toggleTreeViewButton->setFocusPolicy(Qt::TabFocus);
    // ui->toggleTreeViewButton->setIconSize(QSize(16, 16));
    // ui->toggleTreeViewButton->setIcon(QIcon(QString::fromUtf8(":/images/drawer_icon.png")));

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

/*!
 * \brief MainWindow::setupSignalsSlots
 * connect between signals and slots
 */
void MainWindow::setupSignalsSlots()
{
    // new note button
    connect(z_newNoteButton, &QPushButton::pressed, this, &MainWindow::onNewNoteButtonPressed);
    connect(z_newNoteButton, &QPushButton::clicked, this, &MainWindow::onNewNoteButtonClicked);
    // delete note button
    connect(z_trashButton, &QPushButton::pressed, this, &MainWindow::onTrashButtonPressed);
    connect(z_trashButton, &QPushButton::clicked, this, &MainWindow::onTrashButtonClicked);
    // connect(z_listModel, &NoteListModel::rowsRemoved, this,[this]() { z_trashButton->setEnabled(true); });
    // 3 dots button
    connect(z_dotsButton, &QPushButton::pressed, this, &MainWindow::onDotsButtonPressed);
    connect(z_dotsButton, &QPushButton::clicked, this, &MainWindow::onDotsButtonClicked);
    // Style Editor Button
    connect(z_styleEditorButton, &QPushButton::clicked, this, &MainWindow::onStyleEditorButtonClicked);
}

void MainWindow::setupSearchEdit()
{
    // clear button
    z_clearButton = new QToolButton(z_searchEdit);
    QPixmap pixmap(QStringLiteral(":images/closeButton.png"));
    z_clearButton->setIcon(QIcon(pixmap));
    QSize clearSize(15, 15);
    z_clearButton->setIconSize(clearSize);
    z_clearButton->setCursor(Qt::ArrowCursor);
    z_clearButton->hide();


    // search button
    QToolButton *searchButton = new QToolButton(z_searchEdit);
    QPixmap newPixmap(QStringLiteral(":images/magnifyingGlass.png"));
    searchButton->setIcon(QIcon(newPixmap));
    QSize searchSize(18, 18);
    searchButton->setIconSize(searchSize);
    searchButton->setCursor(Qt::ArrowCursor);

    // layout
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::RightToLeft, z_searchEdit);
    layout->setContentsMargins(2, 0, 3, 0);
    layout->addWidget(z_clearButton);
    layout->addStretch();
    layout->addWidget(searchButton);
    z_searchEdit->setLayout(layout);

    z_searchEdit->installEventFilter(this);
}

/*!
 * \brief MainWindow::eventFilter
 * Mostly take care on the event happened on widget whose filter installed to the mainwindow
 * \param object
 * \param event
 * \return
 */
bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    switch (event->type()){
        case QEvent::Enter:{
            if(qApp->applicationState()==Qt::ApplicationActive){
                if (object == z_newNoteButton) {
                    setCursor(Qt::PointingHandCursor);
                    z_newNoteButton->setIcon(QIcon(QStringLiteral(":/images/newNote_Hovered.png")));
                    qDebug()<<"z_newNoteButton\n";
                }
                if (object == z_trashButton) {
                    setCursor(Qt::PointingHandCursor);
                    z_trashButton->setIcon(QIcon(QStringLiteral(":/images/trashCan_Hovered.png")));
                    qDebug()<<"z_trashButton\n";
                }
                if (object == z_dotsButton) {
                    setCursor(Qt::PointingHandCursor);
                    z_dotsButton->setIcon(QIcon(QStringLiteral(":/images/3dots_Hovered.png")));
                    qDebug()<<"z_dotsButton\n";
                }
            }
            if (object == ui->frame) {
                ui->centralWidget->setCursor(Qt::ArrowCursor);
            }
            break;
        }
        case QEvent::Leave:{
            if(qApp->applicationState()==Qt::ApplicationActive){
                if (object == z_newNoteButton) {
                    unsetCursor();
                    z_newNoteButton->setIcon(QIcon(QStringLiteral(":/images/newNote_Regular.png")));
                }
                if (object == z_trashButton) {
                    unsetCursor();
                    z_trashButton->setIcon(QIcon(QStringLiteral(":/images/trashCan_Regular.png")));
                }
                if (object == z_dotsButton) {
                    unsetCursor();
                    z_dotsButton->setIcon(QIcon(QStringLiteral(":/images/3dots_Regular.png")));
                }
            }
            break;
        }
        case QEvent::WindowActivate:{
            z_newNoteButton->setIcon(QIcon(QStringLiteral(":/images/newNote_Regular.png")));
            z_trashButton->setIcon(QIcon(QStringLiteral(":/images/trashCan_Regular.png")));
            z_dotsButton->setIcon(QIcon(QStringLiteral(":/images/3dots_Regular.png")));
            break;
        }
        default:
            break;
    }
    return QObject::eventFilter(object, event);
}

/*!
 * \brief MainWindow::onNewNoteButtonPressed
 * When the new-note button is pressed, set it's icon accordingly
 */
void MainWindow::onNewNoteButtonPressed()
{
    z_newNoteButton->setIcon(QIcon(QStringLiteral(":/images/newNote_Pressed.png")));
}

/*!
 * \brief MainWindow::onNewNoteButtonClicked
 * Create a new note when clicking the 'new note' button
 */
void MainWindow::onNewNoteButtonClicked()
{
    // if (!z_newNoteButton->isVisible()) {
    //     return;
    // }
    // if (z_listViewLogic->isAnimationRunning()) {
    //     return;
    // }
    z_newNoteButton->setIcon(QIcon(QStringLiteral(":/images/newNote_Regular.png")));

    // save the data of the previous selected
    // z_noteEditorLogic->saveNoteToDB();

    // if (!z_searchEdit->text().isEmpty()) {
    //     z_listViewLogic->clearSearch(true);
    // } else {
    //     createNewNote();
    // }
}

/*!
 * \brief MainWindow::onTrashButtonPressed
 * When the trash button is pressed, set it's icon accordingly
 */
void MainWindow::onTrashButtonPressed()
{
    z_trashButton->setIcon(QIcon(QStringLiteral(":/images/trashCan_Pressed.png")));
}

/*!
 * \brief MainWindow::onTrashButtonClicked
 * Delete selected note when clicking the 'delete note' button
 */
void MainWindow::onTrashButtonClicked()
{
    z_trashButton->setIcon(QIcon(QStringLiteral(":/images/trashCan_Regular.png")));

    // z_trashButton->blockSignals(true);
    // z_noteEditorLogic->deleteCurrentNote();
    // z_trashButton->blockSignals(false);
}

/*!
 * \brief MainWindow::onDotsButtonPressed
 * When the 3 dots button is pressed, set it's icon accordingly
 */
void MainWindow::onDotsButtonPressed()
{
    z_dotsButton->setIcon(QIcon(QStringLiteral(":/images/3dots_Pressed.png")));
}

void MainWindow::onDotsButtonClicked()
{
    z_dotsButton->setIcon(QIcon(QStringLiteral(":/images/3dots_Regular.png")));
}

void MainWindow::onStyleEditorButtonClicked()
{
    // if (z_settingsDatabase->value(QStringLiteral("editorSettingsWindowGeometry"), "NULL") == "NULL")
    //     z_styleEditorWindow.move(z_newNoteButton->mapToGlobal(QPoint(-z_styleEditorWindow.width() - z_newNoteButton->width(),z_newNoteButton->height())));

    // if (z_styleEditorWindow.isVisible()) {
    //     z_styleEditorWindow.hide();
    // } else {
    //     z_styleEditorWindow.show();
    //     z_styleEditorWindow.setFocus();
    // }
}
