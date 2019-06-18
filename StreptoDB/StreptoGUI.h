#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_StreptoGUI.h"
#include <QtWidgets\QLabel>
#include <DBController.h>

class StreptoGUI : public QMainWindow, public Ui::StreptoGUIClass
{
	Q_OBJECT

public:
	StreptoGUI(QMainWindow* parent = 0);
	Ui::StreptoGUIClass ui;
	//StreptoGUI(QMainWindow* parent, int t);
	//private:
	//Ui::StreptoGUIClass ui;
	//StreptoGUI(QWidget* parent);
	//void bttnPushed();
public slots:
	void uploadPic();
	void loadDB();
	void itemSelected(int x, int y);
	void testCalc();
	void compare();

private slots:
	void fillTable(vector<Image>);
	void fillTable2(vector<CalcedParams>);
};

static vector<Image> resultGlob;
static DBController *dbcon = new DBController();