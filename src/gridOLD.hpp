#include <iostream>
#include <cstdlib>

using namespace std;

// grid sizes defined here
#define FourFour 1 // 4x4
#define FiveFive 2 // 5x5
#define SixSix 3 // 6x6
#define FiveFour 4 // developer's choice: 5x4

class Grid {
    public:
        void gridSetSize() {
            cout << "What size of grid do you want?" << endl;
            cout << "\t1: 4 x 4 grid" << endl;
            cout << "\t2: 5 x 5 grid" << endl;
            cout << "\t3: 6 x 6 grid" << endl;
            cout << "\t4: 5 x 4 grid (Developer's Choice)" << endl;
            cin >> gridSize;
            system("clear");
            printGrid();
        }
        void printGrid() { // TODO: Change code to allow other sizes
            string str = "";
            for(int i = 0; i < 4; i++) { // rows
                str += ":";
                for(int j = 0; j < 4; j++) { // each cell in the row
                    str += " color :";
                }
                str += "\n_________________________________\n";
            }
            cout << str << endl;
        }
    protected:
        int gridSize;
};

