/********************************************************************************
** Form generated from reading UI file 'UploadDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADDIALOG_H
#define UI_UPLOADDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_uploadDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGraphicsView *graphicsView;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_image_id;
    QLabel *label_3;
    QLineEdit *lineEdit_timestamp;
    QLabel *label_4;
    QLineEdit *lineEdit_imagesize;
    QLabel *label_5;
    QLineEdit *lineEdit_resolution;
    QLabel *label_6;
    QLineEdit *lineEdit_broth_id;
    QLabel *label_7;
    QLineEdit *lineEdit_group_id;
    QLabel *label_test;
    QPushButton *pushButton_2;

    void setupUi(QDialog *uploadDialog)
    {
        if (uploadDialog->objectName().isEmpty())
            uploadDialog->setObjectName(QString::fromUtf8("uploadDialog"));
        uploadDialog->resize(408, 244);
        buttonBox = new QDialogButtonBox(uploadDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(240, 210, 156, 23));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        graphicsView = new QGraphicsView(uploadDialog);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 30, 191, 171));
        pushButton = new QPushButton(uploadDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 210, 75, 23));
        label = new QLabel(uploadDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 91, 16));
        label_2 = new QLabel(uploadDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 30, 81, 16));
        lineEdit_image_id = new QLineEdit(uploadDialog);
        lineEdit_image_id->setObjectName(QString::fromUtf8("lineEdit_image_id"));
        lineEdit_image_id->setGeometry(QRect(290, 30, 113, 20));
        label_3 = new QLabel(uploadDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 50, 81, 16));
        lineEdit_timestamp = new QLineEdit(uploadDialog);
        lineEdit_timestamp->setObjectName(QString::fromUtf8("lineEdit_timestamp"));
        lineEdit_timestamp->setGeometry(QRect(290, 50, 113, 20));
        label_4 = new QLabel(uploadDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(210, 70, 81, 16));
        lineEdit_imagesize = new QLineEdit(uploadDialog);
        lineEdit_imagesize->setObjectName(QString::fromUtf8("lineEdit_imagesize"));
        lineEdit_imagesize->setGeometry(QRect(290, 70, 113, 20));
        label_5 = new QLabel(uploadDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(210, 90, 81, 16));
        lineEdit_resolution = new QLineEdit(uploadDialog);
        lineEdit_resolution->setObjectName(QString::fromUtf8("lineEdit_resolution"));
        lineEdit_resolution->setGeometry(QRect(290, 90, 113, 20));
        label_6 = new QLabel(uploadDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(210, 110, 81, 16));
        lineEdit_broth_id = new QLineEdit(uploadDialog);
        lineEdit_broth_id->setObjectName(QString::fromUtf8("lineEdit_broth_id"));
        lineEdit_broth_id->setGeometry(QRect(290, 110, 113, 20));
        label_7 = new QLabel(uploadDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(210, 130, 81, 16));
        lineEdit_group_id = new QLineEdit(uploadDialog);
        lineEdit_group_id->setObjectName(QString::fromUtf8("lineEdit_group_id"));
        lineEdit_group_id->setGeometry(QRect(290, 130, 113, 20));
        label_test = new QLabel(uploadDialog);
        label_test->setObjectName(QString::fromUtf8("label_test"));
        label_test->setGeometry(QRect(210, 170, 191, 16));
        pushButton_2 = new QPushButton(uploadDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(130, 210, 75, 23));

        retranslateUi(uploadDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), uploadDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), uploadDialog, SLOT(reject()));
        QObject::connect(pushButton, SIGNAL(clicked()), uploadDialog, SLOT(openFile()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), uploadDialog, SLOT(insertIntoDB()));

        QMetaObject::connectSlotsByName(uploadDialog);
    } // setupUi

    void retranslateUi(QDialog *uploadDialog)
    {
        uploadDialog->setWindowTitle(QApplication::translate("uploadDialog", "StreptoDB - Bilder Upload", nullptr));
        pushButton->setText(QApplication::translate("uploadDialog", "Ausw\303\244hlen...", nullptr));
        label->setText(QApplication::translate("uploadDialog", "neuer Datensatz:", nullptr));
        label_2->setText(QApplication::translate("uploadDialog", "IMAGE_ID", nullptr));
        label_3->setText(QApplication::translate("uploadDialog", "TIMESTAMP:", nullptr));
        label_4->setText(QApplication::translate("uploadDialog", "IMAGESIZE:", nullptr));
        label_5->setText(QApplication::translate("uploadDialog", "RESOLUTION:", nullptr));
        label_6->setText(QApplication::translate("uploadDialog", "BROTH_ID:", nullptr));
        label_7->setText(QApplication::translate("uploadDialog", "GROUP_ID:", nullptr));
        label_test->setText(QApplication::translate("uploadDialog", "testing...", nullptr));
        pushButton_2->setText(QApplication::translate("uploadDialog", "speichern", nullptr));
    } // retranslateUi

};

namespace Ui {
    class uploadDialog: public Ui_uploadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADDIALOG_H
