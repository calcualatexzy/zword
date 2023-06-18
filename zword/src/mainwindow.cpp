
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>
#include <QString>
#include <QDebug>
#include <QToolButton>
#include <QMessageBox>
#include <vector>
#include <QFileDialog>
#include <QLineEdit>
#include <QTextDocument>
#include <QTextCursor>
#include <QColorDialog>
#include <QFontDialog>
#include "theme.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , z_trashButton(nullptr)
    , z_dotsButton(nullptr)
    , z_newNoteButton(nullptr)
    , z_styleEditorButton(nullptr)
    , z_colorButton(nullptr)
    , z_ExpendReplaceButton(nullptr)
    , z_searchEdit(nullptr)
    , z_replaceEdit(nullptr)
    , z_searchButton(nullptr)
    , z_lastSearchIndex(-1)
    , z_ReplaceExpand(false)
    , z_isSearching(false)
    , z_isReplacing(false)
    , z_searchClearButton(nullptr)
    , z_replaceClearButton(nullptr)
    , z_textEdit(nullptr)
    , z_highlighter(nullptr)
    , z_currentNodeData(nullptr)
    , z_listModel(nullptr)
    , z_listView(nullptr)
    , z_splitter(nullptr)
    , z_foldersWidget(nullptr)
    , z_noteListWidget(nullptr)
    , z_displayFont((QStringLiteral("Segoe UI")))
    , z_currentCharsLimit(64)
    , z_currentFontFamily(QStringLiteral("Segoe UI"))
    , z_editorDateLabel(nullptr)
    , z_currentTheme(Theme::Sepia)
    , z_currentEditorTextColor(26, 26, 26)
{
    ui->setupUi(this);
    setupMainWindow();
    setupFonts();
    setupNodeData();
    // setupKeyboardShortcuts();
    setupNewNoteButtonAndTrashButton();
    setupSplitter();
    setupRightFrame();
    resetEditorSettings();
    setupSearchAndReplace();
    setupNodeList();

    setupKeyboardShortcuts();
    setupSignalsSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::setupMainWindow(){

    QFile mainWindowStyleFile(QStringLiteral(":/styles/main-windows.css"));
    if(mainWindowStyleFile.isReadable()){
        mainWindowStyleFile.open(QFile::ReadOnly);
        z_styleSheet = QString::fromLatin1(mainWindowStyleFile.readAll());
        setStyleSheet(z_styleSheet);
    }
    /**** Apply the stylesheet for all children we change classes for ****/
    // middle frame
    ui->searchEdit->setStyleSheet(z_styleSheet);
    //ui->verticalSpacer_upSearchEdit->setStyleSheet(z_styleSheet);
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

    ui->searchEdit->setStyleSheet(z_styleSheet);

    ui->horizontalSpacer_6->changeSize(24, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

    z_newNoteButton = ui->newNoteButton;
    z_trashButton = ui->trashButton;
    z_dotsButton = ui->dotsButton;
    z_styleEditorButton = ui->styleEditorButton;
    z_colorButton = ui->ColorButton;
    z_ExpendReplaceButton=ui->ExpendReplaceButton;
    z_searchEdit = ui->searchEdit;
    z_replaceEdit=ui->replaceEdit;
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
    z_dotsButton->setToolTip(tr("Reset Format"));
    z_styleEditorButton->setToolTip(tr("Style The Editor"));
    z_colorButton->setToolTip(tr("Set Color"));

    z_styleEditorButton->setText(QStringLiteral("Aa"));
    z_styleEditorButton->setFont(QFont(QStringLiteral("Roboto"), 16, QFont::Bold));

    //z_colorButton->setText(QStringLiteral("Color"));
    z_colorButton->setFont(QFont(QStringLiteral("Roboto"), 8, QFont::Bold));
    QPixmap pixmap(QStringLiteral(":images/font_color.png"));
    z_colorButton->setIcon(QIcon(pixmap));

    // ui->toggleTreeViewButton->setMaximumSize({ 33, 25 });
    // ui->toggleTreeViewButton->setMinimumSize({ 33, 25 });
    // ui->toggleTreeViewButton->setCursor(QCursor(Qt::PointingHandCursor));
    // ui->toggleTreeViewButton->setFocusPolicy(Qt::TabFocus);
    // ui->toggleTreeViewButton->setIconSize(QSize(16, 16));
    // ui->toggleTreeViewButton->setIcon(QIcon(QString::fromUtf8(":/images/drawer_icon.png")));

    QFont titleFont(z_displayFont, 10, QFont::DemiBold);
    ui->listviewLabel1->setFont(titleFont);
    ui->listviewLabel2->setFont(titleFont);
    ui->listviewLabel1->setText("Document list");
    ui->listviewLabel2->setText("(^_^)");
    z_editorDateLabel->setText("Welcome!");

    this->setWindowTitle(QStringLiteral("Zword"));
    setWindowIcon(QIcon(QStringLiteral(":/images/zword_icon.png")));

    z_highlighter = new Highlighter(z_textEdit->document());
}

void MainWindow::setupFonts()
{
    z_editorDateLabel->setFont(QFont(z_displayFont, 10, QFont::Bold));
    z_searchEdit->setFont(QFont(z_displayFont, 10));
    z_replaceEdit->setFont(QFont(z_displayFont, 10));
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
    z_colorButton->installEventFilter(this);
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

void MainWindow::setupNodeData()
{

}


void MainWindow::setupKeyboardShortcuts()
{
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_N), this, SLOT(onNewNoteButtonClicked()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_D), this, SLOT(onTrashButtonClicked()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), this, SLOT(onSearchButtonClicked()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_H), this, SLOT(onReplaceButtonClicked()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this, SLOT(saveNodeData()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_O), this, SLOT(openNodeData()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_L), this, SLOT(alignLeft()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_E), this, SLOT(alignMiddle()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_R), this, SLOT(alignRight()));
}

void MainWindow::setupNodeList()
{
    z_listView = ui->listView;
    z_listModel = new QStringListModel(this);
    z_listView->setModel(z_listModel);
    z_listView->setEditTriggers(QAbstractItemView::SelectedClicked);
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

/*!
 * \brief MainWindow::setTheme
 * Changes the app theme
 */
void MainWindow::setTheme(Theme theme)
{
    z_currentTheme = theme;

    setCSSThemeAndUpdate(this, theme);
    //setCSSThemeAndUpdate(ui->verticalSpacer_upSearchEdit, theme);
    setCSSThemeAndUpdate(ui->verticalSpacer_upSearchEdit2, theme);
    setCSSThemeAndUpdate(ui->styleEditorButton, theme);
    setCSSThemeAndUpdate(ui->listviewLabel1, theme);
    setCSSThemeAndUpdate(ui->searchEdit, theme);
    setCSSThemeAndUpdate(ui->frameRight, z_currentTheme);
    setCSSThemeAndUpdate(ui->frameRightTop, z_currentTheme);

    switch (theme) {
    case Theme::Light: {
        z_currentEditorTextColor = QColor(26, 26, 26);
        break;
    }
    case Theme::Dark: {
        z_currentEditorTextColor = QColor(204, 204, 204);
        break;
    }
    case Theme::Sepia: {
        z_currentEditorTextColor = QColor(95, 74, 50);
        break;
    }
    }
}

void MainWindow::resetEditorSettings()
{
    z_textEdit->setLineWrapColumnOrWidth(z_currentCharsLimit);
    if(!z_currentFontPointSize)  z_currentFontPointSize = 13;
    z_currentSelectedFont = QFont(z_currentFontFamily, z_currentFontPointSize, QFont::Normal);
    z_currentSelectedColor = QColor();
    z_textEdit->setFont(z_currentSelectedFont);
    z_textEdit->setWordWrapMode(QTextOption::WordWrap);
    z_textEdit->setLineWrapMode(QTextEdit::FixedColumnWidth);
    z_textEdit->setFontItalic(false);
    z_textEdit->setFontWeight(QFont::Normal);
    setTheme(z_currentTheme);

    //set tab width
    QFontMetrics currentFontMetrics(z_currentSelectedFont);
    z_textEdit->setTabStopDistance(4 * currentFontMetrics.horizontalAdvance(QLatin1Char(' ')));
}

void MainWindow::setTextStyle()
{
    if(!z_currentNodeData->getStyle("Size").empty()){
        std::istringstream iss(z_currentNodeData->getStyle("Size"));
        iss >> z_currentFontPointSize;
    }
    if(z_currentNodeData->getStyle("Font").empty()){
        z_textEdit->setFont(z_currentSelectedFont);
    }
    else{
        qDebug() << "setFont";
        z_currentSelectedFont = QFont(QString::fromStdString(z_currentNodeData->getStyle("Font")), z_currentFontPointSize, QFont::Normal);
        z_textEdit->setFont(z_currentSelectedFont);
    }
    if(z_currentNodeData->getStyle("Color").empty()){
        z_textEdit->setTextColor(z_currentSelectedColor);
    }
    else{
        std::string color_str = z_currentNodeData->getStyle("Color");
        std::istringstream iss(color_str);
        int r,g,b;
        iss >> r >> g >> b;
        qDebug() << r << g << b;
        z_currentSelectedColor = QColor(r, g, b);
        QTextCursor cursor = z_textEdit->textCursor();
        z_textEdit->selectAll();
        z_textEdit->setTextColor(z_currentSelectedColor);
        z_textEdit->setTextCursor(cursor);
    }
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
    connect(z_colorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);

    // Search
    connect(z_searchButton, &QToolButton::clicked, this, &MainWindow::onSearchButtonClicked);
    connect(z_searchEdit, &QLineEdit::returnPressed, this, &MainWindow::onSearchButtonClicked);
    connect(z_searchEdit, &QLineEdit::textEdited, [this]{z_searchClearButton->show();z_isSearching=false;});
    connect(z_searchClearButton, &QToolButton::clicked, this, &MainWindow::onSearchClearButtonClicked);

    // Replace
    connect(z_replaceButton, &QToolButton::clicked, this, &MainWindow::onReplaceButtonClicked);
    connect(z_replaceEdit, &QLineEdit::returnPressed, this, &MainWindow::onReplaceButtonClicked);
    connect(z_replaceEdit, &QLineEdit::textEdited, [this]{z_replaceClearButton->show();});
    connect(z_replaceClearButton, &QToolButton::clicked, this, &MainWindow::onReplaceClearButtonClicked);

    connect(z_ExpendReplaceButton, &QPushButton::clicked, this, &MainWindow::onExpendReplaceButtonClicked);
}

void MainWindow::setupSearchAndReplace(){
    QPixmap pixmap(QStringLiteral(":images/tree-node-normal.png"));
    z_ExpendReplaceButton->setIcon(QIcon(pixmap));
    setupSearchEdit();
    setupReplaceEdit();
    z_replaceEdit->hide();
    z_searchIterator=SearchIterator();
}

void MainWindow::setupSearchEdit()
{   

    z_searchEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    // clear button
    z_searchClearButton = new QToolButton(z_searchEdit);
    QPixmap pixmap(QStringLiteral(":images/closeButton.png"));
    z_searchClearButton->setIcon(QIcon(pixmap));
    QSize clearSize(15, 15);
    z_searchClearButton->setIconSize(clearSize);
    z_searchClearButton->setCursor(Qt::PointingHandCursor);
    z_searchClearButton->setStyleSheet("QToolButton{border_style: flat; background: transparent;}");
    z_searchClearButton->hide();

    // search button
    z_searchButton = new QToolButton(z_searchEdit);
    QPixmap newPixmap(QStringLiteral(":images/magnifyingGlass.png"));
    z_searchButton->setIcon(QIcon(newPixmap));
    QSize searchSize(18, 18);
    z_searchButton->setIconSize(searchSize);
    z_searchButton->setCursor(Qt::PointingHandCursor);

    z_searchButton->setToolButtonStyle(Qt::ToolButtonFollowStyle);
    z_searchButton->setStyleSheet("QToolButton{border_style: flat; background: transparent;}");
    z_searchEdit->setTextMargins(24, 0, 0, 0);

    //layout
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::RightToLeft, z_searchEdit);
    layout->setContentsMargins(2, 0, 3, 0);

    layout->addWidget(z_searchClearButton);
    layout->addStretch();
    layout->addWidget(z_searchButton);
    z_searchEdit->setLayout(layout);

    z_searchEdit->installEventFilter(this);
}

void MainWindow::setupReplaceEdit(){
    z_replaceEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    // clear button
    z_replaceClearButton = new QToolButton(z_replaceEdit);
    QPixmap pixmap(QStringLiteral(":images/closeButton.png"));
    z_replaceClearButton->setIcon(QIcon(pixmap));
    QSize clearSize(15, 15);
    z_replaceClearButton->setIconSize(clearSize);
    z_replaceClearButton->setCursor(Qt::PointingHandCursor);
    z_replaceClearButton->setStyleSheet("QToolButton{border_style: flat; background: transparent;}");
    z_replaceClearButton->hide();

    // replace button
    z_replaceButton = new QToolButton(z_replaceEdit);
    QPixmap newPixmap(QStringLiteral(":images/Glass.png"));
    z_replaceButton->setIcon(QIcon(newPixmap));
    QSize searchSize(18, 18);
    z_replaceButton->setIconSize(searchSize);
    z_replaceButton->setCursor(Qt::PointingHandCursor);

    z_replaceButton->setToolButtonStyle(Qt::ToolButtonFollowStyle);
    z_replaceButton->setStyleSheet("QToolButton{border_style: flat; background: transparent;}");
    z_replaceEdit->setTextMargins(24, 0, 0, 0);

    //layout
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::RightToLeft, z_replaceEdit);
    layout->setContentsMargins(2, 0, 3, 0);

    layout->addWidget(z_replaceClearButton);
    layout->addStretch();
    layout->addWidget(z_replaceButton);
    z_replaceEdit->setLayout(layout);

    z_replaceEdit->installEventFilter(this);
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
    z_newNoteButton->setIcon(QIcon(QStringLiteral(":/images/newNote_Regular.png")));

    if(!z_vNodeData.empty()){
        saveNodeData();
    }
    NodeData* newNodeData = new NodeData;
    z_vNodeData.push_back(newNodeData);
    z_currentNodeData = newNodeData;
    saveAsNodeData();
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

    QModelIndex index;
    index = z_listView->currentIndex();
    z_listModel->removeRow(index.row());
    bool currentNodeChanged = false;
    vector<NodeData*>::iterator it;
    for(it = z_vNodeData.begin(); it != z_vNodeData.end(); it++){

        if(*it == z_currentNodeData && !currentNodeChanged){
            if(it+1==z_vNodeData.end())
            {
                z_currentNodeData = nullptr;
                it = z_vNodeData.erase(it);
                break;
            }
            z_currentNodeData = *(it+1);
            it = z_vNodeData.erase(it);
            currentNodeChanged = true;
        }
        if(currentNodeChanged){
            (*it)->setListrow((*it)->listrow()-1);
        }
    }
    if(z_currentNodeData)
        setCurrentNodetoText();
    else if(!z_vNodeData.empty()){
        z_currentNodeData = *(z_vNodeData.end()-1);
        setCurrentNodetoText();
    }
    else{
        z_textEdit->clear();
        z_editorDateLabel->setText("ZWORD is brilliant!");
    }
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
    z_textEdit->selectAll();
    resetEditorSettings();
    z_currentNodeData->resetFormat();
}

void MainWindow::onStyleEditorButtonClicked()
{
    saveNodeData();
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
    {
        z_currentFontFamily = font.family();
        z_currentNodeData->setStyle_Key("Font", z_currentFontFamily.toStdString());
        z_currentFontPointSize = font.pointSize();
        if(!z_currentFontPointSize) z_currentFontPointSize = 12;
        z_currentNodeData->setStyle_Key("Size", std::to_string(z_currentFontPointSize));
        resetEditorSettings();
    }
}

void MainWindow::onExpendReplaceButtonClicked(){
    if(z_ReplaceExpand){
        QPixmap pixmap(QStringLiteral(":images/tree-node-normal.png"));
        z_ExpendReplaceButton->setIcon(QIcon(pixmap));
        z_ReplaceExpand = false;
        z_replaceEdit->hide();
        onReplaceClearButtonClicked();
    }else{
        QPixmap pixmap(QStringLiteral(":images/tree-node-expanded.png"));
        z_ExpendReplaceButton->setIcon(QIcon(pixmap));
        z_ReplaceExpand = true;
        z_replaceEdit->show();
    }
}

void MainWindow::onSearchButtonClicked(){
    // saveNodeData();
    z_search = z_searchEdit->text();
    if(z_search.isEmpty()){
        onSearchClearButtonClicked();
        return;
    }

    qDebug()<<"searching for "<<z_search;
    if(!z_isSearching){
        z_isSearching = true;
        z_textEdit->setReadOnly(z_isSearching);
        qDebug()<<"build new Iterator";
        z_searchIterator =  SearchIterator(z_search, z_textEdit->document(), 0);
        z_textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
    }else if(z_searchIterator.IsEnd())z_searchIterator.Init();
    qDebug()<<"searching next";
    if(!++z_searchIterator){
        if(z_searchIterator.IsHit())onSearchButtonClicked();
        return;
    }
    qDebug()<<"searched next";

    QTextEdit::ExtraSelection line;
    line.format.setBackground(QColor(255, 255, 0));
    line.format.setProperty(QTextFormat::FullWidthSelection, true);
    line.cursor = *z_searchIterator;
    z_textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>() << line);
}

