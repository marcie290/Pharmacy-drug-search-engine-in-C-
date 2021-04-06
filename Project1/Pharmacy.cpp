#include "Pharmacy.h"
#include "Drug.h"
#include "Syrup.h"
#include "Tablets.h"
#include "Powder.h"
#include "Pointers.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <bitset>
#include <cctype>
#include <algorithm>  
#include <vector> 
#include <numeric>
#include <iterator>  
#include <streambuf>


struct Pointers;
class Drug;

using namespace std;

string read_from_text_file(string fileName, Pointers *&pHead) {

	std::ifstream ifs(fileName);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	return content;
}

string read_from_binary_file(string fileName)
{

	ifstream file(fileName, ios::binary);
	vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});

	ostringstream vts;

	if (!buffer.empty())
	{
		std::copy(buffer.begin(), buffer.end() - 1,
			std::ostream_iterator<unsigned char>(vts, ""));

		vts << buffer.back();
	}

	string data = vts.str();

	stringstream sstream(data);
	string output;

	while (sstream.good())
	{
		bitset<8> bits;
		sstream >> bits;
		char c = char(bits.to_ulong());
		output += c;
	}

	cout << output << endl;
	return output;
}

void extract_data(string output, Pointers *&pHead) {

	output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
	std::string delimiter = ",", new_data;
	size_t last = 0, next = 0;
	int it = 0, id, cost, age1, age2, n;
	string nazwa;


	while (((next = output.find(delimiter, last)) != string::npos) && ((next + 2) != string::npos)) {


		new_data = output.substr(last, next - last);
		last = next + 1;

		switch (it) {

		case 0: {

			nazwa = new_data;
			it++;
		}
				break;

		case 1: {

			id = string_to_int(new_data);
			it++;
		}
				break;

		case 2: {
			cost = string_to_int(new_data);
			it++;
		}
				break;

		case 3: {
			age1 = string_to_int(new_data);
			it++;
		}
				break;

		case 4: {
			age2 = string_to_int(new_data);
			it++;
		}
				break;

		default:
			cout << "nie udalo sie switch" << endl;
		}

		Drug* dodP = nullptr;

		if ((it == 5)) {

			n = nazwa.length();
			char *name = new char[n + 1];
			strcpy(name, nazwa.c_str());

			switch (id) {
			case 1: {

				dodP = dynamic_cast<Drug*>(new Syrup(name, id, cost, age1, age2, "", "syrup"));
				addPointer(pHead, dodP);
			}
					break;

			case 2: {

				dodP = dynamic_cast<Drug*>(new Tablets(name, id, cost, age1, age2, "", "tablets"));
				addPointer(pHead, dodP);
			}
					break;

			case 3: {
			
				dodP = dynamic_cast<Drug*>(new Powder(name, id, cost, age1, age2, "", "powder"));
				addPointer(pHead, dodP);
			}
					break;

			default:
				cout << "nie udalo sie przypisac do odpowiedniej klasy" << endl;
			}

			it = 0;
			delete[]name;
		}
		dodP = nullptr;
	}
}

int string_to_int(string new_data) {
	int nmb;
	stringstream geek(new_data);
	geek >> nmb;
	return nmb;
}


void add_symptoms(string name_of_drug, string symptoms, Pointers *pHead) {


	while (pHead) {

		if (pHead->obj->get_name() == name_of_drug) {

			pHead->obj->add_symptom(symptoms);
			return;
		}

		pHead = pHead->next;
	}

}

void extract_symptoms(string fileName, Pointers *&pHead) {

	int pos;
	string name_of_drug, symptoms, line;
	ifstream inFile;
	inFile.open(fileName, ios::in);

	if (inFile.good() == false)
	{
		cout << " nie udalo sie otworzyc pliku" << endl;
	}
	else
	{
		while (!inFile.eof())
		{
			getline(inFile, line);

			pos = line.find(",");
			name_of_drug = line.substr(0, pos);
			line.erase(0, pos + 1);

			symptoms = line;
			add_symptoms(name_of_drug, symptoms, pHead);

		}
		inFile.close();
	}
}


void write_to_file(string outsetFile, Pointers *pHead) {

	ofstream file;
	file.open(outsetFile);
	string str;
	string nazwa, liczba;

	while (pHead) {


		std::string s;
		std::stringstream ss;
		ss << pHead->obj->get_name();
		ss >> nazwa;
		nazwa = " " + nazwa;
		str.append(nazwa.begin(), nazwa.end());

		nazwa = std::to_string(pHead->obj->get_cost());
		nazwa = " " + nazwa;
		str.append(nazwa.begin(), nazwa.end());

		nazwa = std::to_string(pHead->obj->get_age1());
		nazwa = " " + nazwa;
		str.append(nazwa.begin(), nazwa.end());

		nazwa = std::to_string(pHead->obj->get_age2());
		nazwa = " " + nazwa;
		str.append(nazwa.begin(), nazwa.end());

		nazwa = pHead->obj->get_symptom();
		nazwa = " " + nazwa;
		str.append(nazwa.begin(), nazwa.end());

		nazwa = "\n";
		nazwa = " " + nazwa;
		str.append(nazwa.begin(), nazwa.end());
		pHead = pHead->next;

	}

	for (std::size_t i = 0; i < str.size(); ++i)
	{
		file<< bitset<8>(str.c_str()[i]);
	}
	cout << "Pomyslnie zapisano do pliku wyjsciowego." << endl;

	file.close();
}