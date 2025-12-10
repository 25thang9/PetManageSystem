// SubMenu.h 
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

class SubMenu {
private:
    vector<string> items;
    string title;
    int selected = 0;

    void gotoxy(short x, short y) {
        COORD pos = {x, y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

public:
    SubMenu(const string& t, const vector<string>& menuItems)
        : title(t), items(menuItems) {}

    int show() {
        system("cls");
        const int startX = 20;
        const int startY = 6;
        const int width = 50;

        while (true) {
            gotoxy(startX + 8, startY - 2);
            setColor(14);
            cout << title;
            setColor(7);

            gotoxy(startX - 2, startY - 1);
            cout << string(width + 4, '=');

            for (int i = 0; i < items.size(); ++i) {
                gotoxy(startX, startY + i);
                if (i == selected) {
                    setColor(240); // highlight
                    cout << " > " << items[i];
                    cout << string(width - items[i].length() - 3, ' ');
                } else {
                    setColor(15);
                    cout << "   " << items[i];
                    cout << string(width - items[i].length() - 3, ' ');
                }
                setColor(7);
            }

            gotoxy(startX - 2, startY + items.size());
            cout << string(width + 4, '=');

            gotoxy(startX - 2, startY + items.size() + 2);
            setColor(14);
            cout << "Up/Down arrow keys to move • Enter to select • ESC to go back";

            int key = _getch();
            if (key == 0 || key == 224) key = _getch();

            switch (key) {
                case 72: selected = (selected - 1 + items.size()) % items.size(); break;
                case 80: selected = (selected + 1) % items.size(); break;
                case 13: return selected;
                case 27: return -1;
            }
        }
    }
};