void MainWindow::onReplaceButtonClicked(){
    if(!z_ReplaceExpand)onExpendReplaceButtonClicked();
    if(!z_isSearching){
        onSearchButtonClicked();
        return ;
    }
    z_replace=z_replaceEdit->text();
    if(z_replace.isEmpty()){
        onReplaceClearButtonClicked();
        return;
    }
    z_isReplacing=true;
    z_textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
    QTextCursor cursor = *z_searchIterator;
    if(cursor.hasSelection()){
        z_textEdit->setReadOnly(false);
        cursor.beginEditBlock();
        cursor.removeSelectedText();
        cursor.insertText(z_replace);
        cursor.endEditBlock();
        z_textEdit->setReadOnly(true);
        int pos=z_searchIterator.GetPos();
        z_searchIterator=SearchIterator(z_search, z_textEdit->document(), pos);
        onSearchButtonClicked();
    }
}

void MainWindow::onSearchClearButtonClicked(){   
    z_isSearching = false;
    z_textEdit->setReadOnly(z_isSearching);
    z_searchEdit->clear();
    z_searchIterator = SearchIterator();
    z_textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
    z_searchClearButton->hide();
}

void MainWindow::onReplaceClearButtonClicked(){
    z_isReplacing = false;
    z_textEdit->setReadOnly(z_isSearching);
    z_replaceEdit->clear();

    z_replaceClearButton->hide();
}

