#include <DBController.h>
#include <sqlite/sqlite3.h> 

using namespace std;


DBController::DBController() {
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


vector<Image> DBController::testCon(void) {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	string query = "SELECT * FROM Streptomyceten;";

	rc = sqlite3_open("../Database/StreptoDB.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
		sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg);
	}
	sqlite3_close(db);

	return *result;
}
