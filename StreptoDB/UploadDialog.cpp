#include "UploadDialog.h"

using namespace std;



uploadDialog::uploadDialog(QDialog* parent) : QDialog(parent)
{
	ui.setupUi(this);
	grpID = 1;
	//ui.label -> setText("blaa");
}


void uploadDialog::openFile() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());

	if (!fileName.isEmpty())
	{
		uploadDialog::dragOpenFile(fileName);
	}


	//ui.label->setText(fileName);
	//delete(&fileName);
}


//Collects the user inputs and calls DBController::addImage(Image);
void uploadDialog::insertIntoDB() {
	DBController *dbcon2 = new DBController();
	img.image_id = ui.lineEdit_image_id->text().toInt();
	img.date = ui.lineEdit_timestamp->text().toStdString();
	img.imagesize = ui.lineEdit_imagesize->text().toDouble();
	img.resolution_x = ui.lineEdit_resolution_x->text().toDouble();
	img.resolution_y = ui.lineEdit_resolution_y->text().toDouble();
	img.broth_id = atoi(ui.comboBox_broth->currentText().toStdString().substr(ui.comboBox_broth->currentText().toStdString().find("-") + 1).c_str());
	img.group_id = atoi(ui.comboBox_group->currentText().toStdString().substr(ui.comboBox_group->currentText().toStdString().find("-") + 1).c_str());
	//ui.label_test->setText(QString::number(atoi(ui.comboBox_broth->currentText().toStdString().substr(ui.comboBox_broth->currentText().toStdString().find("-")+1).c_str())));
	img.filePath = ui.line_path->text().toStdString();

	if (dbcon2->addImage2(img)) {
		ui.label_test->setText("successfully saved Image to DB.");
	}
	else {
		ui.label_test->setText("ups, something went wrong :(");
	}
}



void uploadDialog::dragOpenFile(QString fileName) {
	QImage image(fileName);

		if (image.isNull())
		{
			QMessageBox::information(this, "Image Viewer", "Error Displaying image");
			return;
		}

		img.image_preview = image.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

		QPixmap pixmap2;
		pixmap2 = pixmap2.fromImage(image);

		QGraphicsScene* scene = new QGraphicsScene();
		scene->addPixmap(pixmap2.scaled(150, 150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
		ui.graphicsView->setScene(scene);
		ui.graphicsView->show();

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

			ui.lineEdit_image_id->setText(QString::number(id + 1));
			ui.lineEdit_timestamp->setText(buffer2);
			ui.lineEdit_imagesize->setText("auto fill");
			ui.lineEdit_resolution_x->setText(QString::number(image.width()));
			ui.lineEdit_resolution_y->setText(QString::number(image.height()));

			ui.comboBox_broth->clear();
			vector<Broth> vbroth = dbcon2->getBroth("NOT NULL");
			int temp = 0;
			for (int g = 0; g < vbroth.size(); g++) {
				ui.comboBox_broth->addItem(QString::fromStdString(vbroth[g].name + "\t   -" + std::to_string(vbroth[g].broth_id)));
				if (fileName.toStdString().find(vbroth[g].name, fileName.size() - 10) != string::npos) {
					temp = g;
				}
			}
			ui.comboBox_broth->setCurrentIndex(temp);

			ui.comboBox_group->clear();
			vector<Group> vGroup = dbcon2->getGroup("NOT NULL");
			for (int g = 0; g < vGroup.size(); g++) {
				ui.comboBox_group->addItem(QString::fromStdString(vGroup[g].intern_id + "\t   -" + std::to_string(vGroup[g].group_id)));
				
			}
			ui.comboBox_group->setCurrentIndex(grpID-1);

			ui.line_path->setText(fileName);
	

}
