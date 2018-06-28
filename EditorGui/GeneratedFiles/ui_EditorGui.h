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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
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
    QWidget *gridLayoutWidget;
    QGridLayout *mainGrid;
    QVBoxLayout *verticalLayout;
    QTableWidget *pointsList;
    QPlainTextEdit *newPointText;
    QPushButton *addPointButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *exportPointsButton;
    QPushButton *importPointsButton;
    QScrollArea *scrollArea;
    DrawingArea *drawingArea;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EditorGuiClass)
    {
        if (EditorGuiClass->objectName().isEmpty())
            EditorGuiClass->setObjectName(QStringLiteral("EditorGuiClass"));
        EditorGuiClass->resize(873, 621);
        actionVlose = new QAction(EditorGuiClass);
        actionVlose->setObjectName(QStringLiteral("actionVlose"));
        actionClose = new QAction(EditorGuiClass);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralWidget = new QWidget(EditorGuiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(4, 12, 791, 491));
        mainGrid = new QGridLayout(gridLayoutWidget);
        mainGrid->setSpacing(6);
        mainGrid->setContentsMargins(11, 11, 11, 11);
        mainGrid->setObjectName(QStringLiteral("mainGrid"));
        mainGrid->setSizeConstraint(QLayout::SetMaximumSize);
        mainGrid->setContentsMargins(3, 3, 3, 3);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        pointsList = new QTableWidget(gridLayoutWidget);
        pointsList->setObjectName(QStringLiteral("pointsList"));
        sizePolicy.setHeightForWidth(pointsList->sizePolicy().hasHeightForWidth());
        pointsList->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pointsList);

        newPointText = new QPlainTextEdit(gridLayoutWidget);
        newPointText->setObjectName(QStringLiteral("newPointText"));
        newPointText->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(newPointText);

        addPointButton = new QPushButton(gridLayoutWidget);
        addPointButton->setObjectName(QStringLiteral("addPointButton"));

        verticalLayout->addWidget(addPointButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        exportPointsButton = new QPushButton(gridLayoutWidget);
        exportPointsButton->setObjectName(QStringLiteral("exportPointsButton"));

        horizontalLayout->addWidget(exportPointsButton);

        importPointsButton = new QPushButton(gridLayoutWidget);
        importPointsButton->setObjectName(QStringLiteral("importPointsButton"));

        horizontalLayout->addWidget(importPointsButton);


        verticalLayout->addLayout(horizontalLayout);


        mainGrid->addLayout(verticalLayout, 0, 0, 1, 1);

        scrollArea = new QScrollArea(gridLayoutWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setWidgetResizable(true);
        drawingArea = new DrawingArea();
        drawingArea->setObjectName(QStringLiteral("drawingArea"));
        drawingArea->setGeometry(QRect(0, 0, 518, 483));
        sizePolicy.setHeightForWidth(drawingArea->sizePolicy().hasHeightForWidth());
        drawingArea->setSizePolicy(sizePolicy);
        scrollArea->setWidget(drawingArea);

        mainGrid->addWidget(scrollArea, 0, 1, 1, 1);

        mainGrid->setColumnStretch(1, 1);
        EditorGuiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditorGuiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 873, 26));
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
        addPointButton->setText(QApplication::translate("EditorGuiClass", "Add point (int int double)", nullptr));
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
