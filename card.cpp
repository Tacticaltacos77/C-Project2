#include <string>
using namespace std;

#include "card.h"
//Constructor
Card::Card(string name,string symbol, int val){
    this->symbol = symbol;
    this->name= name;
    value = val;
}
//Copy Constructor
Card::Card(const Card& og){
    this->name = og.name;
    this->symbol = og.symbol;
    this->value = og.value;
}
