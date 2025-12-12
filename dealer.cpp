/*
 * File:   dealer.cpp
 * Author: James Fregeau
 * Created on November 11th, 2025, 4:00 PM
 * Dealer OBJ Containar 
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

//Clears the dealers hand before delete it 
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
void Dealer :: introduce(){
    cout<<"Hello Welcome to BlackJack my name is "<<name<<endl;
    cout<<"All inputs should be either lowercase or title case"<<endl;
}
//Not really need is just to make person absract //prob not best practice
void Dealer :: printInfo(){
    cout << "Dealer: " << name << endl;
}

