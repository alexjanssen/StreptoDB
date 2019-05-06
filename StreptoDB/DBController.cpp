#include <stdio.h>
#include <sqlite/sqlite3.h> 


class DBController {
public:
	double length;         // Length of a box
	double breadth;        // Breadth of a box
	double height;         // Height of a box

	// Member functions declaration
	//double getVolume(void);
	//int testCon(void);


	// Member functions definitions
	int DBController::testCon(void) {
		sqlite3* db;
		char* zErrMsg = 0;
		int rc;

		rc = sqlite3_open("../Database/StreptoDB.db", &db);

		if (rc) {
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			return '0';
		}
		else {
			fprintf(stderr, "Opened database successfully\n");
		}
		sqlite3_close(db);

		return 1;
	}

};

/*int DBController(){
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	rc = sqlite3_open("../Database/StreptoDB.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		//return(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
	sqlite3_close(db);

	return 0;
}*/
	



