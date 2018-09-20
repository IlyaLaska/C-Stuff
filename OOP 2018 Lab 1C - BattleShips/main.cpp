//DONE//add ship placing algorithm
//DONE//add opponent AI
//DONE//come up with victory conditions (based on playerLiveSectors and machineLiveSectors) and add them in makeMove and machineMove
//DONE//am currently coming up with new angle if old one does not work, should reroll the point since no angle may be doable
//place two grids side by side
//show only hits on opponent's board
//write something to file
//show message on complete ship destruction
//make opponent hit close by after successful hit
//ask for new games

#include <iostream>
#include "Battleships.h"

using namespace std;

int main() {
    cout << "Grid legend: " << endl;
    cout << "\"-\" - Empty, S - Ship, H - hit, D - Dead, X - Miss" << endl;
    auto game = Battleships();
    game.showGrids();
    game.makeMove();
//    _sleep(1000000);
    return 0;
}