using namespace std;
#include "round.h"

//Constructor
Round::Round(Player *player, Dealer *dealer){
    playerName = player->getName();
    dealerName = dealer->getName();
    this->payOut = player->getPayOut();
}