#pragma once

#include <stdio.h>
#include <Isolat.cpp>
#include <vector>

using namespace std;

class DBController {
public:
	DBController();

	vector<Isolat> testCon(void);



	//static int callback();
	//vector<Isolat> DBController::testCon(void);

	// = new vector<Isolat>;
	//vector<Isolat> DBController::result3;
};
static vector<Isolat> *result = new vector<Isolat>;