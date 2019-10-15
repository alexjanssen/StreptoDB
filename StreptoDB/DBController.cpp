#include <DBController.h>
#include <fstream> 
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <QtCore\QBuffer>

using namespace std;


//Used for Debugging
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}



//Constructor sets the Database Path.
DBController::DBController() {
	db_name = "../Database/StreptoDB.db";
}
	


//empty callback
static int callback(void* param, int numCols, char** col, char** colName)
{
	// just an empty callback for deleting

	return 0;
}


//This function is called to receive the query result of "DBController::getImages()" and 
//write that to the static vector "result".
static int callback_img(void* param, int numCols, char** col, char** colName)
{
	// int numCols: holds the number of results
	// (array) colName: holds each column returned
	// (array) col: holds each value
	Image img = Image();
	int* col_width = (int*)param; // this isn't necessary, but it's convenient

	img.image_id = atoi(col[0]);
	unsigned char* data = (unsigned char*)col[1];
	img.image_preview = QImage::fromData(data, atoi(col[3]),nullptr);
	img.date = (string)col[2];
	img.imagesize = atoi(col[3]);
	img.resolution_x = atoi(col[4]);
	img.resolution_y = atoi(col[5]);
	img.broth_id = atoi(col[6]);
	img.group_id = atoi(col[7]);
	img.filePath = (string)col[8];
	img.scale = atof(col[9]);

	result->push_back(img);

	return 0;
}


//This function is called to receive the query result of "DBController::getGroup()" and 
//write that to the static vector "result".
static int callback_group(void* param, int numCols, char** col, char** colName)
{
	// int numCols: holds the number of results
	// (array) colName: holds each column returned
	// (array) col: holds each value
	//Group grp = Group();
	int* col_width = (int*)param; // this isn't necessary, but it's convenient
	Group group = Group();
	group.group_id = atoi(col[0]);
	group.intern_id = (string)(col[1]);
	group.date = (string)col[2];
	group.sci_name = (string)col[3];
	group.genome_lnk = (string)col[4];
	group.latitude = atof(col[5]);
	group.longitude = atof(col[6]);
	group.siderophore = (bool)atoi(col[7]);
	group.spore_color = (string)col[8];

	grp->push_back(group);

	return 0;
}


//This function is called to receive the query result of "DBController::getBroth()" and 
//write that to the static Object broth.
static int callback_broth(void* param, int numCols, char** col, char** colName)
{
	// int numCols: holds the number of results
	// (array) colName: holds each column returned
	// (array) col: holds each value
	Broth bro = Broth();
	int* col_width = (int*)param; // this isn't necessary, but it's convenient

	bro.broth_id = atoi(col[0]);
	bro.name = (string)(col[1]);
	bro.info = (string)col[2];

	broth->push_back(bro);

	return 0;
}


//same for Calculated-Paramaters
static int callback_calcedParams(void* param, int numCols, char** col, char** colName)
{
	// int numCols: holds the number of results
	// (array) colName: holds each column returned
	// (array) col: holds each value
	CalcedParams cp = CalcedParams();
	int* col_width = (int*)param; // this isn't necessary, but it's convenient

	cp.calc_id = atoi(col[0]);
	cp.image_id = atoi(col[1]);
	cp.class_id = atoi(col[2]);
	cp.value = atof(col[3]);
	cp.timestamp = (string)col[4];

	result_calcedParams->push_back(cp);

	return 0;
}


//still same apeshit
static int callback_maxID(void* param, int numCols, char** col, char** colName)
{
	int* col_width = (int*)param;
	if (col[0] == NULL) {
		maxID = 0;
	}else{ maxID = atoi(col[0]); }
	
	return 0;
}


//still same apeshit
static int callback_getImgBroth(void* param, int numCols, char** col, char** colName)
{
	int* col_width = (int*)param;
	ImgBroth ib = ImgBroth();
	if (col[0] == NULL) {
		ib.img_id = 0;
		ib.broth_id = 0;
	}
	else { 
		ib.img_id = atoi(col[0]);
		ib.broth_id = atoi(col[1]);
	}
	imgBroth->push_back(ib);

	return 0;
}


//same for Compare
static int callback_compare(void* param, int numCols, char** col, char** colName)
{
	// int numCols: holds the number of results
	// (array) colName: holds each column returned
	// (array) col: holds each value
	Compare com = Compare();
	int* col_width = (int*)param; // this isn't necessary, but it's convenient

	com.image_id = atoi(col[0]);
	com.diff = atof(col[1]);

	result_compare->push_back(com);

	return 0;
}


