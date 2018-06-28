/********************************************************************************
** Form generated from reading UI file 'EditorGui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORGUI_H
#define UI_EDITORGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "DrawingArea.h"

QT_BEGIN_NAMESPACE

class Ui_EditorGuiClass
{
public:
    QAction *actionVlose;
    QAction *actionClose;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QScrollArea *scrollArea;
    DrawingArea *drawingArea;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *pointsList;
    QHBoxLayout *horizontalLayout;
    QPushButton *exportPointsButton;
    QPushButton *importPointsButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EditorGuiClass)
    {
        if (EditorGuiClass->objectName().isEmpty())
            EditorGuiClass->setObjectName(QStringLiteral("EditorGuiClass"));
        EditorGuiClass->resize(891, 494);
        actionVlose = new QAction(EditorGuiClass);
        actionVlose->setObjectName(QStringLiteral("actionVlose"));
        actionClose = new QAction(EditorGuiClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralWidget = new QWidget(EditorGuiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(280, 10, 601, 401));
        scrollArea = new QScrollArea(groupBox);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(9, 16, 581, 371));
        scrollArea->setWidgetResizable(true);
        drawingArea = new DrawingArea();
        drawingArea->setObjectName(QStringLiteral("drawingArea"));
        drawingArea->setGeometry(QRect(0, 0, 579, 369));
        scrollArea->setWidget(drawingArea);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 258, 401));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pointsList = new QTableWidget(verticalLayoutWidget);
        pointsList->setObjectName(QStringLiteral("pointsList"));

        verticalLayout->addWidget(pointsList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        exportPointsButton = new QPushButton(verticalLayoutWidget);
        exportPointsButton->setObjectName(QStringLiteral("exportPointsButton"));

        horizontalLayout->addWidget(exportPointsButton);

        importPointsButton = new QPushButton(verticalLayoutWidget);
        importPointsButton->setObjectName(QStringLiteral("importPointsButton"));

        horizontalLayout->addWidget(importPointsButton);


        verticalLayout->addLayout(horizontalLayout);

        EditorGuiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditorGuiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 891, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        EditorGuiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EditorGuiClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EditorGuiClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EditorGuiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EditorGuiClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionVlose);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);

        retranslateUi(EditorGuiClass);

        QMetaObject::connectSlotsByName(EditorGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditorGuiClass)
    {
        EditorGuiClass->setWindowTitle(QApplication::translate("EditorGuiClass", "EditorGui", nullptr));
        actionVlose->setText(QApplication::translate("EditorGuiClass", "Save", nullptr));
        actionClose->setText(QApplication::translate("EditorGuiClass", "Close", nullptr));
        groupBox->setTitle(QApplication::translate("EditorGuiClass", "GroupBox", nullptr));
        exportPointsButton->setText(QApplication::translate("EditorGuiClass", "Export points", nullptr));
        importPointsButton->setText(QApplication::translate("EditorGuiClass", "Import points", nullptr));
        menuFile->setTitle(QApplication::translate("EditorGuiClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditorGuiClass: public Ui_EditorGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITORGUI_H