void MainWindow::pageCut()
{

}

void MainWindow::alignLeft()
{
    QTextCursor lcursor = z_textEdit->textCursor();
    QTextCursor cursor = z_textEdit->textCursor();
    if(lcursor.hasSelection()){
        z_textEdit->setAlignment(Qt::AlignLeft);
    }
    else z_textEdit->selectAll();

    z_textEdit->setAlignment(Qt::AlignLeft);
    z_textEdit->setTextCursor(lcursor);
}

void MainWindow::alignMiddle()
{
    QTextCursor cursor = z_textEdit->textCursor();
    if(cursor.hasSelection()){
        z_textEdit->setAlignment(Qt::AlignCenter);
    }
    else z_textEdit->selectAll();
    z_textEdit->setAlignment(Qt::AlignCenter);
    z_textEdit->setTextCursor(cursor);
}

void MainWindow::alignRight()
{
    QTextCursor cursor = z_textEdit->textCursor();
    if(cursor.hasSelection()){
        z_textEdit->setAlignment(Qt::AlignRight);
    }
    else z_textEdit->selectAll();
    z_textEdit->setAlignment(Qt::AlignRight);
    z_textEdit->setTextCursor(cursor);
}

void MainWindow::saveNodeData()
{   
    QString content;
    if(z_currentNodeData==nullptr)content = z_textEdit->toPlainText();
    if(z_vNodeData.empty()||z_currentNodeData==nullptr){
        NodeData* newNodeData = new NodeData;
        z_vNodeData.push_back(newNodeData);
        z_currentNodeData = *(z_vNodeData.end() - 1);
        if(!saveAsNodeData())return ;
    }
    if(!content.isEmpty())z_textEdit->setText(content);
    QString filename;
    filename = z_currentNodeData->filename();
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    z_editorDateLabel->setText(filename);
    QTextStream out(&file);
    z_currentNodeData->TextEditToPrimate(z_textEdit);
    qDebug() << "save Node data";
    out << z_currentNodeData->primate();
    file.close();
    z_currentNodeData->PrimateToContent();
    setCurrentNodetoText();
}

