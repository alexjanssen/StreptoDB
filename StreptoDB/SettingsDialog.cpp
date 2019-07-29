#include "SettingsDialog.h"
#include <QtWidgets\QFileDialog>
#include <QtWidgets\QMessageBox>
#include <QHeaderView>
#include <fstream>
#include <string>
//#include <sqlite/sqlite3.h> 


using namespace std;



settingsDialog::settingsDialog(QDialog* parent) : QDialog(parent)
{
	ui.setupUi(this);
	//ui.label -> setText("blaa");
}


void settingsDialog::selectPath() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());

	if (!fileName.isEmpty())
	{

		if (fileName.isNull())
		{
			QMessageBox::information(this, "Image Viewer", "Error Displaying image");
			return;
		}



		ui.lineEdit_path->setText(fileName);
	}


	//delete(&fileName);
}


//ToDo
void settingsDialog::saveSettings() {
	ui.label->setText("successfully saved Settings.");
}
