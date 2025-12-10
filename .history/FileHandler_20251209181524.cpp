// FileHandler.cpp - ĐỌC & GHI FILE AN TOÀN VỚI DẤU CÁCH & TIẾNG VIỆT
#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
using namespace std;

void FileHandler::loadFromFile(vector<Pet*>& list) {
    ifstream file("../Pet/pets.txt");

    // Nếu file không tồn tại → thông báo và trả về danh sách rỗng (không lỗi)
    if (!file.is_open()) {
        cout << "Khong tim thay file pets.txt -> Bat dau voi danh sach rong.\n";
        return;
    }

    string line;
    int count = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;  // bỏ dòng trống

        stringstream ss(line);
        string species, name, color, breed, owner;
        int age;

        // Dùng tab (\t) làm dấu phân cách → an toàn tuyệt đối với dấu cách
        if (!getline(ss, species, '\t')) continue;
        if (!getline(ss, name,    '\t')) continue;
        if (!(ss >> age)) continue;
        ss.ignore(); // bỏ tab còn lại sau số
        if (!getline(ss, color,   '\t')) continue;
        if (!getline(ss, breed,   '\t')) continue;
        if (!getline(ss, owner,   '\t')) owner = ""; // chủ nhân có thể để trống

        // Tạo đối tượng Pet và thêm vào danh sách
        list.push_back(new Pet(species, name, age, color, breed, owner));
        count++;
    }

    file.close();
    cout << "Da tai thanh cong " << count << " thu cung tu file pets.txt!\n";
}

void FileHandler::saveToFile(const vector<Pet*>& list) {
    ofstream file("pets.txt");
    if (!file.is_open()) {
        cout << "Loi: Khong the tao file pets.txt!\n";
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
    cout << "Da luu thanh cong " << list.size() << " thu cung vao pets.txt!\n";
}