void MainWindow::savePrimateData()
{

}

void MainWindow::openNodeData()
{
    bool currentNodeChanged = false;
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    if(filename.isEmpty())
        return;
    QFile file(filename);

    for(auto elem : z_vNodeData){
        if(elem->filename() == filename){
            z_currentNodeData = elem;
            currentNodeChanged = true;
            break;
        }
    }


    if(!currentNodeChanged){
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }
        QTextStream in(&file);
        QString text = in.readAll();
        file.close();
        NodeData* newNodeData = new NodeData;
        z_vNodeData.push_back(newNodeData);
        z_currentNodeData = *(z_vNodeData.end() - 1);
        z_currentNodeData->setPrimate(text);
        z_currentNodeData->PrimateToContent();
        z_currentNodeData->setFilename(filename);
        insertCurrentNodetoList();
    }
    else{
        QModelIndex index = z_listModel->index(z_currentNodeData->listrow(), 0);
        z_listView->setCurrentIndex(index);
    }
    setCurrentNodetoText();
    qDebug() << z_vNodeData.size();
}

void MainWindow::insertCurrentNodetoList()
{
    z_currentNodeData->setListrow(z_listModel->rowCount());
    z_listModel->insertRow(z_listModel->rowCount());
    QModelIndex index = z_listModel->index(z_listModel->rowCount()-1, 0);
    z_listModel->setData(index, z_currentNodeData->filename(), Qt::DisplayRole);
    z_listView->setCurrentIndex(index);
}

