#include "Blackjack.h"

//cl /EHsc /std:c++11 main.cpp Blackjack.cpp

int main(void) {
    
    Deck* deck = new Deck();
    deck->shuffle();
    cout << "Welcome to Blackjack" << endl;

    int numPlayer;

    cout << "How many players are playing?" << endl;
    cin >> numPlayer;

    playDealer(playPlayers(deck, createPlayers(deck, numPlayer), numPlayer), deck, numPlayer);

    return 0;
}