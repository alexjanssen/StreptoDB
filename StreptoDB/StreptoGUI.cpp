#include "StreptoGUI.h"

//#include <string>
//#include <sqlite/sqlite3.h> 


using namespace std; 



//Todo comment
StreptoGUI::StreptoGUI(QMainWindow*parent)	: QMainWindow(parent)
{
	setAcceptDrops(true);	//needed for drag & drop
	ui.setupUi(this);
	StreptoGUI::loadSettings();
	//ui.label -> setText("blaa");
}



//reading settings from settings.txt
void StreptoGUI::loadSettings() {
	string line;
	ifstream myfile("../StreptoDB/Settings/settings.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.find("path:") != std::string::npos) {
				line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
				line = line.substr(line.find("path:") + 5);
				globPath = line;
			}
			else if (line.find("filter:") != std::string::npos) {
				line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
				line = line.substr(line.find("filter:") + 7);
				ui.line_filter->setText(QString::fromStdString(line));
			}
			//ui.label->setText(QString::fromStdString(line) + "\n");
		}
		myfile.close();
		ui.label->setText("Settings loaded...");
	}
	else ui.label->setText("Unable to open Settings-File.");
}



//Todo comment
void StreptoGUI::uploadPic() {
	uploadDialog* f = new uploadDialog();
	if (!ui.line_groupID_group->text().isEmpty()) {
		f->grpID = ui.line_groupID_group->text().toInt();
	}
	
	f->show();

}


//Todo comment
void StreptoGUI::loadDB() {
	//####################################################
	
	//DBController *dbcon = new DBController();
	QString temp = ui.line_filter->text();
	StreptoGUI::loadSettings();
	ui.line_filter->setText(temp);
	vector<Image> result;
	result = dbcon->getImages(ui.line_filter->text().toStdString());
	resultGlob = dbcon->getImages("%");
	if (result.size() == 0) {
		ui.label_4->setText("Can't open database.");
	}
	else {
		ui.label_4->setText("Opened database successfully.");
		fillTable(result);
		//resultGlob.clear();
		//resultGlob = result;
		result.clear();
	}
	//####################################################
}


