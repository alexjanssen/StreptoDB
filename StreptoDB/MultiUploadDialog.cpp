#include "MultiUploadDialog.h"
#include <QtWidgets\QFileDialog>
#include <QtWidgets\QMessageBox>
#include <QtWidgets\QGraphicsPixmapItem>
#include <QtWidgets/qtablewidget.h>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <CVController.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <QBuffer>
#include <ctime>
//#include <string>
//#include <sqlite/sqlite3.h> 


using namespace std;


//Constructor yds
multiUploadDialog::multiUploadDialog(QDialog* parent) : QDialog(parent){
	ui.setupUi(this);
	vImg->clear();
	ui.label_out->setText("Dont forget to save!");
}


//Open File Functions, they call loadFile(QString, int)
void multiUploadDialog::selectFile1() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());

	if (!fileName.isEmpty())
	{
		multiUploadDialog::loadFile(fileName, 1);
	}
}

void multiUploadDialog::selectFile2() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());

	if (!fileName.isEmpty())
	{
		multiUploadDialog::loadFile(fileName, 2);
	}
}

void multiUploadDialog::selectFile3() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());

	if (!fileName.isEmpty())
	{
		multiUploadDialog::loadFile(fileName, 3);
	}
}

void multiUploadDialog::selectFile4() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());

	if (!fileName.isEmpty())
	{
		multiUploadDialog::loadFile(fileName, 4);
	}
}