void MainWindow::setCurrentNodetoText()
{

    z_textEdit->setText(z_currentNodeData->content());
    z_editorDateLabel->setText(z_currentNodeData->filename());

    QTextCharFormat format;
    z_textEdit->setFocus();
    QTextCursor cursor = z_textEdit->textCursor();
    for(auto elem : z_currentNodeData->getBold()){
        qDebug() << elem.first << elem.second.length();
        cursor.clearSelection();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, elem.first);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, elem.second.length());
        format = z_textEdit->currentCharFormat();
        qDebug() << cursor.selectedText();
        format.setFontWeight(QFont::Bold);
        z_textEdit->setTextCursor(cursor);
        z_textEdit->setCurrentCharFormat(format);
    }
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::Start);
    z_textEdit->setTextCursor(cursor);

    for(auto elem : z_currentNodeData->getItalic()){
        qDebug() << elem.first << elem.second.length();
        cursor.clearSelection();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, elem.first);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, elem.second.length());
        format = z_textEdit->currentCharFormat();
        qDebug() << cursor.selectedText();
        format.setFontItalic(true);
        z_textEdit->setTextCursor(cursor);
        z_textEdit->setCurrentCharFormat(format);
    }
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::Start);
    z_textEdit->setTextCursor(cursor);

    vector<Qt::Alignment>& alignment = z_currentNodeData->getAlign();
    for(auto elem : alignment){
        qDebug() << elem;
        z_textEdit->setTextCursor(cursor);
        z_textEdit->setAlignment(elem);
        cursor.movePosition(QTextCursor::NextBlock);
    }
    cursor.clearSelection();
    cursor.movePosition(QTextCursor::Start);
    z_textEdit->setTextCursor(cursor);
    setTextStyle();
}