//is called when clicking on a QtableWidgetItem in the QTableWidget
//and fills the right side of the gui with Details from the Image selected
void StreptoGUI::itemSelected(int x, int y)
{	//first check if selected item exists
	if (ui.tableWidget->item(x, y) ){ 
		selX = x;
		selY = y;
		int imgID = atoi(ui.tableWidget->item(x, y)->text().toStdString().c_str());
		//search for item in global result vector with imageID
		for (int i = 0; i < resultGlob.size(); i++) {
			//if found, set graphicsView with image
			if (resultGlob[i].image_id == imgID) {
				QPixmap pixmap2;
				//load pic with filePath from Settings:
				string newPath = resultGlob[i].filePath;
				string temp = newPath.substr(0, newPath.find_last_of("/"));
				newPath = resultGlob[i].filePath.substr(temp.find_last_of("/"));
				newPath = globPath + newPath;
				ui.label_3->setText(QString::fromStdString(newPath));


				QImage image(QString::fromStdString(newPath));
				pixmap2 = pixmap2.fromImage(image);

				QGraphicsScene* scene = new QGraphicsScene();
				scene->addPixmap(pixmap2.scaled(374, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
				ui.graphicsView->setScene(scene);
				ui.graphicsView->show();
				//fill image Parameters
				ui.line_ID->setText(QString::number(resultGlob[i].image_id));
				ui.line_timestamp->setText(QString::fromStdString(resultGlob[i].date));
				ui.line_imgSize->setText(QString::number(resultGlob[i].imagesize));
				ui.line_resolution_x->setText(QString::number(resultGlob[i].resolution_x));
				ui.line_resolution_y->setText(QString::number(resultGlob[i].resolution_y));

				//Fill up the Broth combobox and set Broth
				ui.comboBox_broth->clear();
				vector<Broth> vbroth = dbcon->getBroth("NOT NULL");
				int temp2 = 0;
				for (int g = 0; g < vbroth.size(); g++) {
					ui.comboBox_broth->addItem(QString::fromStdString(vbroth[g].name + "\t   -" + std::to_string(vbroth[g].broth_id)));
					if (vbroth[g].broth_id == resultGlob[i].broth_id) {
						temp2 = g;
					}
				}
				ui.comboBox_broth->setCurrentIndex(temp2);
				
				//ui.line_brothID->setText(QString::number(resultGlob[i].broth_id));
				//ui.line_groupID->setText(QString::number(resultGlob[i].group_id));
				ui.line_path->setText(QString::fromStdString(resultGlob[i].filePath));
				ui.line_scale->setText(QString::number(resultGlob[i].scale, 'd', 1));
				//fill group Parameters
				Group grp = dbcon->getGroup("=" + std::to_string(resultGlob[i].group_id))[0];
				ui.line_groupID_group->setText(QString::number(grp.group_id));
				ui.line_internID->setText(QString::fromStdString(grp.intern_id));
				ui.line_timestamp_group->setText(QString::fromStdString(grp.date));
				ui.line_scientific->setText(QString::fromStdString(grp.sci_name));
				ui.line_genome->setText(QString::fromStdString(grp.genome_lnk));
				ui.line_locality->setText(QString::number(grp.latitude));
				ui.line_locality_2->setText(QString::number(grp.longitude));
				ui.line_spore_color->setText(QString::fromStdString(grp.spore_color));
				ui.checkBox_siderophore->setChecked(grp.siderophore);

				//fill Strain-Inhibition
				ui.line_inhibit_internID->setText(QString::fromStdString(grp.intern_id));
				ui.line_inhibit_broth->setText(QString::fromStdString(dbcon->getBroth("=" + std::to_string(resultGlob[i].broth_id))[0].name));
				vector<TestStrain> ts = dbcon->getTestStrains();
				ui.comboBox_testStrain->clear();
				for (int g = 0; g < ts.size(); g++) {
					ui.comboBox_testStrain->addItem(QString::fromStdString(ts[g].strain_name));
				}

				//vector<CalcedParams> result;
				//result = dbcon->getCalcedParams(resultGlob[i].image_id);
				fillTable2(dbcon->getCalcedParams(resultGlob[i].image_id));
				ui.label_12->setText(QString::number(dbcon->getCalcedParams(resultGlob[i].image_id).size()));
				fillTable3(dbcon->getInhibition(resultGlob[i].image_id));

			}
		}
		ui.label->setText("x: " + QString::number(x) + " | y: " + QString::number(y));
		column = y;
	}else {
		//Error message
		ui.label->setText("Selected item not found.");
		vector<Group> vGrp = dbcon->getGroup("NOT NULL");
		for (int k = 0; k < vGrp.size(); k++) {
			if (ui.tableWidget->verticalHeaderItem(x)->text().toStdString() == vGrp[k].intern_id) {
				//GROUP
				ui.line_groupID_group->setText(QString::number(vGrp[k].group_id));
				ui.line_internID->setText(QString::fromStdString(vGrp[k].intern_id));
				ui.line_timestamp_group->setText(QString::fromStdString(vGrp[k].date));
				ui.line_scientific->setText(QString::fromStdString(vGrp[k].sci_name));
				ui.line_genome->setText(QString::fromStdString(vGrp[k].genome_lnk));
				ui.line_locality->setText(QString::number(vGrp[k].latitude));
				ui.line_locality_2->setText(QString::number(vGrp[k].longitude));
				ui.line_spore_color->setText(QString::fromStdString(vGrp[k].spore_color));
				ui.checkBox_siderophore->setChecked(vGrp[k].siderophore);
				//IMAGE
				ui.line_ID->setText("");
				ui.line_timestamp->setText("");
				ui.line_imgSize->setText("");
				ui.line_resolution_x->setText("");
				ui.line_resolution_y->setText("");
				//ui.line_brothID->setText("");
				
				//ui.line_groupID->setText("");
				ui.line_path->setText("");
				ui.line_scale->setText("");

				vector<CalcedParams> what;
				vector<StrainInhibition> dubious_val;
				fillTable2(what);
				fillTable3(dubious_val);
			}
		}
	}
	
}


//Todo comment
void StreptoGUI::fillTable(vector<Image> result){
	ui.tableWidget->setRowCount(0);
	ui.tableWidget->setColumnCount(4);
	ui.tableWidget->verticalHeader()->setVisible(true);
	ui.tableWidget->verticalHeader()->setFixedWidth(50);
	ui.tableWidget->verticalHeader()->resizeSection(0, 50);
	ui.tableWidget->setColumnWidth(0, 175); //154
	ui.tableWidget->setColumnWidth(1, 175);
	ui.tableWidget->setColumnWidth(2, 175);
	ui.tableWidget->setColumnWidth(3, 175);
	
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

	//fills that vertical header with the group-name, yeah looks gross.
	ui.tableWidget->setRowCount(group.size());
	ui.label->setText("Groups found: "+ QString::number(group.size()));
	for (int z = 0; z < group.size(); z++) {
		ui.tableWidget->setRowHeight(z, 100);
		ui.tableWidget->setVerticalHeaderItem(z, new QTableWidgetItem(QString::fromStdString(dbcon->getGroup("=" + std::to_string(group[z]))[0].intern_id)));
		//ui.label->setText(ui.label->text() + QString::fromStdString(dbcon->getGroup("=" + std::to_string(group[z]))[0].intern_id) + " | ");
		for (int x = 0; x < result.size(); x++) {
			if(group[z] == result[x].group_id){
				QPixmap pixmap;
				QTableWidgetItem* twi = new QTableWidgetItem();
				//pixmap.loadFromData(result[0].image_preview);
				pixmap = pixmap.fromImage(result[x].image_preview);
				twi->setData(Qt::DecorationRole, pixmap.scaled(125, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
				twi->setText(QString::number(result[x].image_id));
				//Set Text color red, if parameters are missing
				try {
					dbcon->getCalcedParams(result[x].image_id).at(0).calc_id; 
				}
				catch (exception) {
					twi->setForeground(QBrush(QColor(255, 0, 0)));
				}
				
				ui.tableWidget->setItem(z, result[x].broth_id-1, twi);
				//ui.label->setText(ui.label->text() + " / " + QString::number(result[x].broth_id));
			}
		}
	}
	group.clear();
}


//Todo comment
void StreptoGUI::fillTable2(vector<CalcedParams> result) {
	ui.tableWidget_2->setColumnCount(5);
	ui.tableWidget_2->verticalHeader()->setVisible(false);
	ui.tableWidget_2->setColumnWidth(0, 100);
	ui.tableWidget_2->setColumnWidth(1, 100);
	ui.tableWidget_2->setColumnWidth(2, 100);
	ui.tableWidget_2->setColumnWidth(3, 100);
	ui.tableWidget_2->setColumnWidth(4, 100);

	ui.tableWidget_2->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
	ui.tableWidget_2->setHorizontalHeaderItem(1, new QTableWidgetItem("Image-ID"));
	ui.tableWidget_2->setHorizontalHeaderItem(2, new QTableWidgetItem("Classf-ID"));
	ui.tableWidget_2->setHorizontalHeaderItem(3, new QTableWidgetItem("Value"));
	ui.tableWidget_2->setHorizontalHeaderItem(4, new QTableWidgetItem("Timestamp"));

	ui.tableWidget_2->setRowCount(result.size());
	for (int i = 0; i < result.size(); i++) {
		ui.tableWidget_2->setRowHeight(i, 30);
		ui.tableWidget_2->setItem(i, 0, new QTableWidgetItem(QString::number(result[i].calc_id)));
		ui.tableWidget_2->setItem(i, 1, new QTableWidgetItem(QString::number(result[i].image_id)));
		ui.tableWidget_2->setItem(i, 2, new QTableWidgetItem(QString::number(result[i].class_id)));
		ui.tableWidget_2->setItem(i, 3, new QTableWidgetItem(QString::number(result[i].value)));
		ui.tableWidget_2->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(result[i].timestamp)));
	}
	ui.label_12->setText(QString::number(result.size()));

}


//Todo comment
void StreptoGUI::fillTable3(vector<StrainInhibition> result) {
	ui.tableWidget_3->setColumnCount(5);
	ui.tableWidget_3->verticalHeader()->setVisible(false);
	ui.tableWidget_3->setColumnWidth(0, 100);
	ui.tableWidget_3->setColumnWidth(1, 100);
	ui.tableWidget_3->setColumnWidth(2, 100);
	ui.tableWidget_3->setColumnWidth(3, 100);
	ui.tableWidget_3->setColumnWidth(4, 100);

	ui.tableWidget_3->setHorizontalHeaderItem(0, new QTableWidgetItem("SI-ID"));
	ui.tableWidget_3->setHorizontalHeaderItem(1, new QTableWidgetItem("ID-Intern"));
	ui.tableWidget_3->setHorizontalHeaderItem(2, new QTableWidgetItem("Broth"));
	ui.tableWidget_3->setHorizontalHeaderItem(3, new QTableWidgetItem("Test-Strain"));
	ui.tableWidget_3->setHorizontalHeaderItem(4, new QTableWidgetItem("Inhibition"));
	//ui.tableWidget_3->setHorizontalHeaderItem(4, new QTableWidgetItem("Timestamp"));

	ui.tableWidget_3->setRowCount(result.size());
	for (int i = 0; i < result.size(); i++) {
		ui.tableWidget_3->setRowHeight(i, 30);
		ui.tableWidget_3->setItem(i, 0, new QTableWidgetItem(QString::number(result[i].id)));
		ui.tableWidget_3->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(result[i].id_intern)));
		ui.tableWidget_3->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(result[i].broth_name)));
		ui.tableWidget_3->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(result[i].strain_name)));
		ui.tableWidget_3->setItem(i, 4, new QTableWidgetItem(QString::number(result[i].inhibition)));
	}
	//ui.label_12->setText(QString::number(result.size()));

}


