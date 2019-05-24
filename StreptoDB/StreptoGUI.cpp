#include "StreptoGUI.h"
#include <QtWidgets\QFileDialog>
#include <QtWidgets\QMessageBox>
#include <QtWidgets\QGraphicsPixmapItem>
#include <QtWidgets/qtablewidget.h>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <CVController.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <UploadDialog.h>
//#include <string>
//#include <sqlite/sqlite3.h> 


using namespace std; 



StreptoGUI::StreptoGUI(QMainWindow*parent)	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ui.label -> setText("blaa");
}

void StreptoGUI::uploadPic() {
	uploadDialog* f = new uploadDialog();
	f->show();

}





void StreptoGUI::loadDB() {
	//####################################################
	
	DBController *dbcon = new DBController();
	
	vector<Image> result2;
	result2 = dbcon->getImages();
	if (result2.size() == 0) {
		ui.label_4->setText("Can't open database.");
	}
	else {
		ui.label_4->setText("Opened database successfully.");
		fillTable(result2);
	}
	//####################################################

}



void StreptoGUI::fillTable(vector<Image> result){
	ui.tableWidget->setRowCount(10);
	ui.tableWidget->setRowHeight(0,100);
	ui.tableWidget->setRowHeight(1, 100);
	ui.tableWidget->setColumnCount(5);
	ui.tableWidget->verticalHeader()->setVisible(false);
	//ui.tableWidget->setShowGrid(false);
	//->setStyleSheet("QTableView {selection-background-color: red;}");
	//->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	ui.tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Image-ID"));
	ui.tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Image-Preview"));
	ui.tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Timestamp"));
	ui.tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Imagesize"));
	ui.tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Resolution"));


	//QPixmap pixmap;
	//pixmap = result[0].image_preview;
	QTableWidgetItem *twi = new QTableWidgetItem();
	twi->setData(Qt::DecorationRole, result[0].image_preview.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	ui.tableWidget->setItem(0, 1, twi);
	ui.tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(result[0].image_id)));
	ui.tableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(result[0].date)));
	ui.tableWidget->setItem(0, 3, new QTableWidgetItem(QString::fromStdString(to_string(result[0].imagesize))));
	ui.tableWidget->setItem(0, 4, new QTableWidgetItem(QString::fromStdString(to_string(result[0].resolution))));
}