#include <iostream>
#include <string>
#include "GuessGame.h"

using namespace std;

int getGuess(GuessGame* game);

int main() {
    auto game = new GuessGame;
//    game->getNum();
    int guess;
    bool guessed;
    do {
        guess = game->getGuess();
        guessed = game->guess(guess);
    } while(!guessed);
    _sleep(1000);
    return 0;
}

//int getGuess(GuessGame* game) {
//    string guessStr;
//    int guess = 0;
//    cout << "Please enter your guess: ";
//    getline(cin, guessStr);
//    if(guessStr == "give up") {
//        game->getNum();
//        return getGuess(game);
//    }
//    try {
//        guess = stoi(guessStr);
//        if(guess < 10000 || guess >= 100000) throw guess;
//    } catch(invalid_argument& e) {
//        cout << "Catastrophic failure: " << e.what() << endl;
//        return getGuess(game);
//    } catch (int e) {
//        cout << "Your guess is either too big or too small" << endl;
//        return getGuess(game);
//    }
//
//    return guess;
//}