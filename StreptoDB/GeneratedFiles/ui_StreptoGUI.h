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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StreptoGUIClass
{
public:
    QAction *actionAnalys;
    QAction *action_settings;
    QAction *actionSave;
    QAction *action_Close;
    QAction *action_bout_StreptoDB;
    QAction *actionDubious_Option;
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
    QLineEdit *line_resolution_x;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *line_path;
    QLabel *label_13;
    QTableWidget *tableWidget_4;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QPushButton *bttn_compare;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLineEdit *line_groupID_group;
    QLineEdit *line_internID;
    QLabel *label_21;
    QLineEdit *line_timestamp_group;
    QLabel *label_22;
    QLineEdit *line_scientific;
    QLabel *label_23;
    QLineEdit *line_genome;
    QLabel *label_24;
    QLineEdit *line_locality;
    QLabel *label_25;
    QLabel *label_26;
    QLineEdit *line_spore_color;
    QLabel *label_27;
    QCheckBox *checkBox_siderophore;
    QFrame *line;
    QLineEdit *line_filter;
    QPushButton *bttn_IMG_save;
    QTabWidget *tabWidget;
    QWidget *tab_Calculations;
    QTableWidget *tableWidget_2;
    QWidget *tab_2;
    QTableWidget *tableWidget_3;
    QLineEdit *line_inhibit_internID;
    QLineEdit *line_inhibit_broth;
    QComboBox *comboBox_testStrain;
    QCheckBox *checkBox_inhibition;
    QPushButton *bttn_add_inhibit;
    QLabel *label_28;
    QPushButton *bttn_GRP_delete;
    QPushButton *bttn_GRP_save;
    QPushButton *bttn_IMG_delete;
    QPushButton *bttn_subtable_delete;
    QLineEdit *line_resolution_y;
    QPushButton *bttn_newGroup;
    QLineEdit *line_locality_2;
    QLineEdit *line_scale;
    QLabel *label_47;
    QPushButton *bttn_editBroth;
    QPushButton *bttn_editTeststrains;
    QPushButton *bttn_loadsql;
    QPushButton *bttn_segmentation;
    QLabel *label_29;
    QLabel *label_30;
    QSpinBox *spinBox_BG;
    QSpinBox *spinBox_TH;
    QPushButton *bttn_calc;
    QLabel *label_31;
    QSpinBox *spinBox_FG;
    QLabel *label_32;
    QLabel *label_33;
    QComboBox *comboBox_broth;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_38;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_41;
    QLabel *label_42;
    QLabel *label_43;
    QLabel *label_44;
    QLabel *label_45;
    QLabel *label_46;
    QLabel *label_48;
    QLabel *label_49;
    QLabel *label_50;
    QLabel *label_51;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuInfo;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StreptoGUIClass)
    {
        if (StreptoGUIClass->objectName().isEmpty())
            StreptoGUIClass->setObjectName(QString::fromUtf8("StreptoGUIClass"));
        StreptoGUIClass->resize(1513, 974);
        actionAnalys = new QAction(StreptoGUIClass);
        actionAnalys->setObjectName(QString::fromUtf8("actionAnalys"));
        action_settings = new QAction(StreptoGUIClass);
        action_settings->setObjectName(QString::fromUtf8("action_settings"));
        actionSave = new QAction(StreptoGUIClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        action_Close = new QAction(StreptoGUIClass);
        action_Close->setObjectName(QString::fromUtf8("action_Close"));
        action_bout_StreptoDB = new QAction(StreptoGUIClass);
        action_bout_StreptoDB->setObjectName(QString::fromUtf8("action_bout_StreptoDB"));
        actionDubious_Option = new QAction(StreptoGUIClass);
        actionDubious_Option->setObjectName(QString::fromUtf8("actionDubious_Option"));
        centralWidget = new QWidget(StreptoGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        bttn_uploadPic = new QPushButton(centralWidget);
        bttn_uploadPic->setObjectName(QString::fromUtf8("bttn_uploadPic"));
        bttn_uploadPic->setGeometry(QRect(790, 360, 75, 23));
        line_ID = new QLineEdit(centralWidget);
        line_ID->setObjectName(QString::fromUtf8("line_ID"));
        line_ID->setGeometry(QRect(1270, 240, 151, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 690, 251, 16));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 40, 771, 651));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(790, 40, 385, 311));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(780, 20, 71, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(870, 360, 231, 21));
        bttn_loadDB = new QPushButton(centralWidget);
        bttn_loadDB->setObjectName(QString::fromUtf8("bttn_loadDB"));
        bttn_loadDB->setGeometry(QRect(60, 10, 75, 23));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(280, 10, 311, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1190, 243, 71, 20));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(1190, 260, 71, 21));
        line_timestamp = new QLineEdit(centralWidget);
        line_timestamp->setObjectName(QString::fromUtf8("line_timestamp"));
        line_timestamp->setGeometry(QRect(1270, 260, 151, 20));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1190, 280, 71, 21));
        line_imgSize = new QLineEdit(centralWidget);
        line_imgSize->setObjectName(QString::fromUtf8("line_imgSize"));
        line_imgSize->setGeometry(QRect(1270, 280, 151, 20));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(1190, 300, 81, 21));
        line_resolution_x = new QLineEdit(centralWidget);
        line_resolution_x->setObjectName(QString::fromUtf8("line_resolution_x"));
        line_resolution_x->setGeometry(QRect(1270, 300, 71, 20));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(1190, 320, 71, 21));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(790, 400, 111, 21));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(900, 400, 261, 21));
        line_path = new QLineEdit(centralWidget);
        line_path->setObjectName(QString::fromUtf8("line_path"));
        line_path->setGeometry(QRect(1270, 340, 151, 20));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(1190, 340, 71, 21));
        tableWidget_4 = new QTableWidget(centralWidget);
        tableWidget_4->setObjectName(QString::fromUtf8("tableWidget_4"));
        tableWidget_4->setGeometry(QRect(10, 770, 1491, 151));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 710, 91, 16));
        label_14->setLayoutDirection(Qt::LeftToRight);
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 730, 171, 16));
        label_15->setLayoutDirection(Qt::LeftToRight);
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 720, 221, 16));
        label_16->setLayoutDirection(Qt::LeftToRight);
        bttn_compare = new QPushButton(centralWidget);
        bttn_compare->setObjectName(QString::fromUtf8("bttn_compare"));
        bttn_compare->setGeometry(QRect(140, 10, 131, 23));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 750, 241, 16));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(1190, 20, 71, 16));
        label_18->setFont(font);
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(1190, 220, 71, 16));
        label_19->setFont(font);
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(1190, 40, 71, 20));
        line_groupID_group = new QLineEdit(centralWidget);
        line_groupID_group->setObjectName(QString::fromUtf8("line_groupID_group"));
        line_groupID_group->setGeometry(QRect(1270, 40, 151, 20));
        line_internID = new QLineEdit(centralWidget);
        line_internID->setObjectName(QString::fromUtf8("line_internID"));
        line_internID->setGeometry(QRect(1270, 60, 151, 20));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(1190, 60, 71, 20));
        line_timestamp_group = new QLineEdit(centralWidget);
        line_timestamp_group->setObjectName(QString::fromUtf8("line_timestamp_group"));
        line_timestamp_group->setGeometry(QRect(1270, 80, 151, 20));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(1190, 80, 71, 20));
        line_scientific = new QLineEdit(centralWidget);
        line_scientific->setObjectName(QString::fromUtf8("line_scientific"));
        line_scientific->setGeometry(QRect(1270, 100, 151, 20));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(1190, 100, 81, 20));
        line_genome = new QLineEdit(centralWidget);
        line_genome->setObjectName(QString::fromUtf8("line_genome"));
        line_genome->setGeometry(QRect(1270, 120, 151, 20));
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(1190, 120, 71, 20));
        line_locality = new QLineEdit(centralWidget);
        line_locality->setObjectName(QString::fromUtf8("line_locality"));
        line_locality->setGeometry(QRect(1270, 140, 71, 20));
        label_25 = new QLabel(centralWidget);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(1190, 140, 81, 20));
        label_26 = new QLabel(centralWidget);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(1190, 180, 71, 20));
        line_spore_color = new QLineEdit(centralWidget);
        line_spore_color->setObjectName(QString::fromUtf8("line_spore_color"));
        line_spore_color->setGeometry(QRect(1270, 160, 151, 20));
        label_27 = new QLabel(centralWidget);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(1190, 160, 71, 20));
        checkBox_siderophore = new QCheckBox(centralWidget);
        checkBox_siderophore->setObjectName(QString::fromUtf8("checkBox_siderophore"));
        checkBox_siderophore->setGeometry(QRect(1270, 180, 51, 21));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(1190, 200, 231, 21));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        line->setFont(font1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_filter = new QLineEdit(centralWidget);
        line_filter->setObjectName(QString::fromUtf8("line_filter"));
        line_filter->setGeometry(QRect(10, 11, 41, 20));
        bttn_IMG_save = new QPushButton(centralWidget);
        bttn_IMG_save->setObjectName(QString::fromUtf8("bttn_IMG_save"));
        bttn_IMG_save->setGeometry(QRect(1340, 380, 41, 23));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(790, 430, 511, 241));
        tab_Calculations = new QWidget();
        tab_Calculations->setObjectName(QString::fromUtf8("tab_Calculations"));
        tableWidget_2 = new QTableWidget(tab_Calculations);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(0, 0, 511, 221));
        tabWidget->addTab(tab_Calculations, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tableWidget_3 = new QTableWidget(tab_2);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));
        tableWidget_3->setGeometry(QRect(0, 0, 511, 221));
        tabWidget->addTab(tab_2, QString());
        line_inhibit_internID = new QLineEdit(centralWidget);
        line_inhibit_internID->setObjectName(QString::fromUtf8("line_inhibit_internID"));
        line_inhibit_internID->setEnabled(false);
        line_inhibit_internID->setGeometry(QRect(790, 670, 113, 21));
        line_inhibit_internID->setAcceptDrops(false);
        line_inhibit_internID->setReadOnly(true);
        line_inhibit_broth = new QLineEdit(centralWidget);
        line_inhibit_broth->setObjectName(QString::fromUtf8("line_inhibit_broth"));
        line_inhibit_broth->setEnabled(false);
        line_inhibit_broth->setGeometry(QRect(910, 670, 113, 21));
        line_inhibit_broth->setReadOnly(true);
        comboBox_testStrain = new QComboBox(centralWidget);
        comboBox_testStrain->setObjectName(QString::fromUtf8("comboBox_testStrain"));
        comboBox_testStrain->setGeometry(QRect(1030, 670, 121, 22));
        checkBox_inhibition = new QCheckBox(centralWidget);
        checkBox_inhibition->setObjectName(QString::fromUtf8("checkBox_inhibition"));
        checkBox_inhibition->setGeometry(QRect(1160, 670, 71, 21));
        bttn_add_inhibit = new QPushButton(centralWidget);
        bttn_add_inhibit->setObjectName(QString::fromUtf8("bttn_add_inhibit"));
        bttn_add_inhibit->setGeometry(QRect(1230, 670, 71, 23));
        label_28 = new QLabel(centralWidget);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(1090, 690, 211, 31));
        bttn_GRP_delete = new QPushButton(centralWidget);
        bttn_GRP_delete->setObjectName(QString::fromUtf8("bttn_GRP_delete"));
        bttn_GRP_delete->setGeometry(QRect(1380, 180, 41, 23));
        bttn_GRP_save = new QPushButton(centralWidget);
        bttn_GRP_save->setObjectName(QString::fromUtf8("bttn_GRP_save"));
        bttn_GRP_save->setGeometry(QRect(1340, 180, 41, 23));
        bttn_IMG_delete = new QPushButton(centralWidget);
        bttn_IMG_delete->setObjectName(QString::fromUtf8("bttn_IMG_delete"));
        bttn_IMG_delete->setGeometry(QRect(1380, 380, 41, 23));
        bttn_subtable_delete = new QPushButton(centralWidget);
        bttn_subtable_delete->setObjectName(QString::fromUtf8("bttn_subtable_delete"));
        bttn_subtable_delete->setGeometry(QRect(1220, 430, 71, 23));
        line_resolution_y = new QLineEdit(centralWidget);
        line_resolution_y->setObjectName(QString::fromUtf8("line_resolution_y"));
        line_resolution_y->setGeometry(QRect(1350, 300, 71, 20));
        bttn_newGroup = new QPushButton(centralWidget);
        bttn_newGroup->setObjectName(QString::fromUtf8("bttn_newGroup"));
        bttn_newGroup->setGeometry(QRect(600, 10, 75, 23));
        line_locality_2 = new QLineEdit(centralWidget);
        line_locality_2->setObjectName(QString::fromUtf8("line_locality_2"));
        line_locality_2->setGeometry(QRect(1350, 140, 71, 20));
        line_scale = new QLineEdit(centralWidget);
        line_scale->setObjectName(QString::fromUtf8("line_scale"));
        line_scale->setGeometry(QRect(1270, 360, 151, 20));
        label_47 = new QLabel(centralWidget);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setGeometry(QRect(1190, 360, 71, 21));
        bttn_editBroth = new QPushButton(centralWidget);
        bttn_editBroth->setObjectName(QString::fromUtf8("bttn_editBroth"));
        bttn_editBroth->setGeometry(QRect(1100, 10, 75, 23));
        bttn_editTeststrains = new QPushButton(centralWidget);
        bttn_editTeststrains->setObjectName(QString::fromUtf8("bttn_editTeststrains"));
        bttn_editTeststrains->setGeometry(QRect(680, 10, 91, 23));
        bttn_loadsql = new QPushButton(centralWidget);
        bttn_loadsql->setObjectName(QString::fromUtf8("bttn_loadsql"));
        bttn_loadsql->setGeometry(QRect(1360, 720, 131, 23));
        bttn_segmentation = new QPushButton(centralWidget);
        bttn_segmentation->setObjectName(QString::fromUtf8("bttn_segmentation"));
        bttn_segmentation->setGeometry(QRect(540, 700, 111, 23));
        label_29 = new QLabel(centralWidget);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(260, 700, 81, 16));
        label_29->setLayoutDirection(Qt::LeftToRight);
        label_30 = new QLabel(centralWidget);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(260, 720, 81, 16));
        label_30->setLayoutDirection(Qt::LeftToRight);
        spinBox_BG = new QSpinBox(centralWidget);
        spinBox_BG->setObjectName(QString::fromUtf8("spinBox_BG"));
        spinBox_BG->setGeometry(QRect(340, 700, 42, 22));
        spinBox_BG->setMinimum(-999);
        spinBox_BG->setMaximum(999);
        spinBox_TH = new QSpinBox(centralWidget);
        spinBox_TH->setObjectName(QString::fromUtf8("spinBox_TH"));
        spinBox_TH->setGeometry(QRect(340, 720, 42, 22));
        spinBox_TH->setMinimum(-999);
        spinBox_TH->setMaximum(999);
        bttn_calc = new QPushButton(centralWidget);
        bttn_calc->setObjectName(QString::fromUtf8("bttn_calc"));
        bttn_calc->setGeometry(QRect(540, 730, 111, 23));
        label_31 = new QLabel(centralWidget);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(260, 740, 81, 16));
        label_31->setLayoutDirection(Qt::LeftToRight);
        spinBox_FG = new QSpinBox(centralWidget);
        spinBox_FG->setObjectName(QString::fromUtf8("spinBox_FG"));
        spinBox_FG->setGeometry(QRect(340, 740, 42, 22));
        spinBox_FG->setMinimum(-999);
        spinBox_FG->setMaximum(999);
        label_32 = new QLabel(centralWidget);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(390, 740, 141, 16));
        label_32->setLayoutDirection(Qt::LeftToRight);
        label_33 = new QLabel(centralWidget);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(390, 700, 131, 16));
        label_33->setLayoutDirection(Qt::LeftToRight);
        comboBox_broth = new QComboBox(centralWidget);
        comboBox_broth->setObjectName(QString::fromUtf8("comboBox_broth"));
        comboBox_broth->setGeometry(QRect(1270, 320, 151, 22));
        label_34 = new QLabel(centralWidget);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(1020, 750, 471, 21));
        label_34->setLayoutDirection(Qt::LeftToRight);
        label_34->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_35 = new QLabel(centralWidget);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(1330, 430, 141, 21));
        label_35->setFont(font);
        label_35->setLayoutDirection(Qt::LeftToRight);
        label_35->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_36 = new QLabel(centralWidget);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(1310, 430, 21, 21));
        label_36->setFont(font);
        label_36->setLayoutDirection(Qt::LeftToRight);
        label_36->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_37 = new QLabel(centralWidget);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(1310, 450, 161, 21));
        label_37->setLayoutDirection(Qt::LeftToRight);
        label_37->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_38 = new QLabel(centralWidget);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(1310, 470, 191, 21));
        label_38->setLayoutDirection(Qt::LeftToRight);
        label_38->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_39 = new QLabel(centralWidget);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(1310, 490, 201, 21));
        label_39->setLayoutDirection(Qt::LeftToRight);
        label_39->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_40 = new QLabel(centralWidget);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setGeometry(QRect(1310, 510, 171, 21));
        label_40->setLayoutDirection(Qt::LeftToRight);
        label_40->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_41 = new QLabel(centralWidget);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setGeometry(QRect(1310, 530, 171, 21));
        label_41->setLayoutDirection(Qt::LeftToRight);
        label_41->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_42 = new QLabel(centralWidget);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        label_42->setGeometry(QRect(1310, 550, 201, 21));
        label_42->setLayoutDirection(Qt::LeftToRight);
        label_42->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_43 = new QLabel(centralWidget);
        label_43->setObjectName(QString::fromUtf8("label_43"));
        label_43->setGeometry(QRect(1310, 590, 211, 21));
        label_43->setLayoutDirection(Qt::LeftToRight);
        label_43->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_44 = new QLabel(centralWidget);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        label_44->setGeometry(QRect(1310, 570, 191, 21));
        label_44->setLayoutDirection(Qt::LeftToRight);
        label_44->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_45 = new QLabel(centralWidget);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setGeometry(QRect(1310, 610, 171, 21));
        label_45->setLayoutDirection(Qt::LeftToRight);
        label_45->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_46 = new QLabel(centralWidget);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        label_46->setGeometry(QRect(390, 720, 71, 16));
        label_46->setLayoutDirection(Qt::LeftToRight);
        label_48 = new QLabel(centralWidget);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setGeometry(QRect(660, 700, 191, 51));
        label_48->setLayoutDirection(Qt::LeftToRight);
        label_49 = new QLabel(centralWidget);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        label_49->setGeometry(QRect(1430, 40, 81, 151));
        label_50 = new QLabel(centralWidget);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setGeometry(QRect(1430, 360, 81, 21));
        label_50->setLayoutDirection(Qt::LeftToRight);
        label_50->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_51 = new QLabel(centralWidget);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        label_51->setGeometry(QRect(1310, 640, 201, 51));
        label_51->setLayoutDirection(Qt::LeftToRight);
        label_51->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        StreptoGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StreptoGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1513, 21));
        menuBar->setDefaultUp(true);
        menuBar->setNativeMenuBar(true);
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QString::fromUtf8("menuDatei"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(menuDatei->sizePolicy().hasHeightForWidth());
        menuDatei->setSizePolicy(sizePolicy);
        menuDatei->setContextMenuPolicy(Qt::NoContextMenu);
        menuDatei->setLayoutDirection(Qt::LeftToRight);
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QString::fromUtf8("menuInfo"));
        StreptoGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(StreptoGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy1);
        mainToolBar->setBaseSize(QSize(1, 1));
        mainToolBar->setIconSize(QSize(48, 48));
        StreptoGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(StreptoGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        StreptoGUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuInfo->menuAction());
        menuDatei->addAction(action_settings);
        menuDatei->addAction(actionDubious_Option);
        menuDatei->addAction(action_Close);
        menuInfo->addAction(action_bout_StreptoDB);

        retranslateUi(StreptoGUIClass);
        QObject::connect(bttn_uploadPic, SIGNAL(clicked()), StreptoGUIClass, SLOT(uploadPic()));
        QObject::connect(bttn_loadDB, SIGNAL(clicked()), StreptoGUIClass, SLOT(loadDB()));
        QObject::connect(tableWidget, SIGNAL(cellClicked(int,int)), StreptoGUIClass, SLOT(itemSelected(int,int)));
        QObject::connect(bttn_compare, SIGNAL(clicked()), StreptoGUIClass, SLOT(compare()));
        QObject::connect(tableWidget_2, SIGNAL(cellClicked(int,int)), StreptoGUIClass, SLOT(paramSelected(int,int)));
        QObject::connect(bttn_add_inhibit, SIGNAL(clicked()), StreptoGUIClass, SLOT(addInhibition()));
        QObject::connect(bttn_GRP_save, SIGNAL(clicked()), StreptoGUIClass, SLOT(grpSave()));
        QObject::connect(bttn_GRP_delete, SIGNAL(clicked()), StreptoGUIClass, SLOT(grpDelete()));
        QObject::connect(bttn_IMG_save, SIGNAL(clicked()), StreptoGUIClass, SLOT(imgSave()));
        QObject::connect(bttn_IMG_delete, SIGNAL(clicked()), StreptoGUIClass, SLOT(imgDelete()));
        QObject::connect(bttn_subtable_delete, SIGNAL(clicked()), StreptoGUIClass, SLOT(subtableDelete()));
        QObject::connect(bttn_newGroup, SIGNAL(clicked()), StreptoGUIClass, SLOT(newGroup()));
        QObject::connect(action_settings, SIGNAL(triggered()), StreptoGUIClass, SLOT(act_settings()));
        QObject::connect(bttn_editTeststrains, SIGNAL(clicked()), StreptoGUIClass, SLOT(editTestStrains()));
        QObject::connect(bttn_segmentation, SIGNAL(clicked()), StreptoGUIClass, SLOT(showSegmentation()));
        QObject::connect(bttn_calc, SIGNAL(clicked()), StreptoGUIClass, SLOT(testCalc()));
        QObject::connect(bttn_loadsql, SIGNAL(clicked()), StreptoGUIClass, SLOT(loadSql()));
        QObject::connect(action_Close, SIGNAL(triggered()), StreptoGUIClass, SLOT(close()));
        QObject::connect(actionDubious_Option, SIGNAL(triggered()), StreptoGUIClass, SLOT(showMinimized()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StreptoGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *StreptoGUIClass)
    {
        StreptoGUIClass->setWindowTitle(QApplication::translate("StreptoGUIClass", "StreptoGUI", nullptr));
        actionAnalys->setText(QApplication::translate("StreptoGUIClass", "Evaluations", nullptr));
        action_settings->setText(QApplication::translate("StreptoGUIClass", "Settings", nullptr));
        actionSave->setText(QApplication::translate("StreptoGUIClass", "Save All", nullptr));
        action_Close->setText(QApplication::translate("StreptoGUIClass", "Close", nullptr));
        action_bout_StreptoDB->setText(QApplication::translate("StreptoGUIClass", "About StreptoDB...", nullptr));
        actionDubious_Option->setText(QApplication::translate("StreptoGUIClass", "Minimize", nullptr));
        bttn_uploadPic->setText(QApplication::translate("StreptoGUIClass", "Upload", nullptr));
        label->setText(QApplication::translate("StreptoGUIClass", "StreptoDB", nullptr));
        label_2->setText(QApplication::translate("StreptoGUIClass", "Imageview:", nullptr));
        label_3->setText(QApplication::translate("StreptoGUIClass", "Path...", nullptr));
        bttn_loadDB->setText(QApplication::translate("StreptoGUIClass", "refresh", nullptr));
        label_4->setText(QApplication::translate("StreptoGUIClass", "DB-Status...", nullptr));
        label_5->setText(QApplication::translate("StreptoGUIClass", "ID:", nullptr));
        label_6->setText(QApplication::translate("StreptoGUIClass", "Timestamp:", nullptr));
        label_7->setText(QApplication::translate("StreptoGUIClass", "Imagesize:", nullptr));
        label_8->setText(QApplication::translate("StreptoGUIClass", "Resolution_x/y:", nullptr));
        label_9->setText(QApplication::translate("StreptoGUIClass", "Broth-ID:", nullptr));
        label_11->setText(QApplication::translate("StreptoGUIClass", "Calculated Parameter:", nullptr));
        label_12->setText(QApplication::translate("StreptoGUIClass", "...", nullptr));
        label_13->setText(QApplication::translate("StreptoGUIClass", "Path:", nullptr));
        label_14->setText(QApplication::translate("StreptoGUIClass", "- Select an Image", nullptr));
        label_15->setText(QApplication::translate("StreptoGUIClass", "- Adjust attributes for comparison:", nullptr));
        label_16->setText(QApplication::translate("StreptoGUIClass", "- look at the Fore/Background segmentation:", nullptr));
        bttn_compare->setText(QApplication::translate("StreptoGUIClass", "order by selected-Group", nullptr));
        label_17->setText(QApplication::translate("StreptoGUIClass", "Comparison: ", nullptr));
        label_18->setText(QApplication::translate("StreptoGUIClass", "Group Info:", nullptr));
        label_19->setText(QApplication::translate("StreptoGUIClass", "Picture Info:", nullptr));
        label_20->setText(QApplication::translate("StreptoGUIClass", "Group-ID:", nullptr));
        label_21->setText(QApplication::translate("StreptoGUIClass", "Intern-ID:", nullptr));
        label_22->setText(QApplication::translate("StreptoGUIClass", "Timestamp:", nullptr));
        label_23->setText(QApplication::translate("StreptoGUIClass", "Scientific-Name:", nullptr));
        label_24->setText(QApplication::translate("StreptoGUIClass", "Genome-Link:", nullptr));
        label_25->setText(QApplication::translate("StreptoGUIClass", "Position_lat/lon:", nullptr));
        label_26->setText(QApplication::translate("StreptoGUIClass", "Siderophore:", nullptr));
        label_27->setText(QApplication::translate("StreptoGUIClass", "Spore-Color:", nullptr));
        checkBox_siderophore->setText(QString());
#ifndef QT_NO_TOOLTIP
        line_filter->setToolTip(QApplication::translate("StreptoGUIClass", "Filter (intern-ID)", nullptr));
#endif // QT_NO_TOOLTIP
        line_filter->setText(QApplication::translate("StreptoGUIClass", "CS ", nullptr));
        bttn_IMG_save->setText(QApplication::translate("StreptoGUIClass", "Save", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_Calculations), QApplication::translate("StreptoGUIClass", "Calculations", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("StreptoGUIClass", "Strain-Inhibition", nullptr));
        checkBox_inhibition->setText(QApplication::translate("StreptoGUIClass", "Inhibition", nullptr));
        bttn_add_inhibit->setText(QApplication::translate("StreptoGUIClass", "add", nullptr));
        label_28->setText(QApplication::translate("StreptoGUIClass", "...", nullptr));
        bttn_GRP_delete->setText(QApplication::translate("StreptoGUIClass", "Delete", nullptr));
        bttn_GRP_save->setText(QApplication::translate("StreptoGUIClass", "Save", nullptr));
        bttn_IMG_delete->setText(QApplication::translate("StreptoGUIClass", "Delete", nullptr));
        bttn_subtable_delete->setText(QApplication::translate("StreptoGUIClass", "Delete Entry", nullptr));
        bttn_newGroup->setText(QApplication::translate("StreptoGUIClass", "new Group", nullptr));
        label_47->setText(QApplication::translate("StreptoGUIClass", "Scale:", nullptr));
        bttn_editBroth->setText(QApplication::translate("StreptoGUIClass", "edit Broth", nullptr));
        bttn_editTeststrains->setText(QApplication::translate("StreptoGUIClass", "edit Test-Strains", nullptr));
        bttn_loadsql->setText(QApplication::translate("StreptoGUIClass", "run SQL-File", nullptr));
        bttn_segmentation->setText(QApplication::translate("StreptoGUIClass", "Show Segmentation", nullptr));
        label_29->setText(QApplication::translate("StreptoGUIClass", "Background(%):", nullptr));
        label_30->setText(QApplication::translate("StreptoGUIClass", "Threshold(%):", nullptr));
        bttn_calc->setText(QApplication::translate("StreptoGUIClass", "Add Calculations", nullptr));
        label_31->setText(QApplication::translate("StreptoGUIClass", "Foreground:", nullptr));
        label_32->setText(QApplication::translate("StreptoGUIClass", "(Dilation-iterations(0 to 100))", nullptr));
        label_33->setText(QApplication::translate("StreptoGUIClass", "(Circle-Size(-200 to 200))", nullptr));
        label_34->setText(QApplication::translate("StreptoGUIClass", "...", nullptr));
        label_35->setText(QApplication::translate("StreptoGUIClass", "Short Param Description:", nullptr));
        label_36->setText(QApplication::translate("StreptoGUIClass", "ID:", nullptr));
        label_37->setText(QApplication::translate("StreptoGUIClass", "1: size of one pixel in mm (0.00X)", nullptr));
        label_38->setText(QApplication::translate("StreptoGUIClass", "2: size of Streptomyces in mm\302\262 (1-500)", nullptr));
        label_39->setText(QApplication::translate("StreptoGUIClass", "3: mean foreground channel red (0-255)", nullptr));
        label_40->setText(QApplication::translate("StreptoGUIClass", "4: mean fg-channel green (0-255)", nullptr));
        label_41->setText(QApplication::translate("StreptoGUIClass", "5: mean fg- channel blue (0-255)", nullptr));
        label_42->setText(QApplication::translate("StreptoGUIClass", "6: mean background channel red (0-255)", nullptr));
        label_43->setText(QApplication::translate("StreptoGUIClass", "8: mean bg-channel blue (0-255)", nullptr));
        label_44->setText(QApplication::translate("StreptoGUIClass", "7: mean bg-channel green (0-255)", nullptr));
        label_45->setText(QApplication::translate("StreptoGUIClass", "9: Shape; roundness-factor (0-1)", nullptr));
        label_46->setText(QApplication::translate("StreptoGUIClass", "(-100 to 100)", nullptr));
        label_48->setText(QApplication::translate("StreptoGUIClass", "Pictures with missing Parameters\n"
"have a red ID. Please add calculations\n"
"for these pics.", nullptr));
        label_49->setText(QApplication::translate("StreptoGUIClass", "Please dont\n"
"leave any fields\n"
"empty and dont\n"
"try to crash it\n"
"with special \n"
"characters.", nullptr));
        label_50->setText(QApplication::translate("StreptoGUIClass", "(in mm > 0)", nullptr));
        label_51->setText(QApplication::translate("StreptoGUIClass", "Click on a param to see the total \n"
"difference to the other image-params\n"
"with the same broth and same\n"
"classification.", nullptr));
        menuDatei->setTitle(QApplication::translate("StreptoGUIClass", "Options", nullptr));
        menuInfo->setTitle(QApplication::translate("StreptoGUIClass", "Info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StreptoGUIClass: public Ui_StreptoGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREPTOGUI_H
