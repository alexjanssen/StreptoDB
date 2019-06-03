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
	int i;
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
vector<Image> DBController::getImages(void) {	
	char* zErrMsg = 0;
	string query = "SELECT * FROM Images;";
	int rc = DBController::openDB();
	if (rc) {
		result->empty();
		sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg);
	}
	else {
		DBOUT("Can't execute SQL-Statement(DBController::getImages()):(80)", sqlite3_errmsg(db));
	}
	sqlite3_close(db);

	return *result;
}






 //Todo comment
 bool DBController::addImage2(Image img) {
	 
	 QImage image(QString::fromStdString(img.filePath));
	 if (image.isNull())
	 {
		 DBOUT("Image file open failed: DBController(147)", sqlite3_errmsg(db));
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
		 DBOUT("db open failed: DBController(152)", sqlite3_errmsg(db));
		 return false;
	 }
	 else {
		 sqlite3_stmt* stmt = NULL;
		 string err_str;
		 rc = sqlite3_prepare(db, \
			 "INSERT INTO Images(IMAGE_ID, IMAGE_PREVIEW_BLOB, TIMESTAMP, IMAGESIZE, RESOLUTION, BROTH_ID, GROUP_ID, PATH)" \
			 " VALUES(?,?,?,?,?,?,?,?);", \
			 -1, &stmt, NULL); 
		 if (rc != SQLITE_OK) {
			 DBOUT("prepare failed: DBController(162)" , sqlite3_errmsg(db));
			 
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
				 DBOUT("bind failed: DBController(176)", sqlite3_errmsg(db));
				 return false;
			 }
			 else {
				 rc = sqlite3_step(stmt);
				 if (rc != SQLITE_DONE)
					 DBOUT("execution failed: DBController(183)", sqlite3_errmsg(db));
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





 //Stuff I might need later idk
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