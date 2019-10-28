#include "EditTestStrainsDialog.h"

using namespace std;



editTestStrainsDialog::editTestStrainsDialog(QDialog* parent) : QDialog(parent)
{
	ui.setupUi(this);
	loadDB();
}



void editTestStrainsDialog::loadDB(){
	DBController* dbcon = new DBController();
	testStrain_glob = dbcon->getTestStrains();
	if (testStrain_glob.size() > 0) {
		fillTable(testStrain_glob);
	}else {
		ui.label_test->setText("error loading DB, maybe empty.");
	}

}




void editTestStrainsDialog::deleteItem(){
	DBController* dbcon3 = new DBController();
	if (dbcon3->deleteTestStrain(ui.tableWidget->item(ui.tableWidget->currentRow(), 0)->text().toInt())) {
		loadDB();
		ui.label_test->setText("successfully deleted TestStrain.");
	}else {
		loadDB();
		ui.label_test->setText("failed to delete TestStrain.");
	}
}



//Collects the user inputs and calls DBController::addTestStrains(TestStrain);
void editTestStrainsDialog::addItem(){
	DBController* dbcon2 = new DBController();
	//TestStrain newTS = TestStrain();
	newTS.strain_id = ui.lineEdit_strainID->text().toInt();
	newTS.strain_name = ui.lineEdit_strainName->text().toStdString();
	newTS.broth_id = ui.lineEdit_strainBrothID->text().toInt();

	if (dbcon2->addTestStrain(newTS)) {
		loadDB();
		ui.label_test->setText("successfully saved Image to DB.");
	}
	else {
		loadDB();
		ui.label_test->setText("ups, something went wrong :(");
		
	}

}



void editTestStrainsDialog::fillTable(vector<TestStrain> result) {
	
	ui.tableWidget->setColumnCount(3);
	ui.tableWidget->verticalHeader()->setVisible(false);
	ui.tableWidget->setColumnWidth(0, 100);
	ui.tableWidget->setColumnWidth(1, 100);
	ui.tableWidget->setColumnWidth(2, 100);

	ui.tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Strain-ID"));
	ui.tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Strain-Name"));
	ui.tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Broth-ID"));

	ui.tableWidget->setRowCount(result.size());
	for (int i = 0; i < result.size(); i++) {
		ui.tableWidget->setRowHeight(i, 30);
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(result[i].strain_id)));
		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(result[i].strain_name)));
		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(result[i].broth_id)));
	}
	ui.label_test->setText(QString::number(result.size()));

	//set default Values for new TestStrain
	if (ui.tableWidget->rowCount() > 0) {
		ui.lineEdit_strainID->setText(QString::number(ui.tableWidget->item(ui.tableWidget->rowCount() - 1, 0)->text().toInt() + 1));
	}else {
		ui.lineEdit_strainID->setText("1");
	}
	ui.lineEdit_strainName->setText("insert name");
	ui.lineEdit_strainBrothID->setText("1");

}