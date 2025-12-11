using namespace std;
#include "round.h"
Round::Round(Player *player, Dealer *dealer){
    playerName = player->getName();
    dealerName = dealer->getName();
    this->payOut = player->getPayOut();
}