//This function is called to receive the query result of "DBController::getInhibition()" and 
//write that to the static vector "result".
static int callback_inhibition(void* param, int numCols, char** col, char** colName)
{
	// int numCols: holds the number of results
	// (array) colName: holds each column returned
	// (array) col: holds each value
	StrainInhibition si = StrainInhibition();
	int* col_width = (int*)param; // this isn't necessary, but it's convenient

	si.id = atoi(col[0]);
	si.id_intern = (string)(col[1]);
	si.broth_name = (string)(col[2]);
	si.strain_name = (string)col[3];
	si.inhibition = (bool)atoi(col[4]);

	result_inhibition->push_back(si);

	return 0;
}


//same for testStrains
static int callback_testStrains(void* param, int numCols, char** col, char** colName)
{
	// int numCols: holds the number of results
	// (array) colName: holds each column returned
	// (array) col: holds each value
	TestStrain ts = TestStrain();
	int* col_width = (int*)param; // this isn't necessary, but it's convenient

	ts.strain_id = atoi(col[0]);
	ts.strain_name = (string)(col[1]);
	ts.broth_id = atoi(col[2]);
	
	result_testStrains->push_back(ts);

	return 0;
}










//opens the database yds
bool DBController::openDB() {
	//return true if DB-Connection opened successfully
	char* zErrMsg = 0;
	int rc;
	rc = sqlite3_open(db_name.c_str(), &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return false;
	} else {
		fprintf(stderr, "Opened database successfully\n");
		return true;
	}
}


