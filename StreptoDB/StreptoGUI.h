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

public slots:
	void uploadPic();
	void loadDB();
	void itemSelected(int x, int y);
	void testCalc();
	void addInhibition();
	void compare();
	void paramSelected(int x, int y);
	void imgSave();
	void imgDelete();
	void grpSave();
	void grpDelete();
	void subtableDelete();
	void newGroup();

protected:    
	void dragMoveEvent(QDragMoveEvent* event);
	void dropEvent(QDropEvent* event);
	void dragEnterEvent(QDragEnterEvent* event);


private slots:
	void fillTable(vector<Image>);
	void fillTable2(vector<CalcedParams>);
	void fillTable3(vector<StrainInhibition> result);
};

static vector<Image> resultGlob;
static DBController *dbcon = new DBController();
static int column;