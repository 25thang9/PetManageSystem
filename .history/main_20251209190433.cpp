// main.cpp - Pet Shop Management System (English version)
#include <iostream>
#include <vector>
#include <limits>
#include <windows.h>
#include "BeautifulMenu.h"
#include "PetManager.h"
using namespace std;

int main() {
    // Enable full Unicode support (Vietnamese characters, etc.)
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    PetManager shop;
    shop.loadData();

    vector<string> mainMenuItems = {
        "1. Manage Pet List",
        "2. Search / Filter Pets",
        "3. Edit Pet Information",
        "4. Delete Pet",
        "5. Sort Pet List",
        "6. Statistics",
        "7. File Management",
        "0. Exit Program"
    };

    BeautifulMenu mainMenu("PET SHOP MANAGEMENT SYSTEM", mainMenuItems);

    while (true) {
        int choice = mainMenu.show();

        // ESC pressed or user selected Exit
        if (choice == -1 || choice == 7) {
            shop.saveData();
            system("cls");
            cout << "\n\n       Thank you for using the program!\n\n";
            system("pause");
            break;
        }

        switch (choice) {
            case 0: shop.addPet();                  break;
            case 1: shop.displayAndSearchMenu();    break;
            case 2: shop.editPet();                 break;
            case 3: shop.deletePet();               break;
            case 4: shop.sortMenu();                break;
            case 5: shop.statisticsMenu();          break;
            case 6: shop.fileManagementMenu();      break;
            default:
                cout << "Invalid option!\n";
                system("pause");
        }
    }

    return 0;
}