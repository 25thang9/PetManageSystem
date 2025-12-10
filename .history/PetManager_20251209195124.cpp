// PetManager.cpp - FINAL VERSION 2025: Full arrow key menu, Vietnamese support, perfect file I/O
#include "PetManager.h"
#include "FileHandler.h"
#include "SubMenu.h"          // Menu con dùng mũi tên
#include <algorithm>
#include <map>
#include <limits>
#include <sstream>
#include <windows.h>
using namespace std;

// RAII - Destructor
PetManager::~PetManager() {
    for (auto p : pets) delete p;
    pets.clear();
}

void PetManager::loadData() { FileHandler::loadFromFile(pets); }
void PetManager::saveData() const { FileHandler::saveToFile(pets); }
// ADD PET
void PetManager::addPet() {
    system("cls");
    cout << "╔══════════════════════════════════╗\n";
    cout << "║          ADD NEW PET             ║\n";
    cout << "╚══════════════════════════════════╝\n\n";

    string species, name, color, breed, owner;
    int age;

    cout << "Species          : ";   getline(cin, species);
    cout << "Name             : ";   getline(cin, name);
    
    cout << "Age              : ";
    while (!(cin >> age)) {
        cout << "          Age must be a number! Re-enter: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(); // 

    cout << "Color            : ";   getline(cin, color);
    cout << "Breed            : ";   getline(cin, breed);
    cout << "Owner            : ";   getline(cin, owner);

    pets.push_back(new Pet(species, name, age, color, breed, owner));

    cout << "\n          ADDED SUCCESSFULLY!\n\n";
    system("pause");
}

// HIỂN THỊ TẤT CẢ
void PetManager::displayAll() const {
    system("cls");
    if (pets.empty()) {
        cout << "          List is empty!\n\n";
        system("pause");
        return;
    }

    cout << "SPECIES    NAME                AGE  COLOR         BREED           OWNER\n";
    cout << string(85, '=') << endl;
    for (const auto& p : pets) p->display();
    cout << string(85, '=') << endl;
    cout << "          Total: " << pets.size() << " pet(s)\n\n";
    system("pause");
}

// TÌM KIẾM & LỌC
void PetManager::searchByName() const {
    string n;
    cout << "          Enter pet name to search: ";
    cin.ignore();
    getline(cin, n);

    bool found = false;
    cout << "\n          RESULTS:\n";
    cout << string(85, '-') << endl;
    for (const auto& p : pets) {
        if (p->getName() == n) {
            p->display();
            found = true;
        }
    }
    if (!found) cout << "          Not found!\n";
    cout << string(85, '-') << endl;
    system("pause");
}

void PetManager::filterBySpecies() const { /* giữ nguyên như cũ */ }
void PetManager::filterByColor() const { /* giữ nguyên */ }
void PetManager::filterByOwner() const { /* giữ nguyên */ }

// MENU CON MỤC 2 - DÙNG MŨI TÊN
void PetManager::displayAndSearchMenu() {
    vector<string> items = {
        "1. Display all pets",
        "2. Search by name",
        "3. Filter by species",
        "4. Filter by color",
        "5. Filter by owner",
        "0. Back to main menu"
    };
    SubMenu menu("DISPLAY / SEARCH / FILTER", items);

    while (true) {
        int c = menu.show();
        if (c == -1 || c == 5) return;

        switch (c) {
            case 0: displayAll(); break;
            case 1: searchByName(); break;
            case 2: filterBySpecies(); break;
            case 3: filterByColor(); break;
            case 4: filterByOwner(); break;
        }
    }
}

// MENU CON MỤC 5 - SẮP XẾP
void PetManager::sortMenu() {
    vector<string> items = {
        "1. Sort by name (A-Z)",
        "2. Sort by name (Z-A)",
        "3. Sort by age (ascending)",
        "4. Sort by age (descending)",
        "5. Sort by breed (A-Z)",
        "6. Sort by color (A-Z)",
        "0. Back to main menu"
    };
    SubMenu menu("SORT PET LIST", items);

    while (true) {
        int c = menu.show();
        if (c == -1 || c == 6) return;

        vector<Pet*> tmp = pets;
        switch (c) {
            case 0: sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b){ return a->getName() < b->getName(); }); break;
            case 1: sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b){ return a->getName() > b->getName(); }); break;
            case 2: sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b){ return a->getAge()  < b->getAge(); }); break;
            case 3: sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b){ return a->getAge()  > b->getAge(); }); break;
            case 4: sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b){ return a->getBreed() < b->getBreed(); }); break;
            case 5: sort(tmp.begin(), tmp.end(), [](Pet* a, Pet* b){ return a->getColor() < b->getColor(); }); break;
        }

        system("cls");
        cout << "          SORTED SUCCESSFULLY!\n\n";
        displayAll();
    }
}

