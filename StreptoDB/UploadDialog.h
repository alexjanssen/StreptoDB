#pragma once

#include <QtWidgets/qdialog.h>
#include "ui_StreptoGUI.h"
#include <QtWidgets\QLabel>
#include <DBController.h>
#include <ui_UploadDialog.h>

class uploadDialog : public QDialog, public Ui::StreptoGUIClass
{
	Q_OBJECT

public:
	uploadDialog(QDialog* parent = 0);
	Ui::uploadDialog ui;
	//StreptoGUI(QMainWindow* parent, int t);
	//private:
	//Ui::StreptoGUIClass ui;
	//StreptoGUI(QWidget* parent);
	//void bttnPushed();
public slots:
	void openFile();
	//void loadDB();

//private slots:
//	void fillTable(vector<Image>);
};