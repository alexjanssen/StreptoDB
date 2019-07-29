#include "StreptoGUI.h"

//#include <string>
//#include <sqlite/sqlite3.h> 


using namespace std; 



//Todo comment
StreptoGUI::StreptoGUI(QMainWindow*parent)	: QMainWindow(parent)
{
	setAcceptDrops(true);	//needed for drag & drop
	ui.setupUi(this);
	//ui.label -> setText("blaa");
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
		int imgID = atoi(ui.tableWidget->item(x, y)->text().toStdString().c_str());
		//search for item in global result vector with imageID
		for (int i = 0; i < resultGlob.size(); i++) {
			//if found, set graphicsView with image
			if (resultGlob[i].image_id == imgID) {
				QPixmap pixmap2;
				QImage image(resultGlob[i].filePath.c_str());
				pixmap2 = pixmap2.fromImage(image);

				QGraphicsScene* scene = new QGraphicsScene();
				scene->addPixmap(pixmap2.scaled(300, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
				ui.graphicsView->setScene(scene);
				ui.graphicsView->show();
				//fill image Parameters
				ui.line_ID->setText(QString::number(resultGlob[i].image_id));
				ui.line_timestamp->setText(QString::fromStdString(resultGlob[i].date));
				ui.line_imgSize->setText(QString::number(resultGlob[i].imagesize));
				ui.line_resolution_x->setText(QString::number(resultGlob[i].resolution_x));
				ui.line_resolution_y->setText(QString::number(resultGlob[i].resolution_y));
				ui.line_brothID->setText(QString::number(resultGlob[i].broth_id));
				ui.line_groupID->setText(QString::number(resultGlob[i].group_id));
				ui.line_path->setText(QString::fromStdString(resultGlob[i].filePath));
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
				ui.line_brothID->setText("");
				ui.line_groupID->setText("");
				ui.line_path->setText("");

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
	ui.tableWidget->verticalHeader()->setFixedWidth(40);
	ui.tableWidget->verticalHeader()->resizeSection(0, 40);
	ui.tableWidget->setColumnWidth(0, 154);
	ui.tableWidget->setColumnWidth(1, 154);
	ui.tableWidget->setColumnWidth(2, 154);
	ui.tableWidget->setColumnWidth(3, 154);
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
	ui.label->setText("Groups found: ");
	for (int z = 0; z < group.size(); z++) {
		ui.tableWidget->setRowHeight(z, 100);
		ui.tableWidget->setVerticalHeaderItem(z, new QTableWidgetItem(QString::fromStdString(dbcon->getGroup("=" + std::to_string(group[z]))[0].intern_id)));
		ui.label->setText(ui.label->text() + QString::fromStdString(dbcon->getGroup("=" + std::to_string(group[z]))[0].intern_id) + " | ");
		for (int x = 0; x < result.size(); x++) {
			if(group[z] == result[x].group_id){
				QPixmap pixmap;
				QTableWidgetItem* twi = new QTableWidgetItem();
				//pixmap.loadFromData(result[0].image_preview);
				pixmap = pixmap.fromImage(result[x].image_preview);
				twi->setData(Qt::DecorationRole, pixmap.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
				twi->setText(QString::number(result[x].image_id));
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
	cp.calc_id = dbcon->getMaxCalcParamID() + 1;
	cp.image_id = ui.line_ID->text().toInt();
	cp.class_id = 1;	//Yeah, thats hard coded for mean_grey()
	cp.timestamp = ui.line_timestamp->text().toStdString();

	cv::Mat testbildM = cv::imread(ui.line_path->text().toStdString());
    cv::Scalar tempVal = cv::mean(testbildM);
	cp.value = tempVal.val[0];

	if (!dbcon->addCalcedParams(cp)) {
		ui.label_12->setText("Successfully added new Parameters to DB.");
	}
	else {
		ui.label_12->setText("Something went wrong calculating and adding new Parameters to DB.");
	}

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
		if (!dbcon->addStrainInhibition(maxID,ui.line_ID->text().toInt(), strainID, ui.line_brothID->text().toInt(), ui.checkBox_inhibition->isChecked())) {
			ui.label_28->setText("Success!");
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

		vector<Compare> comp = dbcon->getCompare(ui.tableWidget_2->item(x, 3)->text().toDouble(), ui.line_brothID->text().toInt(), ui.tableWidget_2->item(x, 2)->text().toInt());
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
					twi->setData(Qt::DecorationRole, pixmap.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
					twi->setText(QString::number(resultGlob[u].image_id)+"\n"+QString::number(comp[i].diff));
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
	img2.broth_id = ui.line_brothID->text().toInt();
	img2.group_id = ui.line_groupID->text().toInt();
	img2.filePath = ui.line_path->text().toStdString();

	if (!dbcon->updateImage(img2)) {
		ui.label_3->setText("successfully updated Image.");
	}
	else {
		ui.label_3->setText("failed to update Image.");
	}
}


//Arbeit Arbeit
void StreptoGUI::imgDelete(){
	if (dbcon->deleteImage(ui.line_ID->text().toInt())) {
		ui.label_3->setText("successfully deleted Image.");
	}
	else {
		ui.label_3->setText("failed to delete Image.");
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
		}else { ui.label_3->setText("Failed to delete entry in Calculations"); }
	}
	else {	//Strain-Inhibition
		//ui.label_12->setText(QString::number(ui.tableWidget_3->currentRow()));
		if (dbcon->deleteStrainInhibition(ui.tableWidget_3->item(ui.tableWidget_3->currentRow(), 0)->text().toDouble())) {
			ui.label_3->setText("Successfully deleted entry in Strain-Inhibition");
		}
		else { ui.label_3->setText("Failed to delete entry in Strain-Inhibition"); }
	}
		//ui.tableWidget_2->currentRow();
}

void StreptoGUI::newGroup(){
	multiUploadDialog* f = new multiUploadDialog();
	f->show();
}

void StreptoGUI::act_settings()
{
	settingsDialog* f = new settingsDialog();
	f->show();
}


//Todo
void StreptoGUI::compare(){
	//vector<Compare> comp = dbcon->getCompare(ui.line);


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

	//ui.label_3->setText(QString::number(mimeData->urls().size()));
	for (int i = 0; i < mimeData->urls().size();i++) {
		//ui.label_3->setText(ui.label_3->text() + mimeData->urls().at(i).toString() + " ; "+ QString::number(mimeData->urls().size()) +"\n");
	}
	// check for our needed mime type, here a file or a list of files
	//if (mimeData->hasUrls())
	//{
		//QStringList pathList;
		//QList<QUrl> urlList = mimeData->urls();

		// extract the local paths of the files
		//for (int i = 0; i < urlList.size() && i < 32; +i)
		//{
		//	pathList.append(urlList.at(i).toLocalFile());
		//}

		// call a function to open the files
		//openFiles(pathList);
	//}
}
