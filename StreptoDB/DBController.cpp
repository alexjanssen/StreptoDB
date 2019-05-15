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
	Isolat iso2 = Isolat();
	int i;
	int* col_width = (int*)param; // this isn't necessary, but it's convenient
	
	result->empty();
	// print out the contents of the row
	//for (i = 0; i < numCols; i++) {
	iso2.id = (int)col[0];
	iso2.id_intern = (int)col[1];
	iso2.id_group = (int)col[2];
	iso2.multiple_counter = (int)col[3];
	iso2.date = col[4];
	iso2.scientific_name = col[5];
	iso2.spore_color = col[6];
	iso2.genome_link = col[7];
	iso2.image_preview = (QImage)col[8];
	iso2.siderophore_bool = col[9];
	iso2.broth_id = (int)col[10];
	iso2.image_para_id = (int)col[11];
	iso2.locality = col[12];
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
