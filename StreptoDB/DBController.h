#pragma once

#include <stdio.h>
#include <Image.cpp>
#include <vector>
#include <sqlite/sqlite3.h> 

using namespace std;

class DBController {
public:
	DBController();
	vector<Image> getImages(void);
	//bool addImage(Image);
	bool addImage2(Image);

private:
	bool openDB();
	//void closeDB();

};
static vector<Image> *result = new vector<Image>;
static sqlite3 *db;
static string& db_name = string("../Database/StreptoDB.db");