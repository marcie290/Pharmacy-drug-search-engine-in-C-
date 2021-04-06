#include <iostream>
#include "Drug.h"
#include <string>
#pragma once

using namespace std;


class Tablets : public Drug {

	string category;

public:
	Tablets(const char *_name, int id, int _cost, int _age1, int _age2, string _symptom, string category);

	virtual void show_category() {}

};