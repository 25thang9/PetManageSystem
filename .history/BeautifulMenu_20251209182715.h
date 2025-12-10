// BeautifulMenu.h - Menu đẹp như ảnh, mũi tên, Enter chọn, ESC thoát
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

class BeautifulMenu {
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
    BeautifulMenu(const string& t, const vector<string>& menuItems)
        : title(t), items(menuItems) {}

    // Trả về chỉ số được chọn (0,1,2...) hoặc -1 nếu ESC
    int show() {
        system("cls");

        const int startX = 25;
        const int startY = 6;
        const int boxWidth = 50;

        while (true) {
            // Tiêu đề
            gotoxy(startX + (boxWidth - (int)title.length()) / 2, startY - 2);
            setColor(14); // vàng
            cout << title;
            setColor(7);

            // Khung trên + dưới
            gotoxy(startX - 3, startY - 1);
            cout << string(boxWidth + 6, '═');

            gotoxy(startX - 3, startY + (int)items.size());
            cout << string(boxWidth + 6, '═');

            // Các mục menu
            for (int i = 0; i < items.size(); ++i) {
                gotoxy(startX, startY + i);
                if (i == selected) {
                    setColor(240); // nền trắng, chữ đen
                    cout << " > " << items[i];
                    cout << string(boxWidth - (int)items[i].length() - 3, ' ');
                } else {
                    setColor(15); // trắng thường
                    cout << "   " << items[i];
                    cout << string(boxWidth - (int)items[i].length() - 3, ' ');
                }
                setColor(7);
            }

            // Hướng dẫn
            gotoxy(startX - 3, startY + (int)items.size() + 2);
            setColor(14);
            cout << "Dung phim mui ten ↑↓ de di chuyen • Enter de chon • ESC de thoat";

            // Nhận phím
            int key = _getch();
            if (key == 0 || key == 224) key = _getch(); // phím đặc biệt

            switch (key) {
                case 72: // lên
                    selected = (selected - 1 + (int)items.size()) % items.size();
                    break;
                case 80: // xuống
                    selected = (selected + 1) % items.size();
                    break;
                case 13: // Enter
                    return selected;
                case 27: // ESC
                    return -1;
            }
        }
    }
};