//returns all datasets from table Image
vector<Image> DBController::getImages(string filt) {	
	char* zErrMsg = 0;
	string query = "SELECT " \
					"I.IMAGE_ID, " \
					"I.IMAGE_PREVIEW_BLOB, " \
					"I.TIMESTAMP, " \
					"I.IMAGESIZE, " \
					"I.RESOLUTION_X, " \
					"I.RESOLUTION_Y, " \
					"I.BROTH_ID, " \
					"I.GROUP_ID, " \
					"I.PATH, " \
					"I.SCALE, " \
					"S.ID_INTERN " \
					"FROM Images I LEFT JOIN Streptomyceten S ON I.GROUP_ID = S.ID_GROUP " \
					"WHERE S.ID_INTERN LIKE '" + filt + "%' " \
					"ORDER BY S.ID_INTERN ASC;";

	int rc = DBController::openDB();
	if (rc) {
		result->clear();
		sqlite3_exec(db, query.c_str(), callback_img, NULL, &zErrMsg);
	}
	else {
		DBOUT("Can't execute SQL-Statement(DBController::getImages()):", sqlite3_errmsg(db));
	}
	sqlite3_close(db);

	return *result;
}


 //return Group for specific GROUP_ID
 vector<Group> DBController::getGroup(string id) {
	 char* zErrMsg = 0;
	 string query = "SELECT * FROM Streptomyceten WHERE ID_GROUP "+ id +" ORDER BY ID_GROUP ASC;";
	 int rc = DBController::openDB();
	 if (rc) {
		 grp->clear();
		 sqlite3_exec(db, query.c_str(), callback_group, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getGroup(int)):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return *grp;
 }


 //UPDATE Streptomyceten
 bool DBController::updateGroup(Group grp) {

	 int rc = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);
	 if (rc != SQLITE_OK) {
		 DBOUT("db open failed: DBController::updateGroup(Group)", sqlite3_errmsg(db));
		 return false;
	 }
	 else {
		 sqlite3_stmt* stmt = NULL;
		 string err_str;
		 rc = sqlite3_prepare(db, \
			 "UPDATE Streptomyceten " \
			 "SET " \
			 "ID_GROUP = ?," \
			 "ID_INTERN = ?," \
			 "DATE = ?," \
			 "SCIENTIFIC_NAME = ?," \
			 "GENOME_LINK = ?," \
			 "LATITUDE = ?," \
			 "LONGITUDE = ?," \
			 "SIDEROPHORE_BOOL = ?," \
			 "SPORE_COLOR = ?" \
			 "WHERE ID_GROUP = ?;", \
			 - 1, &stmt, NULL);
		 if (rc != SQLITE_OK) {
			 DBOUT("prepare failed: DBController::updateGroup(Group)", sqlite3_errmsg(db));

			 return false;
		 }
		 else {
			 // SQLITE_STATIC because the statement is finalized
			 // before the buffer is freed:
			 sqlite3_bind_int(stmt, 1, grp.group_id);
			 sqlite3_bind_text(stmt, 2, grp.intern_id.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_text(stmt, 3, grp.date.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_text(stmt, 4, grp.sci_name.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_text(stmt, 5, grp.genome_lnk.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_double(stmt, 6, grp.latitude);
			 sqlite3_bind_double(stmt, 7, grp.longitude);
			 sqlite3_bind_int(stmt, 8, grp.siderophore);
			 sqlite3_bind_text(stmt, 9, grp.spore_color.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_int(stmt, 10, grp.group_id);
			 //sqlite3_bind_double(stmt, 5, grp.locality);

			 if (rc != SQLITE_OK) {
				 DBOUT("bind failed: DBController::updateGroup(Group)", sqlite3_errmsg(db));
				 return false;
			 }
			 else {
				 rc = sqlite3_step(stmt);
				 if (rc != SQLITE_DONE)
					 DBOUT("execution failed: DBController::updateGroup(Group)", sqlite3_errmsg(db));
				 return false;
			 }
		 }
		 sqlite3_finalize(stmt);
	 }
	 sqlite3_close(db);
	 return true;
 }


 //DELETE FROM Streptomyceten WHERE ID_GROUP = ?
 bool DBController::deleteGroup(int id_grp, vector<int> imgs) {
	 char* zErrMsg = 0;
	 string query = "DELETE FROM Streptomyceten " \
		 "WHERE ID_GROUP = " + std::to_string(id_grp) + "; ";

	 for (int i = 0; i < imgs.size(); i++) {
		 DBController::deleteImage(imgs[i]);
	 }

	 int rc = DBController::openDB();
	 if (rc && sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg) == SQLITE_OK) {
		 return true;
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::deleteGroup()):", sqlite3_errmsg(db));
		 return false;
	 }
	 sqlite3_close(db);
 }


 //INSERT INTO Streptomyceten
 bool DBController::addGroup(Group grp) {

	 int rc = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);
	 if (rc != SQLITE_OK) {
		 DBOUT("db open failed: DBController::addGroup(Group)", sqlite3_errmsg(db));
		 return false;
	 }
	 else {
		 sqlite3_stmt* stmt = NULL;
		 string err_str;
		 rc = sqlite3_prepare(db, \
			 "INSERT INTO Streptomyceten(ID_GROUP, ID_INTERN, DATE, SCIENTIFIC_NAME, GENOME_LINK, LATITUDE, LONGITUDE, SIDEROPHORE_BOOL, SPORE_COLOR)" \
			 " VALUES(?,?,?,?,?,?,?,?,?);", \
			 - 1, &stmt, NULL);
		 if (rc != SQLITE_OK) {
			 DBOUT("prepare failed: DBController::addGroup(Group)", sqlite3_errmsg(db));

			 return false;
		 }
		 else {
			 // SQLITE_STATIC because the statement is finalized
			 // before the buffer is freed:
			 sqlite3_bind_int(stmt, 1, grp.group_id);
			 sqlite3_bind_text(stmt, 2, grp.intern_id.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_text(stmt, 3, grp.date.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_text(stmt, 4, grp.sci_name.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_text(stmt, 5, grp.genome_lnk.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_double(stmt, 6, grp.latitude);
			 sqlite3_bind_double(stmt, 7, grp.longitude);
			 sqlite3_bind_int(stmt, 8, grp.siderophore);
			 sqlite3_bind_text(stmt, 9, grp.spore_color.c_str(), -1, SQLITE_STATIC);

			 if (rc != SQLITE_OK) {
				 DBOUT("bind failed: DBController::addGroup(Group)", sqlite3_errmsg(db));
				 return false;
			 }
			 else {
				 rc = sqlite3_step(stmt);
				 if (rc != SQLITE_DONE) {
					 DBOUT("execution failed: DBController::addGroup(Group)", sqlite3_errmsg(db));
					 return false;
				 }
			 }
		 }
		 sqlite3_finalize(stmt);
	 }
	 sqlite3_close(db);
	 return true;
 }


 //return Broth for specific BROTH_ID
 vector<Broth> DBController::getBroth(string id) {
	 char* zErrMsg = 0;
	 string query = "SELECT * FROM Broth WHERE BROTH_ID " + id + " ORDER BY BROTH_ID ASC;";
	 int rc = DBController::openDB();
	 if (rc) {
		 broth->clear();
		 sqlite3_exec(db, query.c_str(), callback_broth, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getBroth(int)):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return *broth;
 }


 //return max ID from Calculated Parameters
 int DBController::getMaxCalcParamID() {
	 char* zErrMsg = 0;
	 string query = "SELECT MAX(CalcP_ID) FROM CalculatedParameters;";
	 int rc = DBController::openDB();
	 if (rc) {
		 //result->empty();
		 sqlite3_exec(db, query.c_str(), callback_maxID, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getMaxCalcParamID()):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return maxID;
 }


 //return max ID from Strain-Inhibition
 int DBController::getMaxInhibitionID() {
	 char* zErrMsg = 0;
	 string query = "SELECT MAX(\"STRAIN-INHIBITS_ID\") FROM 'Strain-Inhibits';";
	 int rc = DBController::openDB();
	 if (rc) {
		 //result->empty();
		 sqlite3_exec(db, query.c_str(), callback_maxID, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getInhibitID()):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return maxID;
 }


 //return max ID from Image
 int DBController::getMaxImageID() {
	 char* zErrMsg = 0;
	 string query = "SELECT MAX(IMAGE_ID) FROM Images;";
	 int rc = DBController::openDB();
	 if (rc) {
		 //result->empty();
		 sqlite3_exec(db, query.c_str(), callback_maxID, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getMaxCalcParamID()):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return maxID;
 }


 //return max ID from Group
 int DBController::getMaxGroupID() {
	 char* zErrMsg = 0;
	 string query = "SELECT MAX(ID_GROUP) FROM Streptomyceten;";
	 int rc = DBController::openDB();
	 if (rc) {
		 //result->empty();
		 sqlite3_exec(db, query.c_str(), callback_maxID, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getMaxGroupID()):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return maxID;
 }



 //return GroupID of given ImageID
 int DBController::getGroupID(int imageID) {
	 char* zErrMsg = 0;
	 string query = "SELECT GROUP_ID FROM Images WHERE IMAGE_ID = "+ std::to_string(imageID) +";";
	 int rc = DBController::openDB();
	 if (rc) {
		 //result->empty();
		 sqlite3_exec(db, query.c_str(), callback_maxID, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getGroupID()):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return maxID;
 }



 //returns calculated Parameters for specific IMAGE_ID
 vector<CalcedParams> DBController::getCalcedParams(int id) {
	 char* zErrMsg = 0;
	 string query = "SELECT * FROM CalculatedParameters WHERE IMAGE_ID = " + std::to_string(id) + ";";
	 int rc = DBController::openDB();
	 if (rc) {
		 result_calcedParams->clear();
		 sqlite3_exec(db, query.c_str(), callback_calcedParams, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getCalcedParams(int)):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return *result_calcedParams;
 }


 //returns vector with imageID and brothID for a given groupID
 vector<ImgBroth> DBController::getImgBroth(int id) {
	 char* zErrMsg = 0;
	 string query = "SELECT IMAGE_ID, BROTH_ID FROM Images where GROUP_ID = " + std::to_string(id) + " ORDER BY BROTH_ID ASC;";
	 int rc = DBController::openDB();
	 if (rc) {
		 imgBroth->clear();
		 sqlite3_exec(db, query.c_str(), callback_getImgBroth, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getImgBroth(int)):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return *imgBroth;
 }


 //returns Vector of Images with absolute difference for a specific Classification Parameter and a given Value
 vector<Compare> DBController::getCompare(double val, int broth_id, int classP_ID) {
	 //returns vector<Compare>
	 //double val		-> Value to compare
	 //int broth_id		-> broth ID
	 //int classP_ID	-> Classification Paramater ID
	 char* zErrMsg = 0;
	 string query =	 "SELECT " \
					 "t1.IMAGE_ID," \
					 "t1.diff " \
					 "FROM" \
						 "(SELECT " \
						 "MAX(cp.TIMESTAMP)," \
						 "cp.IMAGE_ID," \
						 "cp.ClassP_ID," \
						 "cp.VALUE," \
						 "ABS(cp.VALUE - " + std::to_string(val) + ") as diff " \
							 "FROM CalculatedParameters cp " \
							 "LEFT JOIN Images i ON cp.IMAGE_ID = i.IMAGE_ID " \
								 "WHERE " \
								 "i.BROTH_ID = " + std::to_string(broth_id) +  \
								 " AND cp.ClassP_ID = " + std::to_string(classP_ID) + \
						 " GROUP BY cp.IMAGE_ID" \
						 " ORDER BY diff ASC) t1;";
	 int rc = DBController::openDB();
	 if (rc) {
		 DBOUT(query.c_str());
		 result_compare->clear();
		 sqlite3_exec(db, query.c_str(), callback_compare, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getCalcedParams(int)):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return *result_compare;
 }


 //returns all Test-Strains
 vector<TestStrain> DBController::getTestStrains() {
	 char* zErrMsg = 0;
	 string query = "SELECT * FROM Test_Strains;";
	 int rc = DBController::openDB();
	 if (rc) {
		 result_testStrains->clear();
		 sqlite3_exec(db, query.c_str(), callback_testStrains, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getTestStrains(int)):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return *result_testStrains;
 }


 //returns Inhibitions for specific IMAGE_ID
 vector<StrainInhibition> DBController::getInhibition(int id) {
	 char* zErrMsg = 0;
	 string query = "SELECT " \
		 "SI.'STRAIN-INHIBITS_ID', " \
		 "S.ID_INTERN, " \
		 "B.BROTH_NAME, " \
		 "TS.STRAIN_NAME, " \
		 "SI.INHIBITION_BOOL " \
		 "FROM 'Strain-Inhibits' SI " \
		 "LEFT JOIN Broth B ON B.BROTH_ID = SI.BROTH_ID " \
		 "LEFT JOIN Test_Strains TS ON TS.STRAIN_ID = SI.STRAIN_ID " \
		 "LEFT JOIN Images I ON I.IMAGE_ID = SI.IMAGE_ID " \
		 "LEFT JOIN Streptomyceten S ON S.ID_GROUP = I.GROUP_ID " \
		 "WHERE " \
		 "SI.IMAGE_ID = " + std::to_string(id) + ";";

	 int rc = DBController::openDB();
	 if (rc) {
		 result_inhibition->clear();
		 sqlite3_exec(db, query.c_str(), callback_inhibition, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getInhibition(int)):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return *result_inhibition;
 }


 //INSERT INTO Images
 bool DBController::addImage2(Image img) {
	 
	 QImage image(QString::fromStdString(img.filePath));
	 if (image.isNull())
	 {
		 DBOUT("Image file open failed: DBController::addImage2(Image)", sqlite3_errmsg(db));
		 return false;
	 }

	 //You can obtain a pointer to the pixels in the image (as unsigned char *)
	 //using QImage::constBits() and QImage::byteCount()
	 image = image.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	 QByteArray bytes;
	 QBuffer buffer(&bytes);
	 buffer.open(QIODevice::WriteOnly);
	 image.save(&buffer, "tif");
	 buffer.close();

	 unsigned char* data = (unsigned char*)malloc(bytes.size());
	 memcpy(data, reinterpret_cast<unsigned char*>(bytes.data()), bytes.size());
	 int size = bytes.size();

	 int rc = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);
	 if (rc != SQLITE_OK) {
		 DBOUT("db open failed: DBController::addImage2(Image)", sqlite3_errmsg(db));
		 return false;
	 }
	 else {
		 sqlite3_stmt* stmt = NULL;
		 string err_str;
		 rc = sqlite3_prepare(db, \
			 "INSERT INTO Images(IMAGE_ID, IMAGE_PREVIEW_BLOB, TIMESTAMP, IMAGESIZE, RESOLUTION_X, RESOLUTION_Y, BROTH_ID, GROUP_ID, PATH, SCALE)" \
			 " VALUES(?,?,?,?,?,?,?,?,?,?);", \
			 - 1, &stmt, NULL);
		 if (rc != SQLITE_OK) {
			 DBOUT("prepare failed: DBController::addImage2(Image)", sqlite3_errmsg(db));

			 return false;
		 }
		 else {
			 // SQLITE_STATIC because the statement is finalized
			 // before the buffer is freed:
			 sqlite3_bind_int(stmt, 1, img.image_id);
			 rc = sqlite3_bind_blob(stmt, 2, data, size, SQLITE_STATIC);
			 sqlite3_bind_text(stmt, 3, img.date.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_double(stmt, 4, (double)size);
			 sqlite3_bind_double(stmt, 5, img.resolution_x);
			 sqlite3_bind_double(stmt, 6, img.resolution_y);
			 sqlite3_bind_int(stmt, 7, img.broth_id);
			 sqlite3_bind_int(stmt, 8, img.group_id);
			 sqlite3_bind_text(stmt, 9, img.filePath.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_double(stmt, 10, img.scale);

			 if (rc != SQLITE_OK) {
				 DBOUT("bind failed: DBController::addImage2(Image)", sqlite3_errmsg(db));
				 return false;
			 }
			 else {
				 rc = sqlite3_step(stmt);
				 if (rc != SQLITE_DONE) {
					 DBOUT("execution failed: DBController::addImage2(Image)", sqlite3_errmsg(db));
					 return false;
				 }
			 }
		 }
		 sqlite3_finalize(stmt);
	 }
	 sqlite3_close(db);
	 //delete[] data;
	 free(data);
	 //buffer.~QBuffer();
	 return true;
 }


 //UPDATE Images
 bool DBController::updateImage(Image img){

	 QImage image(QString::fromStdString(img.filePath));
	 if (image.isNull())
	 {
		 DBOUT("Image file open failed: DBController::updateImage(Image)", sqlite3_errmsg(db));
		 return false;
	 }

	 //You can obtain a pointer to the pixels in the image (as unsigned char *)
	 //using QImage::constBits() and QImage::byteCount()
	 image = image.scaled(100, 100, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	 QByteArray bytes;
	 QBuffer buffer(&bytes);
	 buffer.open(QIODevice::WriteOnly);
	 image.save(&buffer, "tif");
	 buffer.close();

	 unsigned char* data = (unsigned char*)malloc(bytes.size());
	 memcpy(data, reinterpret_cast<unsigned char*>(bytes.data()), bytes.size());
	 int size = bytes.size();

	 int rc = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);
	 if (rc != SQLITE_OK) {
		 DBOUT("db open failed: DBController::updateImage(Image)", sqlite3_errmsg(db));
		 return false;
	 }
	 else {
		 sqlite3_stmt* stmt = NULL;
		 string err_str;
		 rc = sqlite3_prepare(db, \
			 "UPDATE Images " \
			 "SET " \
			 "IMAGE_ID = ?," \
			 "IMAGE_PREVIEW_BLOB = ?," \
			 "TIMESTAMP = ?," \
			 "IMAGESIZE = ?," \
			 "RESOLUTION_X = ?," \
			 "RESOLUTION_Y = ?," \
			 "BROTH_ID = ?," \
			 "GROUP_ID = ?," \
			 "PATH = ?," \
			 "SCALE = ?" \
			 "WHERE IMAGE_ID = ?;" , \
			 - 1, &stmt, NULL);
		 if (rc != SQLITE_OK) {
			 DBOUT("prepare failed: DBController::updateImage(Image)", sqlite3_errmsg(db));

			 return false;
		 }
		 else {
			 // SQLITE_STATIC because the statement is finalized
			 // before the buffer is freed:
			 sqlite3_bind_int(stmt, 1, img.image_id);
			 rc = sqlite3_bind_blob(stmt, 2, data, size, SQLITE_STATIC);
			 sqlite3_bind_text(stmt, 3, img.date.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_double(stmt, 4, size);
			 sqlite3_bind_double(stmt, 5, img.resolution_x);
			 sqlite3_bind_double(stmt, 6, img.resolution_y);
			 sqlite3_bind_int(stmt, 7, img.broth_id);
			 sqlite3_bind_int(stmt, 8, img.group_id);
			 sqlite3_bind_text(stmt, 9, img.filePath.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_double(stmt, 10, img.scale);
			 sqlite3_bind_int(stmt, 11, img.image_id);

			 if (rc != SQLITE_OK) {
				 DBOUT("bind failed: DBController::updateImage(Image)", sqlite3_errmsg(db));
				 return false;
			 }
			 else {
				 rc = sqlite3_step(stmt);
				 if (rc != SQLITE_DONE)
					 DBOUT("execution failed: DBController::updateImage(Image)", sqlite3_errmsg(db));
				 return false;
			 }
		 }
		 sqlite3_finalize(stmt);
	 }
	 sqlite3_close(db);
	 //delete[] data;
	 free(data);
	 buffer.~QBuffer();
	 return true;
 }


 //DELETE FROM Images WHERE IMAGE_ID = ?
 //DBController::deleteCalculatedParameters(?);
 //DBController::deleteStrainInhibits(?);
 bool DBController::deleteImage(int id){
	 char* zErrMsg = 0;
	 string query = "DELETE FROM Images " \
		 "WHERE IMAGE_ID = "+ std::to_string(id) +"; ";

	 int rc = DBController::openDB();
	 if (rc && sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg)==SQLITE_OK) {
		 DBController::deleteCalculatedParameters(id);
		 DBController::deleteStrainInhibits(id);
		 return true;
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::deleteImage()):", sqlite3_errmsg(db));
		 return false;
	 }
	 sqlite3_close(db);
 }


 //DELETE FROM CalculatedParameters WHERE IMAGE_ID = ?
 bool DBController::deleteCalculatedParameters(int img_id) {
	 char* zErrMsg = 0;
	 string query = "DELETE FROM CalculatedParameters " \
		 "WHERE IMAGE_ID = " + std::to_string(img_id) + "; ";

	 int rc = DBController::openDB();
	 if (rc && sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg) == SQLITE_OK) {
		 return true;
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::deleteCalculatedParameters()):", sqlite3_errmsg(db));
		 return false;
	 }
	 sqlite3_close(db);
 }


 //DELETE FROM CalculatedParameters WHERE CalcP_ID = ?
 bool DBController::deleteCalcedParam(int calcP_ID) {
	 char* zErrMsg = 0;
	 string query = "DELETE FROM CalculatedParameters " \
		 "WHERE CalcP_ID = " + std::to_string(calcP_ID) + "; ";

	 int rc = DBController::openDB();
	 if (rc && sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg) == SQLITE_OK) {
		 return true;
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::deleteCalcedParams()):", sqlite3_errmsg(db));
		 return false;
	 }
	 sqlite3_close(db);
 }


 //DELETE FROM 'Strain-Inhibits' WHERE IMAGE_ID = ?
 bool DBController::deleteStrainInhibits(int img_id) {
	 char* zErrMsg = 0;
	 string query = "DELETE FROM 'Strain-Inhibits' " \
		 "WHERE IMAGE_ID = " + std::to_string(img_id) + "; ";

	 int rc = DBController::openDB();
	 if (rc && sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg) == SQLITE_OK) {
		 return true;
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::deleteCalculatedParameters()):", sqlite3_errmsg(db));
		 return false;
	 }
	 sqlite3_close(db);
 }


 //DELETE FROM \"Strain-Inhibits\" WHERE \"STRAIN-INHIBITS_ID\" = ?
 bool DBController::deleteStrainInhibition(int SI_ID) {
	 char* zErrMsg = 0;
	 string query = "DELETE FROM \"Strain-Inhibits\" " \
		 "WHERE \"STRAIN-INHIBITS_ID\" = " + std::to_string(SI_ID) + "; ";

	 int rc = DBController::openDB();
	 if (rc && sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg) == SQLITE_OK) {
		 return true;
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::deleteStrainInhibition()):", sqlite3_errmsg(db));
		 return false;
	 }
	 sqlite3_close(db);
 }


 //INSERT INTO CalculatedParameters
 bool DBController::addCalcedParams(CalcedParams cp) {

	 int rc = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);
	 if (rc != SQLITE_OK) {
		 DBOUT("db open failed: DBController::addCalcedParams(CalcedParams)", sqlite3_errmsg(db));
		 return false;
	 }
	 else {
		 sqlite3_stmt* stmt = NULL;
		 string err_str;
		 rc = sqlite3_prepare(db, \
			 "INSERT INTO CalculatedParameters(CalcP_ID, IMAGE_ID, ClassP_ID, VALUE, TIMESTAMP)" \
			 " VALUES(?,?,?,?,?);", \
			 - 1, &stmt, NULL);
		 if (rc != SQLITE_OK) {
			 DBOUT("prepare failed: DBController::addCalcedParams(CalcedParams)", sqlite3_errmsg(db));

			 return false;
		 }
		 else {
			 // SQLITE_STATIC because the statement is finalized
			 // before the buffer is freed:
			 sqlite3_bind_int(stmt, 1, cp.calc_id);
			 sqlite3_bind_int(stmt, 2, cp.image_id);
			 sqlite3_bind_int(stmt, 3, cp.class_id);
			 sqlite3_bind_double(stmt, 4, cp.value);
			 sqlite3_bind_text(stmt, 5, cp.timestamp.c_str(), -1, SQLITE_STATIC);

			 if (rc != SQLITE_OK) {
				 DBOUT("bind failed: DBController::addCalcedParams(CalcedParams)", sqlite3_errmsg(db));
				 return false;
			 }
			 else {
				 rc = sqlite3_step(stmt);
				 if (rc != SQLITE_DONE)
					 DBOUT("execution failed: DBController::addCalcedParams(CalcedParams)", sqlite3_errmsg(db));
				 return false;
			 }
		 }
		 sqlite3_finalize(stmt);
	 }
	 sqlite3_close(db);
	 return true;
 }


 //INSERT INTO 'Strain-Inhibits'
 bool DBController::addStrainInhibition(int si_id, int img_id, int strain_id, int broth_id, bool inhibit) {

	 int rc = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);
	 if (rc != SQLITE_OK) {
		 DBOUT("db open failed: DBController::addStrainInhibition(int img_id, int strain_id, int broth_id, bool inhibit)", sqlite3_errmsg(db));
		 return false;
	 }
	 else {
		 sqlite3_stmt* stmt = NULL;
		 string err_str;
		 rc = sqlite3_prepare(db, \
			 "INSERT INTO 'Strain-Inhibits'('STRAIN-INHIBITS_ID', IMAGE_ID, STRAIN_ID, BROTH_ID, INHIBITION_BOOL)" \
			 " VALUES(?,?,?,?,?);", \
			 - 1, &stmt, NULL);
		 if (rc != SQLITE_OK) {
			 DBOUT("prepare failed: DBController::addStrainInhibition(int img_id, int strain_id, int broth_id, bool inhibit)", sqlite3_errmsg(db));

			 return false;
		 }
		 else {
			 // SQLITE_STATIC because the statement is finalized
			 // before the buffer is freed:
			 sqlite3_bind_int(stmt, 1, si_id);
			 sqlite3_bind_int(stmt, 2, img_id);
			 sqlite3_bind_int(stmt, 3, strain_id);
			 sqlite3_bind_int(stmt, 4, broth_id);
			 sqlite3_bind_int(stmt, 5, inhibit);

			 if (rc != SQLITE_OK) {
				 DBOUT("bind failed: DBController::addStrainInhibition(int img_id, int strain_id, int broth_id, bool inhibit)", sqlite3_errmsg(db));
				 return false;
			 }
			 else {
				 rc = sqlite3_step(stmt);
				 if (rc != SQLITE_DONE)
					 DBOUT("execution failed: DBController::addStrainInhibition(int img_id, int strain_id, int broth_id, bool inhibit)", sqlite3_errmsg(db));
					
				 return false;
			 }
		 }
		 sqlite3_finalize(stmt);
	 }
	 sqlite3_close(db);
	 return true;
 }


 //Stuff I might need later idk


 /* Strain-Inhibition evaluation
 //################################################################
 SELECT 
    S.ID_INTERN,
    B.BROTH_NAME,
    TS.STRAIN_NAME,
    SI.INHIBITION_BOOL
FROM "Strain-Inhibits" SI
    LEFT JOIN Broth B ON B.BROTH_ID = SI.BROTH_ID
    LEFT JOIN Test_Strains TS ON TS.STRAIN_ID = SI.STRAIN_ID
    LEFT JOIN Images I ON I.IMAGE_ID = SI.IMAGE_ID
    LEFT JOIN Streptomyceten S ON S.ID_GROUP = I.GROUP_ID
WHERE
    SI.IMAGE_ID = 2
;
//################################################################
 */



 /* bool DBController::addImage(Image img) {
	char* zErrMsg = 0;

	QPixmap inPixmap;
	inPixmap.fromImage(img.image_preview);
	QByteArray inByteArray;
	QBuffer inBuffer(&inByteArray);
	inBuffer.open(QIODevice::WriteOnly);
	inPixmap.save(&inBuffer, "PNG");

	if (DBController::openDB()) {
		//sqlite3_exec(db, sql, callback, NULL, &zErrMsg);
		char* query;
		query = "INSERT INTO Images	(IMAGE_ID, "\
			"IMAGE_PREVIEW_BLOB, "\
			"TIMESTAMP, "\
			"IMAGESIZE, "\
			"RESOLUTION, "\
			"BROTH_ID, "\
			"GROUP_ID) "  \
			"VALUES				(" + std::to_string(img.image_id) + ","\
			+ inByteArray.toStdString + ","\
			+ img.date + ","\
			+ std::to_string(img.imagesize) + ","\
			+ std::to_string(img.resolution) + ","\
			+ std::to_string(img.broth_id) + ","\
			+ std::to_string(img.group_id) + \
			")";
		int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			return false;
		} else {
			fprintf(stdout, "Records created successfully\n");
			return true;
		}
	} else {
		return false;
	}
	DBController::closeDB();
 }*/