#include <iostream>
#include <stdlib.h> // used for system(3) commands
#include <chrono> // used to pause screen
#include <thread> // used to pause screen
#include <string> // data type used for compatability
#include "grid.hpp" // header file with grid classes

using namespace std;

class MemoryMatchGame {
    public:
        MemoryMatchGame() { // ctor
            theme = "color";
            matchCount = 0;
        }
        bool isGridFull();
        void clear() {
            // clear screen
            system("clear");
        }
        void hide(int, int, int, int);
        void setSize() {
            cout << "What size grid do you want?" << endl;
            cout << "1: 4 x 4" << endl;
            cout << "2: 6 x 6" << endl;
            cout << "3: 8 x 8" << endl;
            cin >> size;
        }
        void createGridClass() {
            switch(size) {
                case 5: // debugging, for a 2x2 grid
                    g1 = new TwoTwo;
                    break;
                case 1:
                    g1 = new FourFour;
                    break;
                case 2:
                    g1 = new SixSix;
                    break;
                case 3:
                    g1 = new EightEight;
                    break;
            }
            // for accessibility purposes
            rows = g1->rows;
            columns = g1->columns;
        } // instantiate the grid class
        void start();
        void setDifficulty();
        void hostess();
        Grid* g1;
        int difficulty;
        string theme;
        int matchCount;
    private:
        int size;
        int rows;
        int columns;
};

void MemoryMatchGame::hostess() { // similar to the hostess in Wheel of Fortune
    int r1, c1, r2, c2;
    while(!isGridFull()) {
        isGridFull();
        g1->printGrid();
        FIRST:cout << "Choose row #: ";
        cin >> r1;
        cout << "Choose column #: ";
        cin >> c1;
        cout << endl;
        if(r1 > rows || c1 > columns) { // the player tried choosing something ouside the array
            cout << "Illegal Move. Please try again." << endl;
            goto FIRST;
        }
        if(g1->checkGrid[(c1 - 1)][(r1 - 1)] == true) { // this cell has already been picked (and matched)
            cout << "This cell has already been matched! Illegal move. Please try again." << endl;
            goto FIRST;
        }
        g1->displayGrid[(c1 - 1)][(r1 - 1)] = g1->answerGrid[(c1 - 1)][(r1 - 1)];
        clear();
        g1->printGrid();
        SECOND:cout << "Choose row #: ";
        cin >> r2;
        cout << "Choose column #: ";
        cin >> c2;
        if(r2 == r1 && c2 == c1) {
            cout << "Illegal Move. Please try again." << endl;
            goto SECOND;
        }
        else if(r2 > rows || c2 > columns) { // the player tried choosing something ouside the array
            cout << "Illegal Move. Please try again." << endl;
            goto SECOND;
        }
        if(g1->checkGrid[(c2 - 1)][(r2 - 1)] == true) { // this cell has already been picked (and matched)
            cout << "This cell has already been matched! Illegal move. Please try again." << endl;
            goto SECOND;
        }
        g1->displayGrid[(c2 - 1)][(r2 - 1)] = g1->answerGrid[(c2 - 1)][(r2 - 1)];
        clear();
        g1->printGrid();
        if(g1->answerGrid[(c1 - 1)][(r1 - 1)] == g1->answerGrid[(c2 - 1)][(r2 - 1)]) {
            clear();
            cout << "You got a match!" << endl;
            matchCount++;
            // cout << "Current Match Count is " << matchCount << endl; // debugging statement
            g1->checkGrid[(c1 - 1)][(r1 - 1)] = true;
            g1->checkGrid[(c2 - 1)][(r2 - 1)] = true;
        }
        else {
            this_thread::sleep_for(chrono::seconds(difficulty / 3)); // display unmatched cards for (difficulty) seconds
            clear();
            cout << "Sorry, you did not get a match." << endl;
            hide(r1, c1, r2, c2);
        }
    }
    cout << "The game is complete!" << endl;
    // cout << "Time taken:" << time << endl;
    exit(0);
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

void MemoryMatchGame::start() {
    clear();
    cout << "Nishant Kompella - Final Project" << endl;
    cout << "Welcome to the Memory Match Game! Press 1 to start." << endl;
    int placeholder;
    cin >> placeholder; // program will not continue until key is pressed
    setSize();
    createGridClass(); // instantiate grid class
    //getConfig(*rows, *cols)
    //Grid* g = creator.create(rows, cols)
    //hostess(g, rows, cols)
    g1->setGrid();
    // print out answerGrid post-shuffle (included for debugging)
/*     for(int r = 0; r < rows; r++) { // rows
        for(int c = 0; c < columns; c++) { // columns
            cout << ": " << g1->answerGrid[c][r] << " ";
        }
        cout << endl;
    } */
    setDifficulty();
    hostess();
}

void MemoryMatchGame::hide(int r1, int c1, int r2, int c2) {
    g1->displayGrid[(c1 - 1)][(r1 - 1)] = theme;
    g1->displayGrid[(c2 - 1)][(r2 - 1)] = theme;
}

bool MemoryMatchGame::isGridFull() {
    if(matchCount == (rows * columns / 2)) {
        cout << "The game is complete!" << endl;
        exit(0);
    }
    return false; // the check passed
}