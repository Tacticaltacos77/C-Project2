/*
 * File:   dealer.cpp
 * Author: James Fregeau
 * Created on November 7th, 2025, 12:30 AM
 * Created blackjack
 */

#include <iostream>
using namespace std;
#include "dealer.h"

//Constructor
Dealer :: Dealer(int standVal, string name): Person(name){
    this->standVal = standVal;
    hidden = true;
    hand = new Hand();
}
Dealer :: ~Dealer(){
    hand->clearHand();
    delete []hand;
    hand =nullptr;
}
//Resets the dealer vars. not really needed right now but in the future if they get more vars 
void Dealer :: resetDealerVars(){
    hidden =true;
    hand->clearHand();
}

//Not really need is just to make person absract
void Dealer :: printInfo(){
    cout << "Dealer: " << name << endl;
}

