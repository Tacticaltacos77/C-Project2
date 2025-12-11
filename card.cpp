/*
 * File:   card.cpp
 * Author: James Fregeau
 * Created on November 7th, 2025, 12:30 AM
 * Created blackjack
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
