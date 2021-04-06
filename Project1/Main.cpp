#include "Pharmacy.h"
#include "Drug.h"
#include "Syrup.h"
#include "Tablets.h"
#include "Powder.h"
#include "Pointers.h"
#include <string>

using namespace std;

struct Pointers;
class Drug;


int main(int argc, char **argv)
{
	bool b = 0;
	string  out = "-out", inmed = "-inmed", insym = "-insym", outset = "-outset";
	string outFile, inmedFile, inSymFile, outsetFile;
	int var;
	Pointers *pHead = nullptr;

	for (int i = 1; i < argc; ++i) {
		if (i + 1 == argc) {
			break;
		}


		if (argv[i] == out) {
			outFile = argv[i + 1];
		}
		else if (argv[i] == inmed) {
			inmedFile = argv[i + 1];
		}
		else if (argv[i] == insym) {
			inSymFile = argv[i + 1];
		}
		else if (argv[i] == outset) {
			outsetFile = argv[i + 1];
		}
	}

	if (outFile == "" || inmedFile == "" || inSymFile == "" || outsetFile == "") {
		cout << "\nNie udalo sie otworzyc pliku.\nNie istnieje albo nie podales rozszerzenia."<< endl;
		exit(0);
	}

	string output = read_from_text_file(inmedFile, pHead); 
	extract_data(output, pHead);
	extract_symptoms(inSymFile, pHead);


	cout << "\n***********************************************" << endl;
	cout << "\n\n******************APTEKA***********************" << endl;
	cout << "\n\n***********************************************\n\n" << endl;
	cout << "Witamy w naszej aptece. W czym mozemy Ci pomoc?";

	while (1) {

		cout << "\n\nMENU GLOWNE" << endl;
		cout << "1. Chce wyszukac lek odpowiedni dla siebie." << endl;
		cout << "2. Chce zobaczyc cala baze lekow." << endl;
		cout << "3. Chce dopisac nowy lek" << endl;
		cout << "4. Chce zapisac dane do pliku binarnego i odczytac je z tego pliku." << endl;
		cout << "5. Koniec programu.\n" << endl;
		cout << "Wybierz odpowiedni numer: " << endl;

		if (!(cin >> var)) {
			cerr << "To nie jest liczba!" << endl;
			b = true;
			break;
		}

		switch (var) {

		case 1:
			find(pHead, outsetFile);
			break;

		case 2:
			show_base(pHead);
			break;

		case 3:
			add_drug(pHead);
			break;
		case 4: {
			write_to_file(outFile, pHead);
			read_from_binary_file(outFile);
		}break;

		case 5: {
			b = true;
		}break;

		default:
			cout << "Nie ma takiej opcji w menu." << endl;
			b = true;
			break;
		}

		if (b) {
			break;
		}
		else
			b = 0;

	}

	deleteList(pHead);

	return 0;
}