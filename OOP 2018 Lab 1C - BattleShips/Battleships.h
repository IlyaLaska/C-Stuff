//
// Created by illya on 9/18/2018.
//

#ifndef OOP_LAB_1C_BATTLESHIPS_H
#define OOP_LAB_1C_BATTLESHIPS_H


class Battleships {//change types
private:
    int playerLiveSectors = 20;
    int machineLiveSectors = 20;
    char playerGrid[10][10];
    char machineGrid[10][10];
    void fillGrid(char grid[][10]);
    void placeShips(char grid[][10]);
    void machineMove();
    void gameResults(bool winner);
    void writeResults();
public:
    Battleships();
    ~Battleships();
    void makeMove();
    void move(int X, int Y);
    void stats();
    void showGrids();
};


#endif //OOP_LAB_1C_BATTLESHIPS_H
