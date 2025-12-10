// PetManager.cpp 
#include "PetManager.h"
#include "FileHandler.h"
#include <algorithm>
#include <map>
#include <vector>
#include <cstdlib>  
#include <limits>      
#include <sstream>
using namespace std;

PetManager::~PetManager() { 
    for (auto p : pets) delete p; 
    pets.clear();
}

void PetManager::loadData() { FileHandler::loadFromFile(pets); }
void PetManager::saveData() const { FileHandler::saveToFile(pets); }

// PetManager.cpp – HÀM THÊM MỚI HOÀN HẢO NHẤT 
void PetManager::addPet() {
    system("cls");
    cout << "╔══════════════════════════════════╗\n";
    cout << "║            ADD NEW PET           ║\n";
    cout << "╚══════════════════════════════════╝\n\n";

    string species, name, color, breed, owner;
    int age;

    // Xóa bộ đệm từ lần nhập trước 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Species: ";
    getline(cin, species);                    

    cout << "Pet's name: ";
    getline(cin, name);                       

    cout << "Pet's age: ";
    while (!(cin >> age)) {
        cout << "Age is number, Re-Enter: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(); 

    cout << "Color: ";
    getline(cin, color);                      

    cout << "Breed: ";
    getline(cin, breed);                       
    cout << "Owner's name: ";
    getline(cin, owner);                      

    // Thêm vào danh sách
    pets.push_back(new Pet(species, name, age, color, breed, owner));

    cout << "\n  ADDED SUCCESSFULLY !\n\n";
    system("pause");
}
void PetManager::displayAll() const {
    system("cls");
    if (pets.empty()) { cout << "Empty list!\n\n"; system("pause"); return; }
    cout << "SPECIES    NAME           AGE  COLOR       BREED          OWNER\n";
    cout << string(75, '-') << endl;
    for (const auto& p : pets) p->display();
    cout << string(75, '-') << endl;
    cout << "Total: " << pets.size() << " pets\n\n";
    system("pause");
}

void PetManager::searchByName() const {
    string n; cout << "Enter name: "; cin >> n;
    bool found = false;
    cout << "SPECIES   NAME          AGE   COLOR      BREED         OWNER\n";
    for (const auto& p : pets) if (p->getName() == n) { p->display(); found = true; }
    if (!found) cout << "Not found!\n";
    system("pause");
}

void PetManager::filterBySpecies() const {
    string s; cout << "Enter species: "; cin >> s;
    bool found = false;
    for (const auto& p : pets) {
        if (p->getSpecies() == s) {
            if (!found) cout << "\n=== " << s << " ===\n" << string(60,'-') << endl;
            p->display(); found = true;
        }
    }
    if (!found) cout << "No pets found!\n";
    system("pause");
}

void PetManager::filterByColor() const {
    string c; cout << "Enter color: "; cin >> c;
    bool found = false;
    for (const auto& p : pets) {
        if (p->getColor() == c) {
            if (!found) cout << "\n=== Color " << c << " ===\n" << string(60,'-') << endl;
            p->display(); found = true;
        }
    }
    if (!found) cout << "No pets found!\n";
    system("pause");
}

void PetManager::filterByOwner() const {
    string o; cout << "Enter owner: "; cin >> o;
    bool found = false;
    for (const auto& p : pets) {
        if (p->getOwner() == o) {
            if (!found) cout << "\n=== Owner " << o << " ===\n" << string(60,'-') << endl;
            p->display(); found = true;
        }
    }
    if (!found) cout << "No pets found!\n";
    system("pause");
}

// MENU CON MỤC 2
void PetManager::displayAndSearchMenu() {
    int c;
    do {
        system("cls");
        cout << "=== 2. DISPLAY / SEARCH / FILTER ===\n";
        cout << "1. Display all\n2. Search by name\n3. Filter by species\n";
        cout << "4. Filter by color\n5. Filter by owner\n0. Back\nChoose: ";
        cin >> c;
        switch(c) {
            case 1: displayAll(); break;
            case 2: searchByName(); break;
            case 3: filterBySpecies(); break;
            case 4: filterByColor(); break;
            case 5: filterByOwner(); break;
            case 0: return;
            default: cout << "Invalid choice!\n"; system("pause");
        }
    } while(true);
}

// MENU CON MỤC 5 – SẮP XẾP
void PetManager::sortMenu() {
    int c;
    do {
        system("cls");
        cout << "=== 5. SORT MENU ===\n";
        cout << "1. Name A-Z\n2. Name Z-A\n3. Age ascending\n";
        cout << "4. Age descending\n5. Breed A-Z\n6. Color A-Z\n0. Back\nChoose: ";
        cin >> c;

        if (c == 0) return;

        vector<Pet*> tmp = pets;
        switch(c) {
            case 1: sort(tmp.begin(),tmp.end(),[](Pet*a,Pet*b){return a->getName()<b->getName();}); break;
            case 2: sort(tmp.begin(),tmp.end(),[](Pet*a,Pet*b){return a->getName()>b->getName();}); break;
            case 3: sort(tmp.begin(),tmp.end(),[](Pet*a,Pet*b){return a->getAge()<b->getAge();}); break;
            case 4: sort(tmp.begin(),tmp.end(),[](Pet*a,Pet*b){return a->getAge()>b->getAge();}); break;
            case 5: sort(tmp.begin(),tmp.end(),[](Pet*a,Pet*b){return a->getBreed()<b->getBreed();}); break;
            case 6: sort(tmp.begin(),tmp.end(),[](Pet*a,Pet*b){return a->getColor()<b->getColor();}); break;
            default: cout << "Invalid choice!\n"; system("pause"); continue;
        }

        system("cls");
        cout << "=== SORTED LIST ===\n";
        cout << "SPECIES    NAME           AGE  COLOR       BREED          OWNER\n";
        cout << string(75, '-') << endl;
        for (const auto& p : tmp) p->display();
        cout << string(75, '-') << endl;
        cout << "Total: " << tmp.size() << " pets\n\n";
        system("pause");

    } while(true);
}

// MENU CON MỤC 6 – THỐNG KÊ
void PetManager::statisticsMenu() const {
    map<string,int> sp, cl, br;
    for (const auto& p : pets) {
        sp[p->getSpecies()]++;
        cl[p->getColor()]++;
        br[p->getBreed()]++;
    }
    int c;
    do {
        system("cls");
        cout << "=== 6. STATISTICS ===\n";
        cout << "1. Total pets\n2. By species\n3. By breed\n4. By color\n0. Back\nChoose: ";
        cin >> c;
        system("cls");
        switch(c) {
            case 1: cout << "Total: " << pets.size() << " pets\n\n"; break;
            case 2: cout << "BY SPECIES:\n"; for(auto& x:sp) cout << x.first << ": " << x.second << "\n"; cout << endl; break;
            case 3: cout << "BY BREED:\n";   for(auto& x:br) cout << x.first << ": " << x.second << "\n"; cout << endl; break;
            case 4: cout << "BY COLOR:\n";   for(auto& x:cl) cout << x.first << ": " << x.second << "\n"; cout << endl; break;
            case 0: return;
            default: cout << "Invalid!\n\n";
        }
        if(c != 0) system("pause");
    } while(true);
}

// HÀM SỬA – HOÀN CHỈNH
// PetManager.cpp - HÀM SỬA THÔNG TIN THÚ CƯNG 
void PetManager::editPet() {
    system("cls");
    if (pets.empty()) {
        cout << "list is empty!\n\n";
        system("pause");
        return;
    }

    // Bước 1: Hiển thị danh sách có STT để người dùng chọn chính xác
    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                          PET LIST                            ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
    cout << "STT | SPECIES    NAME                AGE  COLOR         BREED           OWNER\n";
    cout << string(78, '=') << endl;
    for (size_t i = 0; i < pets.size(); ++i) {
        cout << left << setw(3) << (i + 1) << " | ";
        pets[i]->display();
    }
    cout << string(78, '=') << endl;

    // Bước 2: Chọn thú cưng cần sửa bằng STT (tránh lỗi trùng tên)
    int stt;
    cout << "\nNhap STT thu cung can sua (0 de huy): ";
    while (!(cin >> stt) || stt < 0 || stt > (int)pets.size()) {
        cout << "STT khong hop le! Nhap lai (0-" << pets.size() << "): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    if (stt == 0) {
        system("pause");
        return;
    }

    Pet* pet = pets[stt - 1];
    system("cls");

    // Bước 3: Hiển thị thông tin hiện tại đẹp mắt
    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                     NEWEST INFORMATION                       ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n";
    pet->display();
    cout << string(78, '=') << endl;

    // Bước 4: Nhập thông tin mới – CHO PHÉP DẤU CÁCH & TIẾNG VIỆT
    string input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // xóa bộ đệm an toàn

    cout << "\nInput new information (Enter = Not change):\n\n";

    cout << "Species       [" << pet->getSpecies() << "]: ";
    getline(cin, input);
    if (!input.empty()) pet->setSpecies(input);

    cout << "Name        [" << pet->getName()    << "]: ";
    getline(cin, input);
    if (!input.empty()) pet->setName(input);

    cout << "Age       [" << pet->getAge()     << "]: ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            int newAge = stoi(input);
            if (newAge >= 0 && newAge <= 300) {
                pet->setAge(newAge);
            } else {
                cout << "Age is not valid (0-300), not change.\n";
            }
        } catch (...) {
            cout << "Age is not valid, not change.\n";
        }
    }

    cout << "Color     [" << pet->getColor()   << "]: ";
    getline(cin, input);
    if (!input.empty()) pet->setColor(input);

    cout << "Breed      [" << pet->getBreed()   << "]: ";
    getline(cin, input);
    if (!input.empty()) pet->setBreed(input);

    cout << "Owner      [" << pet->getOwner()   << "]: ";
    getline(cin, input);
    if (!input.empty()) pet->setOwner(input);

    // Bước 5: Thông báo thành công
    system("cls");
    cout << "╔══════════════════════════════════════════════════════════════╗\n";
    cout << "║                    SUCCESSFUL UPDATE!                        ║\n";
    cout << "╚══════════════════════════════════════════════════════════════╝\n\n";
    cout << "Corrected information:\n";
    pet->display();
    cout << "\n\n";
    system("pause");
}
// HÀM XÓA – AN TOÀN, CÓ XÁC NHẬN
void PetManager::deletePet() {
    system("cls");
    if (pets.empty()) { cout << "Empty list!\n\n"; system("pause"); return; }
    displayAll();
    string name; cout << "\nEnter name to delete: "; cin >> name;

    auto it = pets.begin();
    for (; it != pets.end(); ++it)
        if ((*it)->getName() == name) break;

    if (it == pets.end()) { cout << "Not found!\n\n"; system("pause"); return; }

    cout << "\nPet to delete:\n"; (*it)->display();
    cout << "\nType YES to confirm delete: ";
    string confirm; cin >> confirm;
    if (confirm == "YES" || confirm == "yes") {
        delete *it;
        pets.erase(it);
        cout << "\nDeleted successfully!\n\n";
    } else {
        cout << "\nDelete cancelled.\n\n";
    }
    system("pause");
}
void PetManager::fileManagementMenu() {
    int choice;
    do {
        system("cls");
        cout << "        7. FILE MANAGEMENT         \n";
        cout << "  1. Save data to file\n";
        cout << "  2 Load data from file\n";
        cout << "  3 View current data file content\n";
        cout << "  0.  Back\n";
        cout << "  Your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                saveData();
                system("pause");
                break;

            case 2:
                loadData();
                system("pause");
                break;

            case 3:
                system("cls");
                cout << "=== CONTENT OF pets.txt ===\n\n";
                system("type pets.txt"); 
                cout << "\n\n";
                system("pause");
                break;

            case 0:
                return; // quay lại menu chính

            default:
                cout << "Invalid choice!\n";
                system("pause");
        }
    } while (true);
}