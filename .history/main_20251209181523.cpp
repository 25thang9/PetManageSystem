// main.cpp
#include <iostream>
#include <vector>
#include <limits>
#include "BeautifulMenu.h"
#include "PetManager.h"
using namespace std;

int main() {
    // Hỗ trợ tiếng Việt có dấu 100%
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    PetManager shop;
    shop.loadData();

    vector<string> mainMenuItems = {
        "1. QUAN LY DANH SACH THU CUNG",
        "2. TIM KIEM / LOC THONG TIN",
        "3. SUA THONG TIN THU CUNG",
        "4. XOA THU CUNG",
        "5. SAP XEP DANH SACH",
        "6. THONG KE",
        "7. QUAN LY FILE",
        "0. THOAT CHUONG TRINH"
    };

    BeautifulMenu mainMenu("CHUONG TRINH QUAN LY CUA HANG THU CUNG", mainMenuItems);

    while (true) {
        int choice = mainMenu.show();

        if (choice == -1 || choice == 7) { // ESC hoặc chọn Thoát
            shop.saveData();
            system("cls");
            cout << "\n\n       Cam on ban da su dung chuong trinh!\n\n";
            break;
        }

        switch (choice) {
            case 0: shop.addPet(); break;
            case 1: shop.displayAndSearchMenu(); break;
            case 2: shop.editPet(); break;
            case 3: shop.deletePet(); break;
            case 4: shop.sortMenu(); break;
            case 5: shop.statisticsMenu(); break;
            case 6: shop.fileManagementMenu(); break;
        }
    }

    return 0;
}