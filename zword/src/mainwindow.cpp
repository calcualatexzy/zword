
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
#include "theme.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , z_trashButton(nullptr)
    , z_dotsButton(nullptr)
    , z_newNoteButton(nullptr)
    , z_styleEditorButton(nullptr)
    , z_searchEdit(nullptr)
    , z_searchButton(nullptr)
    , z_lastSearchIndex(-1)
    , z_isSearching(false)
    , z_isReplacing(false)
    , z_clearButton(nullptr)
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
    setupSearchEdit();
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

    ui->searchEdit->setStyleSheet(z_styleSheet);

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

void MainWindow::setupNodeData()
{

}


void MainWindow::setupKeyboardShortcuts()
{
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_N), this, SLOT(onNewNoteButtonClicked()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_D), this, SLOT(onTrashButtonClicked()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_F), this, SLOT(onSearchButtonClicked()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this, SLOT(saveNodeData()));
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_O), this, SLOT(openNodeData()));
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
    setCSSThemeAndUpdate(ui->verticalSpacer_upSearchEdit, theme);
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
    z_currentFontPointSize = 13;
    z_currentSelectedFont = QFont(z_currentFontFamily, z_currentFontPointSize, QFont::Normal);
    z_textEdit->setFont(z_currentSelectedFont);
    z_textEdit->setWordWrapMode(QTextOption::WordWrap);
    z_textEdit->setLineWrapMode(QTextEdit::FixedColumnWidth);

    setTheme(z_currentTheme);

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

    // Search
    connect(z_searchButton, &QToolButton::clicked, this, &MainWindow::onSearchButtonClicked);
    connect(z_searchEdit, &QLineEdit::returnPressed, this, &MainWindow::onSearchButtonClicked);
    connect(z_searchEdit, &QLineEdit::textEdited, [this]{z_clearButton->show();});
    connect(z_clearButton, &QToolButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(this, &MainWindow::signalReplace, this, &MainWindow::replaceSearchEdit);
}

void MainWindow::setupSearchEdit()
{
    z_searchEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);
    // clear button
    z_clearButton = new QToolButton(z_searchEdit);
    QPixmap pixmap(QStringLiteral(":images/closeButton.png"));
    z_clearButton->setIcon(QIcon(pixmap));
    QSize clearSize(15, 15);
    z_clearButton->setIconSize(clearSize);
    z_clearButton->setCursor(Qt::PointingHandCursor);
    z_clearButton->setStyleSheet("QToolButton{border_style: flat; background: transparent;}");
    z_clearButton->hide();

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

    layout->addWidget(z_clearButton);
    layout->addStretch();
    layout->addWidget(z_searchButton);
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
        case QEvent::KeyPress:{
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->modifiers() == (Qt::ControlModifier) && keyEvent->key() == Qt::Key_H && z_isReplacing){
                emit signalReplace();
            }
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

void MainWindow::onSearchButtonClicked()
{
    z_isSearching = true;
    z_textEdit->setReadOnly(z_isSearching);
    saveNodeData();
    z_search = z_searchEdit->text();
    if(z_search.isEmpty()) return;
    int findreplace = z_search.toStdString().find("->");
    if(findreplace != -1){
        std::string strreplace = z_search.toStdString().substr(findreplace + 2);
        z_replace = QString::fromStdString(strreplace);
        z_isReplacing = true;
        z_search.resize(findreplace);
    }
    else{
        z_isReplacing = false;
        z_replace.clear();
    }

    QTextDocument* doc = z_textEdit->document();
    QTextCursor ret = doc->find(z_search, z_lastSearchIndex+1, QTextDocument::FindCaseSensitively);
    if(!ret.isNull()){
        z_lastSearchIndex = ret.position() - 1;
        QList<QTextEdit::ExtraSelection> extra_selections;

        QTextEdit::ExtraSelection line;
        line.format.setBackground(QColor(255, 255, 0));
        line.format.setProperty(QTextFormat::FullWidthSelection, true);
        line.cursor = ret;
        extra_selections.append(line);
        z_textEdit->setExtraSelections(extra_selections);
    }
    else{
        z_lastSearchIndex = -1;
        z_isReplacing = false;
        z_isSearching = false;
    }
    qDebug() << z_lastSearchIndex;
    qDebug() << "search:" << z_search;
    qDebug() << "replace:" << z_replace;
}

void MainWindow::onClearButtonClicked()
{
    z_isSearching = false;
    z_isReplacing = false;
    z_textEdit->setReadOnly(z_isSearching);
    z_searchEdit->clear();
    z_lastSearchIndex = -1;
    QList<QTextEdit::ExtraSelection> extra_selections;
    z_textEdit->setExtraSelections(extra_selections);
    z_clearButton->hide();
}

void MainWindow::replaceSearchEdit()
{
    std::pair<int, int> coor = z_currentNodeData->IndexToCoor(z_lastSearchIndex + 1 - z_search.length());
    std::string line = z_currentNodeData->rowContent(coor.first).toStdString();
    std::string subbehind = line.substr(coor.second + z_search.length());
    std::string subforward = line.substr(0, coor.second);
    z_currentNodeData->setRowContent(coor.first, QString::fromStdString(subforward+z_replace.toStdString()+subbehind));
    z_textEdit->setReadOnly(false);
    setCurrentNodetoText();
    QList<QTextEdit::ExtraSelection> extra_selections;
    z_textEdit->setExtraSelections(extra_selections);
    z_textEdit->setReadOnly(true);
    z_isReplacing = false;
    z_replace.clear();
}

void MainWindow::saveNodeData()
{
    if(z_vNodeData.empty()){
        NodeData* newNodeData = new NodeData;
        z_vNodeData.push_back(newNodeData);
        z_currentNodeData = *(z_vNodeData.end() - 1);
        saveAsNodeData();
    }
    QString filename = z_currentNodeData->filename();
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    z_editorDateLabel->setText(filename);
    savePrimateData();
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

    vector<pair<int, QString>> boldFormat = z_currentNodeData->getBold();
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
}

void MainWindow::saveAsNodeData()
{
    QString filename;
    filename = QFileDialog::getSaveFileName(this, "Save");
    if (filename.isEmpty())
            return;
    z_currentNodeData->setFilename(filename);

    z_editorDateLabel->setText(z_currentNodeData->filename());
    z_textEdit->setText(QString());

    insertCurrentNodetoList();
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

