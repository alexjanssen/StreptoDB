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
#include <QtWidgets/QComboBox>
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
    QLineEdit *lineEdit_resolution_x;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_test;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_resolution_y;
    QComboBox *comboBox_broth;
    QComboBox *comboBox_group;
    QLabel *label_13;
    QLineEdit *line_path;
    QLineEdit *line_scale;
    QLabel *label_14;

    void setupUi(QDialog *uploadDialog)
    {
        if (uploadDialog->objectName().isEmpty())
            uploadDialog->setObjectName(QString::fromUtf8("uploadDialog"));
        uploadDialog->resize(407, 263);
        buttonBox = new QDialogButtonBox(uploadDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(240, 230, 156, 23));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        graphicsView = new QGraphicsView(uploadDialog);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 30, 191, 171));
        pushButton = new QPushButton(uploadDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 230, 75, 23));
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
        lineEdit_resolution_x = new QLineEdit(uploadDialog);
        lineEdit_resolution_x->setObjectName(QString::fromUtf8("lineEdit_resolution_x"));
        lineEdit_resolution_x->setGeometry(QRect(290, 90, 53, 20));
        label_6 = new QLabel(uploadDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(210, 110, 81, 16));
        label_7 = new QLabel(uploadDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(210, 130, 81, 16));
        label_test = new QLabel(uploadDialog);
        label_test->setObjectName(QString::fromUtf8("label_test"));
        label_test->setGeometry(QRect(210, 200, 191, 16));
        pushButton_2 = new QPushButton(uploadDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(130, 230, 75, 23));
        lineEdit_resolution_y = new QLineEdit(uploadDialog);
        lineEdit_resolution_y->setObjectName(QString::fromUtf8("lineEdit_resolution_y"));
        lineEdit_resolution_y->setGeometry(QRect(350, 90, 53, 20));
        comboBox_broth = new QComboBox(uploadDialog);
        comboBox_broth->setObjectName(QString::fromUtf8("comboBox_broth"));
        comboBox_broth->setGeometry(QRect(290, 110, 113, 22));
        comboBox_group = new QComboBox(uploadDialog);
        comboBox_group->setObjectName(QString::fromUtf8("comboBox_group"));
        comboBox_group->setGeometry(QRect(290, 130, 113, 22));
        QPalette palette;
        QBrush brush(QColor(227, 227, 227, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        comboBox_group->setPalette(palette);
        label_13 = new QLabel(uploadDialog);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(210, 150, 71, 21));
        line_path = new QLineEdit(uploadDialog);
        line_path->setObjectName(QString::fromUtf8("line_path"));
        line_path->setGeometry(QRect(290, 150, 113, 20));
        line_scale = new QLineEdit(uploadDialog);
        line_scale->setObjectName(QString::fromUtf8("line_scale"));
        line_scale->setGeometry(QRect(290, 170, 113, 20));
        QPalette palette1;
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        QBrush brush2(QColor(255, 105, 105, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        QBrush brush3(QColor(240, 240, 240, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        line_scale->setPalette(palette1);
        label_14 = new QLabel(uploadDialog);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(210, 170, 71, 21));

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
        pushButton->setText(QApplication::translate("uploadDialog", "Select...", nullptr));
        label->setText(QApplication::translate("uploadDialog", "New Image:", nullptr));
        label_2->setText(QApplication::translate("uploadDialog", "ImageID:", nullptr));
        label_3->setText(QApplication::translate("uploadDialog", "Timestamp:", nullptr));
        label_4->setText(QApplication::translate("uploadDialog", "Imagesize:", nullptr));
        label_5->setText(QApplication::translate("uploadDialog", "Resolution:", nullptr));
        label_6->setText(QApplication::translate("uploadDialog", "Broth:", nullptr));
        label_7->setText(QApplication::translate("uploadDialog", "Group:", nullptr));
        label_test->setText(QApplication::translate("uploadDialog", "testing...", nullptr));
        pushButton_2->setText(QApplication::translate("uploadDialog", "Save", nullptr));
        label_13->setText(QApplication::translate("uploadDialog", "Path:", nullptr));
        label_14->setText(QApplication::translate("uploadDialog", "Scale:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class uploadDialog: public Ui_uploadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADDIALOG_H
