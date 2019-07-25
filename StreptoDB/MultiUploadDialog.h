#pragma once

#include <QtWidgets/qdialog.h>
#include "ui_StreptoGUI.h"
#include <QtWidgets\QLabel>
#include <DBController.h>
#include <ui_MultiUploadDialog.h>
#include <string>

class multiUploadDialog : public QDialog, public Ui::StreptoGUIClass
{
	Q_OBJECT

public:
	multiUploadDialog(QDialog* parent = 0);
	Ui::multiUpload ui;
	//StreptoGUI(QMainWindow* parent, int t);
	//private:
	//Ui::StreptoGUIClass ui;
	//StreptoGUI(QWidget* parent);
	//void bttnPushed();
public slots:
	void selectFile1();
	void loadFile(string path, int broth);
	void saveAll();


	//private slots:
	//	void fillTable(vector<Image>);
};

static Group group;
static Image img1;
static Image img2;
static Image img3;
static Image img4;