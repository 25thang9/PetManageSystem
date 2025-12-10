// Pet.cpp - Định nghĩa các hàm của lớp Pet
#include "Pet.h"
using namespace std;

// Constructor
Pet::Pet(string s, string n, int a, string c, string b, string o)
    : species(s), name(n), age(a), color(c), breed(b), owner(o) {}

// Hàm hiển thị 
void Pet::display() const {
    cout << left
         << setw(10) << species
         << setw(15) << name
         << setw(6)  << age
         << setw(12) << color
         << setw(15) << breed
         << owner << endl;
}