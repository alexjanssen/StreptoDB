#pragma once

#include <QtWidgets/qdialog.h>
#include "ui_StreptoGUI.h"
#include <QtWidgets\QLabel>
#include <DBController.h>
#include <ui_UploadDialog.h>
#include <QtWidgets\QFileDialog>
#include <QtWidgets\QMessageBox>
#include <QtWidgets\QGraphicsPixmapItem>
#include <QtWidgets/qtablewidget.h>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <CVController.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <ctime>
//#include <string>

class uploadDialog : public QDialog, public Ui::StreptoGUIClass
{
	Q_OBJECT

public:
	uploadDialog(QDialog* parent = 0);
	Ui::uploadDialog ui;
	int grpID;
public slots:
	void openFile();
	void insertIntoDB();

	void dragOpenFile(QString path);

};

static Image img;