#include <iostream>

using namespace std;

#include "deck.h"

//Constructor
Deck::Deck(){
    currSize = 0;
    deck = new Card *[FULLDECKSIZE];
    
    filldeck();
    shuffleDeck();
}
Deck::~Deck(){
    emptyDeck();
}
void Deck::emptyDeck(){
    for(int i=0;i<UNIQUECARDS;i++){
        delete deck[i];
        deck[i]=nullptr;
    }
}


void Deck::filldeck(){
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
    //Randomizes the deck
    shuffleDeck();

    //Cleans up the cards array
    for(int i=0;i<UNIQUECARDS;i++){
        delete cards[i];
    }
    delete [] cards;
}

void Deck::resetDeck(){
    currSize = FULLDECKSIZE;
    shuffleDeck();
}

void Deck::shuffleDeck(){
    int ran;
    Card *temp;
    for(int i=0; i<FULLDECKSIZE;i++){
        ran = rand() % FULLDECKSIZE;
        temp = deck[ran];
        deck[ran] = deck[i];
        deck[i] = temp;
    }
}
Card * Deck::removeCardFromDeck(){
    if(currSize<=0){
        resetDeck();
    }
    return deck[--currSize];
}
