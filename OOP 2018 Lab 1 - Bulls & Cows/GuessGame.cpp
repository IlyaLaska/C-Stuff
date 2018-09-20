//
// Created by illya on 9/13/2018.
//
#include <ctime>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include "GuessGame.h"

GuessGame::GuessGame() {
    std::cout << "New game created" << std::endl;
    points = 0;
    bulls = 0;
    cows = 0;
    secretNumber = createNumber();
//        std::cout << "The number is: " << secretNumber << std::endl;
}

GuessGame::~GuessGame() {
    std::cout << "Thanks for playing" << std:: endl;
}

bool GuessGame::guess(int number) {
    if(number == secretNumber) {
        correctGuess();
        return true;
    } else {
        incorrectGuess(number);
        return false;
    }
}

void GuessGame::correctGuess() {
    std::cout << "Congratulations! You guessed correctly" << std::endl;
    delete this;
}

int GuessGame::createNumber() {
    srand(time(NULL));
    int num;
    numArray[0] = (rand() % 9) + 1;//generate the first num separately since it cannot be 0 and should not be checked for duplicates
    int i = 1;
    while (i < 5) {
        num = (rand() % 10);

        for (int j: numArray) {//look through every element already filled
            if(j == num) {//this num is already present
                goto fail;
            }
        }
        numArray[i] = num;
        i++;
        fail://if this num is already in numArray restart cycle
        continue;
    }
    int number;
    std::stringstream toInt;
    for(int k: numArray) toInt << k;
    toInt >> number;
//    std::cout << "The number is: " << number << std::endl;
    return number;
}

void GuessGame::incorrectGuess(int number) {
    std::cout << "Alas You did not guess the whole number" << std::endl;
    setPoints(number);
    std::cout << std::setw(20) << "Your results: " << std::endl;
    std::cout << "Bulls: " << bulls << "  Cows:" << cows << std::endl;
    std::cout << "Points: " << points << std::endl;
    bulls = 0;
    cows = 0;
    points = 0;
}

void GuessGame::getNum() {
    std::cout << "The secret number is: " << secretNumber << std::endl;
}

void GuessGame::setPoints(int number) {
    int pow = 10000;
    int num;
    for (int i : numArray) {
        num = (int)floor(number/pow);
        if(num == i) {
            bulls++;
            points +=2;
        }
        else {
            for (int j: numArray) {
                if(num == j) {
                    cows++;
                    points++;
                    break;
                }
            }
        }
        number -= num*pow;
        pow /= 10;
//        std::cout << number << std::endl;
    }
}

int GuessGame::getGuess() {
    std::string guessStr;
    int guess = 0;
    std::cout << "Please enter your guess: ";
    getline(std::cin, guessStr);
    if(guessStr == "give up") {
        getNum();
        return getGuess();
    }
    try {
        guess = stoi(guessStr);
        if(guess < 10000 || guess >= 100000) throw guess;
    } catch(std::invalid_argument& e) {
        std::cout << "Catastrophic failure: " << e.what() << std::endl;
        return getGuess();
    } catch (int e) {
        std::cout << "Your guess is either too big or too small" << std::endl;
        return getGuess();
    }

    return guess;
}

//doing it the dumb way:
//    std::string numString = "";
//    for (int k: numArray) {
//        std::cout << k << std::endl;
//        numString += std::to_string(k);
//    }
//    std::cout << numString << std::endl;
//    int number = std::stoi(numString);