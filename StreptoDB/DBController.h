#pragma once

#include <stdio.h>
#include <vector>
#include <Group.cpp>
#include <Image.cpp>
#include <Compare.cpp>
#include <CalcedParams.cpp>
#include <sqlite/sqlite3.h> 
#include <StrainInhibition.cpp>
#include <Broth.cpp>
#include <TestStrain.cpp>
#include <ImgBroth.cpp>

using namespace std;

class DBController {
public:
	DBController();
	vector<Image> getImages(string str);
	vector<Group> getGroup(string);
	bool updateGroup(Group grp);
	bool deleteGroup(int id_grp, vector<int> imgs);
	bool addGroup(Group grp);
	vector<Broth> getBroth(string id);
	int getMaxCalcParamID();
	int getMaxInhibitionID();
	int getMaxImageID();
	int getMaxGroupID();
	int getGroupID(int imageID);
	vector<CalcedParams> getCalcedParams(int);
	vector<ImgBroth> getImgBroth(int id);
	vector<Compare> getCompare(double, int, int);
	vector<TestStrain> getTestStrains();
	vector<StrainInhibition> getInhibition(int);


	bool addImage2(Image img);
	bool updateImage(Image img);
	bool deleteImage(int id);
	bool deleteCalculatedParameters(int img_id);
	bool deleteCalcedParam(int calcP_ID);
	bool deleteStrainInhibits(int img_id);
	bool deleteStrainInhibition(int SI_ID);
	bool addCalcedParams(CalcedParams cp);

	bool addStrainInhibition(int si_id, int img_id, int strain_id, int broth_id, bool inhibit);

private:
	bool openDB();
	//void closeDB();

};
static vector<Image> *result = new vector<Image>;
static sqlite3 *db;
static string& db_name = string("../Database/StreptoDB.db");
static vector<Group> *grp = new vector<Group>;
static vector<Broth> *broth = new vector<Broth>;
static int maxID;
static vector<CalcedParams> *result_calcedParams = new vector<CalcedParams>;
static vector<Compare>* result_compare = new vector<Compare>;
static vector<StrainInhibition>* result_inhibition = new vector<StrainInhibition>;
static vector<TestStrain>* result_testStrains = new vector<TestStrain>;
static vector<ImgBroth>* imgBroth = new vector<ImgBroth>;