//loads file from QString and auto-fills the input lines depending on given broth
//This function gets a broth list from the db and trys to find a broth in the given url-string, 
//when he cant find any, its set so 1 or whatever you hand to bid.
void multiUploadDialog::loadFile(QString fileName, int bid){
	QImage image(fileName);
	if (image.isNull()){	
		QMessageBox::information(this, "Image Viewer", "Error Displaying image");
		return;
	}
	Image img = Image();
	img.image_preview = image.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	vImg->push_back(img);
	
	DBController* dbcon2 = new DBController();
	int id = dbcon2->getMaxImageID();			//set imageID
	int newGrpID = dbcon2->getMaxGroupID() + 1;	//set groupID
	//Actual Date
	std::time_t rawtime;
	std::tm* timeinfo;
	char buffer2[80];

	std::time(&rawtime);
	timeinfo = std::localtime(&rawtime);

	std::strftime(buffer2, 80, "%Y-%m-%d", timeinfo);
	std::puts(buffer2);

	//lets find the right brothID
	vector<Broth> vbroth = dbcon2->getBroth("NOT NULL");
	for (int g = 0; g < vbroth.size(); g++) {
		if (fileName.toStdString().find(vbroth[g].name, fileName.size() - 10) != string::npos) {
			bid = g+1;
		}
	}
	

	//Then auto-fill for each broth
	if (bid == 1) {
		//Group parameter
		ui.line_groupID_group->setText(QString::number(newGrpID));
		ui.line_internID->setText("XX 00");
		ui.line_timestamp_group->setText(buffer2);
		ui.line_scientific->setText("NN");
		ui.line_genome->setText("www.rub.de");
		ui.line_locality->setText("0.0");
		ui.line_locality_2->setText("0.0");
		ui.line_spore_color->setText("default");
		//Image Parameter
		ui.line_ID->setText(QString::number(id + 1));
		ui.line_timestamp->setText(buffer2);
		ui.line_imgSize->setText("auto fill");
		ui.line_resolution_x->setText(QString::number(image.width()));
		ui.line_resolution_y->setText(QString::number(image.height()));
		ui.line_groupID->setText(QString::number(newGrpID));
		ui.line_path->setText(fileName);
		ui.line_scale->setText(QString::number(2));

		QPixmap pixmap2;
		pixmap2 = pixmap2.fromImage(image);

		QGraphicsScene* scene = new QGraphicsScene();
		scene->addPixmap(pixmap2.scaled(150, 150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
		ui.graphicsView->setScene(scene);
		ui.graphicsView->show();
		//Choose the right Broth
		ui.comboBox_broth->clear();
		vector<Broth> vbroth = dbcon2->getBroth("NOT NULL");
		for (int g = 0; g < vbroth.size(); g++) {
			ui.comboBox_broth->addItem(QString::fromStdString(vbroth[g].name + "\t   -" + std::to_string(vbroth[g].broth_id)));
			if (fileName.toStdString().find(vbroth[g].name, fileName.size() - 10) != string::npos) {
				bid = g+1;
			}
		}
		ui.comboBox_broth->setCurrentIndex(bid-1);
	}//same for BrothID = 2
	else if (bid == 2) {
		ui.line_ID_2->setText(QString::number(id + 2));
		ui.line_timestamp_2->setText(buffer2);
		ui.line_imgSize_2->setText("auto fill");
		ui.line_resolution_x_2->setText(QString::number(image.width()));
		ui.line_resolution_y_2->setText(QString::number(image.height()));
		ui.line_groupID_2->setText(QString::number(newGrpID));
		ui.line_path_2->setText(fileName);
		ui.line_scale_2->setText(QString::number(2));

		QPixmap pixmap2;
		pixmap2 = pixmap2.fromImage(image);

		QGraphicsScene* scene = new QGraphicsScene();
		scene->addPixmap(pixmap2.scaled(150, 150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
		ui.graphicsView_2->setScene(scene);
		ui.graphicsView_2->show();

		ui.comboBox_broth_2->clear();
		vector<Broth> vbroth = dbcon2->getBroth("NOT NULL");
		for (int g = 0; g < vbroth.size(); g++) {
			ui.comboBox_broth_2->addItem(QString::fromStdString(vbroth[g].name + "\t   -" + std::to_string(vbroth[g].broth_id)));
			if (fileName.toStdString().find(vbroth[g].name, fileName.size() - 10) != string::npos) {
				bid = g + 1;
			}
		}
		ui.comboBox_broth_2->setCurrentIndex(bid - 1);
	}//you get it
	else if (bid == 3) {
		ui.line_ID_3->setText(QString::number(id + 3));
		ui.line_timestamp_3->setText(buffer2);
		ui.line_imgSize_3->setText("auto fill");
		ui.line_resolution_x_3->setText(QString::number(image.width()));
		ui.line_resolution_y_3->setText(QString::number(image.height()));
		ui.line_groupID_3->setText(QString::number(newGrpID));
		ui.line_path_3->setText(fileName);
		ui.line_scale_3->setText(QString::number(2));

		QPixmap pixmap2;
		pixmap2 = pixmap2.fromImage(image);

		QGraphicsScene* scene = new QGraphicsScene();
		scene->addPixmap(pixmap2.scaled(150, 150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
		ui.graphicsView_3->setScene(scene);
		ui.graphicsView_3->show();

		ui.comboBox_broth_3->clear();
		vector<Broth> vbroth = dbcon2->getBroth("NOT NULL");
		for (int g = 0; g < vbroth.size(); g++) {
			ui.comboBox_broth_3->addItem(QString::fromStdString(vbroth[g].name + "\t   -" + std::to_string(vbroth[g].broth_id)));
			if (fileName.toStdString().find(vbroth[g].name, fileName.size() - 10) != string::npos) {
				bid = g + 1;
			}
		}
		ui.comboBox_broth_3->setCurrentIndex(bid - 1);
	}//no comment
	else if (bid == 4) {
		ui.line_ID_4->setText(QString::number(id + 4));
		ui.line_timestamp_4->setText(buffer2);
		ui.line_imgSize_4->setText("auto fill");
		ui.line_resolution_x_4->setText(QString::number(image.width()));
		ui.line_resolution_y_4->setText(QString::number(image.height()));
		ui.line_groupID_4->setText(QString::number(newGrpID));
		ui.line_path_4->setText(fileName);
		ui.line_scale_4->setText(QString::number(2));

		QPixmap pixmap2;
		pixmap2 = pixmap2.fromImage(image);

		QGraphicsScene* scene = new QGraphicsScene();
		scene->addPixmap(pixmap2.scaled(150, 150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
		ui.graphicsView_4->setScene(scene);
		ui.graphicsView_4->show();

		ui.comboBox_broth_4->clear();
		vector<Broth> vbroth = dbcon2->getBroth("NOT NULL");
		for (int g = 0; g < vbroth.size(); g++) {
			ui.comboBox_broth_4->addItem(QString::fromStdString(vbroth[g].name + "\t   -" + std::to_string(vbroth[g].broth_id)));
			if (fileName.toStdString().find(vbroth[g].name, fileName.size() - 10) != string::npos) {
				bid = g + 1;
			}
		}
		ui.comboBox_broth_4->setCurrentIndex(bid - 1);
	}
	

}


//Collects the user inputs and calls DBController::addImage(Image);
void multiUploadDialog::saveAll() {
	DBController* dbcon2 = new DBController();
	group.group_id = ui.line_groupID_group->text().toInt();
	group.intern_id = ui.line_internID->text().toStdString();
	group.date = ui.line_timestamp_group->text().toStdString();
	group.sci_name = ui.line_scientific->text().toStdString();
	group.genome_lnk = ui.line_genome->text().toStdString();
	group.latitude = ui.line_locality->text().toDouble();
	group.longitude = ui.line_locality_2->text().toDouble();
	group.siderophore = ui.checkBox_siderophore->isChecked();
	group.spore_color = ui.line_spore_color->text().toStdString();

	vImg->at(0).image_id = ui.line_ID->text().toInt();
	vImg->at(0).date = ui.line_timestamp->text().toStdString();
	vImg->at(0).imagesize = ui.line_imgSize->text().toDouble();
	vImg->at(0).resolution_x = ui.line_resolution_x->text().toDouble();
	vImg->at(0).resolution_y = ui.line_resolution_y->text().toDouble();
	vImg->at(0).broth_id = atoi(ui.comboBox_broth->currentText().toStdString().substr(ui.comboBox_broth->currentText().toStdString().find("-") + 1).c_str());
	vImg->at(0).group_id = ui.line_groupID_group->text().toInt();
	vImg->at(0).filePath = ui.line_path->text().toStdString();
	vImg->at(0).scale = ui.line_scale->text().toDouble();

	vImg->at(1).image_id = ui.line_ID_2->text().toInt();
	vImg->at(1).date = ui.line_timestamp_2->text().toStdString();
	vImg->at(1).imagesize = ui.line_imgSize_2->text().toDouble();
	vImg->at(1).resolution_x = ui.line_resolution_x_2->text().toDouble();
	vImg->at(1).resolution_y = ui.line_resolution_y_2->text().toDouble();
	vImg->at(1).broth_id = atoi(ui.comboBox_broth_2->currentText().toStdString().substr(ui.comboBox_broth_2->currentText().toStdString().find("-") + 1).c_str());
	vImg->at(1).group_id = ui.line_groupID_group->text().toInt();
	vImg->at(1).filePath = ui.line_path_2->text().toStdString();
	vImg->at(1).scale = ui.line_scale_2->text().toDouble();

	vImg->at(2).image_id = ui.line_ID_3->text().toInt();
	vImg->at(2).date = ui.line_timestamp_3->text().toStdString();
	vImg->at(2).imagesize = ui.line_imgSize_3->text().toDouble();
	vImg->at(2).resolution_x = ui.line_resolution_x_3->text().toDouble();
	vImg->at(2).resolution_y = ui.line_resolution_y_3->text().toDouble();
	vImg->at(2).broth_id = atoi(ui.comboBox_broth_3->currentText().toStdString().substr(ui.comboBox_broth_3->currentText().toStdString().find("-") + 1).c_str());
	vImg->at(2).group_id = ui.line_groupID_group->text().toInt();
	vImg->at(2).filePath = ui.line_path_3->text().toStdString();
	vImg->at(2).scale = ui.line_scale_3->text().toDouble();

	vImg->at(3).image_id = ui.line_ID_4->text().toInt();
	vImg->at(3).date = ui.line_timestamp_4->text().toStdString();
	vImg->at(3).imagesize = ui.line_imgSize_4->text().toDouble();
	vImg->at(3).resolution_x = ui.line_resolution_x_4->text().toDouble();
	vImg->at(3).resolution_y = ui.line_resolution_y_4->text().toDouble();
	vImg->at(3).broth_id = atoi(ui.comboBox_broth_4->currentText().toStdString().substr(ui.comboBox_broth_4->currentText().toStdString().find("-") + 1).c_str());
	vImg->at(3).group_id = ui.line_groupID_group->text().toInt();
	vImg->at(3).filePath = ui.line_path_4->text().toStdString();
	vImg->at(3).scale = ui.line_scale_4->text().toDouble();

	if (dbcon2->addGroup(group)) {
		for (int i = 0; i < vImg->size(); i++) {
			if (dbcon2->addImage2(vImg->at(i))) {
				ui.label_out->setText("successfully created Group and saved Images.");
			}else {
				ui.label_out->setText("failed to save Images in DB.   -" + QString::number(i));
			}
		}
	}else {
		ui.label_out->setText("failed to create Group in DB.");
	}
}


//just iterates an url vector and calls loadFile() for each url.
void multiUploadDialog::dragOpenFiles(vector<string> urls){
	vImg->clear();
	ui.label_out->setText("Dont forget to save!");
	if (!urls.empty()) {
		for (int i = 0; i < urls.size(); i++) {
			multiUploadDialog::loadFile(QString::fromStdString(urls[i]), 0);
		}
	}
	urls.clear();

}
