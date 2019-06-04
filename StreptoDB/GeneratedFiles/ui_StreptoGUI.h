/********************************************************************************
** Form generated from reading UI file 'StreptoGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREPTOGUI_H
#define UI_STREPTOGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StreptoGUIClass
{
public:
    QAction *actionNeu;
    QAction *action_ffnen;
    QAction *actionSpeichern;
    QAction *action_Beenden;
    QAction *action_ber_StreptoDB;
    QWidget *centralWidget;
    QPushButton *bttn_uploadPic;
    QLineEdit *line_ID;
    QLabel *label;
    QTableWidget *tableWidget;
    QGraphicsView *graphicsView;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *bttn_loadDB;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *line_timestamp;
    QLabel *label_7;
    QLineEdit *line_imgSize;
    QLabel *label_8;
    QLineEdit *line_resolution;
    QLabel *label_9;
    QLineEdit *line_brothID;
    QLabel *label_10;
    QLineEdit *line_groupID;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuInfo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StreptoGUIClass)
    {
        if (StreptoGUIClass->objectName().isEmpty())
            StreptoGUIClass->setObjectName(QString::fromUtf8("StreptoGUIClass"));
        StreptoGUIClass->resize(1247, 803);
        actionNeu = new QAction(StreptoGUIClass);
        actionNeu->setObjectName(QString::fromUtf8("actionNeu"));
        action_ffnen = new QAction(StreptoGUIClass);
        action_ffnen->setObjectName(QString::fromUtf8("action_ffnen"));
        actionSpeichern = new QAction(StreptoGUIClass);
        actionSpeichern->setObjectName(QString::fromUtf8("actionSpeichern"));
        action_Beenden = new QAction(StreptoGUIClass);
        action_Beenden->setObjectName(QString::fromUtf8("action_Beenden"));
        action_ber_StreptoDB = new QAction(StreptoGUIClass);
        action_ber_StreptoDB->setObjectName(QString::fromUtf8("action_ber_StreptoDB"));
        centralWidget = new QWidget(StreptoGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        bttn_uploadPic = new QPushButton(centralWidget);
        bttn_uploadPic->setObjectName(QString::fromUtf8("bttn_uploadPic"));
        bttn_uploadPic->setGeometry(QRect(680, 350, 75, 23));
        line_ID = new QLineEdit(centralWidget);
        line_ID->setObjectName(QString::fromUtf8("line_ID"));
        line_ID->setGeometry(QRect(1100, 40, 113, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 670, 251, 16));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 40, 661, 621));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(680, 40, 301, 301));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(680, 20, 71, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(760, 350, 341, 21));
        bttn_loadDB = new QPushButton(centralWidget);
        bttn_loadDB->setObjectName(QString::fromUtf8("bttn_loadDB"));
        bttn_loadDB->setGeometry(QRect(10, 10, 75, 23));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 5, 441, 31));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1030, 43, 71, 20));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(1030, 70, 71, 21));
        line_timestamp = new QLineEdit(centralWidget);
        line_timestamp->setObjectName(QString::fromUtf8("line_timestamp"));
        line_timestamp->setGeometry(QRect(1100, 70, 113, 20));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1030, 100, 71, 21));
        line_imgSize = new QLineEdit(centralWidget);
        line_imgSize->setObjectName(QString::fromUtf8("line_imgSize"));
        line_imgSize->setGeometry(QRect(1100, 100, 113, 20));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(1030, 130, 71, 21));
        line_resolution = new QLineEdit(centralWidget);
        line_resolution->setObjectName(QString::fromUtf8("line_resolution"));
        line_resolution->setGeometry(QRect(1100, 130, 113, 20));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(1030, 160, 71, 21));
        line_brothID = new QLineEdit(centralWidget);
        line_brothID->setObjectName(QString::fromUtf8("line_brothID"));
        line_brothID->setGeometry(QRect(1100, 160, 113, 20));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(1030, 190, 71, 21));
        line_groupID = new QLineEdit(centralWidget);
        line_groupID->setObjectName(QString::fromUtf8("line_groupID"));
        line_groupID->setGeometry(QRect(1100, 190, 113, 20));
        StreptoGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StreptoGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1247, 21));
        menuBar->setDefaultUp(true);
        menuBar->setNativeMenuBar(true);
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QString::fromUtf8("menuDatei"));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QString::fromUtf8("menuInfo"));
        StreptoGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(StreptoGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setBaseSize(QSize(1, 1));
        mainToolBar->setIconSize(QSize(48, 48));
        StreptoGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(StreptoGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        StreptoGUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuInfo->menuAction());
        menuDatei->addAction(actionNeu);
        menuDatei->addAction(action_ffnen);
        menuDatei->addAction(actionSpeichern);
        menuDatei->addAction(action_Beenden);
        menuInfo->addAction(action_ber_StreptoDB);

        retranslateUi(StreptoGUIClass);
        QObject::connect(bttn_uploadPic, SIGNAL(clicked()), StreptoGUIClass, SLOT(uploadPic()));
        QObject::connect(bttn_loadDB, SIGNAL(clicked()), StreptoGUIClass, SLOT(loadDB()));
        QObject::connect(tableWidget, SIGNAL(cellClicked(int,int)), StreptoGUIClass, SLOT(itemSelected(int,int)));

        QMetaObject::connectSlotsByName(StreptoGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *StreptoGUIClass)
    {
        StreptoGUIClass->setWindowTitle(QApplication::translate("StreptoGUIClass", "StreptoGUI", nullptr));
        actionNeu->setText(QApplication::translate("StreptoGUIClass", "Neu...", nullptr));
        action_ffnen->setText(QApplication::translate("StreptoGUIClass", "\303\226ffnen...", nullptr));
        actionSpeichern->setText(QApplication::translate("StreptoGUIClass", "Speichern", nullptr));
        action_Beenden->setText(QApplication::translate("StreptoGUIClass", " Beenden", nullptr));
        action_ber_StreptoDB->setText(QApplication::translate("StreptoGUIClass", "\303\274ber StreptoDB...", nullptr));
        bttn_uploadPic->setText(QApplication::translate("StreptoGUIClass", "Upload", nullptr));
        label->setText(QApplication::translate("StreptoGUIClass", "StreptoDB", nullptr));
        label_2->setText(QApplication::translate("StreptoGUIClass", "Bilder Ansicht:", nullptr));
        label_3->setText(QApplication::translate("StreptoGUIClass", "Pfad...", nullptr));
        bttn_loadDB->setText(QApplication::translate("StreptoGUIClass", "DB-Test", nullptr));
        label_4->setText(QApplication::translate("StreptoGUIClass", "DB-Status...", nullptr));
        label_5->setText(QApplication::translate("StreptoGUIClass", "ID:", nullptr));
        label_6->setText(QApplication::translate("StreptoGUIClass", "Timestamp:", nullptr));
        label_7->setText(QApplication::translate("StreptoGUIClass", "Imagesize:", nullptr));
        label_8->setText(QApplication::translate("StreptoGUIClass", "Resolution:", nullptr));
        label_9->setText(QApplication::translate("StreptoGUIClass", "Broth-ID:", nullptr));
        label_10->setText(QApplication::translate("StreptoGUIClass", "Group-ID:", nullptr));
        menuDatei->setTitle(QApplication::translate("StreptoGUIClass", "Datei", nullptr));
        menuInfo->setTitle(QApplication::translate("StreptoGUIClass", "Info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StreptoGUIClass: public Ui_StreptoGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREPTOGUI_H