// MENU CON MỤC 6 - THỐNG KÊ
void PetManager::statisticsMenu() const {
    vector<string> items = {
        "1. Total number of pets",
        "2. Statistics by species",
        "3.Statistics by breed",
        "4. Statistics by color",
        "0. Back to main menu"
    };
    SubMenu menu("STATISTICS", items);

    map<string, int> speciesCount, colorCount, breedCount;
    for (const auto& p : pets) {
        speciesCount[p->getSpecies()]++;
        colorCount[p->getColor()]++;
        breedCount[p->getBreed()]++;
    }

    while (true) {
        int c = menu.show();
        if (c == -1 || c == 4) return;

        system("cls");
        cout << "╔══════════════════════════════════════════════════════════════╗\n";
        cout << "║                         STATISTICS                           ║\n";
        cout << "╚══════════════════════════════════════════════════════════════╝\n\n";

        switch (c) {
            case 0:
                cout << "          Total pets in shop: " << pets.size() << endl;
                break;
            case 1:
                cout << "          BY SPECIES:\n";
                for (const auto& x : speciesCount)
                    cout << "            " << x.first << ": " << x.second << " pet(s)\n";
                break;
            case 2:
                cout << "          BY BREED:\n";
                for (const auto& x : breedCount)
                    cout << "            " << x.first << ": " << x.second << " pet(s)\n";
                break;
            case 3:
                cout << "          BY COLOR:\n";
                for (const auto& x : colorCount)
                    cout << "            " << x.first << ": " << x.second << " pet(s)\n";
                break;
        }
        cout << "\n";
        system("pause");
    }
}

// MENU CON MỤC 7 - QUẢN LÝ FILE
void PetManager::fileManagementMenu() {
    vector<string> items = {
        "1. Save data to file",
        "2. Load data from file",
        "3. View current file content",
        "0. Back to main menu"
    };
    SubMenu menu("FILE MANAGEMENT", items);

    while (true) {
        int c = menu.show();
        if (c == -1 || c == 3) return;

        switch (c) {
            case 0: saveData(); system("pause"); break;
            case 1: loadData(); system("pause"); break;
            case 2:
                system("cls");
                cout << "╔══════════════════════════════════════════════════════════════╗\n";
                cout << "║                   CONTENT OF pets.txt                       ║\n";
                cout << "╚══════════════════════════════════════════════════════════════╝\n\n";
                system("type pets.txt 2>nul || echo [File not found or empty]");
                cout << "\n\n";
                system("pause");
                break;
        }
    }
}

// SỬA THÔNG TIN - HOÀN HẢO
void PetManager::editPet() {
    system("cls");
    if (pets.empty()) {
        cout << "          List is empty!\n\n";
        system("pause");
        return;
    }

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                          PET LIST                            ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    cout << "STT | SPECIES    NAME                AGE  COLOR         BREED           OWNER\n";
    cout << string(85, '=') << endl;
    for (size_t i = 0; i < pets.size(); ++i) {
        cout << left << setw(3) << (i + 1) << " | ";
        pets[i]->display();
    }
    cout << string(85, '=') << endl;

    int stt;
    cout << "\n          Enter STT to edit (0 to cancel): ";
    cin >> stt;
    if (stt < 1 || stt > (int)pets.size()) {
        cout << "          Invalid STT!\n\n";
        system("pause");
        return;
    }

    Pet* pet = pets[stt - 1];
    system("cls");

    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                     CURRENT INFORMATION                      ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
    pet->display();
    cout << string(85, '=') << endl;

    string input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n          Enter new info (Enter = keep old):\n\n";

    cout << "          Species [" << pet->getSpecies() << "]: "; getline(cin, input); if (!input.empty()) pet->setSpecies(input);
    cout << "          Name    [" << pet->getName()    << "]: "; getline(cin, input); if (!input.empty()) pet->setName(input);
    cout << "          Age     [" << pet->getAge()     << "]: "; getline(cin, input);
    if (!input.empty()) {
        try { pet->setAge(stoi(input)); } catch (...) { cout << "          Invalid age, unchanged.\n"; }
    }
    cout << "          Color   [" << pet->getColor()   << "]: "; getline(cin, input); if (!input.empty()) pet->setColor(input);
    cout << "          Breed   [" << pet->getBreed()   << "]: "; getline(cin, input); if (!input.empty()) pet->setBreed(input);
    cout << "          Owner   [" << pet->getOwner()   << "]: "; getline(cin, input); if (!input.empty()) pet->setOwner(input);

    cout << "\n          UPDATED SUCCESSFULLY!\n\n";
    system("pause");
}

// XÓA - CÓ XÁC NHẬN
void PetManager::deletePet() {
    system("cls");
    if (pets.empty()) {
        cout << "          List is empty!\n\n";
        system("pause");
        return;
    }

    displayAll();
    string name;
    cout << "\n          Enter name to delete: ";
    cin.ignore();
    getline(cin, name);

    auto it = find_if(pets.begin(), pets.end(),
        [&name](Pet* p) { return p->getName() == name; });

    if (it == pets.end()) {
        cout << "          Not found!\n\n";
        system("pause");
        return;
    }

    cout << "\n          Pet to delete:\n";
    (*it)->display();
    cout << "\n          Type YES to confirm: ";
    string confirm; cin >> confirm;

    if (confirm == "YES" || confirm == "yes") {
        delete *it;
        pets.erase(it);
        cout << "\n          DELETED SUCCESSFULLY!\n\n";
    } else {
        cout << "\n          Delete cancelled.\n\n";
    }
    system("pause");
}