//for testing Calculations
void StreptoGUI::testCalc() {
	CalcedParams cp = CalcedParams();
	cp.image_id = ui.line_ID->text().toInt();
	cp.timestamp = ui.line_timestamp->text().toStdString();

	//get filePath from Settings:
	string newPath = ui.line_path->text().toStdString();
	string temp = newPath.substr(0, newPath.find_last_of("/"));
	newPath = ui.line_path->text().toStdString().substr(temp.find_last_of("/"));
	newPath = globPath + newPath;

	//delete all calculated Parameters for selected image
	if (!dbcon->deleteCalculatedParameters(cp.image_id)) {}
	else { ui.label_28->setText("failed to delete image calculations."); }

	//Calculations and all openCV functions are in CVController, also loading the file
	//lets calculate and add the paramaters one by one:
	ui.label_28->setText("saving... everything ok so far.");
	//Start with Scale:
	try {
		cp.calc_id = dbcon->getMaxCalcParamID() + 1;
	}
	catch (exception) { cp.calc_id = 1; };
	bool fail = false;

	cp.class_id = 1; //scale()
	int scaleLength = cvcon->extractScale(newPath);
	double scale = ui.line_scale->text().toDouble() / scaleLength;	//size of one Pixel in mm; not square millimeter!
	cp.value = scale;
	if(ui.line_scale->text().toDouble() == 0){ ui.label_28->setText("Invalid Scale!"); fail = true; }
	
	if (!dbcon->addCalcedParams(cp)) {}
	else { ui.label_28->setText("Scale failed to save."); fail = true; }
	
	//Then calculate the segmentations:
	cvcon->segmentation(newPath, ui.spinBox_TH->text().toDouble() / 100, ui.spinBox_BG->text().toDouble() / 100, ui.spinBox_FG->text().toDouble(), false);

	//and calculate the foreground-size:
	cp.calc_id++;
	cp.class_id = 2;	//size_foreground()
	double area = cvcon->foregroundSize(scale);
	cp.value = area;
	if (!dbcon->addCalcedParams(cp)) {}
	else {ui.label_28->setText("size_foreground failed to save."); fail = true;
	}

	//and calculate the fore-/back-ground colours:
	cp.calc_id++;
	cp.class_id = 3;	//foreground_channel_0()
	cp.value = cvcon->meanFG(0);
	if (!dbcon->addCalcedParams(cp)) {}
	else { ui.label_28->setText("foreground_channel_0 failed to save."); fail = true;
	}
	cp.calc_id++;
	cp.class_id = 4;	//foreground_channel_1()
	cp.value = cvcon->meanFG(1);
	if (!dbcon->addCalcedParams(cp)) {}
	else { ui.label_28->setText("foreground_channel_1 failed to save."); fail = true;
	}
	cp.calc_id++;
	cp.class_id = 5;	//foreground_channel_2()
	cp.value = cvcon->meanFG(2);
	if (!dbcon->addCalcedParams(cp)) {}
	else { ui.label_28->setText("foreground_channel_2 failed to save."); fail = true;
	}
	cp.calc_id++;
	cp.class_id = 6;	//background_channel_0()
	cp.value = cvcon->meanBG(0);
	if (!dbcon->addCalcedParams(cp)) {}
	else { ui.label_28->setText("background_channel_0 failed to save."); fail = true;
	}
	cp.calc_id++;
	cp.class_id = 7;	//background_channel_1()
	cp.value = cvcon->meanBG(1);
	if (!dbcon->addCalcedParams(cp)) {}
	else { ui.label_28->setText("background_channel_1 failed to save."); fail = true;
	}
	cp.calc_id++;
	cp.class_id = 8;	//background_channel_2()
	cp.value = cvcon->meanBG(2);
	if (!dbcon->addCalcedParams(cp)) {}
	else { ui.label_28->setText("background_channel_2 failed to save."); fail = true;
	}
	cp.calc_id++;
	cp.class_id = 9;	//circularity
	cp.value = cvcon->circFact(scale,area);
	if (!dbcon->addCalcedParams(cp)) {}
	else { ui.label_28->setText("circularity failed to save."); fail = true;
	}
	itemSelected(selX, selY);
	//cvcon->foregroundExtraction(newPath);
	//cvcon->histo(newPath);
	if (fail==true) { 
		dbcon->deleteCalculatedParameters(cp.image_id); 
		//ui.label_28->setText("");
	}
	
}

