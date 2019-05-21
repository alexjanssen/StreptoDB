#pragma once

#include <stdio.h>
#include <Image.cpp>
#include <vector>

using namespace std;

class DBController {
public:
	DBController();

	vector<Image> testCon(void);



	//static int callback();
	//vector<Isolat> DBController::testCon(void);

	// = new vector<Isolat>;
	//vector<Isolat> DBController::result3;
};
static vector<Image> *result = new vector<Image>;