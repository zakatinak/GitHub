//////////////////////////////////////
//  Zak Inak
//  Project 6c CS2401
//  Main for Othello game. Starts a game, and prints out the winner at the end.
//  12/9/17
//////////////////////////////////////
#include "Othello.h"
#include <iostream>
#include "colors.h"

using namespace std;
using namespace main_savitch_14;

int main()
{
    Othello board1;
    cout << "input moves as: C5 (for column c, row 5)\n";
    int winner = board1.play();
    if (winner == 0)
    {
        cout << "\nPlayer 1 wins!\n";
    }
    else if (winner == 1)
    {
        cout << "\nIt's a tie!\n";
    }
    else
    {
        cout << "\nPlayer 2 wins!\n";
    }
    cout << "\nGame Over!\n";
    return 0;
}
