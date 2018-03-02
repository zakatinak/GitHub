//////////////////////////////////////
//  Zak Inak
//  Project 6c CS2401
//  Implementation file for Othello.h
//  12/9/17
//////////////////////////////////////
#include "Othello.h"

namespace main_savitch_14
{
    Othello::Othello()
    {
        for(int i=0; i<8; ++i)
        {
            for(int j=0; j<8; ++j)
            {
                if((i==3&&j==3))
                {
                    board[i][j].set_state(1);
                }
                else if((i==3&&j==4))
                {
                    board[i][j].set_state(2);
                }
                else if((i==4&&j==3))
                {
                    board[i][j].set_state(2);
                }
                else if((i==4&&j==4))
                {
                    board[i][j].set_state(1);
                }
                else
                {
                    board[i][j].set_state(0);
                }
            }
        }
    }

    Othello::Othello(const Othello& game)
    {
        for(int i=0; i<8; ++i)
        {
            for(int j=0; j<8; ++j)
            {
                board[i][j] = game.board[i][j];
            }
        }

        std::string move = "Make a move";
        int number_of_moves = game.moves_completed();
        for (int i=0; i<number_of_moves; ++i)
        {
            game::make_move(move);
        }
    }

    void Othello::make_move(const std::string& move)
    {
        int column = convert_move_column(move);
        int row = convert_move_row(move);

        if (game::moves_completed()%2 == 0)
        {
            board[row][column].set_state(1);
        }
        else
        {
            board[row][column].set_state(2);
        }

        int color = (game::moves_completed()%2 + 1);
        for (int i=row-1; i<row+2; ++i)
        {
            if (i<0){i=0;}
            if (i>7){break;}
            for (int j=column-1; j<column+2; ++j)
            {
                if (j<0){j=0;}
                if (j>7){break;}
                way line = is_flanking(row, column, i, j);
                flip_line(row, column, i, j, line);
            }
        }

        game::make_move(move);

        if (is_game_over())
        {
            game::make_move(move);
        }
    }

    void Othello::restart()
    {
        game::restart();
    }

    game* Othello::clone()const
    {
        Othello* clone = new Othello;
        clone->game::restart();

        for(int i=0; i<8; ++i)
        {
            for(int j=0; j<8; ++j)
            {
                clone->board[i][j] = board[i][j];
            }
        }

        std::string move = "Make a move";
        int number_of_moves = moves_completed();
        for (int i=0; i<number_of_moves; ++i)
        {
            clone->game::make_move(move);
        }

        return clone;
    }

    void Othello::compute_moves(std::queue<std::string>& moves)const
    {
        std::string move;
        for (char row=49; row<57; ++row) //row = '1' to '8'
        {
            for (char column=65; column<73; ++column) //column = 'A' to 'H'
            {
                move.clear();
                move.push_back(column);
                move.push_back(row);
                if (is_legal(move))
                {
                    moves.push(move);
                }
            }
        }
    }

    void Othello::display_status()const
    {
        std::cout << "\n     A  B  C  D  E  F  G  H\n";
        for(int i=0; i<8; ++i)
        {
            std::cout << i + 1 << "   ";
            for(int j=0; j<8; ++j)
            {
                if (board[i][j].get_state() == 0)
                {
                    std::cout << "\u25A1  ";
                }
                else if (board[i][j].get_state() == 1)
                {
                    std::cout << GREEN << "\u25CF  " << BLACK;
                }
                else
                {
                    std::cout << BLACK << "\u25CF  " << BLACK;
                }
            }
            std::cout << std::endl;
        }
    }

    int Othello::evaluate()const
    {
        int player1sum = 0;
        int player2sum = 0;
        for (int i=0; i<8; ++i)
        {
            for (int j=0; j<8; ++j)
            {
                if (board[i][j].get_state() == 1)
                {
                    ++player1sum;
                }
                else if(board[i][j].get_state() == 2)
                {
                    ++player2sum;
                }
            }
        }
        return (player2sum - player1sum);
    }

    bool Othello::is_game_over()const
    {
        std::string move;
        for (char row=49; row<57; ++row) //row = '1' to '8'
        {
            for (char column=65; column<73; ++column) //column = 'A' to 'H'
            {
                move.clear();
                move.push_back(column);
                move.push_back(row);
                if (is_legal(move))
                {
                    return false;
                }
            }
        }

        //std::cout << "Player " << (game::moves_completed()%2)+1 << " can make no more legal moves at this time!\n";
        return true;
    }

    bool Othello::is_legal(const std::string& move)const
    {
        if (move.size()!=2 || !((move[0]>=65 && move[0]<=72)||(move[0]>=97 && move[0]<=104)) || move[1]<49 || move[1]>56)
        {
            return false;
        }
        int column = convert_move_column(move);
        int row = convert_move_row(move);
        if (board[row][column].get_state() != 0)
        {
            return false;
        }
        bool adjacent = false;
        bool flanking = false;
        int color = (game::moves_completed()%2 + 1);
        for (int i=row-1; i<row+2; ++i)
        {
            if (i<0){i=0;}
            if (i>7){break;}
            for (int j=column-1; j<column+2; ++j)
            {
                if (j<0){j=0;}
                if (j>7){break;}
                if (board[i][j].get_state()!=color && board[i][j].get_state()!=0)
                {
                    adjacent = true;
                }
                else
                {
                    adjacent = false;
                }
                if (adjacent && (is_flanking(row, column, i, j)!=NO_FLANK))
                {
                    flanking = true;
                }
                if (flanking == true)
                {
                    break;
                }
            }
            if (flanking == true)
            {
                break;
            }
        }
        if (!(flanking))
        {
            return false;
        }

        return true;
    }

