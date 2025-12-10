
#include "dealer.h"

//Constructor
Dealer :: Dealer(int standVal, string name): Person(name){
    this->standVal = standVal;
    hidden = true;
}
void Dealer :: resetDealerVars(){
    hidden =true;
}