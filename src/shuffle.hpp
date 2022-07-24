#include <iostream>
#include <string>

// By Nishant Kompella

using namespace std;

void shufflePos(int n, int arr[]);

void printArray(int *a, int length) {
    cout << "[ ";
    for (int i = 0; i < length; i ++) {
        cout << a[i];
        if (i != length - 1) {
            cout << ", ";
        }
    }
    cout << " ]\n";
}

bool check(int arr[], int size) {
    int count[size];
    for(int i = 0; i < size; i++) { // set the count
        count[i] = 0;
    }
    for(int i = 0; i < size; i++) {
        count[i]++;
    }
    for(int i = 0; i < size; i++) {
        if(count[i] != 1) {
            return false; // there were more or less than 1 values
        }
    }
    return true;
}

void shufflePos(int n, int arr[]) {
    for(int i = 0; i < n; i++) {
        arr[i] = i;
    } 
    // shuffle positions
    srand(time(0));
    for(int i = 0; i < (n - 2); i++) {
        /*if(arr[i] != i) // i has already been swapped
            continue;
        */
        int tmp = arr[i];
//        cout << "i = " << i << ", n - i = " << (n - i) << ", ";
        int random = rand();
//        cout << "random = " << random << ", ";
        int nextPos = i + random % (n - i);
//        cout << "nextPosition = " << nextPos << endl;
        arr[i] = arr[nextPos]; // swap
        arr[nextPos] = tmp;
    }
        //printArray(arr, n);
/*    bool chck = check(arr, n);
    if(chck == false)
        cout << "FALSE" << endl;
    else
        cout << "TRUE" << endl; */
}

void swapString(string arr[], int pos1, int pos2) {
    string tmp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = tmp;
    return;
}

void shuffleString(string strs[], int len) {
    int valArr[len];
    shufflePos(len, valArr);
    string to[len];
    // copying values into another array
    for(int i = 0; i < len; i++) {
        to[i] = strs[valArr[i]];
    }
    // copying to[] into strs[]
    for(int i = 0; i < len; i++) {
        strs[i] = to[i];
    }
}

void nshuffle(int i, string** arr) {
    int n = i * i; // length of 1D array
    string darr[n]; // 1D array
    for(int r = 0; r < n; r++) { // fill values of 1D array // rows
        for(int c = 0; c < n; c++) { // columns
            darr[(i * r + c)] = arr[c][r];
        }
    }
    shuffleString(darr, n);
    // convert 1D array back into 2D array
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < n; c++) {
            arr[c][r] = darr[(i * r) + c];
        }
    }
}

// Ignore the following code -- Used for Debugging
/*
void shuffle(int i, string arr[]) {
    string colorTheme[8][8] = {
        {"blue", "blue", "green", "green", "violet", "violet", "teal", "teal"},
        {"beige", "beige", "red", "red", "indigo", "indigo", "pink", "pink"},
        {"cyan", "cyan", "yellow", "yellow", "orange", "orange", "azure", "azure"},
        {"purple", "purple", "lime", "lime", "tangerine", "tangerine", "fuschia", "fuschia"},
        {"brown", "brown", "gray", "gray", "black", "black", "white", "white"},
        {"olive", "olive", "crimson", "crimson", "silver", "silver", "gold", "gold"},
        {"maroon", "maroon", "coral", "coral", "plum", "plum", "ivory", "ivory"},
        {"aqua", "aqua", "jade", "jade", "amber", "amber", "ruby", "ruby"}
    };
    int n = i * i; // length of 1D array
    string darr[n]; // 1D array
    for(int r = 0; r < i; r++) { // fill values of 1D array // rows
        for(int c = 0; c < i; c++) { // columns
            darr[(i * r + c)] = colorTheme[c][r];
        }
    }
//    cout << 1 << endl;
    shuffleString(darr, n);
//    cout << 2 << endl;
    // convert 1D array back into 2D array
    for(int r = 0; r < i; r++) {
        for(int c = 0; c < i; c++) {
            colorTheme[c][r] = darr[(i * r) + c];
        }
    }
/*    for(int r = 0; r < i; r++) { // rows
        for(int c = 0; c < i; c++) { // columns
            cout << ": " << colorTheme[c][r] << " ";
        }
        cout << endl;
    } */
// }
