#include <iostream>
#include "Pointers.h"

#pragma once

using namespace std;

class Drug {

	char  *name;
	int id, cost, age1, age2;
	string symptom;

public:

	Drug(const char *_name, int id, int _cost, int _age1, int _age2, string _symptom);

	virtual~Drug() {

		delete[]name;
	}
   
	virtual void show_category()=0;

	void find_drug(int patients_age, string patients_symptoms,
		           Pointers *pHead, string outsetFile);

	void show();


	char  *get_name() const {
		return name;
	}

	int get_cost() const {
		return cost;
	}

	int get_age1() const {
		return age1;
	}

	int get_age2() const {
		return age2;
	}

	string get_symptom() const {
		return symptom;
	}

	void add_symptom(string _symptom) {
		symptom = _symptom;
	}
};

