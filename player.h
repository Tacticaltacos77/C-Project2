/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  Array Structure Specification
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

const int NAMEBUFFER = 20;

#include "person.h"


class Player : public Person{
    private:
        float balance, startBalance;
        int bet, currHand;
        bool hasHit, canSplit, canDouble, hasSplit, hasDouble, nat21, hasLost, endRound, push;
        Hand  *splitHand;
    public:
        friend class Game;
        Player(string name);
        ~Player(){delete splitHand; splitHand = nullptr; delete hand; hand = nullptr;}
        class InvalidBalance{};
        void printInfo(){};
        bool placeBet();
        void printSplitHand();
        void split();
        void hitDouble();
        void stand();
        void resetPlayerVars();
};

#endif /* PLAYER_H */