//for testing Calculations
void StreptoGUI::showSegmentation() {
	//get filePath from Settings:
	string newPath = ui.line_path->text().toStdString();
	string temp = newPath.substr(0, newPath.find_last_of("/"));
	newPath = ui.line_path->text().toStdString().substr(temp.find_last_of("/"));
	newPath = globPath + newPath;

	//cvcon->histo(newPath);
	cvcon->segmentation(newPath, ui.spinBox_TH->text().toDouble()/100, ui.spinBox_BG->text().toDouble()/100, ui.spinBox_FG->text().toDouble(),true);
}



//for adding Strain-Inhibitions to DB
void StreptoGUI::addInhibition() {
	vector<TestStrain> ts = dbcon->getTestStrains();
	int strainID = 0;
	int maxID = dbcon->getMaxInhibitionID() + 1;
	for (int i = 0; i < ts.size(); i++) {
		if (ui.comboBox_testStrain->currentText().toStdString() == ts[i].strain_name) {
			strainID = ts[i].strain_id;
		}
	}

	if (strainID != 0) {
		if (!dbcon->addStrainInhibition(maxID,ui.line_ID->text().toInt(), strainID, atoi(ui.comboBox_broth->currentText().toStdString().substr(ui.comboBox_broth->currentText().toStdString().find("-") + 1).c_str()), ui.checkBox_inhibition->isChecked())) {
			ui.label_28->setText("Success!");
			itemSelected(selX, selY);
		}
		else {
			ui.label_28->setText("Fail!");
		}
	}
	else {
		ui.label_28->setText("Fail! \nStrainID = 0)");
	}
}


//is called when clicking on a QtableWidgetItem in the QTableWidget
//and fills the right side of the gui with Details from the Image selected
void StreptoGUI::paramSelected(int x, int y)
{	//first check if selected item exists
	if (ui.tableWidget_2->item(x, y)) {
		int imgID = ui.line_ID->text().toInt();

		vector<Compare> comp = dbcon->getCompare(ui.tableWidget_2->item(x, 3)->text().toDouble(), atoi(ui.comboBox_broth->currentText().toStdString().substr(ui.comboBox_broth->currentText().toStdString().find("-") + 1).c_str()), ui.tableWidget_2->item(x, 2)->text().toInt());
		//vector<Compare> comp = dbcon->getCompare(42, 1, 1);

		ui.tableWidget_4->setRowCount(1);
		ui.tableWidget_4->setColumnCount(comp.size());
		//ui.tableWidget_3->verticalHeader()->setVisible(false);
		//ui.tableWidget_3->horizontalHeader()->setVisible(false);
		ui.tableWidget_4->setRowHeight(0, 100);
		//ui.tableWidget_3->setVerticalHeaderItem(0, new QTableWidgetItem(QString::fromStdString(dbcon->getGroup(ui.line_groupID->text().toInt()).intern_id)));
		ui.tableWidget_4->setVerticalHeaderItem(0, new QTableWidgetItem(ui.tableWidget->horizontalHeaderItem(column)->text()));
		for (int i = 0; i < comp.size(); i++) {
			ui.tableWidget_4->setColumnWidth(i, 175);
			for (int u = 0; u < resultGlob.size(); u++) {
				//if found, set graphicsView with image
				if (resultGlob[u].image_id == comp[i].image_id) {
					QPixmap pixmap;
					QTableWidgetItem* twi = new QTableWidgetItem();
					//pixmap.loadFromData(result[0].image_preview);
					pixmap = pixmap.fromImage(resultGlob[u].image_preview);
					twi->setData(Qt::DecorationRole, pixmap.scaled(125, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
					twi->setText(QString::number(resultGlob[u].image_id)+"\n"+ QString::number(cv::sqrt(comp[i].diff), 'f', 2));
					
					ui.tableWidget_4->setItem(0, i, twi);

					//ui.tableWidget_3->setHorizontalHeaderItem(i, new QTableWidgetItem("ISP2"));
					ui.tableWidget_4->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(dbcon->getGroup("=" + std::to_string(resultGlob[u].group_id))[0].intern_id)));

				}

			}
		}
		ui.label_17->setText("Compare result count: " + QString::number(comp.size()));
	}
	else {
		//Error message
		ui.label_17->setText("Selected Param not found.");
	}

}


