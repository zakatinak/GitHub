//////////////////////////////////////
//  Zak Inak
//  Project 6c CS2401
//  Othello game derived from game class written by Walter Savitch.
//  Allows user to play a game of othello against another human by entering
//  coordinates for where to place each piece (like "C5"). The board
//  is made up of a double array of Space classes, which can be empty,
//  or a piece designated for either player that will look different.
//  This game uses linux commands to print to board to the screen in
//  different colors.
//  12/9/17
//////////////////////////////////////
#ifndef OTHELLO_H
#define OTHELLO_H
#include "game.h"
#include "Space.h"
#include "colors.h"
#include <iostream>

namespace main_savitch_14
{
    class Othello:public game
    {
    public:
        Othello();
        Othello(const Othello& game);

        // Have the next player make a specified move:
    	void make_move(const std::string& move);
        // Restart the game from the beginning:
    	void restart();
        // Return a pointer to a copy of myself:
    	game* clone()const;
        // Compute all the moves that the next player can make:
    	void compute_moves(std::queue<std::string>& moves)const;
    	// Display the status of the current game:
    	void display_status()const;
    	// Evaluate a board position:
	// NOTE: positive values are good for the computer.
    	int evaluate()const;
    	// Return true if the current game is finished:
    	bool is_game_over()const;
    	// Return true if the given move is legal for the next player:
    	bool is_legal(const std::string& move)const;

    	std::string get_user_move()const;

    	game::who winning()const;

    private:
        static const int BOARDSIZE = 8;
        Space board[BOARDSIZE][BOARDSIZE];
        int convert_move_column(const std::string& move)const;
        int convert_move_row(const std::string&move)const;
        enum way {NO_FLANK, UP, DOWN, LEFT, RIGHT, DIAG_UL, DIAG_UR, DIAG_DL, DIAG_DR};
        way is_flanking(const int &row, const int &column, const int &adj_row, const int&adj_column)const;
        void flip_line(const int &row, const int &column, const int &adj_row, const int&adj_column, const way &direction);
    };
}
#endif // OTHELLO_H
