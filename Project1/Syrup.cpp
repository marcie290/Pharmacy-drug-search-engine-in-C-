#include "Syrup.h"
#include <string>

class Drug;


Syrup::Syrup(const char *_name, int _id, int _cost, int _age1, int _age2, string _symptom, string _category):

	Drug{ _name, _id, _cost, _age1, _age2, _symptom }, category(_category) {

}