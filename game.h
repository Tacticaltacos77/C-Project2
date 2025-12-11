/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  Array Structure Specification
 */

#ifndef GAME_H
#define GAME_H

using namespace std;

#include "player.h"
#include "dealer.h"
#include "deck.h"
class Game{
    private:
        Player *player =nullptr;
        Dealer *dealer = nullptr;
        Deck *deck = nullptr;
        bool endGame;    
    public:
        Game(Player *player);
        ~Game();
        bool startGame();
        void gameLoop();
        void printHands();
        void dealerTurn();
        void playerTurn();
        void printPlayerDecisionTree();
        void resetAllGameVars();
        void payOut();
        void starterCards();
        void checkPlayerStatus();
};

#endif /* GAME_H */

