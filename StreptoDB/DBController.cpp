#include <DBController.h>
#include <fstream> 
#include <iostream>
#include <Windows.h>
#include <sstream>
using namespace std;



#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}


DBController::DBController() {
	db_name = "../Database/StreptoDB.db";
}
	
static int callback(void* param, int numCols, char** col, char** colName)
{
	// int numCols: holds the number of results
	// (array) colName: holds each column returned
	// (array) col: holds each value
	Image img = Image();
	int i;
	int* col_width = (int*)param; // this isn't necessary, but it's convenient
	
	result->empty();
	// print out the contents of the row
	//for (i = 0; i < numCols; i++) {
	img.image_id = (int)col[0];
	img.image_preview = (QImage)col[1];
	img.date = (string)col[2];
	img.imagesize = (int)col[3];
	img.resolution = (int)col[4];
	img.broth_id = (int)col[5];
	img.group_id = (int)col[6];

	//QByteArray outByteArray = col[8];
	//QImage image;// = (QImage)col[8];
	//image.fromData(outByteArray);
	//outPixmap.fromImage(outByteArray);

	result->push_back(img);

	return 0;
}


bool DBController::openDB() {
	//return true if DB-Connection opened successfully
	char* zErrMsg = 0;
	int rc;
	rc = sqlite3_open("../Database/StreptoDB.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return false;
	} else {
		fprintf(stderr, "Opened database successfully\n");
		return true;
	}
}

void DBController::closeDB() {
	//closes the DB-Connection
	sqlite3_close(db);
}


vector<Image> DBController::getImages(void) {	
	char* zErrMsg = 0;
	string query = "SELECT * FROM Images;";
	int rc = DBController::openDB();
	if (rc) {
		sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg);
	}
	else {
		fprintf(stderr, "Can't execute SQL-Statement(DBController::getImages()): %s\n", sqlite3_errmsg(db));
	}
	DBController::closeDB();

	return *result;
}


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




 bool DBController::addImage2(Image img) {
	 
	 ifstream file("banana.JPG", ios::in | ios::binary);
	 if (!file) {
		 return false;
	 }
	 file.seekg(0, ifstream::end);
	 streampos size = file.tellg();
	 file.seekg(0);

	 char* buffer = new char[size];
	 file.read(buffer, size);

	 //sqlite3* db = NULL;
	 int rc = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);
	 if (rc != SQLITE_OK) {
		 return false;// cerr << "db open failed: " << sqlite3_errmsg(db) << endl;
	 }
	 else {
		 sqlite3_stmt* stmt = NULL;
		 rc = sqlite3_prepare_v2(db, \
			 "INSERT INTO Image(IMAGE_ID, IMAGE_PREVIEW_BLOB, TIMESTAMP, IMAGESIZE, RESOLUTION, BROTH_ID, GROUP_ID)" \
			 " VALUES(?,?,?,?,?,?,?)", \
			 -1, &stmt, NULL); 
		 if (rc != SQLITE_OK) {
			 DBOUT("prepare failed: DBController(162)");
			 return false;//cerr << "prepare failed: " << sqlite3_errmsg(db) << endl;
		 }
		 else {
			 // SQLITE_STATIC because the statement is finalized
			 // before the buffer is freed:
			 sqlite3_bind_int(stmt, 1, img.image_id);
			 rc = sqlite3_bind_blob(stmt, 2, buffer, size, SQLITE_STATIC);
			 sqlite3_bind_text(stmt, 3, img.date.c_str(), -1, SQLITE_STATIC);
			 sqlite3_bind_double(stmt, 4, img.imagesize);
			 sqlite3_bind_double(stmt, 5, img.resolution);
			 sqlite3_bind_int(stmt, 6, img.broth_id);
			 sqlite3_bind_int(stmt, 7, img.group_id);

			 if (rc != SQLITE_OK) {
				 DBOUT("bind failed: DBController(176)");
				 
				 return false;// cerr << "bind failed: " << sqlite3_errmsg(db) << endl;
			 }
			 else {
				 rc = sqlite3_step(stmt);
				 if (rc != SQLITE_DONE)
					 DBOUT("execution failed: DBController(183)");
					 return false;// cerr << "execution failed: " << sqlite3_errmsg(db) << endl;
			 }
		 }
		 sqlite3_finalize(stmt);
	 }
	 sqlite3_close(db);

	 delete[] buffer;
	 return true;
 }