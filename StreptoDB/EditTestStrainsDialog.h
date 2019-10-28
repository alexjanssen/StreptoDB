#pragma once

#include <QtWidgets/qdialog.h>
#include "ui_StreptoGUI.h"
#include <QtWidgets\QLabel>
#include <DBController.h>
#include <ui_EditTestStrainsDialog.h>
#include <QtWidgets\QMessageBox>
#include <QtWidgets/qtablewidget.h>
#include <QTableWidgetItem>
#include <QHeaderView>
//#include <vector>
//#include <TestStrain.cpp>
//#include <string>

class editTestStrainsDialog : public QDialog, public Ui::StreptoGUIClass
{
	Q_OBJECT

public:
	editTestStrainsDialog(QDialog* parent = 0);
	Ui::editTestStrainsDialog ui;
public slots:
	void loadDB();
	void addItem();
	void deleteItem();
	void fillTable(vector<TestStrain> result);
};

static vector<TestStrain> testStrain_glob;// = new vector<TestStrain>;
static TestStrain newTS;