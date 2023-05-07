/********************************************************************************
** Form generated from reading UI file 'zword.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZWORD_H
#define UI_ZWORD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_zword
{
public:
    QAction *actionNew_File;
    QAction *actionOpen_File;
    QAction *actionSave_File;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionSelect_All;
    QAction *actionFind;
    QAction *actionSave_As;
    QAction *actionPrint;
    QAction *actionExit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QFontComboBox *fontComboBox;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *zword)
    {
        if (zword->objectName().isEmpty())
            zword->setObjectName("zword");
        zword->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(zword->sizePolicy().hasHeightForWidth());
        zword->setSizePolicy(sizePolicy);
        actionNew_File = new QAction(zword);
        actionNew_File->setObjectName("actionNew_File");
        actionOpen_File = new QAction(zword);
        actionOpen_File->setObjectName("actionOpen_File");
        actionSave_File = new QAction(zword);
        actionSave_File->setObjectName("actionSave_File");
        actionCopy = new QAction(zword);
        actionCopy->setObjectName("actionCopy");
        actionCut = new QAction(zword);
        actionCut->setObjectName("actionCut");
        actionPaste = new QAction(zword);
        actionPaste->setObjectName("actionPaste");
        actionUndo = new QAction(zword);
        actionUndo->setObjectName("actionUndo");
        actionRedo = new QAction(zword);
        actionRedo->setObjectName("actionRedo");
        actionSelect_All = new QAction(zword);
        actionSelect_All->setObjectName("actionSelect_All");
        actionFind = new QAction(zword);
        actionFind->setObjectName("actionFind");
        actionSave_As = new QAction(zword);
        actionSave_As->setObjectName("actionSave_As");
        actionPrint = new QAction(zword);
        actionPrint->setObjectName("actionPrint");
        actionExit = new QAction(zword);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(zword);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));

        gridLayout->addWidget(textEdit, 1, 0, 1, 1);

        fontComboBox = new QFontComboBox(centralwidget);
        fontComboBox->setObjectName("fontComboBox");

        gridLayout->addWidget(fontComboBox, 0, 0, 1, 1);

        zword->setCentralWidget(centralwidget);
        menubar = new QMenuBar(zword);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 17));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        zword->setMenuBar(menubar);
        statusbar = new QStatusBar(zword);
        statusbar->setObjectName("statusbar");
        zword->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionNew_File);
        menuFile->addAction(actionOpen_File);
        menuFile->addAction(actionSave_File);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelect_All);
        menuEdit->addAction(actionFind);

        retranslateUi(zword);

        QMetaObject::connectSlotsByName(zword);
    } // setupUi

    void retranslateUi(QMainWindow *zword)
    {
        zword->setWindowTitle(QCoreApplication::translate("zword", "zword", nullptr));
        actionNew_File->setText(QCoreApplication::translate("zword", "New File...", nullptr));
        actionNew_File->setIconText(QCoreApplication::translate("zword", "New...", nullptr));
#if QT_CONFIG(shortcut)
        actionNew_File->setShortcut(QCoreApplication::translate("zword", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen_File->setText(QCoreApplication::translate("zword", "Open File...", nullptr));
        actionOpen_File->setIconText(QCoreApplication::translate("zword", "Open...", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen_File->setShortcut(QCoreApplication::translate("zword", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_File->setText(QCoreApplication::translate("zword", "Save File...", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_File->setShortcut(QCoreApplication::translate("zword", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("zword", "Copy", nullptr));
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("zword", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCut->setText(QCoreApplication::translate("zword", "Cut", nullptr));
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("zword", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("zword", "Paste", nullptr));
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("zword", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUndo->setText(QCoreApplication::translate("zword", "Undo", nullptr));
#if QT_CONFIG(shortcut)
        actionUndo->setShortcut(QCoreApplication::translate("zword", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRedo->setText(QCoreApplication::translate("zword", "Redo", nullptr));
#if QT_CONFIG(shortcut)
        actionRedo->setShortcut(QCoreApplication::translate("zword", "Ctrl+Y", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSelect_All->setText(QCoreApplication::translate("zword", "Select All", nullptr));
#if QT_CONFIG(shortcut)
        actionSelect_All->setShortcut(QCoreApplication::translate("zword", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFind->setText(QCoreApplication::translate("zword", "Find", nullptr));
#if QT_CONFIG(shortcut)
        actionFind->setShortcut(QCoreApplication::translate("zword", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_As->setText(QCoreApplication::translate("zword", "Save As...", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_As->setShortcut(QCoreApplication::translate("zword", "Alt+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPrint->setText(QCoreApplication::translate("zword", "Print", nullptr));
#if QT_CONFIG(shortcut)
        actionPrint->setShortcut(QCoreApplication::translate("zword", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("zword", "Exit", nullptr));
        menuFile->setTitle(QCoreApplication::translate("zword", "File(F)", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("zword", "Edit(E)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class zword: public Ui_zword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZWORD_H
