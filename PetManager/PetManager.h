// PetManager.h - Lớp chính quản lý (Composition + RAII)
#pragma once
#include "../Pet/Pet.h"
#include "../FileHandle/FileHandler.h"
#include "../Menu/SubMenu.h"          // Menu con dùng mũi tên
#include <algorithm>
#include <map>
#include <limits>
#include <sstream>
#include <windows.h>
#include <vector>
using namespace std;
class PetManager {
    vector<Pet*> pets;
public:
    ~PetManager();                          // Tự động dọn dẹp
    void loadData();
    void saveData() const;
    void addPet();
    void displayAll() const;
    void displayAndSearchMenu();            // Mục 2 – có menu con
    void editPet();
    void deletePet();
    void sortMenu();                        // Mục 5 – 5.1 đến 5.6
    void statisticsMenu() const;            // Mục 6 – 6.1 đến 6.4
    void fileManagementMenu();              // Mục 7 - 7.1 đến 7.3   
private:
    void searchByName() const;
    void filterBySpecies() const;
    void filterByColor() const;
    void filterByOwner() const;
};