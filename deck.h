/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  Array Structure Specification
 */

#ifndef DECK_H
#define DECK_H
#include <string>
using namespace std;

const int DECKSIZE = 52;
const int DECKS = 6;
const int UNIQUECARDS = 13;
const int FULLDECKSIZE = DECKSIZE * DECKS;
#include "card.h"

class Deck{
    private:
        Card **deck = nullptr;
        int currSize;
        int numDecks = DECKS;
        int deckSize = DECKSIZE;
    public:
        Deck();
        ~Deck();
        Deck& operator--(){
            --currSize;
            return *this;
        }
        void emptyDeck();
        void filldeck();
        void shuffleDeck();
        void resetDeck();
        Card *removeCardFromDeck();
};

#endif /* CARD_H */

