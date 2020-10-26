#include <cstdio>      /* printf, scanf, puts, NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;
#define N 20
#define X N
#define Y N
#define PERIOD_SEC 1
#define NUMBER_OF_CELLS 300
#define NUMBER_OF_TURNS 10
bool colony[X][Y];

bool up(int x, int y) {
    if (y - 1 < 0) return false;
    return colony[x][y - 1];
}

bool down(int x, int y) {
    if (y + 1 >= Y) return false;
    return colony[x][y + 1];
}

bool right(int x, int y) {
    if (x + 1 >= X) return false;
    return colony[x + 1][y];
}

bool left(int x, int y) {
    if (x - 1 < 0) return false;
    return colony[x - 1][y];
}

bool upright(int x, int y) {
    if (x + 1 >= X) return false;
    if (y - 1 < 0) return false;
    return colony[x + 1][y - 1];
}

bool upleft(int x, int y) {
    if (x - 1 < 0) return false;
    if (y - 1 < 0) return false;
    return colony[x - 1][y - 1];
}

bool downright(int x, int y) {
    if (x + 1 >= X) return false;
    if (y + 1 >= Y) return false;
    return colony[x + 1][y + 1];
}

bool downleft(int x, int y) {
    if (x - 1 < 0) return false;
    if (y + 1 >= Y) return false;
    return colony[x - 1][y + 1];
}

void initColony(bool colony[X][Y]) {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            colony[i][j] = false;
        }
    }
}

int countAlive(bool colony[X][Y]) {
    int alive = 0;
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            if (colony[i][j])
                alive++;
        }
    }
    return alive;
}

int turn = 0;

void printColony() {
    //	ofstream myfile;
    //	myfile.open("colony.txt", ios::app);
    //	myfile << "Turn " << turn << " Alive " << countAlive(colony) << "\r\n";
    system("clear");
    cout << "Turn " << turn << " Alive " << countAlive(colony) << endl;
    turn++;
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            if (colony[i][j]) {
                cout << "|X";
                // myfile << "|X";
            } else {
                cout << "| ";
                // myfile << "| ";
            }
        }
        cout << "|" << endl;
        // myfile << "|" << "\r\n";
    }
    // myfile << "\r\n";
    // myfile.close();
}

void generateColony(unsigned int cellNum) {
    unsigned int generatedCells = 0;
    int posX, posY;
    /* initialize random seed: */
    srand(time(NULL));
    /* generate secret number between 1 and 10: */
    while (generatedCells < cellNum) {
        posX = rand() % X;
        posY = rand() % Y;
        if (!colony[posX][posY]) {
            colony[posX][posY] = true;
            generatedCells++;
        }
    }
}

void doTurn() {
    bool newColony[X][Y];
    initColony(newColony);
    int cellsAlive;
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            cellsAlive = 0;
            if (up(i, j)) cellsAlive++;
            if (down(i, j)) cellsAlive++;
            if (right(i, j)) cellsAlive++;
            if (left(i, j)) cellsAlive++;
            if (upright(i, j)) cellsAlive++;
            if (upleft(i, j)) cellsAlive++;
            if (downright(i, j)) cellsAlive++;
            if (downleft(i, j)) cellsAlive++;
            if (colony[i][j]) {
                if (cellsAlive < 2) newColony[i][j] = false;
                if (cellsAlive == 2 || cellsAlive == 3) newColony[i][j] = true;
                if (cellsAlive > 3) newColony[i][j] = false;
            } else {
                if (cellsAlive == 3) newColony[i][j] = true;
                else newColony[i][j] = false;
            }
        }
    }
    memcpy(colony, newColony, sizeof (colony));
}

int main(int argc, char** argv) {
    //ofstream myfile;
    //myfile.open("colony.txt");
    //myfile << "";
    //myfile.close();

    initColony(colony);
    generateColony(NUMBER_OF_CELLS);
    printColony();

    for (int turn = 1; turn < NUMBER_OF_TURNS; turn++) {
        Sleep(PERIOD_SEC * 1000);
        doTurn();
        printColony();
    }

    return 0;
}
