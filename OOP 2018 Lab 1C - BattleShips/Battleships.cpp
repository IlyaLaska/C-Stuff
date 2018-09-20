//
// Created by illya on 9/18/2018.
//
#include "Battleships.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

Battleships::Battleships() {
    srand(time(NULL));
    fillGrid(playerGrid);
    fillGrid(machineGrid);
}

Battleships::~Battleships() {
    cout << "Thanks for playing!" << endl;
}

void Battleships::fillGrid(char grid[][10]) {
    //Filling with emptyness to avoid unpredictability
    for (int i = 0; i < 10; ++i) {
        for (char &cell: grid[i]) {
            cell = 'E';
        }
    }
    //N - near; used to surround placed ships to avoid touching
    placeShips(grid);
    cout << "Out of placeShips" << endl;
    for (int i = 0; i < 10; ++i) {
        for (char &cell: grid[i]) {
            if(cell != 'S') cell = '-';
        }
    }
}

void Battleships::placeShips(char grid[][10]) {
    // 1 2 3
    // 8 S 4 ship surround map
    // 7 6 5
    for (int j = 9; j >= 0; --j) {
//        cout << "Iteration: " << j << endl;
        int xPos = rand() % 10;
        int yPos = rand() % 10;
//        cout << "xPos: " << xPos << "   yPos: " << yPos << endl;
        if(grid[yPos][xPos] != 'S' && grid[yPos][xPos] != 'N') grid[yPos][xPos] = 'S';
        else {
            j++;
            continue;
        }
        if(j <= 3) {//first 4 ships
//            cout << "1-Deckers: X: " << xPos << "   Y: " << yPos << endl;
            //surrounding 1-Deckers with no-place indicators
            if(xPos-1 >= 0 && xPos-1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-1] != 'S') grid[yPos-1][xPos-1] = 'N';//square 1
            if(xPos >= 0 && xPos < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos] != 'S')grid[yPos-1][xPos] = 'N';//square 2
            if(xPos+1 >= 0 && xPos+1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+1] != 'S') grid[yPos-1][xPos+1] = 'N';//square 3
            if(xPos+1 >= 0 && xPos+1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+1] != 'S') grid[yPos][xPos+1] = 'N';//square 4
            if(xPos+1 >= 0 && xPos+1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+1] != 'S') grid[yPos+1][xPos+1] = 'N';//square 5
            if(xPos >= 0 && xPos < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos] != 'S') grid[yPos+1][xPos] = 'N';//square 6
            if(xPos-1 >= 0 && xPos-1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-1] != 'S') grid[yPos+1][xPos-1] = 'N';//square 7
            if(xPos-1 >= 0 && xPos-1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-1] != 'S') grid[yPos][xPos-1] = 'N';//square 8
        }
        if (j > 3) {//algorithm is past 4 1 sector ships
            int angle = (rand() % 8) + 1;
//            cout << "Angle: " << angle << endl;
            switch (angle) {
                    case 1:
                        if(xPos-1<0 || yPos-1<0 || xPos-1>=10 || yPos-1>=10  || grid[yPos-1][xPos-1] == 'S' || grid[yPos-1][xPos-1] == 'N') {
                            grid[yPos][xPos] = 'E';
                            j++;
                            continue;
                        }
                        if(j > 6) {//if i need to check 3rd sector (3- and 4-decker)
                            if(xPos-2<0 || yPos-2<0 || xPos-2>=10 || yPos-2>=10 || grid[yPos-2][xPos-2] == 'S' || grid[yPos-2][xPos-2] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        if(j > 8) {//if i need to check 4th sector (4-decker)
                            if(xPos-3<0 || yPos-3<0 || xPos-3>=10 || yPos-3>=10 || grid[yPos-3][xPos-3] == 'S' || grid[yPos-3][xPos-3] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        grid[yPos-1][xPos-1] = 'S';//square 1
                        //surround 1st sector
                        if(xPos >= 0 && xPos < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos] != 'S') grid[yPos-1][xPos] = 'N';//square 2
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+1] != 'S') grid[yPos-1][xPos+1] = 'N';//square 3
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+1] != 'S') grid[yPos][xPos+1] = 'N';//square 4
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+1] != 'S') grid[yPos+1][xPos+1] = 'N';//square 5
                        if(xPos >= 0 && xPos < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos] != 'S') grid[yPos+1][xPos] = 'N';//square 6
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-1] != 'S') grid[yPos+1][xPos-1] = 'N';//square 7
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-1] != 'S') grid[yPos][xPos-1] = 'N';//square 8
                        //surround 2 sector
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos-1] != 'S') grid[yPos-2][xPos-1] = 'N';
                        if(xPos >= 0 && xPos < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos] != 'S') grid[yPos-2][xPos] = 'N';
                        if(xPos-2 >= 0 && xPos-2 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-2] != 'S') grid[yPos][xPos-2] = 'N';
                        if(xPos-2 >= 0 && xPos-2 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-2] != 'S') grid[yPos-1][xPos-2] = 'N';
                        if(j > 6) {
                            grid[yPos-2][xPos-2] = 'S';
                            if(xPos-2 >= 0 && xPos-2 < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos-2] != 'S') grid[yPos-3][xPos-2] = 'N';
                            if(xPos-1 >= 0 && xPos-1 < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos-1] != 'S') grid[yPos-3][xPos-1] = 'N';
                            if(xPos-3 >= 0 && xPos-3 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-3] != 'S') grid[yPos-1][xPos-3] = 'N';
                            if(xPos-3 >= 0 && xPos-3 < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos-3] != 'S') grid[yPos-2][xPos-3] = 'N';
                        } else if(xPos-2 >= 0 && xPos-2 < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos-2] != 'S') grid[yPos-2][xPos-2] = 'N';
                        if(j > 8) {
                            grid[yPos-3][xPos-3] = 'S';
                            if(xPos-4 >= 0 && xPos-4 < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos-4] != 'S') grid[yPos-2][xPos-4] = 'N';
                            if(xPos-4 >= 0 && xPos-4 < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos-4] != 'S') grid[yPos-3][xPos-4] = 'N';
                            if(xPos-4 >= 0 && xPos-4 < 10 && yPos-4 >= 0 && yPos-4 < 10 && grid[yPos-4][xPos-4] != 'S') grid[yPos-4][xPos-4] = 'N';
                            if(xPos-3 >= 0 && xPos-3 < 10 && yPos-4 >= 0 && yPos-4 < 10 && grid[yPos-4][xPos-3] != 'S') grid[yPos-4][xPos-3] = 'N';
                            if(xPos-2 >= 0 && xPos-2 < 10 && yPos-4 >= 0 && yPos-4 < 10 && grid[yPos-4][xPos-2] != 'S') grid[yPos-4][xPos-2] = 'N';
                        } else if(xPos-3 >= 0 && xPos-3 < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos-3] != 'S') grid[yPos-3][xPos-3] = 'N';
                        break;
                    case 2:
                        if(yPos-1<0 || yPos-1>= 10 || grid[yPos-1][xPos] == 'S' || grid[yPos-1][xPos] == 'N') {
                            grid[yPos][xPos] = 'E';
                            j++;
                            continue;
                        }
                        if(j > 6) {//if i need to check 3rd sector (3- and 4-decker)
                            if(yPos-2<0 || yPos-2>=10 || grid[yPos-2][xPos] == 'S' || grid[yPos-2][xPos] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        if(j > 8) {//if i need to check 4th sector (4-decker)
                            if(yPos-3<0 || yPos-3>=10 || grid[yPos-3][xPos] == 'S' || grid[yPos-3][xPos] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        //surround 1st sector
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-1] != 'S') grid[yPos-1][xPos-1] = 'N';//square 1
                        grid[yPos-1][xPos] = 'S';//square 2
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+1] != 'S') grid[yPos-1][xPos+1] = 'N';//square 3
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+1] != 'S') grid[yPos][xPos+1] = 'N';//square 4
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+1] != 'S') grid[yPos+1][xPos+1] = 'N';//square 5
                        if(xPos >= 0 && xPos < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos] != 'S') grid[yPos+1][xPos] = 'N';//square 6
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-1] != 'S') grid[yPos+1][xPos-1] = 'N';//square 7
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-1] != 'S') grid[yPos][xPos-1] = 'N';//square 8
                        //surround 2nd sector
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos-1] != 'S') grid[yPos-2][xPos-1] = 'N';
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos+1] != 'S') grid[yPos-2][xPos+1] = 'N';
                        if(j > 6) {
                            grid[yPos-2][xPos] = 'S';
                            //surround 3rd sector
                            if(xPos-1 >= 0 && xPos-1 < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos-1] != 'S') grid[yPos-3][xPos-1] = 'N';
                            if(xPos+1 >= 0 && xPos+1 < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos+1] != 'S') grid[yPos-3][xPos+1] = 'N';
                        } else if(xPos >= 0 && xPos < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos] != 'S') grid[yPos-2][xPos] = 'N';
                        if(j > 8) {
                            //surround 4th sector
                            grid[yPos-3][xPos] = 'S';
                            if(xPos-1 >= 0 && xPos-1 < 10 && yPos-4 >= 0 && yPos-4 < 10 && grid[yPos-4][xPos-1] != 'S') grid[yPos-4][xPos-1] = 'N';
                            if(xPos >= 0 && xPos < 10 && yPos-4 >= 0 && yPos-4 < 10 && grid[yPos-4][xPos] != 'S') grid[yPos-4][xPos] = 'N';
                            if(xPos+1 >= 0 && xPos+1 < 10 && yPos-4 >= 0 && yPos-4 < 10 && grid[yPos-4][xPos+1] != 'S') grid[yPos-4][xPos+1] = 'N';
                        } else if(xPos >= 0 && xPos < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos] != 'S') grid[yPos-3][xPos] = 'N';
                        break;
                    case 3:
                        if(xPos+1<0 || yPos-1<0 || xPos+1>=10 || yPos-1>=10  || grid[yPos-1][xPos+1] == 'S' || grid[yPos-1][xPos+1] == 'N') {
                            grid[yPos][xPos] = 'E';
                            j++;
                            continue;
                        }
                        if(j > 6) {//if i need to check 3rd sector (3- and 4-decker)
                            if(xPos+2<0 || yPos-2<0 || xPos+2>=10 || yPos-2>=10 || grid[yPos-2][xPos+2] == 'S' || grid[yPos-2][xPos+2] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        if(j > 8) {//if i need to check 4th sector (4-decker)
                            if(xPos+3<0 || yPos-3<0 || xPos+3>=10 || yPos-3>=10 || grid[yPos-3][xPos+3] == 'S' || grid[yPos-3][xPos+3] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        //surround 1st sector
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-1] != 'S') grid[yPos-1][xPos-1] = 'N';//square 1
                        if(xPos >= 0 && xPos < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos] != 'S') grid[yPos-1][xPos] = 'N';//square 2
                        grid[yPos-1][xPos+1] = 'S';//square 3
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+1] != 'S') grid[yPos][xPos+1] = 'N';//square 4
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+1] != 'S') grid[yPos+1][xPos+1] = 'N';//square 5
                        if(xPos >= 0 && xPos < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos] != 'S') grid[yPos+1][xPos] = 'N';//square 6
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-1] != 'S') grid[yPos+1][xPos-1] = 'N';//square 7
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-1] != 'S') grid[yPos][xPos-1] = 'N';//square 8
                        //surround 2nd sector
                        if(xPos >= 0 && xPos < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos] != 'S') grid[yPos-2][xPos] = 'N';
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos+1] != 'S') grid[yPos-2][xPos+1] = 'N';
                        if(xPos+2 >= 0 && xPos+2 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+2] != 'S') grid[yPos-1][xPos+2] = 'N';
                        if(xPos+2 >= 0 && xPos+2 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+2] != 'S') grid[yPos][xPos+2] = 'N';
                        if(j > 6) {
                            grid[yPos-2][xPos+2] = 'S';
                            if(xPos+1 >= 0 && xPos+1 < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos+1] != 'S') grid[yPos-3][xPos+1] = 'N';
                            if(xPos+2 >= 0 && xPos+2 < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos+2] != 'S') grid[yPos-3][xPos+2] = 'N';
                            if(xPos+3 >= 0 && xPos+3 < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos+3] != 'S') grid[yPos-2][xPos+3] = 'N';
                            if(xPos+3 >= 0 && xPos+3 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+3] != 'S') grid[yPos-1][xPos+3] = 'N';
                        } else if(xPos+2 >= 0 && xPos+2 < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos+2] != 'S') grid[yPos-2][xPos+2] = 'N';
                        if(j > 8) {
                            grid[yPos-3][xPos+3] = 'S';
                            if(xPos+2 >= 0 && xPos+2 < 10 && yPos-4 >= 0 && yPos-4 < 10 && grid[yPos-4][xPos+2] != 'S') grid[yPos-4][xPos+2] = 'N';
                            if(xPos+3 >= 0 && xPos+3 < 10 && yPos-4 >= 0 && yPos-4 < 10 && grid[yPos-4][xPos+3] != 'S') grid[yPos-4][xPos+3] = 'N';
                            if(xPos+4 >= 0 && xPos+4 < 10 && yPos-4 >= 0 && yPos-4 < 10 && grid[yPos-4][xPos+4] != 'S') grid[yPos-4][xPos+4] = 'N';
                            if(xPos+4 >= 0 && xPos+4 < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos+4] != 'S') grid[yPos-3][xPos+4] = 'N';
                            if(xPos+4 >= 0 && xPos+4 < 10 && yPos-2 >= 0 && yPos-2 < 10 && grid[yPos-2][xPos+4] != 'S') grid[yPos-2][xPos+4] = 'N';
                        } else if(xPos+3 >= 0 && xPos+3 < 10 && yPos-3 >= 0 && yPos-3 < 10 && grid[yPos-3][xPos+3] != 'S') grid[yPos-3][xPos+3] = 'N';
                        break;
                    case 4:
                        if(xPos+1<0 || xPos+1>= 10 || grid[yPos][xPos+1] == 'S' || grid[yPos][xPos+1] == 'N') {
                            grid[yPos][xPos] = 'E';
                            j++;
                            continue;
                        }
                        if(j > 6) {//if i need to check 3rd sector (3- and 4-decker)
                            if(xPos+2<0 || xPos+2>=10 || grid[yPos][xPos+2] == 'S' || grid[yPos][xPos+2] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        if(j > 8) {//if i need to check 4th sector (4-decker)
                            if(xPos+3<0 || xPos+3>=10 || grid[yPos][xPos+3] == 'S' || grid[yPos][xPos+3] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        //surround 1st sector
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-1] != 'S') grid[yPos-1][xPos-1] = 'N';//square 1
                        if(xPos >= 0 && xPos < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos] != 'S') grid[yPos-1][xPos] = 'N';//square 2
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+1] != 'S') grid[yPos-1][xPos+1] = 'N';//square 3
                        grid[yPos][xPos+1] = 'S';//square 4
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+1] != 'S') grid[yPos+1][xPos+1] = 'N';//square 5
                        if(xPos >= 0 && xPos < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos] != 'S') grid[yPos+1][xPos] = 'N';//square 6
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-1] != 'S') grid[yPos+1][xPos-1] = 'N';//square 7
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-1] != 'S') grid[yPos][xPos-1] = 'N';//square 8
                        //surround 2nd sector
                        if(xPos+2 >= 0 && xPos+2 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+2] != 'S') grid[yPos-1][xPos+2] = 'N';
                        if(xPos+2 >= 0 && xPos+2 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+2] != 'S') grid[yPos+1][xPos+2] = 'N';
                        if(j > 6) {
                            //surround 3rd sector
                            grid[yPos][xPos+2] = 'S';
                            if(xPos+3 >= 0 && xPos+3 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+3] != 'S') grid[yPos-1][xPos+3] = 'N';
                            if(xPos+3 >= 0 && xPos+3 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+3] != 'S') grid[yPos+1][xPos+3] = 'N';
                        } else if(xPos+2 >= 0 && xPos+2 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+2] != 'S') grid[yPos][xPos+2] = 'N';
                        if(j > 8) {
                            //surround 4th sector
                            grid[yPos][xPos+3] = 'S';
                            if(xPos+4 >= 0 && xPos+4 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+4] != 'S') grid[yPos-1][xPos+4] = 'N';
                            if(xPos+4 >= 0 && xPos+4 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+4] != 'S') grid[yPos][xPos+4] = 'N';
                            if(xPos+4 >= 0 && xPos+4 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+4] != 'S') grid[yPos+1][xPos+4] = 'N';
                        } else if(xPos+3 >= 0 && xPos+3 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+3] != 'S') grid[yPos][xPos+3] = 'N';
                        break;
                    case 5:
                        if(xPos+1<0 || yPos+1<0 || xPos+1>=10 || yPos+1>=10  || grid[yPos+1][xPos+1] == 'S' || grid[yPos+1][xPos+1] == 'N') {
                            grid[yPos][xPos] = 'E';
                            j++;
                            continue;
                        }
                        if(j > 6) {//if i need to check 3rd sector (3- and 4-decker)
                            if(xPos+2<0 || yPos+2<0 || xPos+2>=10 || yPos+2>=10 || grid[yPos+2][xPos+2] == 'S' || grid[yPos+2][xPos+2] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        if(j > 8) {//if i need to check 4th sector (4-decker)
                            if(xPos+3<0 || yPos+3<0 || xPos+3>=10 || yPos+3>=10 || grid[yPos+3][xPos+3] == 'S' || grid[yPos+3][xPos+3] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        //surround 1st sector
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-1] != 'S') grid[yPos-1][xPos-1] = 'N';//square 1
                        if(xPos >= 0 && xPos < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos] != 'S') grid[yPos-1][xPos] = 'N';//square 2
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+1] != 'S') grid[yPos-1][xPos+1] = 'N';//square 3
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+1] != 'S') grid[yPos][xPos+1] = 'N';//square 4
                        grid[yPos+1][xPos+1] = 'S';//square 5
                        if(xPos >= 0 && xPos < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos] != 'S') grid[yPos+1][xPos] = 'N';//square 6
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-1] != 'S') grid[yPos+1][xPos-1] = 'N';//square 7
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-1] != 'S') grid[yPos][xPos-1] = 'N';//square 8
                        //surround 2nd sector
                        if(xPos+2 >= 0 && xPos+2 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+2] != 'S') grid[yPos][xPos+2] = 'N';
                        if(xPos+2 >= 0 && xPos+2 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+2] != 'S') grid[yPos+1][xPos+2] = 'N';
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos+1] != 'S') grid[yPos+2][xPos+1] = 'N';
                        if(xPos >= 0 && xPos < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos] != 'S') grid[yPos+2][xPos] = 'N';
                        if(j > 6) {
                            grid[yPos+2][xPos+2] = 'S';
                            if(xPos+3 >= 0 && xPos+3 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+3] != 'S') grid[yPos+1][xPos+3] = 'N';
                            if(xPos+3 >= 0 && xPos+3 < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos+3] != 'S') grid[yPos+2][xPos+3] = 'N';
                            if(xPos+1 >= 0 && xPos+1 < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos+1] != 'S') grid[yPos+3][xPos+1] = 'N';
                            if(xPos+2 >= 0 && xPos+2 < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos+2] != 'S') grid[yPos+3][xPos+2] = 'N';
                        } else if(xPos+2 >= 0 && xPos+2 < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos+2] != 'S') grid[yPos+2][xPos+2] = 'N';
                        if(j > 8) {
                            grid[yPos+3][xPos+3] = 'S';
                            if(xPos+4 >= 0 && xPos+4 < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos+4] != 'S') grid[yPos+2][xPos+4] = 'N';
                            if(xPos+4 >= 0 && xPos+4 < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos+4] != 'S') grid[yPos+3][xPos+4] = 'N';
                            if(xPos+4 >= 0 && xPos+4 < 10 && yPos+4 >= 0 && yPos+4 < 10 && grid[yPos+4][xPos+4] != 'S') grid[yPos+4][xPos+4] = 'N';
                            if(xPos+3 >= 0 && xPos+3 < 10 && yPos+4 >= 0 && yPos+4 < 10 && grid[yPos+4][xPos+3] != 'S') grid[yPos+4][xPos+3] = 'N';
                            if(xPos+2 >= 0 && xPos+2 < 10 && yPos+4 >= 0 && yPos+4 < 10 && grid[yPos+4][xPos+2] != 'S') grid[yPos+4][xPos+2] = 'N';
                        } else if(xPos+3 >= 0 && xPos+3 < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos+3] != 'S') grid[yPos+3][xPos+3] = 'N';
                        break;
                    case 6:
                        if(yPos+1<0 || yPos+1>= 10 || grid[yPos+1][xPos] == 'S' || grid[yPos+1][xPos] == 'N') {
                            grid[yPos][xPos] = 'E';
                            j++;
                            continue;
                        }
                        if(j > 6) {//if i need to check 3rd sector (3- and 4-decker)
                            if(yPos+2<0 || yPos+2>=10 || grid[yPos+2][xPos] == 'S' || grid[yPos+2][xPos] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        if(j > 8) {//if i need to check 4th sector (4-decker)
                            if(yPos+3<0 || yPos+3>=10 || grid[yPos+3][xPos] == 'S' || grid[yPos+3][xPos] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        //surround 1st sector
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-1] != 'S') grid[yPos-1][xPos-1] = 'N';//square 1
                        if(xPos >= 0 && xPos < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos] != 'S') grid[yPos-1][xPos] = 'N';//square 2
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+1] != 'S') grid[yPos-1][xPos+1] = 'N';//square 3
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+1] != 'S') grid[yPos][xPos+1] = 'N';//square 4
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+1] != 'S') grid[yPos+1][xPos+1] = 'N';//square 5
                        grid[yPos+1][xPos] = 'S';//square 6
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-1] != 'S') grid[yPos+1][xPos-1] = 'N';//square 7
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-1] != 'S') grid[yPos][xPos-1] = 'N';//square 8
                        //surround 2nd sector
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos+1] != 'S') grid[yPos+2][xPos+1] = 'N';
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos-1] != 'S') grid[yPos+2][xPos-1] = 'N';
                        if(j > 6) {
                            //surround 3rd sector
                            grid[yPos+2][xPos] = 'S';
                            if(xPos+1 >= 0 && xPos+1 < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos+1] != 'S') grid[yPos+3][xPos+1] = 'N';
                            if(xPos-1 >= 0 && xPos-1 < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos-1] != 'S') grid[yPos+3][xPos-1] = 'N';
                        } else if(xPos >= 0 && xPos < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos] != 'S') grid[yPos+2][xPos] = 'N';
                        if(j > 8) {
                            //surround 4th sector
                            grid[yPos+3][xPos] = 'S';
                            if(xPos-1 >= 0 && xPos-1 < 10 && yPos+4 >= 0 && yPos+4 < 10 && grid[yPos+4][xPos-1] != 'S') grid[yPos+4][xPos-1] = 'N';
                            if(xPos >= 0 && xPos < 10 && yPos+4 >= 0 && yPos+4 < 10 && grid[yPos+4][xPos] != 'S') grid[yPos+4][xPos] = 'N';
                            if(xPos+1 >= 0 && xPos+1 < 10 && yPos+4 >= 0 && yPos+4 < 10 && grid[yPos+4][xPos+1] != 'S') grid[yPos+4][xPos+1] = 'N';
                        } else if(xPos >= 0 && xPos < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos] != 'S') grid[yPos+3][xPos] = 'N';
                        break;
                    case 7:
                        if(xPos-1<0 || yPos+1<0 || xPos-1>=10 || yPos+1>=10  || grid[yPos+1][xPos-1] == 'S' || grid[yPos+1][xPos-1] == 'N') {
                            grid[yPos][xPos] = 'E';
                            j++;
                            continue;
                        }
                        if(j > 6) {//if i need to check 3rd sector (3- and 4-decker)
                            if(xPos-2<0 || yPos+2<0 || xPos-2>=10 || yPos+2>=10 || grid[yPos+2][xPos-2] == 'S' || grid[yPos+2][xPos-2] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        if(j > 8) {//if i need to check 4th sector (4-decker)
                            if(xPos-3<0 || yPos+3<0 || xPos-3>=10 || yPos+3>=10 || grid[yPos+3][xPos-3] == 'S' || grid[yPos+3][xPos-3] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        //surround 1st sector
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-1] != 'S') grid[yPos-1][xPos-1] = 'N';//square 1
                        if(xPos >= 0 && xPos < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos] != 'S') grid[yPos-1][xPos] = 'N';//square 2
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+1] != 'S') grid[yPos-1][xPos+1] = 'N';//square 3
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+1] != 'S') grid[yPos][xPos+1] = 'N';//square 4
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+1] != 'S') grid[yPos+1][xPos+1] = 'N';//square 5
                        if(xPos >= 0 && xPos < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos] != 'S') grid[yPos+1][xPos] = 'N';//square 6
                        grid[yPos+1][xPos-1] = 'S';//square 7
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-1] != 'S') grid[yPos][xPos-1] = 'N';//square 8
                        //surround 2nd sector
                        if(xPos >= 0 && xPos < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos] != 'S') grid[yPos+2][xPos] = 'N';
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos-1] != 'S') grid[yPos+2][xPos-1] = 'N';
                        if(xPos-2 >= 0 && xPos-2 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-2] != 'S') grid[yPos+1][xPos-2] = 'N';
                        if(xPos-2 >= 0 && xPos-2 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-2] != 'S') grid[yPos][xPos-2] = 'N';
                        if(j > 6) {
                            grid[yPos+2][xPos-2] = 'S';
                            if(xPos-1 >= 0 && xPos-1 < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos-1] != 'S') grid[yPos+3][xPos-1] = 'N';
                            if(xPos-2 >= 0 && xPos-2 < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos-2] != 'S') grid[yPos+3][xPos-2] = 'N';
                            if(xPos-3 >= 0 && xPos-3 < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos-3] != 'S') grid[yPos+2][xPos-3] = 'N';
                            if(xPos-3 >= 0 && xPos-3 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-3] != 'S') grid[yPos+1][xPos-3] = 'N';
                        } else if(xPos-2 >= 0 && xPos-2 < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos-2] != 'S') grid[yPos+2][xPos-2] = 'N';
                        if(j > 8) {
                            grid[yPos+3][xPos-3] = 'S';
                            if(xPos-2 >= 0 && xPos-2 < 10 && yPos+4 >= 0 && yPos+4 < 10 && grid[yPos+4][xPos-2] != 'S') grid[yPos+4][xPos-2] = 'N';
                            if(xPos-3 >= 0 && xPos-3 < 10 && yPos+4 >= 0 && yPos+4 < 10 && grid[yPos+4][xPos-3] != 'S') grid[yPos+4][xPos-3] = 'N';
                            if(xPos-4 >= 0 && xPos-4 < 10 && yPos+4 >= 0 && yPos+4 < 10 && grid[yPos+4][xPos-4] != 'S') grid[yPos+4][xPos-4] = 'N';
                            if(xPos-4 >= 0 && xPos-4 < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos-4] != 'S') grid[yPos+3][xPos-4] = 'N';
                            if(xPos-4 >= 0 && xPos-4 < 10 && yPos+2 >= 0 && yPos+2 < 10 && grid[yPos+2][xPos-4] != 'S') grid[yPos+2][xPos-4] = 'N';
                        } else if(xPos-3 >= 0 && xPos-3 < 10 && yPos+3 >= 0 && yPos+3 < 10 && grid[yPos+3][xPos-3] != 'S') grid[yPos+3][xPos-3] = 'N';
                        break;
                    case 8:
                        if(xPos-1<0 || xPos-1>= 10 || grid[yPos][xPos-1] == 'S' || grid[yPos][xPos-1] == 'N') {
                            grid[yPos][xPos] = 'E';
                            j++;
                            continue;
                        }
                        if(j > 6) {//if i need to check 3rd sector (3- and 4-decker)
                            if(xPos-2<0 || xPos-2>=10 || grid[yPos][xPos-2] == 'S' || grid[yPos][xPos-2] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        if(j > 8) {//if i need to check 4th sector (4-decker)
                            if(xPos-3<0 || xPos-3>=10 || grid[yPos][xPos-3] == 'S' || grid[yPos][xPos-3] == 'N') {
                                grid[yPos][xPos] = 'E';
                                j++;
                                continue;
                            }
                        }
                        //surround 1st sector
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-1] != 'S') grid[yPos-1][xPos-1] = 'N';//square 1
                        if(xPos >= 0 && xPos < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos] != 'S') grid[yPos-1][xPos] = 'N';//square 2
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos+1] != 'S') grid[yPos-1][xPos+1] = 'N';//square 3
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos+1] != 'S') grid[yPos][xPos+1] = 'N';//square 4
                        if(xPos+1 >= 0 && xPos+1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos+1] != 'S') grid[yPos+1][xPos+1] = 'N';//square 5
                        if(xPos >= 0 && xPos < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos] != 'S') grid[yPos+1][xPos] = 'N';//square 6
                        if(xPos-1 >= 0 && xPos-1 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-1] != 'S') grid[yPos+1][xPos-1] = 'N';//square 7
                        grid[yPos][xPos-1] = 'S';//square 8
                        //surround 2nd sector
                        if(xPos-2 >= 0 && xPos-2 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-2] != 'S') grid[yPos+1][xPos-2] = 'N';
                        if(xPos-2 >= 0 && xPos-2 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-2] != 'S') grid[yPos-1][xPos-2] = 'N';
                        if(j > 6) {
                            //surround 3rd sector
                            grid[yPos][xPos-2] = 'S';
                            if(xPos-3 >= 0 && xPos-3 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-3] != 'S') grid[yPos+1][xPos-3] = 'N';
                            if(xPos-3 >= 0 && xPos-3 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-3] != 'S') grid[yPos-1][xPos-3] = 'N';
                        } else if(xPos-2 >= 0 && xPos-2 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-2] != 'S') grid[yPos][xPos-2] = 'N';
                        if(j > 8) {
                            //surround 4th sector
                            grid[yPos][xPos-3] = 'S';
                            if(xPos-4 >= 0 && xPos-4 < 10 && yPos-1 >= 0 && yPos-1 < 10 && grid[yPos-1][xPos-4] != 'S') grid[yPos-1][xPos-4] = 'N';
                            if(xPos-4 >= 0 && xPos-4 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-4] != 'S') grid[yPos][xPos-4] = 'N';
                            if(xPos-4 >= 0 && xPos-4 < 10 && yPos+1 >= 0 && yPos+1 < 10 && grid[yPos+1][xPos-4] != 'S') grid[yPos+1][xPos-4] = 'N';
                        } else if(xPos-3 >= 0 && xPos-3 < 10 && yPos >= 0 && yPos < 10 && grid[yPos][xPos-3] != 'S') grid[yPos][xPos-3] = 'N';
                        break;
                    default:
                        cout << "This will never happen, as angle will never be " << angle << endl;
                        break;
            }//end of switch statement
        }//end of if(j > 3)//*/
    }//end of for (j<10) loop
}

void Battleships::move(int X, int Y) {
    cout << "You have hit square " << X << ", " << Y << endl;
    if(machineGrid[Y][X] == 'S') {
        machineLiveSectors--;
        machineGrid[Y][X] = 'H';
        cout << "You hit part of an enemy ship!" << endl;
        showGrids();
        if(!machineLiveSectors) return gameResults(false);//player victory - 0, AI victory - 1;
        return makeMove();
    } else if(machineGrid[Y][X] == '-') {
        machineGrid[Y][X] = 'X';
        cout << "You fail to hit an enemy ship" << endl;
    } else {
        cout << "This sector has already been damaged" << endl;
    }
    showGrids();
    return machineMove();
}

void Battleships::machineMove() {
    int X = rand() % 10;
    int Y = rand() % 10;
    if(playerGrid[Y][X] != 'S' || playerGrid[Y][X] != '-') return machineMove();
    cout << "Now your opponent will make his turn" << endl;
    cout << "He decided to hit square " << X << ", " << Y << endl;
    if(playerGrid[Y][X] == 'S') {
        playerLiveSectors--;
        playerGrid[Y][X] = 'H';
        cout << "Your opponent hit part of Your ship!" << endl;
        showGrids();
        if(!playerLiveSectors) return gameResults(true);//player victory - 0, AI victory - 1;
        return machineMove();
    } else if(playerGrid[Y][X] == '-') {
        playerGrid[Y][X] = 'X';
        cout << "Your opponent failed to hit Your ship" << endl;
    } else {
        cout << "The sector Your opponent has hit has already been damaged" << endl;
    }
    showGrids();
    return makeMove();
}

