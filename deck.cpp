/*
 * File:   deck.cpp
 * Author: James Fregeau
 * Created on November 7th, 2025, 12:30 AM
 * Created blackjack
 */

#include "deck.h"

//Constructor
Deck::Deck(){
    currSize = 0;
    deck = new Card *[FULLDECKSIZE];
    
    filldeck();
    //Second shuffle for more randomness. Prob not necassary
    shuffleDeck();
}
//Deconstructor that deletes the whole deck and its items in it
Deck::~Deck(){
    emptyDeck();
}

//Deletes all the cards in the deck
void Deck::emptyDeck(){
    for(int i=0;i<UNIQUECARDS;i++){
        delete deck[i];
        deck[i]=nullptr;
    }
}

void Deck::filldeck(){
    //Creates the skelton of the deck
    if(deck==nullptr){
        deck = new Card *[FULLDECKSIZE];
    }
    //Enum for readiblity
    enum cardNames{
        ACE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING
    };
    //ptr of ptrs of all the potential cards
    Card **cards = new Card*[UNIQUECARDS];
    int cardVal = 0;
    for(cardNames i=ACE; i<=KING;i=static_cast<cardNames>(i+1)){
        //ace is first so on second run we set it to 2 to match the cards
        if(cardVal==11)cardVal=2;
        //the max value is 10 unless is ace then 11
        else if(cardVal !=10)cardVal+=1;
        //vars for cards
        string name = to_string(cardVal);
        string symbol = to_string(cardVal);
        //Updates above vars if cards is a special one
        if(i==ACE){
            name ="Ace";
            symbol ="A";
            cardVal = 11;
        }else if(i==JACK){
            name ="Jack";
            symbol ="J";
        //Queen
        }else if(i==QUEEN){
            name ="Queen";
            symbol ="Q";
        //King
        }else if(i == KING){
            name ="King";
            symbol ="K";
        }
        //creates the card dynamiclly
        cards[i] = new Card(name, symbol, cardVal);
    }
    //assigns deck var currsize
    currSize = 0;
    //Fills the deck
    for(int i=0; i<numDecks*4;i++){
        for(int j=0; j<UNIQUECARDS;j++){
            //Stores a new copy of the cards into the deck
            deck[currSize++] = new Card(*cards[j]);
        }  
    }  
    //Intial shuffle of the deck
    shuffleDeck();

    //Cleans up the intial cards array that is no longer needed
    for(int i=0;i<UNIQUECARDS;i++){
        delete cards[i];
    }
    delete [] cards;
}

//Resets the deck and shuffles it 
void Deck::resetDeck(){
    currSize = FULLDECKSIZE;
    shuffleDeck();
}

//Shuffles deck based on seed
void Deck::shuffleDeck(){
    int ran;
    Card *temp;
    //Swaps random index for the full deck size amount
    for(int i=0; i<FULLDECKSIZE;i++){
        //Generates a random num then %s it to get it in range of the index for the deck
        ran = rand() % FULLDECKSIZE;
        temp = deck[ran];
        deck[ran] = deck[i];
        deck[i] = temp;
    }
}
//Remove a card from the top of the deck and returns it
Card * Deck::removeCardFromDeck(){
    //if deck is empty refill it and shuffle
    if(currSize<=0){
        resetDeck();
    }
    return deck[--currSize];
}