    std::string Othello::get_user_move()const
    {
        std::cout << "Player " << (game::moves_completed()%2)+1 << "'s move.\n";
        return game::get_user_move();
    }

    game::who Othello::winning()const
    {
        int value = evaluate();
        if (value > 0)
            return COMPUTER;
        else if (value < 0)
            return HUMAN;
        else
	    return NEUTRAL;

    }

    int Othello::convert_move_column(const std::string& move)const
    {
        if (move[0]<=72)
        {
            return (move[0] - 65);
        }
        else
        {
            return (move[0] - 97);
        }
    }

    int Othello::convert_move_row(const std::string&move)const
    {
        return (move[1] - 49);
    }

    Othello::way Othello::is_flanking(const int &row, const int &column, const int &adj_row, const int&adj_column)const
    {
        int move_color;
        if (game::moves_completed()%2 == 0)
        {
            move_color = 1;
        }
        else
        {
            move_color = 2;
        }
        bool surrounded = false;
        if (row > adj_row)
        {
            if (column > adj_column)
            {
                for (int i=adj_row-1, j=adj_column-1; i>=0&&j>=0&&(board[i][j].get_state()!=0); --i, --j)
                {
                    if (board[i][j].get_state() == move_color)
                    {
                        surrounded = true;
                        break;
                    }
                }
                if (surrounded)
                    {return DIAG_UL;}
            }
            else if (column < adj_column)
            {
                for (int i=adj_row-1, j=adj_column+1; i>=0&&j<=7&&(board[i][j].get_state()!=0); --i, ++j)
                {
                    if (board[i][j].get_state() == move_color)
                    {
                        surrounded = true;
                        break;
                    }
                }
                if (surrounded)
                    {return DIAG_UR;}
            }
            else
            {
                for (int i=adj_row-1; i>=0&&(board[i][column].get_state()!=0); --i)
                {
                    if (board[i][column].get_state() == move_color)
                    {
                        surrounded = true;
                        break;
                    }
                }
                if (surrounded)
                    {return UP;}
            }

        }
        else if (row < adj_row)
        {
            if (column > adj_column)
            {
                for (int i=adj_row+1, j=adj_column-1; i<=7&&j>=0&&(board[i][j].get_state()!=0); ++i, --j)
                {
                    if (board[i][j].get_state() == move_color)
                    {
                        surrounded = true;
                        break;
                    }
                }
                if (surrounded)
                    {return DIAG_DL;}
            }
            else if (column < adj_column)
            {
                for (int i=adj_row+1, j=adj_column+1; i<=7&&j<=7&&(board[i][j].get_state()!=0); ++i, ++j)
                {
                    if (board[i][j].get_state() == move_color)
                    {
                        surrounded = true;
                        break;
                    }
                }
                if (surrounded)
                    {return DIAG_DR;}
            }
            else
            {
                for (int i=adj_row+1; i<=7&&(board[i][column].get_state()!=0); ++i)
                {
                    if (board[i][column].get_state() == move_color)
                    {
                        surrounded = true;
                        break;
                    }
                }
                if (surrounded)
                    {return DOWN;}
            }
        }
        else
        {
            if (column > adj_column)
            {
                for (int j=adj_column-1; j>=0&&(board[row][j].get_state()!=0); --j)
                {
                    if (board[row][j].get_state() == move_color)
                    {
                        surrounded = true;
                        break;
                    }
                }
                if (surrounded)
                    {return LEFT;}
            }
            else if (column < adj_column)
            {
                for (int j=adj_column+1; j<=7&&(board[row][j].get_state()!=0); ++j)
                {
                    if (board[row][j].get_state() == move_color)
                    {
                        surrounded = true;
                        break;
                    }
                }
                if (surrounded)
                    {return RIGHT;}
            }
            else
            {
                //Same spot being tested - nothing should happen
            }
        }

        if (!surrounded)
            {return NO_FLANK;}
    }

    void Othello::flip_line(const int &row, const int &column, const int &adj_row, const int&adj_column, const Othello::way &direction)
    {
        int move_color;
        if (game::moves_completed()%2 == 0)
        {
            move_color = 1;
        }
        else
        {
            move_color = 2;
        }

        if (direction == DIAG_UL)
        {
                for (int i=adj_row, j=adj_column; board[i][j].get_state()!=move_color; --i, --j)
                {
                    board[i][j].flip();
                }
        }
        else if (direction == DIAG_UR)
        {
            for (int i=adj_row, j=adj_column; board[i][j].get_state()!=move_color; --i, ++j)
            {
                board[i][j].flip();
            }
        }
        else if (direction == UP)
        {
            for (int i=adj_row; board[i][column].get_state()!=move_color; --i)
            {
                board[i][column].flip();
            }
        }
        else if (direction == DIAG_DL)
        {
            for (int i=adj_row, j=adj_column;board[i][j].get_state()!=move_color; ++i, --j)
            {
                board[i][j].flip();
            }
        }
        else if (direction == DIAG_DR)
        {
            for (int i=adj_row, j=adj_column; board[i][j].get_state()!=move_color; ++i, ++j)
            {
                board[i][j].flip();
            }
        }
        else if (direction == DOWN)
        {
            for (int i=adj_row; board[i][column].get_state()!=move_color; ++i)
            {
                board[i][column].flip();
            }
        }
        else if (direction == LEFT)
        {
            for (int j=adj_column; board[row][j].get_state()!=move_color; --j)
            {
                board[row][j].flip();
            }
        }
        else if (direction == RIGHT)
        {
            for (int j=adj_column; board[row][j].get_state()!=move_color; ++j)
            {
                board[row][j].flip();
            }
        }
        else
        {
            //NO_FLANK being tested - nothing should happen
        }
    }
}
