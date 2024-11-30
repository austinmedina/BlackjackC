#include "Blackjack.h"

//cl /EHsc /std:c++11 main.cpp Blackjack.cpp

int main(void) {
    setlocale(LC_ALL, "en_US.UTF-8");

    char cont = 'y';
    char stay = 'y';

    cout << "Welcome to Blackjack" << endl;

    int numPlayer;

    cout << "How many players are playing?" << endl;
    cin >> numPlayer;

    while (cont == 'y' || cont == 'Y') {
        Deck* deck = new Deck();
        cout << "Deck is being shuffled" << endl;
        deck->shuffle();

        vector<Hand> playerDecks = createPlayers(deck, numPlayer);

        dealPlayers(deck, playerDecks);

        playDealer(playPlayers(deck, playerDecks, numPlayer), deck, numPlayer);

        cout << "Would you like to continue (y or Y): ";
        cin >> cont;

        if (cont == 'y' || cont == 'Y') {
            cout << "Is everyone staying? (y or Y for yes, n or N for No): ";
            cin >> stay;
            while ((stay != 'y') && (stay != 'Y') && (stay != 'n') && (stay != 'N')) {
                cout << "INVALID INPUT" << endl << endl;
                cout << "Is everyone staying? (y or Y for yes, n or N for No): ";
                cin >> stay;
            }

            if ((stay == 'n') || (stay == 'N')) {
                cout << "How many people are leaving? Enter the number(s) of their name(s) seperated by spaces";
            }
        }
    }

    return 0;
}