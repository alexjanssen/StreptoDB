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
	//QMimeData* mimeData;

public slots:
	void selectFile1();
	void selectFile2();
	void selectFile3();
	void selectFile4();
	void loadFile(QString path, int bid);
	void saveAll();
	void dragOpenFiles(vector<string> urls);

	void clearInput();


	//private slots:
	//	void fillTable(vector<Image>);
};

static Group group;
static vector<Image> *vImg = new vector<Image>;