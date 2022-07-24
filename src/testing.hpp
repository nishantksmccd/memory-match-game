#include <iostream>
// including file for array
#include <string>
// including files for time
#include <chrono>
#include <thread>
// including file for shuffle
#include <bits/stdc++.h>

using namespace std;

// Nishant Kompella's Final Project - CIS 250

#ifndef TESTING_HPP
#define TESTING_HPP

void shuffle(int, int);

class MemoryMatchGame {
    public:
        MemoryMatchGame();
        void start();
        void setGrid();
        string answerGrid[4][4];
        // setGridSize should go here too
        void setTheme();
        void setDifficulty();
        void printGrid();
        void printAnswerGrid(); // debug purposes
        void hostess(); // interactions
        void hide(int, int, int, int);
    protected:
        int gridsize;
        string displayGrid[4][4];
        int matchCount;
        bool isGridFull();
    private:
        string theme; // theme
        int rows, columns; // rows and columns
        void shuffle2D(); // shuffles 2D array
        void clear(); // clear screen
        int difficulty; // time unmatched cards remain on display
};

MemoryMatchGame::MemoryMatchGame() { // constructor
    matchCount = 0;

    // setting default values here for debug purposes
    theme = "color"; // unless changed
    rows = 4;
    columns = 4;
    difficulty = 3;
}

void MemoryMatchGame::start() {
    // setTheme();
    // setDifficulty
    // setGridSize();
    // setGrid();
    // hostess();
    // setTime
}

void MemoryMatchGame::setTheme() {
    cout << "What theme would you like?" << endl;
    cout << "\t1: Colors" << endl;
    cout << "\t2: C++ Keywords" << endl;
    cout << "\t3: Candy" << endl;
    int i;
    cin >> i;
    switch(i) {
    case 1:
        theme = "color";
        break;
    case 2:
        theme = "keyw";
        break;
    case 3:
        theme = "candy";
        break;
    default:
        break;
    }
}

void MemoryMatchGame::setDifficulty() {
    cout << "What difficulty would you like to set? (Time unmatched cards will remain on display)" << endl;
    int i;
    cout << "1: 2 seconds (Hard)" << endl;
    cout << "2: 4 seconds (Medium)" << endl;
    cout << "3: 6 seconds (Easy)" << endl;
    cin >> i;
    switch(i) {
        case 1:
            difficulty = 2;
        case 2:
            difficulty = 4;
        case 3:
            difficulty = 6;
    }
}

void MemoryMatchGame::setGrid() {
    // displayGrid initialization
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < columns; c++) {
            displayGrid[c][r] = theme;
        }
    }

    string dummyGrid[4 * 4]; // dummy 1D array which will be shuffled

    // answerGrid initialization should go here
    // Note: This is for test purposes. When done, comment out this line.
/*    string testGrid[4][4] = { // NOTE: THIS IS SIDEWAYS!
        {"red", "yellow", "green", "blue"}, // COLUMN 1
        {"violet", "blue", "cyan", "green"}, // column 2
        {"cyan", "yellow", "red", "violet"}, // column 3
        {"orange", "lime", "lime", "orange"} // column 4
    }; // WARNING: THESE ARE TEST VALUES
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < columns; c++) {
            answerGrid[c][r] = testGrid[c][r];
        }
    } */
}

// Shuffle array
void shuffle(string names[], size_t n) { // shuffle a 2D array
    for (size_t i = 0; i < n;) {
        size_t j = i + rand() % (n - i);
        /* Reject this shuffle if the element we're about to place
        * is the same as the previous one
        */
        if (i > 0 && strcmp(names[j], names[i-1]) == 0)
            i = 0;
        else {
            /* Otherwise, place element i and move to the next one*/
            const char* t = names[i];
            names[i] = s[j];
            names[j] = t;
            ++i;
        }
    }
}

void MemoryMatchGame::shuffle2D() { // converts 2D array to 1D array, shuffles, then reconverts
    // convert 2D array into 1D array
    string dummyGrid[16];
    for(int r = 0; r < 4; r++) { // rows
        for(int c = 0; c < 4; c++) { // columns
            dummyGrid[(r + 1) * (c + 1)] = answerGrid[r][c];
        }
    }

    // shuffle 1D array
    int n = sizeof(dummyGrid) / sizeof(dummyGrid[0]);
    shuffle(dummyGrid, n);

    // reconvert 1D array to 2D array

}

void MemoryMatchGame::printAnswerGrid() { // debug
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++) {
            cout << ": " << answerGrid[c][r] << " ";
        }
        cout << endl;
    }
}

void MemoryMatchGame::hostess() { // similar to the hostess in Wheel of Fortune
    int r1, c1, r2, c2;
    while(isGridFull() == false) {
        printGrid();
        FIRST:cout << "Choose row #: ";
        cin >> r1;
        cout << endl << "Choose column #: ";
        cin >> c1;
        cout << endl;
        if(r1 > rows || c1 > columns) { // the player tried choosing something ouside the array
            cout << "Illegal Move. Please try again." << endl;
            goto SECOND;
        }
        displayGrid[(c1 - 1)][(r1 - 1)] = answerGrid[(c1 - 1)][(r1 - 1)];
        clear();
        printGrid();
        SECOND:cout << "Choose row #: ";
        cin >> r2;
        cout << endl << "Choose column #: ";
        cin >> c2;
        cout << endl;
        if(r2 == r1 && c2 == c1) {
            cout << "Illegal Move. Please try again." << endl;
            goto SECOND;
        }
        else if(r2 > rows || c2 > columns) { // the player tried choosing something ouside the array
            cout << "Illegal Move. Please try again." << endl;
            goto SECOND;
        }
        displayGrid[(c2 - 1)][(r2 - 1)] = answerGrid[(c2 - 1)][(r2 - 1)];
        clear();
        printGrid();
        if(displayGrid[(c1 - 1)][(r1 - 1)] == displayGrid[(c2 - 1)][(r2 - 1)]) {
            clear();
            cout << "You got a match!" << endl;
            matchCount++;
        }
        else {
            this_thread::sleep_for(chrono::seconds(difficulty));
            clear();
            cout << "Sorry, you did not get a match." << endl;
            hide(r1, c1, r2, c2);
        }
    }
    cout << "The game is complete!" << endl;
    // cout << "Time taken:" << time << endl;
    exit(0);
}

void MemoryMatchGame::printGrid() {
    for(int r = 0; r < rows; r++) { // rows
        for(int c = 0; c < columns; c++) { // columns
            cout << ": " << displayGrid[c][r] << " ";
        }
        cout << endl;
    }
}

void MemoryMatchGame::hide(int r1, int c1, int r2, int c2) {
    displayGrid[(c1 - 1)][(r1 - 1)] = theme;
    displayGrid[(c2 - 1)][(r2 - 1)] = theme;
}

bool MemoryMatchGame::isGridFull() {
    if(matchCount == rows * columns)
        return true;

    return false;
}

void MemoryMatchGame::clear() {
    system("clear");
}

#endif // TESTING_HPP