#include <iostream>
#include "Drug.h"
#include <string>
//#include <string.h>
#pragma once

using namespace std;

class Drug;

class Syrup : public Drug {

	string category;

public:

	Syrup(const char *_name, int id, int _cost, int _age1, int _age2, string _symptom, string category);
	virtual void show_category() {

		cout << category << endl;
	}
};

