/********************************************************************************
** Form generated from reading UI file 'EditTestStrainsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTESTSTRAINSDIALOG_H
#define UI_EDITTESTSTRAINSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_editTestStrainsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *bttn_addnew;
    QLabel *label;
    QLabel *label_test;
    QTableWidget *tableWidget;
    QPushButton *bttn_delete;
    QLineEdit *lineEdit_strainID;
    QLineEdit *lineEdit_strainName;
    QLineEdit *lineEdit_strainBrothID;
    QLabel *label_2;

    void setupUi(QDialog *editTestStrainsDialog)
    {
        if (editTestStrainsDialog->objectName().isEmpty())
            editTestStrainsDialog->setObjectName(QString::fromUtf8("editTestStrainsDialog"));
        editTestStrainsDialog->resize(439, 293);
        buttonBox = new QDialogButtonBox(editTestStrainsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(260, 260, 156, 23));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        bttn_addnew = new QPushButton(editTestStrainsDialog);
        bttn_addnew->setObjectName(QString::fromUtf8("bttn_addnew"));
        bttn_addnew->setGeometry(QRect(320, 200, 111, 23));
        label = new QLabel(editTestStrainsDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 91, 16));
        label_test = new QLabel(editTestStrainsDialog);
        label_test->setObjectName(QString::fromUtf8("label_test"));
        label_test->setGeometry(QRect(150, 230, 271, 16));
        label_test->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tableWidget = new QTableWidget(editTestStrainsDialog);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 30, 301, 161));
        bttn_delete = new QPushButton(editTestStrainsDialog);
        bttn_delete->setObjectName(QString::fromUtf8("bttn_delete"));
        bttn_delete->setGeometry(QRect(320, 170, 111, 23));
        lineEdit_strainID = new QLineEdit(editTestStrainsDialog);
        lineEdit_strainID->setObjectName(QString::fromUtf8("lineEdit_strainID"));
        lineEdit_strainID->setGeometry(QRect(10, 200, 101, 20));
        lineEdit_strainName = new QLineEdit(editTestStrainsDialog);
        lineEdit_strainName->setObjectName(QString::fromUtf8("lineEdit_strainName"));
        lineEdit_strainName->setGeometry(QRect(110, 200, 101, 20));
        lineEdit_strainBrothID = new QLineEdit(editTestStrainsDialog);
        lineEdit_strainBrothID->setObjectName(QString::fromUtf8("lineEdit_strainBrothID"));
        lineEdit_strainBrothID->setGeometry(QRect(210, 200, 101, 20));
        label_2 = new QLabel(editTestStrainsDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(320, 100, 111, 61));

        retranslateUi(editTestStrainsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), editTestStrainsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), editTestStrainsDialog, SLOT(reject()));
        QObject::connect(bttn_addnew, SIGNAL(clicked()), editTestStrainsDialog, SLOT(addItem()));
        QObject::connect(bttn_delete, SIGNAL(clicked()), editTestStrainsDialog, SLOT(deleteItem()));

        QMetaObject::connectSlotsByName(editTestStrainsDialog);
    } // setupUi

    void retranslateUi(QDialog *editTestStrainsDialog)
    {
        editTestStrainsDialog->setWindowTitle(QApplication::translate("editTestStrainsDialog", "StreptoDB - TestStrains", nullptr));
        bttn_addnew->setText(QApplication::translate("editTestStrainsDialog", "add new Test-Strain", nullptr));
        label->setText(QApplication::translate("editTestStrainsDialog", "Edit Test-Strains:", nullptr));
        label_test->setText(QApplication::translate("editTestStrainsDialog", "testing...", nullptr));
        bttn_delete->setText(QApplication::translate("editTestStrainsDialog", "delete selected", nullptr));
        label_2->setText(QApplication::translate("editTestStrainsDialog", "if you delete a selected \n"
"Test-Strain, all data for \n"
"that Test-Strain will be \n"
"deleted.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editTestStrainsDialog: public Ui_editTestStrainsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTESTSTRAINSDIALOG_H
