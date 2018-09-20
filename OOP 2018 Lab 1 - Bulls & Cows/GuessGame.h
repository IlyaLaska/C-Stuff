//
// Created by illya on 9/13/2018.
//
//#pragma once

#ifndef OOP_LAB_1_GUESSGAME_H
#define OOP_LAB_1_GUESSGAME_H

#include <iostream>


class GuessGame {
private:
    int numArray[5];
    int secretNumber;
    int points;
    int bulls;
    int cows;
    int createNumber();
    void correctGuess();
    void incorrectGuess(int number);
public:
    GuessGame();
    ~GuessGame();
    int getGuess();
    bool guess(int number);
    void getNum();
    void setPoints(int number);
};


#endif //OOP_LAB_1_GUESSGAME_H
