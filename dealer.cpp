
#include <iostream>
using namespace std;
#include "dealer.h"

//Constructor
Dealer :: Dealer(int standVal, string name): Person(name){
    this->standVal = standVal;
    hidden = true;
    hand = new Hand();
}
void Dealer :: resetDealerVars(){
    hidden =true;
}
void Dealer :: printInfo(){
    cout << "Dealer: " << name << endl;
}
void Dealer :: playTurn(){
    // Dealer logic here
}
void Dealer :: printHiddenHand(){
    // Print hidden hand logic here
}