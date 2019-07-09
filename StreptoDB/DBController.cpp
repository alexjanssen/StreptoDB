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
	



//This function is called to receive the query result of "DBController::getImages()" and 
//write that to the static vector "result".
static int callback(void* param, int numCols, char** col, char** colName)
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
	img.resolution = atoi(col[4]);
	img.broth_id = atoi(col[5]);
	img.group_id = atoi(col[6]);
	img.filePath = (string)col[7];

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

	grp.group_id = atoi(col[0]);
	grp.intern_id = (string)(col[1]);
	grp.date = (string)col[2];
	grp.sci_name = (string)col[3];
	grp.genome_lnk = (string)col[4];
	grp.locality = (string)col[5];
	grp.siderophore = (bool)atoi(col[6]);
	grp.spore_color = (string)col[7];

	//result->push_back(grp);

	return 0;
}


//This function is called to receive the query result of "DBController::getBroth()" and 
//write that to the static Object broth.
static int callback_broth(void* param, int numCols, char** col, char** colName)
{
	// int numCols: holds the number of results
	// (array) colName: holds each column returned
	// (array) col: holds each value
	//Group grp = Group();
	int* col_width = (int*)param; // this isn't necessary, but it's convenient

	broth.broth_id = atoi(col[0]);
	broth.name = (string)(col[1]);
	broth.info = (string)col[2];

	//result->push_back(grp);

	return 0;
}


//same shit for Calculated-Paramaters
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


//still same shit
static int callback_maxCalcParamID(void* param, int numCols, char** col, char** colName)
{
	int* col_width = (int*)param;
	maxCalcParamID = atoi(col[0]);
	return 0;
}


//still same shit
static int callback_maxInhibitID(void* param, int numCols, char** col, char** colName)
{
	int* col_width = (int*)param;
	maxInhibitID = atoi(col[0]);
	return 0;
}


//same shit for Compare
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

	si.id_intern = (string)(col[0]);
	si.broth_name = (string)(col[1]);
	si.strain_name = (string)col[2];
	si.inhibition = (bool)atoi(col[3]);

	result_inhibition->push_back(si);

	return 0;
}


//same shit for testStrains
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
					"I.RESOLUTION, " \
					"I.BROTH_ID, " \
					"I.GROUP_ID, " \
					"I.PATH, " \
					"S.ID_INTERN " \
					"FROM Images I LEFT JOIN Streptomyceten S ON I.GROUP_ID = S.ID_GROUP " \
					"WHERE S.ID_INTERN LIKE '" + filt + "%';";

	int rc = DBController::openDB();
	if (rc) {
		result->clear();
		sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg);
	}
	else {
		DBOUT("Can't execute SQL-Statement(DBController::getImages()):(80)", sqlite3_errmsg(db));
	}
	sqlite3_close(db);

	return *result;
}


 //return Group for specific GROUP_ID
 Group DBController::getGroup(int id) {
	 char* zErrMsg = 0;
	 string query = "SELECT * FROM Streptomyceten WHERE ID_GROUP = "+ std::to_string(id) +";";
	 int rc = DBController::openDB();
	 if (rc) {
		 //result->empty();
		 sqlite3_exec(db, query.c_str(), callback_group, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getGroup(int)):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return grp;
 }


 //return Broth for specific BROTH_ID
 Broth DBController::getBroth(int id) {
	 char* zErrMsg = 0;
	 string query = "SELECT * FROM Broth WHERE BROTH_ID = " + std::to_string(id) + ";";
	 int rc = DBController::openDB();
	 if (rc) {
		 //result->empty();
		 sqlite3_exec(db, query.c_str(), callback_broth, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getBroth(int)):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return broth;
 }


 //return max ID from Calculated Parameters
 int DBController::getMaxCalcParamID() {
	 char* zErrMsg = 0;
	 string query = "SELECT MAX(CalcP_ID) FROM CalculatedParameters;";
	 int rc = DBController::openDB();
	 if (rc) {
		 //result->empty();
		 sqlite3_exec(db, query.c_str(), callback_maxCalcParamID, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getMaxCalcParamID()):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return maxCalcParamID;
 }


 //return max ID from Strain-Inhibition
 int DBController::getMaxInhibitionID() {
	 char* zErrMsg = 0;
	 string query = "SELECT MAX(\"STRAIN-INHIBITS_ID\") FROM 'Strain-Inhibits';";
	 int rc = DBController::openDB();
	 if (rc) {
		 //result->empty();
		 sqlite3_exec(db, query.c_str(), callback_maxInhibitID, NULL, &zErrMsg);
	 }
	 else {
		 DBOUT("Can't execute SQL-Statement(DBController::getInhibitID()):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return maxInhibitID;
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
		 DBOUT("Can't execute SQL-Statement(DBController::getCalcedParams(int)):", sqlite3_errmsg(db));
	 }
	 sqlite3_close(db);

	 return *result_inhibition;
 }


 //Todo comment
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
			 "INSERT INTO Images(IMAGE_ID, IMAGE_PREVIEW_BLOB, TIMESTAMP, IMAGESIZE, RESOLUTION, BROTH_ID, GROUP_ID, PATH)" \
			 " VALUES(?,?,?,?,?,?,?,?);", \
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
			 sqlite3_bind_double(stmt, 5, img.resolution);
			 sqlite3_bind_int(stmt, 6, img.broth_id);
			 sqlite3_bind_int(stmt, 7, img.group_id);
			 sqlite3_bind_text(stmt, 8, img.filePath.c_str(), -1, SQLITE_STATIC);

			 if (rc != SQLITE_OK) {
				 DBOUT("bind failed: DBController::addImage2(Image)", sqlite3_errmsg(db));
				 return false;
			 }
			 else {
				 rc = sqlite3_step(stmt);
				 if (rc != SQLITE_DONE)
					 DBOUT("execution failed: DBController::addImage2(Image)", sqlite3_errmsg(db));
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


 //Todo comment
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


 //Todo comment
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