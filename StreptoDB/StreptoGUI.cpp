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



//Todo comment
StreptoGUI::StreptoGUI(QMainWindow*parent)	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ui.label -> setText("blaa");
}



//Todo comment
void StreptoGUI::uploadPic() {
	uploadDialog* f = new uploadDialog();
	f->show();

}



//Todo comment
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



//Todo comment
void StreptoGUI::fillTable(vector<Image> result){
	
	ui.tableWidget->setColumnCount(4);
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->setColumnWidth(0, 162);
	ui.tableWidget->setColumnWidth(1, 162);
	ui.tableWidget->setColumnWidth(2, 162);
	ui.tableWidget->setColumnWidth(3, 162);
	//ui.tableWidget->setShowGrid(false);
	//->setStyleSheet("QTableView {selection-background-color: red;}");
	//->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	ui.tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("ISP2"));
	ui.tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("GN"));
	ui.tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("NCBMM"));
	ui.tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("SFM"));

	//count unique Groups
	vector<int> group;
	bool isIn = false;
	for (int i = 0; i < result.size(); i++) {
		isIn = false;
		for (int u = 0; u < group.size(); u++) {
			if (group[u] == result[i].group_id) {
				isIn = true;
			}
		}
		if (!isIn) {
			group.push_back(result[i].group_id);
		}
	}

	//todo comment
	ui.tableWidget->setRowCount(group.size());

	for (int z = 0; z < group.size(); z++) {
		ui.tableWidget->setRowHeight(z, 100);
		for (int x = 0; x < result.size(); x++) {
			if(group[z] == result[x].group_id){
				QPixmap pixmap;
				QTableWidgetItem* twi = new QTableWidgetItem();
				//pixmap.loadFromData(result[0].image_preview);
				pixmap = pixmap.fromImage(result[x].image_preview);
				twi->setData(Qt::DecorationRole, pixmap.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
				ui.tableWidget->setItem(z, result[x].broth_id-1, twi);
				ui.label->setText(ui.label->text() + " / " + QString::number(result[x].broth_id));
			}
		}
	}

	
	//QPixmap pixmap2;
	//pixmap2 = pixmap2.fromImage(result[1].image_preview);
	//QTableWidgetItem* twi2 = new QTableWidgetItem();
	//twi2->setData(Qt::DecorationRole, pixmap2.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));




	//ui.tableWidget->setItem(0, 0, twi);
	//ui.tableWidget->setItem(0, 1, twi2);
	//ui.tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(result[0].image_id)));
	//ui.tableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(result[0].date)));
	//ui.tableWidget->setItem(0, 3, new QTableWidgetItem(QString::fromStdString(to_string(result[0].imagesize))));
	//ui.tableWidget->setItem(0, 4, new QTableWidgetItem(QString::fromStdString(to_string(result[0].resolution))));
}