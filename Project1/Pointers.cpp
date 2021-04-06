#include "Pointers.h"
#include "Syrup.h"
#include "Powder.h"
#include "Tablets.h"
#include <string>



void addPointer(Pointers *&pHead, Drug *drug) {

	if (not pHead) {

		pHead = new Pointers{ drug, nullptr };
	}

	else
		addPointer(pHead->next, drug);
}


void deleteList(Pointers *& pHead) {

	if (pHead) {

		delete pHead->obj;
		pHead->obj = nullptr;
		
		auto p = pHead->next;
		delete pHead;
		pHead = nullptr;
		deleteList(pHead);
	}
}

void find(Pointers *pHead, string outsetFile) {

	int patients_age;
	string patients_symptoms;

	cout << "Podaj swoj wiek: " << endl;
	cin >> patients_age;
	cout << "Prosze podaj swoje objawy oddzielone przecinkami. Prosze nie uzywac polskich znakow." << endl;
	cin.ignore();
	getline(cin, patients_symptoms);
	

	const char chr[] = "default";
	Syrup objector(chr, 0, 0, 0, 0, "without", "def cat");

	objector.find_drug(patients_age, patients_symptoms, pHead, outsetFile);
}

void show_base(Pointers *pHead) {

	while (pHead) {
		pHead->obj->show();
		pHead = pHead->next;
	}

}

void  add_drug(Pointers *&pHead) {

	int id, cost, age1, age2;
	string new_data, symptom;

	cout << "Wybierz kategoriê leku." << endl;
	cout << "1. Syrop" << endl;
	cout << "2. Tabletka" << endl;
	cout << "3. Proszek" << endl;
	cin >> id;
	cout << "Podaj nazwe leku." << endl;
	cin >> new_data;
	char *name = new char[new_data.size() + 1];
	strcpy(name, new_data.c_str());
	cout << "Podaj cene leku." << endl;
	cin >> cost;
	cout << "Podaj przedzial wiekowy, dla ktorego mozna go stosowac." << endl;
	cout << "Od: ";
	cin >> age1;
	cout << "\nDo: ";
	cin >> age2;
	cout << "Wypisz oddzielone przecinkami objawy, dla ktorych pomaga." << endl;
	cin.ignore();
	getline(cin, symptom);


	switch (id) {

	case 1: {
		Syrup *new_obj = new Syrup(name, id, cost, age1, age2, symptom, "syrop");
		cout << "Pomyslnie dodano." << endl;
		addPointer(pHead, new_obj);
		break;}

	case 2: {
		Tablets *new_obj = new Tablets(name, id, cost, age1, age2, symptom, "tablets");
		cout << "Pomyslnie dodano." << endl;
		addPointer(pHead, new_obj);
		break;}
	case 3: {
		Powder *new_obj = new Powder(name, id, cost, age1, age2, symptom, "tablets");
		cout << "Pomyslnie dodano." << endl;
		addPointer(pHead, new_obj);
		break;}
	default: {
		cout << "nie udalo sie dopisac" << endl;
		break;}
	}

	delete[]name;
}