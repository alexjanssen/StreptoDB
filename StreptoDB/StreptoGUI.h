#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_StreptoGUI.h"
#include <QtWidgets\QLabel>
#include <DBController.h>
#include <QtWidgets\QFileDialog>
#include <QtWidgets\QMessageBox>
#include <QtWidgets\QGraphicsPixmapItem>
#include <QtWidgets/qtablewidget.h>
#include <QTableWidgetItem>
#include <QHeaderView>
//#include <CVController.h>
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
#include <UploadDialog.h>
#include <MultiUploadDialog.h>
#include <ctime>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <SettingsDialog.h>
#include <fstream>

class StreptoGUI : public QMainWindow, public Ui::StreptoGUIClass
{
	Q_OBJECT

public:
	StreptoGUI(QMainWindow* parent = 0);
	Ui::StreptoGUIClass ui;

public slots:
	void uploadPic();
	void loadSettings();
	void loadDB();
	void itemSelected(int x, int y);
	void testCalc();
	void showSegmentation();
	void addInhibition();
	void compare();
	void paramSelected(int x, int y);
	void imgSave();
	void imgDelete();
	void grpSave();
	void grpDelete();
	void subtableDelete();
	void newGroup();
	void act_settings();
	void loadSql();

protected:   
	void dragMoveEvent(QDragMoveEvent* event);
	void dropEvent(QDropEvent* event);
	void dragEnterEvent(QDragEnterEvent* event);

private:
	uploadDialog* ud = new uploadDialog();
	multiUploadDialog* mud = new multiUploadDialog();
	vector<string>* urls = new vector<string>;

private slots:
	void fillTable(vector<Image>);
	void fillTable2(vector<CalcedParams>);
	void fillTable3(vector<StrainInhibition> result);
	
};

static vector<Image> resultGlob;
static DBController *dbcon = new DBController();
static CVController* cvcon = new CVController();
static string globPath = "";
static int column;
static int selX;
static int selY;