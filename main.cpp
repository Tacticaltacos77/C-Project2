#include <iostream>

using namespace std;


#include "game.h"
//Execution begins here
int main(){
    //Maybe add player selection later or load create player or something
    string name;
    cout<<"Welcome enter your name: "<<endl;
    cin >>name;
    //Aggregation
    //Create player outside game to allow for easier time to add diffrent types of games later.(Not tied to blackjack)
    Player *player = new Player(name);
    string cont;
    Game game = Game(player);
    if(cont == "Yes"||cont=="yes"){
        if(game.startGame()!=false){
            
        }

    }
   
    return 0;
}
