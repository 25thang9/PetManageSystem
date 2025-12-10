// FileHandler.cpp - Safe file read/write with full support for spaces & Unicode
#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
using namespace std;

void FileHandler::loadFromFile(vector<Pet*>& list)
{
    ifstream file("pets.txt");

    if (!file.is_open()) {
        cout << "File pets.txt not found -> Starting with empty list.\n";
        return;
    }

    string line;
    int count = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;  // Skip empty lines

        stringstream ss(line);
        string species, name, color, breed, owner;
        int age;

        // Use tab (\t) as delimiter → 100% safe with spaces
        if (!getline(ss, species, '\t')) continue;
        if (!getline(ss, name,    '\t')) continue;
        if (!(ss >> age)) continue;
        ss.ignore(); // Skip the tab after the number
        if (!getline(ss, color,   '\t')) continue;
        if (!getline(ss, breed,   '\t')) continue;
        if (!getline(ss, owner,   '\t')) owner = ""; // Owner can be empty

        list.push_back(new Pet(species, name, age, color, breed, owner));
        count++;
    }

    file.close();
    cout << "Successfully loaded " << count << " pet(s) from pets.txt!\n";
}

void FileHandler::saveToFile(const vector<Pet*>& list)
{
    ofstream file("pets.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot create pets.txt file!\n";
        return;
    }

    for (const auto& p : list) {
        file << p->getSpecies() << "\t"
             << p->getName()    << "\t"
             << p->getAge()     << "\t"
             << p->getColor()   << "\t"
             << p->getBreed()   << "\t"
             << p->getOwner()   << "\n";
    }

    file.close();
    cout << "Successfully saved " << list.size() << " pet(s) to pets.txt!\n";
}