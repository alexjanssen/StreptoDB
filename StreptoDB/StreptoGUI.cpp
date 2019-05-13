#include "StreptoGUI.h"
#include <QtWidgets\QFileDialog>
#include <QtWidgets\QMessageBox>
#include <QtWidgets\QGraphicsPixmapItem>
//#include <string>
//#include <sqlite/sqlite3.h> 


using namespace std;


StreptoGUI::StreptoGUI(QMainWindow*parent)	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ui.label -> setText("blaa");
}

void StreptoGUI::test() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());

	if (!fileName.isEmpty())
	{
		QImage image(fileName);

		if (image.isNull())
		{
			QMessageBox::information(this, "Image Viewer", "Error Displaying image");
			return;
		}

		QPixmap pixmap(fileName);
		QGraphicsScene* scene = new QGraphicsScene();
		scene->addPixmap(pixmap.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
		
		ui.graphicsView->setScene(scene);
		ui.graphicsView->show();

		//delete(&pixmap);
		//delete(&scene);
		//delete(&image);
		
	}


	ui.label_3->setText(fileName);
	//delete(&fileName);
}


void StreptoGUI::test2() {
	//####################################################
	
	DBController *dbcon = new DBController();
	
	vector<Isolat> result2;
	result2 = dbcon->testCon();
	if (result2.size() == 0) {
		ui.label_4->setText("Can't open database.");
	}
	else {
		ui.label_4->setText("Opened database successfully.");
		ui.label_3->setText(QString::fromStdString(result2[0].name));
	}
	//####################################################

}