//Save Image Parameters to DB
void StreptoGUI::imgSave(){
	Image img2 = Image();
	img2.image_id = ui.line_ID->text().toInt();
	img2.date = ui.line_timestamp->text().toStdString();
	img2.imagesize = ui.line_imgSize->text().toDouble();
	img2.resolution_x = ui.line_resolution_x->text().toDouble();
	img2.resolution_y = ui.line_resolution_y->text().toDouble();
	img2.broth_id = atoi(ui.comboBox_broth->currentText().toStdString().substr(ui.comboBox_broth->currentText().toStdString().find("-") + 1).c_str());
	img2.group_id = ui.line_groupID_group->text().toInt();
	img2.filePath = ui.line_path->text().toStdString();
	img2.scale = ui.line_scale->text().toDouble();

	if (!dbcon->updateImage(img2)) {
		ui.label_3->setText("successfully updated Image.");
		StreptoGUI::loadDB();
	}
	else {
		ui.label_3->setText("failed to update Image.");
	}
}


//Arbeit Arbeit
void StreptoGUI::imgDelete(){
	//ui.label_28->setText(QString::number(dbcon->getImages(ui.line_internID->text().toStdString()).size()));
	if (dbcon->getImages(ui.line_internID->text().toStdString()).size() == 1) {
		grpDelete();
	}
	else {

		if (dbcon->deleteImage(ui.line_ID->text().toInt())) {
			ui.label_3->setText("successfully deleted Image.");
			StreptoGUI::loadDB();
		}
		else {
			ui.label_3->setText("failed to delete Image.");
		}
	}
}

void StreptoGUI::grpSave(){
	Group grp2 = Group();
	grp2.group_id = ui.line_groupID_group->text().toInt();
	grp2.intern_id = ui.line_internID->text().toStdString();
	grp2.date = ui.line_timestamp_group->text().toStdString();
	grp2.sci_name = ui.line_scientific->text().toStdString();
	grp2.genome_lnk = ui.line_genome->text().toStdString();
	grp2.latitude = ui.line_locality->text().toDouble();
	grp2.longitude = ui.line_locality_2->text().toDouble();
	grp2.spore_color = ui.line_spore_color->text().toStdString();
	grp2.siderophore = ui.checkBox_siderophore->isChecked();

	if (!dbcon->updateGroup(grp2)) {
		ui.label_3->setText("successfully updated Group.");
		StreptoGUI::loadDB();
	}
	else {
		ui.label_3->setText("failed to update Group.");
	}
}

void StreptoGUI::grpDelete(){
	vector<int> imgs;
	for (int i = 0; i < resultGlob.size(); i++) {
		if (resultGlob[i].group_id == ui.line_groupID_group->text().toInt()) {
			imgs.push_back(resultGlob[i].image_id);
		}
	}
	if (dbcon->deleteGroup(ui.line_groupID_group->text().toInt(), imgs)) {
		ui.label_3->setText("successfully deleted Group.");
		StreptoGUI::loadDB();
	}
	else {
		ui.label_3->setText("failed to delete Group.");
	}
}

void StreptoGUI::subtableDelete(){	
	if (ui.tabWidget->currentIndex() == 0) {	//Calculations
		//ui.label_12->setText(QString::number(ui.tableWidget_2->currentRow()));
		//ui.tableWidget_2->item(ui.tableWidget_2->currentRow(), 0)->text().toDouble();
		if (dbcon->deleteCalcedParam(ui.tableWidget_2->item(ui.tableWidget_2->currentRow(), 0)->text().toDouble())) {
			ui.label_3->setText("Successfully deleted entry in Calculations");
			itemSelected(selX,selY);

		}else { ui.label_3->setText("Failed to delete entry in Calculations"); }
	}
	else {	//Strain-Inhibition
		//ui.label_12->setText(QString::number(ui.tableWidget_3->currentRow()));
		if (dbcon->deleteStrainInhibition(ui.tableWidget_3->item(ui.tableWidget_3->currentRow(), 0)->text().toDouble())) {
			ui.label_3->setText("Successfully deleted entry in Strain-Inhibition");
			itemSelected(selX, selY);
		}
		else { ui.label_3->setText("Failed to delete entry in Strain-Inhibition"); }
	}
		//ui.tableWidget_2->currentRow();
}



