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
	void test();
	void loadDB();
	void fillTable(vector<Isolat>);
};