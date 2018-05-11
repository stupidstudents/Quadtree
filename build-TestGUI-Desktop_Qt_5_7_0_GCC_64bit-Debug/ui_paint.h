/********************************************************************************
** Form generated from reading UI file 'paint.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINT_H
#define UI_PAINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_paint
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *paint)
    {
        if (paint->objectName().isEmpty())
            paint->setObjectName(QStringLiteral("paint"));
        paint->resize(400, 300);
        centralWidget = new QWidget(paint);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 0, 361, 251));
        paint->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(paint);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 19));
        paint->setMenuBar(menuBar);
        mainToolBar = new QToolBar(paint);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        paint->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(paint);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        paint->setStatusBar(statusBar);

        retranslateUi(paint);

        QMetaObject::connectSlotsByName(paint);
    } // setupUi

    void retranslateUi(QMainWindow *paint)
    {
        paint->setWindowTitle(QApplication::translate("paint", "paint", 0));
    } // retranslateUi

};

namespace Ui {
    class paint: public Ui_paint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINT_H