void Battleships::stats() {

}

void Battleships::showGrids() {
    cout << "Player Grid: " << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "| x ||  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 || x |" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "-------------------------------------------------------------" << endl;
//    for (auto &i : playerGrid) {
    for(int i = 0; i < 10; ++i) {
        cout << "| " << i << " ";
        cout << "||";
        for (char cell: playerGrid[i]) {
            cout << " " << setw(2) << cell << " |";
        }
        cout << "| " << i << " |";
        cout << endl;
        cout << "-------------------------------------------------------------" << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
    cout << "| x ||  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 || x |" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "Machine Grid: " << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "| x ||  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 || x |" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "-------------------------------------------------------------" << endl;
//    for (auto &i : machineGrid) {
    for(int i = 0; i < 10; ++i) {
        cout << "| " << i << " ";
        cout << "||";
        for (char cell: machineGrid[i]) {
            cout << " " << setw(2) << cell << " |";
        }
        cout << "| " << i << " |";
        cout << endl;
        cout << "-------------------------------------------------------------" << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
    cout << "| x ||  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 || x |" << endl;
    cout << "-------------------------------------------------------------" << endl;
//    cout << playerGrid << endl;
//    cout << machineGrid << endl;

}

void Battleships::makeMove() {
    int xPos, yPos;
    string xPosString, yPosString;
    cout << "Please make your move:" << endl;
    cout << "X: ";
    getline(cin, xPosString);
    cout << "Y: ";
    getline(cin, yPosString);
    try {
        xPos = stoi(xPosString);
        yPos = stoi(yPosString);
        if(xPos < 0 || xPos > 9) throw xPos;
        if(yPos < 0 || yPos > 9) throw yPos;
    } catch(invalid_argument& e) {
        cout << "Catastrophic failure: " << e.what() << endl;
        return makeMove();
    } catch (int e) {
        cout << "Your sector position is either too big or too small" << endl;
        return makeMove();
    }
    move(xPos, yPos);
}

void Battleships::gameResults(bool winner) {
    string decisionStr;
    if(!winner) {
        cout << "Congratulations! You have won!" << endl;
    } else {
        cout << "Unfortunately You have lost the game" << endl;
    }
    cout << "Do you want to write game results to file? [Y/N]" << endl;
    cout << ">";
    getline(cin, decisionStr);
    cout << endl;
    if(decisionStr == "Y" || decisionStr == "y" || decisionStr == "yes" || decisionStr == "Yes") writeResults();
    delete this;
}

void Battleships::writeResults() {
    ofstream writer("Game Results.txt", ios::app);

    writer.close();
}
