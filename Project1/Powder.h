#include <iostream>
#include "Drug.h"
#include <string>
#pragma once

using namespace std;


class Powder : public Drug {

	string category;

public:

	Powder(const char *_name, int id, int _cost, int _age1, int _age2, string _symptom, string category);

	virtual void show_category() {

		cout << category << endl;
	}
};