bool MainWindow::saveAsNodeData()
{
    QString filename;
    filename = QFileDialog::getSaveFileName(this, "Save");
    if (filename.isEmpty())
        return 0;
    z_currentNodeData->setFilename(filename);

    z_editorDateLabel->setText(z_currentNodeData->filename());
    z_textEdit->setText(QString());

    insertCurrentNodetoList();
    return 1;
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    z_listView->currentIndex() = index;
    for(auto elem : z_vNodeData){
        if(elem->listrow() == z_listView->currentIndex().row()){
            z_currentNodeData = elem;
            break;
        }
    }
    setCurrentNodetoText();
}

void MainWindow::onColorButtonClicked(){
    // QColor color = QColorDialog::getColor(Qt::white, this);
    // if(color.isValid()){
    //     z_textEdit->setTextColor(color);
    // }
    saveNodeData();
    QColorDialog dialog;
    dialog.setOption(QColorDialog::ShowAlphaChannel, false);
    int r=0,g=0,b=0;
    if (dialog.exec() == QDialog::Accepted) {
        QColor color = dialog.selectedColor();
        r = color.red();
        g = color.green();
        b = color.blue();
    }
    std::ostringstream oss;
    oss << r << " " << g << " " << b;
    std::string color_str = oss.str();
    z_currentNodeData->setStyle_Key("Color", color_str);
    setCurrentNodetoText();
}
