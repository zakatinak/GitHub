//////////////////////////////////////
//  Zak Inak
//  Project 6c CS2401
//  Space class written for Othello games. Spaces can be empty,
//  or a have piece designated for either player by the value of "state".
//  This class has the ability to set the state, get the state, or flip
//  the state from one player's piece to the other player's piece.
//  12/4/17
//////////////////////////////////////
#ifndef SPACE_H
#define SPACE_H

class Space{
public:
    Space(int s = 0){state = s;}
    int get_state()const{return state;}
    void set_state(const int &s){state = s;}
    void flip()
        {
            if (state==1)
                {state=2;}
            else if(state==2)
                {state=1;}
        }
private:
    int state;//0 is empty, 1 is white, 2 is black
};
#endif // SPACE_H
