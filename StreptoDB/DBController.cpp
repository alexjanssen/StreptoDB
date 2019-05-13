#include <DBController.h>
#include <sqlite/sqlite3.h> 
//#include <stdio.h>
//#include <string>
//#include <Isolat.cpp>
//#include <vector>


using namespace std;


DBController::DBController() {
	//result3 = *new vector<Isolat>;
}
	
static int callback(void* param, int numCols, char** col, char** colName)
{
	// int numCols: holds the number of results
	// (array) colName: holds each column returned
	// (array) col: holds each value
	Isolat iso2 = Isolat();
	int i;
	int* col_width = (int*)param; // this isn't necessary, but it's convenient
	
	result->empty();
	// print out the contents of the row
	//for (i = 0; i < numCols; i++) {
	iso2.name = col[0];
	iso2.image = (QImage)col[1];
	iso2.medium = col[2];
	result->push_back(iso2);
	//cout << " | " << setw(col_width[i]) << col[i];
//}
//cout << endl;

	return 0;
}


vector<Isolat> DBController::testCon(void) {
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
