#pragma once

#include <stdio.h>
#include <vector>
#include <Group.cpp>
#include <Image.cpp>
#include <CalcedParams.cpp>
#include <sqlite/sqlite3.h> 

using namespace std;

class DBController {
public:
	DBController();
	vector<Image> getImages(void);
	Group getGroup(int);
	int getMaxCalcParamID();
	vector<CalcedParams> getCalcedParams(int);

	bool addImage2(Image);
	bool addCalcedParams(CalcedParams cp);

private:
	bool openDB();
	//void closeDB();

};
static vector<Image> *result = new vector<Image>;
static sqlite3 *db;
static string& db_name = string("../Database/StreptoDB.db");
static Group grp;
static int maxCalcParamID;
static vector<CalcedParams> *result_calcedParams = new vector<CalcedParams>;