//Todo
void StreptoGUI::compare(){
	//vector<Compare> comp = dbcon->getCompare(ui.line);

	//vector of imageIDs and brothIds, the images we want to compare to others
	//this vector is ordered by broth_id ascending
	vector<ImgBroth> imgBroth = dbcon->getImgBroth(ui.line_groupID_group->text().toInt());

	//next we need the calculated Parameters for each imageID in the vector above
	//DBController::getCalcedParams(int id)
	vector<CalcedParams> cpBroth1 = dbcon->getCalcedParams(imgBroth.at(0).img_id);
	vector<CalcedParams> cpBroth2 = dbcon->getCalcedParams(imgBroth.at(1).img_id);
	vector<CalcedParams> cpBroth3 = dbcon->getCalcedParams(imgBroth.at(2).img_id);
	vector<CalcedParams> cpBroth4 = dbcon->getCalcedParams(imgBroth.at(3).img_id);
	//now we want to compare each parameter in each broth vector with all the other groups
	//so we get 4 Lists with 9 Lists in them, each containing the image IDs and Differences to the given Parameter
	//if you are confused now, dont ask me. I dont get paid for this.
	vector<vector<Compare>> comBroth1;
	vector<vector<Compare>> comBroth2;
	vector<vector<Compare>> comBroth3;
	vector<vector<Compare>> comBroth4;
	for (int p = 2; p <= 9; p++) {
		comBroth1.push_back(dbcon->getCompare(cpBroth1.at(p-1).value,1,p));
	}
	for (int p = 2; p <= 9; p++) {
		comBroth2.push_back(dbcon->getCompare(cpBroth2.at(p - 1).value, 2, p));
	}
	for (int p = 2; p <= 9; p++) {
		comBroth3.push_back(dbcon->getCompare(cpBroth3.at(p - 1).value, 3, p));
	}
	for (int p = 2; p <= 9; p++) {
		comBroth4.push_back(dbcon->getCompare(cpBroth4.at(p - 1).value, 4, p));
	}

	//now we want the sum of the differences, but we want the differences to be treated equally,
	//we are no racists here and each difference deserves that.
	//So we iterate that till we get dizzy.
	//We determine the highest difference, and say thats 100% difference, thats our scale
	double maxDiff = 0;
		for (int i = 0; i < comBroth1.size(); i++) {       // loops through each row of vector
			for (int j = 0; j < comBroth1[i].size(); j++) { // loops through each element of each row 
				if (comBroth1[i][j].diff > maxDiff) {
					maxDiff = comBroth1[i][j].diff;
				}
			}
			//here we have maxDiff, now comes math, not even once
			for (int j = 0; j < comBroth1[i].size(); j++) { // loops through each element of each row 
				comBroth1[i][j].diff = comBroth1[i][j].diff / maxDiff * 100;
			}
			maxDiff = 0;
		}
	//-----------------
		for (int i = 0; i < comBroth2.size(); i++) {       // loops through each row of vector
			for (int j = 0; j < comBroth2[i].size(); j++) { // loops through each element of each row 
				if (comBroth2[i][j].diff > maxDiff) {
					maxDiff = comBroth2[i][j].diff;
				}
			}
			//here we have maxDiff, now comes math, not even once
			for (int j = 0; j < comBroth2[i].size(); j++) { // loops through each element of each row 
				comBroth2[i][j].diff = comBroth2[i][j].diff / maxDiff * 100;
			}
			maxDiff = 0;
		}
	//-------------------
		for (int i = 0; i < comBroth3.size(); i++) {       // loops through each row of vector
			for (int j = 0; j < comBroth3[i].size(); j++) { // loops through each element of each row 
				if (comBroth3[i][j].diff > maxDiff) {
					maxDiff = comBroth3[i][j].diff;
				}
			}
			//here we have maxDiff, now comes math, not even once
			for (int j = 0; j < comBroth3[i].size(); j++) { // loops through each element of each row 
				comBroth3[i][j].diff = comBroth3[i][j].diff / maxDiff * 100;
			}
			maxDiff = 0;
		}
	//-------------------
		for (int i = 0; i < comBroth4.size(); i++) {       // loops through each row of vector
			for (int j = 0; j < comBroth4[i].size(); j++) { // loops through each element of each row 
				if (comBroth4[i][j].diff > maxDiff) {
					maxDiff = comBroth4[i][j].diff;
				}
			}
			//here we have maxDiff, now comes math, not even once
			for (int j = 0; j < comBroth4[i].size(); j++) { // loops through each element of each row 
				comBroth4[i][j].diff = comBroth4[i][j].diff / maxDiff * 100;
			}
			maxDiff = 0;
		}

	//now back to the sum of the differences
	//we add up each difference for each imageID, so we need to find each imageID in all Lists.
	//We start with the first List, add up all differences and sort that. As result we get a single
	//List with the added Differences
	vector<Compare> sumOfDiff1;
	vector<Compare> sumOfDiff2;
	vector<Compare> sumOfDiff3;
	vector<Compare> sumOfDiff4;
	for (int i = 0; i < comBroth1[0].size(); i++) {			// loops through each element of the first vector
		sumOfDiff1.push_back(Compare());
		sumOfDiff1[i].image_id = comBroth1[0][i].image_id;	//take each id and find that id in each other vector
		for (int u = 0; u < comBroth1.size(); u++) {       // loops through each row of vector
			for (int j = 0; j < comBroth1[u].size(); j++) { // loops through each element of each row 
				if (sumOfDiff1[i].image_id == comBroth1[u][j].image_id) {
					sumOfDiff1[i].diff = sumOfDiff1[i].diff + comBroth1[u][j].diff;
				}
			}
		}
	}
	for (int i = 0; i < comBroth2[0].size(); i++) {			// loops through each element of the first vector
		sumOfDiff2.push_back(Compare());
		sumOfDiff2[i].image_id = comBroth2[0][i].image_id;	//take each id and find that id in each other vector
		for (int u = 0; u < comBroth2.size(); u++) {       // loops through each row of vector
			for (int j = 0; j < comBroth2[u].size(); j++) { // loops through each element of each row 
				if (sumOfDiff2[i].image_id == comBroth2[u][j].image_id) {
					sumOfDiff2[i].diff = sumOfDiff2[i].diff + comBroth2[u][j].diff;
				}
			}
		}
	}
	for (int i = 0; i < comBroth3[0].size(); i++) {			// loops through each element of the first vector
		sumOfDiff3.push_back(Compare());
		sumOfDiff3[i].image_id = comBroth3[0][i].image_id;	//take each id and find that id in each other vector
		for (int u = 0; u < comBroth3.size(); u++) {       // loops through each row of vector
			for (int j = 0; j < comBroth3[u].size(); j++) { // loops through each element of each row 
				if (sumOfDiff3[i].image_id == comBroth3[u][j].image_id) {
					sumOfDiff3[i].diff = sumOfDiff3[i].diff + comBroth3[u][j].diff;
				}
			}
		}
	}
	for (int i = 0; i < comBroth4[0].size(); i++) {			// loops through each element of the first vector
		sumOfDiff4.push_back(Compare());
		sumOfDiff4[i].image_id = comBroth4[0][i].image_id;	//take each id and find that id in each other vector
		for (int u = 0; u < comBroth4.size(); u++) {       // loops through each row of vector
			for (int j = 0; j < comBroth4[u].size(); j++) { // loops through each element of each row 
				if (sumOfDiff4[i].image_id == comBroth4[u][j].image_id) {
					sumOfDiff4[i].diff = sumOfDiff4[i].diff + comBroth4[u][j].diff;
				}
			}
		}
	}
	//Now we have a vector with the sum of the differences. Since we have 8 Parameter, 
	//we have to divide the result by 8. And Sort that list by the difference ascending.
	//Oh and we need the GroupID, since we want to compare the Groups
	for (int z = 0; z < sumOfDiff1.size(); z++) {
		sumOfDiff1[z].diff = sumOfDiff1[z].diff / 8;
		sumOfDiff1[z].grpID = dbcon->getGroupID(sumOfDiff1[z].image_id);
	}
	for (int z = 0; z < sumOfDiff2.size(); z++) {
		sumOfDiff2[z].diff = sumOfDiff2[z].diff / 8;
		sumOfDiff2[z].grpID = dbcon->getGroupID(sumOfDiff2[z].image_id);
	}
	for (int z = 0; z < sumOfDiff3.size(); z++) {
		sumOfDiff3[z].diff = sumOfDiff3[z].diff / 8;
		sumOfDiff3[z].grpID = dbcon->getGroupID(sumOfDiff3[z].image_id);
	}
	for (int z = 0; z < sumOfDiff4.size(); z++) {
		sumOfDiff4[z].diff = sumOfDiff4[z].diff / 8;
		sumOfDiff4[z].grpID = dbcon->getGroupID(sumOfDiff4[z].image_id);
	}

	//To compare the 4 different Broths, we calculate the median difference for each Group
	//and get the final List with the final sorting
	vector<Compare> finalList;
	for (int i = 0; i < sumOfDiff1.size(); i++) {			// loops through each element of the first vector
		finalList.push_back(Compare());
		finalList[i].grpID = sumOfDiff1[i].grpID;	//take each id and find that id in each other vector
		finalList[i].diff = sumOfDiff1[i].diff;

		for (int u = 0; u < sumOfDiff2.size(); u++) {
			if (finalList[i].grpID == sumOfDiff2[u].grpID) {
				finalList[i].diff = finalList[i].diff + sumOfDiff2[u].diff;
			}
		}
		for (int u = 0; u < sumOfDiff3.size(); u++) {
			if (finalList[i].grpID == sumOfDiff3[u].grpID) {
				finalList[i].diff = finalList[i].diff + sumOfDiff3[u].diff;
			}
		}
		for (int u = 0; u < sumOfDiff4.size(); u++) {
			if (finalList[i].grpID == sumOfDiff4[u].grpID) {
				finalList[i].diff = finalList[i].diff + sumOfDiff4[u].diff;
			}
		}
		finalList[i].diff = finalList[i].diff / 4;
	}
	//almost forgotten: sort the finalList ascending by diff
	vector<Compare> finalList_unsort = finalList;
	finalList.clear();
	Compare smallest;
	while( finalList_unsort.size() > 0) {
		smallest = finalList_unsort[0];
		int count = 0;
		for (int i1 = 0; i1 < finalList_unsort.size(); i1++) {
			if (finalList_unsort[i1].diff <= smallest.diff) {
				smallest = finalList_unsort[i1];
				count = i1;
			}
		}
		finalList.push_back(smallest);
		finalList_unsort.erase(finalList_unsort.begin() + count);
	}


	//Now we want to display our Results
	//lets take the vector resultGlob, and recycle that, yeah green programming lol.
	vector<Image> resultGlob_sorted;
	for(int h = 0; h < finalList.size();h++){
		for (int g = 0; g < resultGlob.size(); g++) {
			if (resultGlob[g].group_id == finalList[h].grpID) {
				resultGlob_sorted.push_back(resultGlob[g]);
			}
		}
	}
	StreptoGUI::fillTable(resultGlob_sorted);


	
	//And fill the bottom table with the calculated differences
	ui.tableWidget_4->setRowCount(4);
	ui.tableWidget_4->setColumnCount(finalList.size());
	//ui.tableWidget_3->verticalHeader()->setVisible(false);
	//ui.tableWidget_3->horizontalHeader()->setVisible(false);
	ui.tableWidget_4->setRowHeight(0, 25);
	ui.tableWidget_4->setRowHeight(1, 25);
	ui.tableWidget_4->setRowHeight(2, 25);
	ui.tableWidget_4->setRowHeight(3, 25);
	//ui.tableWidget_3->setVerticalHeaderItem(0, new QTableWidgetItem(QString::fromStdString(dbcon->getGroup(ui.line_groupID->text().toInt()).intern_id)));
	ui.tableWidget_4->setVerticalHeaderItem(0, new QTableWidgetItem(ui.tableWidget->horizontalHeaderItem(0)->text()));
	ui.tableWidget_4->setVerticalHeaderItem(1, new QTableWidgetItem(ui.tableWidget->horizontalHeaderItem(1)->text()));
	ui.tableWidget_4->setVerticalHeaderItem(2, new QTableWidgetItem(ui.tableWidget->horizontalHeaderItem(2)->text()));
	ui.tableWidget_4->setVerticalHeaderItem(3, new QTableWidgetItem(ui.tableWidget->horizontalHeaderItem(3)->text()));
	//QTableWidgetItem* twi0 = new QTableWidgetItem();
	//QTableWidgetItem* twi1 = new QTableWidgetItem();
	//QTableWidgetItem* twi2 = new QTableWidgetItem();
	//QTableWidgetItem* twi3 = new QTableWidgetItem();

	for (int i = 0; i < finalList.size(); i++) {
		//twi0->setText("0.00 %");
		//twi1->setText("0.00 %");
		//twi2->setText("0.00 %");
		//twi3->setText("0.00 %");
		ui.tableWidget_4->setColumnWidth(i, 100);
		ui.tableWidget_4->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(dbcon->getGroup("=" + std::to_string(finalList[i].grpID))[0].intern_id)));
		for (int s = 0; s < sumOfDiff1.size(); s++) {
			if (finalList[i].grpID == sumOfDiff1[s].grpID) {
				//twi0->setText(QString::number(sumOfDiff1[s].diff) + " %");
				ui.tableWidget_4->setItem(0, i, new QTableWidgetItem(QString::number(sumOfDiff1[s].diff,'f',2) + " %"));
			}
			if (finalList[i].grpID == sumOfDiff2[s].grpID) {
				//twi1->setText(QString::number(sumOfDiff2[s].diff) + " %");
				ui.tableWidget_4->setItem(1, i, new QTableWidgetItem(QString::number(sumOfDiff2[s].diff, 'f', 2) + " %"));
			}
			if (finalList[i].grpID == sumOfDiff3[s].grpID) {
				//twi2->setText(QString::number(sumOfDiff3[s].diff) + " %");
				ui.tableWidget_4->setItem(2, i, new QTableWidgetItem(QString::number(sumOfDiff3[s].diff, 'f', 2) + " %"));
			}
			if (finalList[i].grpID == sumOfDiff4[s].grpID) {
				//twi3->setText(QString::number(sumOfDiff4[s].diff) + " %");
				ui.tableWidget_4->setItem(3, i, new QTableWidgetItem(QString::number(sumOfDiff4[s].diff, 'f', 2) + " %"));
			}
		}
				//ui.tableWidget_4->setItem(0, i, twi0);
				//ui.tableWidget_4->setItem(1, i, twi1);
				//ui.tableWidget_4->setItem(2, i, twi2);
				//ui.tableWidget_4->setItem(3, i, twi3);
	}
	
	
}


