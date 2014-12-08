#include "scientist.h"

Scientist::Scientist() {
    name = "";
    dateOfBirth = "";
    dateOfDeath = "";
    gender = "";
    ID = "";
    //computers = "";
}

bool Scientist::operator==(const Scientist& right) {
    return this->name == right.name;
}
