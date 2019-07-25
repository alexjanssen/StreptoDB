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



multiUploadDialog::multiUploadDialog(QDialog* parent) : QDialog(parent)
{
	ui.setupUi(this);
	//ui.label -> setText("blaa");
}


void multiUploadDialog::selectFile1() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());

	if (!fileName.isEmpty())
	{
		multiUploadDialog::loadFile(fileName.toStdString(), 1);
	}
}



void multiUploadDialog::loadFile(string path, int broth)//broth: 1=ISP2 ; 2=GN ; 3=NCBMM ; 4=SFM
{

	QImage image(QString::fromStdString(path));

	if (image.isNull())
	{
		QMessageBox::information(this, "Image Viewer", "Error Displaying image");
		return;
	}
	//image = image.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	//QByteArray bytes;
	//QBuffer buffer(&bytes);
	//buffer.open(QIODevice::WriteOnly);
	//image.save(&buffer, "tif");
	//buffer.close();

	//unsigned char* data = (unsigned char*)malloc(bytes.size());
	//memcpy(data, reinterpret_cast<unsigned char*>(bytes.data()), bytes.size());
	//int size = bytes.size();
	//free(data);
	//buffer.~QBuffer();

	DBController* dbcon2 = new DBController();
	int id = dbcon2->getMaxImageID();
	int newGrpID = dbcon2->getMaxGroupID() + 1;

	std::time_t rawtime;
	std::tm* timeinfo;
	char buffer2[80];

	std::time(&rawtime);
	timeinfo = std::localtime(&rawtime);

	std::strftime(buffer2, 80, "%Y-%m-%d", timeinfo);
	std::puts(buffer2);

	if (broth == 1) {
		ui.line_ID->setText(QString::number(id + 1));
		ui.line_timestamp->setText(buffer2);
		ui.line_imgSize->setText("auto fill");
		ui.line_resolution_x->setText(QString::number(image.width()));
		ui.line_resolution_y->setText(QString::number(image.height()));
		ui.line_brothID->setText(QString::number(broth));
		ui.line_groupID->setText(QString::number(newGrpID));
		ui.line_path->setText(QString::fromStdString(path));

		img1.image_preview = image.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

		QPixmap pixmap2;
		pixmap2 = pixmap2.fromImage(image);

		QGraphicsScene* scene = new QGraphicsScene();
		scene->addPixmap(pixmap2.scaled(150, 150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
		ui.graphicsView->setScene(scene);
		ui.graphicsView->show();
		

	}
	else if (broth == 2) {

	}
	else if (broth == 3) {

	}
	else if (broth == 4) {

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
	group.locality = ui.line_locality->text().toStdString();
	group.siderophore = ui.checkBox_siderophore->isChecked();
	group.spore_color = ui.line_spore_color->text().toStdString();


	img1.image_id = ui.line_ID->text().toInt();
	img1.date = ui.line_timestamp->text().toStdString();
	img1.imagesize = ui.line_imgSize->text().toDouble();
	img1.resolution_x = ui.line_resolution_x->text().toDouble();
	img1.resolution_y = ui.line_resolution_y->text().toDouble();
	img1.broth_id = ui.line_brothID->text().toInt();
	img1.group_id = ui.line_groupID->text().toInt();
	img1.filePath = ui.line_path->text().toStdString();

	img2.image_id = ui.line_ID_2->text().toInt();
	img2.date = ui.line_timestamp_2->text().toStdString();
	img2.imagesize = ui.line_imgSize_2->text().toDouble();
	img2.resolution_x = ui.line_resolution_x_2->text().toDouble();
	img2.resolution_y = ui.line_resolution_y_2->text().toDouble();
	img2.broth_id = ui.line_brothID_2->text().toInt();
	img2.group_id = ui.line_groupID_2->text().toInt();
	img2.filePath = ui.line_path_2->text().toStdString();

	img3.image_id = ui.line_ID_3->text().toInt();
	img3.date = ui.line_timestamp_3->text().toStdString();
	img3.imagesize = ui.line_imgSize_3->text().toDouble();
	img3.resolution_x = ui.line_resolution_x_3->text().toDouble();
	img3.resolution_y = ui.line_resolution_y_3->text().toDouble();
	img3.broth_id = ui.line_brothID_3->text().toInt();
	img3.group_id = ui.line_groupID_3->text().toInt();
	img3.filePath = ui.line_path_3->text().toStdString();

	img4.image_id = ui.line_ID_4->text().toInt();
	img4.date = ui.line_timestamp_4->text().toStdString();
	img4.imagesize = ui.line_imgSize_4->text().toDouble();
	img4.resolution_x = ui.line_resolution_x_4->text().toDouble();
	img4.resolution_y = ui.line_resolution_y_4->text().toDouble();
	img4.broth_id = ui.line_brothID_4->text().toInt();
	img4.group_id = ui.line_groupID_4->text().toInt();
	img4.filePath = ui.line_path_4->text().toStdString();

	if (dbcon2->addGroup(group) && dbcon2->addImage2(img1) && dbcon2->addImage2(img2) && dbcon2->addImage2(img3) && dbcon2->addImage2(img4)) {
		ui.label_out->setText("successfully created Group and saved Images to DB.");
	}
	else {
		ui.label_out->setText("failed to save Images in DB.");
	}
}
