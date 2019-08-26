#include "SettingsDialog.h"
#include <QtWidgets\QFileDialog>
#include <QtWidgets\QMessageBox>
#include <QHeaderView>
#include <fstream>
#include <string>
#include <algorithm>
//#include <sqlite/sqlite3.h> 


using namespace std;



settingsDialog::settingsDialog(QDialog* parent) : QDialog(parent)
{
	ui.setupUi(this);
	ui.label -> setText("loading Settings...");
	settingsDialog::loadSettings();
}


void settingsDialog::loadSettings() {
	string line;
	ifstream myfile("../StreptoDB/Settings/settings.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.find("path:") != std::string::npos) {
				line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
				line = line.substr(line.find("path:")+5);
				ui.lineEdit_path->setText(QString::fromStdString(line));
			}
			else if (line.find("filter:") != std::string::npos) {
				line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
				line = line.substr(line.find("filter:")+7);
				ui.lineEdit_filt->setText(QString::fromStdString(line));
			}
			//ui.label->setText(QString::fromStdString(line) + "\n");
		}
		myfile.close();
		ui.label->setText("Settings loaded...");
	}else ui.label->setText("Unable to open Settings-File.");
}




void settingsDialog::selectPath() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());
	string path;

	if (!fileName.isEmpty())
	{

		if (fileName.isNull())
		{
			QMessageBox::information(this, "Image Viewer", "Error Displaying image");
			return;
		}

		path = fileName.toStdString();
		path = path.substr(0, path.rfind("/"));
		path = path.substr(0, path.rfind("/"));
		ui.lineEdit_path->setText(QString::fromStdString(path));
	}


	//delete(&fileName);
}


//ToDo
void settingsDialog::saveSettings() {
		
	if (remove("../StreptoDB/Settings/settings.txt") != 0)
		ui.label->setText("Error deleting file");
	else
		ui.label->setText("File successfully deleted");


	//fstream fs("../StreptoDB/Settings/settings.txt");
	std::ofstream outfile("../StreptoDB/Settings/settings.txt");


	outfile << "path:\t\t" + ui.lineEdit_path->text().toStdString();
	outfile << "\nfilter:\t\t" + ui.lineEdit_filt->text().toStdString();

	outfile.close();
	ui.label->setText("successfully saved new Settings.");
}
