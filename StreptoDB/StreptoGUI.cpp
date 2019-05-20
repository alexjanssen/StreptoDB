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
//#include <string>
//#include <sqlite/sqlite3.h> 


using namespace std; 



StreptoGUI::StreptoGUI(QMainWindow*parent)	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ui.label -> setText("blaa");
}

void StreptoGUI::uploadPic() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());

	if (!fileName.isEmpty())
	{
		QImage image(fileName);

		if (image.isNull())
		{
			QMessageBox::information(this, "Image Viewer", "Error Displaying image");
			return;
		}

		
		cv::Mat testbildM = cv::imread(fileName.toStdString());
		QImage imageQ2 = CVController::Mat2QImage(testbildM);


		//QPixmap pixmap(fileName);
		//QImage imageQ = (QImage)pixmap.toImage();
		//cv::Mat testbildM = CVController::QImage2Mat(imageQ);
		//QImage imageQ2 = CVController::Mat2QImage(testbildM);


		//cv::Mat testbildM = cv::imread(fileName.toStdString());
		//QImage *testbildQ = new QImage(); 
		//testbildQ = &CVController::Mat2QImage(testbildM);


		QPixmap pixmap2;
		pixmap2 = pixmap2.fromImage(imageQ2);


		QGraphicsScene* scene = new QGraphicsScene();
		scene->addPixmap(pixmap2.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

		ui.graphicsView->setScene(scene);
		ui.graphicsView->show();


		QTableWidgetItem* twi = new QTableWidgetItem("test");
		twi->setData(Qt::DecorationRole, pixmap2.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
		ui.tableWidget->setItem(0, 0, new QTableWidgetItem(*twi));
		

		//delete(&pixmap);
		//delete(&scene);
		//delete(&image);
		
	}


	ui.label_3->setText(fileName);
	//delete(&fileName);
}


void StreptoGUI::loadDB() {
	//####################################################
	
	DBController *dbcon = new DBController();
	
	vector<Isolat> result2;
	result2 = dbcon->testCon();
	if (result2.size() == 0) {
		ui.label_4->setText("Can't open database.");
	}
	else {
		ui.label_4->setText("Opened database successfully.");
		fillTable(result2);
	}
	//####################################################

}



void StreptoGUI::fillTable(vector<Isolat> result){
	ui.tableWidget->setRowCount(10);
	ui.tableWidget->setRowHeight(0,100);
	ui.tableWidget->setRowHeight(1, 100);
	ui.tableWidget->setColumnCount(5);
	ui.tableWidget->verticalHeader()->setVisible(false);
	//ui.tableWidget->setShowGrid(false);
	//->setStyleSheet("QTableView {selection-background-color: red;}");
	//->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	ui.tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Bild"));
	ui.tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("id"));
	ui.tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("id_intern"));
	ui.tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Nomenklatur"));
	ui.tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Siderophore"));


	//QPixmap pixmap;
	//pixmap = result[0].image_preview;
	QTableWidgetItem *twi = new QTableWidgetItem();
	twi->setData(Qt::DecorationRole, result[0].image_preview.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	ui.tableWidget->setItem(0, 0, twi);
	ui.tableWidget->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(to_string(result[0].id))));
	ui.tableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(to_string(result[0].id_intern))));
	ui.tableWidget->setItem(0, 3, new QTableWidgetItem(QString::fromStdString(result[0].scientific_name)));
	ui.tableWidget->setItem(0, 4, new QTableWidgetItem(QString::fromStdString(to_string(result[0].siderophore_bool))));
}