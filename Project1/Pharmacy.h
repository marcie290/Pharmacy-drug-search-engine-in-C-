#include <iostream>
#include "Pointers.h"
#pragma once

using namespace std;

struct Pointers;

string read_from_text_file(string fileName, Pointers *&pHead);
string read_from_binary_file(string fileName);


int string_to_int(string new_data);


void write_to_file(string outsetFile, Pointers *pHead);

