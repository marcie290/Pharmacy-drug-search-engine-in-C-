#include <iostream>
#pragma once

using namespace std;

class Drug;

struct Pointers {
	Drug *obj;
	Pointers *next;
};


void addPointer(Pointers *& pHead, Drug *drug);

void extract_data(string output, Pointers *&pHead);
void extract_symptoms(string fileName, Pointers *&pHead);


void find(Pointers *pHead, string outsetFile);
void  add_drug(Pointers *&pHead);


void deleteList(Pointers *& pHead);
void show_base(Pointers *pHead);
