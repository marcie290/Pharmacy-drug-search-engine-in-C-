#include "Drug.h"
#include <string>
#include <algorithm>
#include <fstream>

Drug::Drug(const char *_name, int _id, int _cost, int _age1, int _age2, string _symptom)
	:name(new char[strlen(_name) + 1]), cost(_cost), id(_id), age1(_age1), age2(_age2), symptom(_symptom) {

	strcpy(name, _name);
}


void Drug::show() {

	cout << name << ", cena:" << cost << "zl, wiek:" << age1 << "-" << age2 << "lat, Objawy:" << symptom << endl;
}


void Drug::find_drug(int patients_age, string pSymptoms, Pointers *pHead, string outsetFile) {

	int it = 0, i = 1;
	bool b1, b2, b3, b4 = 0, b5 = 0;

	string temp_str;
	size_t found;

	pSymptoms.erase(std::remove(pSymptoms.begin(), pSymptoms.end(), '\n'), pSymptoms.end());
	pSymptoms.append(",", 1);
	std::string delimiter = ",", new_data;
	size_t last = 0, next = 0;


	ofstream file;
	file.open(outsetFile);

	while (((next = pSymptoms.find(delimiter, last)) != string::npos) && ((next + 2) != string::npos)) {

		Pointers *ptr = pHead;
		Pointers *pH = pHead;

		new_data = pSymptoms.substr(last, next - last);
		last = next + 1;


		while (pH) {


			temp_str = pH->obj->get_symptom();
			found = temp_str.find(new_data);

			b1 = (pH->obj->get_age1() <= patients_age);
			b2 = (pH->obj->get_age2() >= patients_age);
			b3 = (found != string::npos);

			if (b1 && b2 && b3) {
				it++;

				b5 = true;

				if (b4 == 0) {
					ptr = pH;
					b4 = true;
				}

				if (it == 2) {

					cout << "\n\n************Zestaw" << i << "************************\n";
					pH->obj->show();
					ptr->obj->show();
					cout << "RAZEM: " << ((ptr->obj->get_cost()) + (pH->obj->get_cost())) << "zl" << endl;

					b4 = 0;
					it = 0;

					int price1 = ptr->obj->get_cost();
					int price2 = pH->obj->get_cost();
					file << "\n\n************Zestaw " << i << "************************\n";
					file << pH->obj->get_name() << ", cena:" << price1 << " zl, " << ptr->obj->get_name() << ", cena:" << price2 << " zl, " << endl;
					file << "RAZEM: " << price1 + price2 << endl;
					i++;
				}
			}
			pH = pH->next;
		}



		if (it == 1) {
			cout << "\n\n************Lek" << "************************\n";
			ptr->obj->show();
			cout << "CENA: " << ptr->obj->get_cost() << "zl" << endl;
		}
	}

	if (b5 == 0) {
		cout << "\nLeku, ktory jest dla Ciebie odpowiedni, nie ma w naszej bazie. " << endl;
		cout << "Wybierz numer 2, aby zobaczyc baze dostepnych lekow. " << endl;
	}
}