//needed so that StreptoGUI gets dropEvent
void StreptoGUI::dragEnterEvent(QDragEnterEvent* event){
	event->accept();
	event->acceptProposedAction();
}


//needed so that StreptoGUI gets dropEvent
void StreptoGUI::dragMoveEvent(QDragMoveEvent* event) {
	event->accept();
}


//Drop Event
void StreptoGUI::dropEvent(QDropEvent* event) {
	const QMimeData* mimeData;
	mimeData = event->mimeData();
	urls->clear();
	ui.label_3->setText("");
	if (mimeData->urls().size() == 1) {
		//uploadDialog* f = new uploadDialog();
		if (!ui.line_groupID_group->text().isEmpty()) {
			ud->grpID = ui.line_groupID_group->text().toInt();
		}
		ud->dragOpenFile(QString::fromStdString(mimeData->urls().at(0).toString().toStdString().substr(8)));
		ud->show();
	}
	else if (mimeData->urls().size() > 1) {
		
		for (int i = 0; i < mimeData->urls().size(); i++) {
			urls->push_back(mimeData->urls().at(i).toString().toStdString().substr(8));
			ui.label_3->setText(QString::fromStdString(mimeData->urls().at(i).toString().toStdString().substr(8)));
		}
		mud->dragOpenFiles(*urls);
		mud->show();
	}

	for (int i = 0; i < mimeData->urls().size();i++) {
		//ui.label_3->setText(ui.label_3->text() + mimeData->urls().at(i).toString() + " ; "+ QString::number(mimeData->urls().size()) +"\n");
	}
}


void StreptoGUI::loadSql() {
	QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", QDir::currentPath());
	string path = fileName.toStdString();
	if (!fileName.isEmpty())
	{
		try {
			dbcon->printResult2File(path);
			ui.label_34->setText("Result: " + QString::fromStdString(path.substr(0, path.length() - 3) + "txt"));
		}
		catch (exception) {
			ui.label_34->setText("Error running sql file!");
		}
		
	}
	else {
		ui.label_34->setText("invalid Sql-File!");
	}


	//ui.label->setText(fileName);
	//delete(&fileName);
}



void StreptoGUI::newGroup() {
	multiUploadDialog* f = new multiUploadDialog();
	f->show();
}

void StreptoGUI::act_settings(){
	settingsDialog* f = new settingsDialog();
	f->show();
}


void StreptoGUI::editTestStrains(){
	editTestStrainsDialog* f = new editTestStrainsDialog();
	f->show();
}
