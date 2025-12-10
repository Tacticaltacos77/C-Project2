/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  Array Structure Specification
 */

#ifndef CARD_H
#define CARD_H
#include <string>
using namespace std;

class Card{
    private:
        string name, symbol;
        int value;
    public:
        //Constructors
        Card();
        Card(string name, string symbol, int val);
        //Copy constructor
        Card(const Card& og);
        //Getters
        string getName(){return name;};
        string getSymbol(){return symbol;};
        int getValue(){return value;};
        
};

#endif /* CARD_H */

