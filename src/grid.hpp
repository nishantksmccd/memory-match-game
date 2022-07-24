#include <iostream>
#include <chrono>
#include <thread>
#include "shuffle.hpp"

using namespace std;

class Grid {
    public:
        Grid() {
            theme = "color";
        }
        string theme;
        const string colorTheme[8][8] = {
                {"blue", "blue", "green", "green", "violet", "violet", "teal", "teal"},
                {"beige", "beige", "red", "red", "indigo", "indigo", "pink", "pink"},
                {"cyan", "cyan", "yellow", "yellow", "orange", "orange", "azure", "azure"},
                {"purple", "purple", "lime", "lime", "tangerine", "tangerine", "fuschia", "fuschia"},
                {"brown", "brown", "gray", "gray", "black", "black", "white", "white"},
                {"olive", "olive", "crimson", "crimson", "silver", "silver", "gold", "gold"},
                {"maroon", "maroon", "coral", "coral", "plum", "plum", "ivory", "ivory"},
                {"aqua", "aqua", "jade", "jade", "amber", "amber", "ruby", "ruby"}
        };
        void defaultAnswerGrid(); // todo
        string displayGrid[8][8];
        void printGrid() {
            for(int r = 0; r < rows; r++) { // rows
                for(int c = 0; c < columns; c++) { // columns
                    cout << ": " << displayGrid[c][r] << " ";
                }
                cout << endl;
            }
        }
        string answerGrid[8][8];
        string dummyGrid[8][8];
        string darr[100];
        bool checkGrid[8][8];
        void setGrid() {
            int rj, cj;
            // displayGrid initialization
            for(int r = 0; r < rows; r++) {
                for(int c = 0; c < columns; c++) {
                    displayGrid[c][r] = theme;
                }
            }

            // dummyGrid initialization (needed for answerGrid init)
            for(int r = 0; r < rows; r++) {
                for(int c = 0; c < columns; c++) {
                    dummyGrid[c][r] = colorTheme[c][r];
                }
            }

            // shuffling dummyGrid
            for(int r = 0; r < rows; r++) { // fill values of 1D array // rows
                for(int c = 0; c < columns; c++) { // columns
                    darr[(rows * r + c)] = dummyGrid[c][r];
                }
            }
            int n = rows * columns;
            shuffleString(darr, n); // shuffle dummyGrid
            for(int r = 0; r < rows; r++) {
                for(int c = 0; c < columns; c++) {
                    dummyGrid[c][r] = darr[(rows * r) + c];
                }
            }


            // answerGrid initialization
            for(int r = 0; r < rows; r++) {
                for(int c = 0; c < columns; c++) {
                    answerGrid[c][r] = dummyGrid[c][r];
                }
            }

            // checkGrid initialization
            for(int r = 0; r < rows; r++) {
                for(int c = 0; c < columns; c++) {
                    checkGrid[c][r] = false;
                }
            }
        }
        int rows;
        int columns;
};

class TwoTwo: public Grid { // WILL NOT BE USED IN-GAME! THIS IS JUST MEANT FOR DEBUGGING PURPOSES.
// to play on a 2x2 grid, type 5 when asked "What size grid do you want?"
    public:
        TwoTwo() {
            rows = 2;
            columns = 2;
            theme = "color";
        }
        string answerGrid[2][2];
        string dummyGrid[4]; // dummy 1D array which will be shuffled
        bool checkGrid[2][2];
};

class FourFour: public Grid {
    public:
        FourFour() { // set # of rows and columns in ctor
            rows = 4;
            columns = 4;
            theme = "color";
        }
        string answerGrid[4][4];
        string dummyGrid[16]; // dummy 1D array which will be shuffled
        bool checkGrid[4][4];
};

class SixSix: public Grid {
    public:
        SixSix() { // set # of rows and columns in ctor
            rows = 6;
            columns = 6;
            theme = "color";
        }
        string answerGrid[6][6];
        string dummyGrid[36]; // dummy 1D array which will be shuffled
        bool checkGrid[6][6];
};

class EightEight: public Grid {
    public:
        EightEight() { // set # of rows and columns in ctor
            rows = 8;
            columns = 8;
            theme = "color";
        }
        string answerGrid[8][8];
        string dummyGrid[64]; // dummy 1D array which will be shuffled
        bool checkGrid[8][8];
};