#include <iostream>
#include "Game.hpp"
#include <chrono>
#include <thread>
// have to do this or sfml causes errors
#define NOMINMAX
#include <Windows.h>
#include "tests.hpp"

using namespace std;

int main() {
    // https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 1);
    cout << "   _____   _    _   ______    _____    _____ \n";
    cout << "  / ____| | |  | | |  ____|  / ____|  / ____|\n";
    cout << " | |      | |__| | | |__    | (___   | (___  \n";
    cout << " | |      |  __  | |  __|    \\___ \\   \\___ \\ \n";
    cout << " | |____  | |  | | | |____   ____) |  ____) |\n";
    cout << "  \\_____| |_|  |_| |______| |_____/  |_____/ \n";
    // how g4g did timed delay
    this_thread::sleep_for(chrono::seconds(1));
    SetConsoleTextAttribute(hConsole, 2);
    cout << "\nMade by Cole Godfrey and Cal Tatualla\n";
    
    string s;
    SetConsoleTextAttribute(hConsole, 3);
    while (s != "Y" && s != "N") {
        cout << "Would you like to run test cases? (Y/N): ";
        cin >> s;
        if (s == "Y") {
            Test test;
            SetConsoleTextAttribute(hConsole, 4);
            cout << "ALL TESTS COMPLETED!\nStarting Game...";
            this_thread::sleep_for(chrono::seconds(3));
            runMainMenu();
        }
        if (s == "N") runMainMenu();
    }
    return 0;
}
