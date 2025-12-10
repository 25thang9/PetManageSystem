// FileHandler.h - Đọc/ghi file (Abstraction)
#pragma once
#include <vector>
#include "../Pet/Pet.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
using std::vector;
class FileHandler {
public:
    static void loadFromFile(vector<Pet*>& list);
    static void saveToFile(const vector<Pet*>& list);
};