/********************************************************************************
** Form generated from reading UI file 'SettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_settingsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *bttn_select;
    QLabel *label_1;
    QLabel *label_2;
    QLineEdit *lineEdit_path;
    QLabel *label_3;
    QPushButton *bttn_save;
    QLabel *label;

    void setupUi(QDialog *settingsDialog)
    {
        if (settingsDialog->objectName().isEmpty())
            settingsDialog->setObjectName(QString::fromUtf8("settingsDialog"));
        settingsDialog->resize(408, 244);
        buttonBox = new QDialogButtonBox(settingsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(240, 210, 156, 23));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        bttn_select = new QPushButton(settingsDialog);
        bttn_select->setObjectName(QString::fromUtf8("bttn_select"));
        bttn_select->setGeometry(QRect(320, 60, 75, 23));
        label_1 = new QLabel(settingsDialog);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setGeometry(QRect(10, 10, 91, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_1->setFont(font);
        label_2 = new QLabel(settingsDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 131, 16));
        lineEdit_path = new QLineEdit(settingsDialog);
        lineEdit_path->setObjectName(QString::fromUtf8("lineEdit_path"));
        lineEdit_path->setEnabled(false);
        lineEdit_path->setGeometry(QRect(140, 40, 261, 20));
        label_3 = new QLabel(settingsDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(200, 60, 121, 21));
        bttn_save = new QPushButton(settingsDialog);
        bttn_save->setObjectName(QString::fromUtf8("bttn_save"));
        bttn_save->setGeometry(QRect(130, 210, 75, 23));
        label = new QLabel(settingsDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 180, 261, 21));

        retranslateUi(settingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), settingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), settingsDialog, SLOT(reject()));
        QObject::connect(bttn_select, SIGNAL(clicked()), settingsDialog, SLOT(selectPath()));
        QObject::connect(bttn_save, SIGNAL(clicked()), settingsDialog, SLOT(saveSettings()));

        QMetaObject::connectSlotsByName(settingsDialog);
    } // setupUi

    void retranslateUi(QDialog *settingsDialog)
    {
        settingsDialog->setWindowTitle(QApplication::translate("settingsDialog", "StreptoDB - Settings", nullptr));
        bttn_select->setText(QApplication::translate("settingsDialog", "Select...", nullptr));
        label_1->setText(QApplication::translate("settingsDialog", "Much Settings:", nullptr));
        label_2->setText(QApplication::translate("settingsDialog", "Standard Path to Images:", nullptr));
        label_3->setText(QApplication::translate("settingsDialog", "Just select one Image:", nullptr));
        bttn_save->setText(QApplication::translate("settingsDialog", "Save", nullptr));
        label->setText(QApplication::translate("settingsDialog", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settingsDialog: public Ui_settingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
