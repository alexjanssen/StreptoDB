#include "UploadDialog.h"
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



uploadDialog::uploadDialog(QDialog* parent) : QDialog(parent)
{
	ui.setupUi(this);
	//ui.label -> setText("blaa");
}

void uploadDialog::openFile() {
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
		//ui.tableWidget->setItem(0, 0, new QTableWidgetItem(*twi));


		//delete(&pixmap);
		//delete(&scene);
		//delete(&image);

	}


	ui.label->setText(fileName);
	//delete(&fileName);
}


