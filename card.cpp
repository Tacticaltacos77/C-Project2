/*
 * File:   card.cpp
 * Author: James Fregeau
 * Created on December 11th, 2025, 3:59PM
 * The actual card container obj 
 */

#include <string>
using namespace std;

#include "card.h"
//Constructor
Card::Card(string name,string symbol, int val){
    this->symbol = symbol;
    this->name= name;
    value = val;
}

//Copy Constructor so that deck is easier to cleanup
Card::Card(const Card& og){
    this->name = og.name;
    this->symbol = og.symbol;
    this->value = og.value;
}
