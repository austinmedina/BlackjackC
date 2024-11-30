#include "Blackjack.h"

using namespace std;

Deck::Deck() {
    string suits[] = {"♥", "♦", "♣", "♠" };
    string vals[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    for (string s : suits) {
        for (string v : vals) {
            Card card(s, v);
            cards.push_back(card);
        }
    }
}

Card Deck::draw() {
    Card temp;
    temp.setVal(cards.at(0).getVal());
    temp.setSuit(cards.at(0).getSuit());
    cards.erase(cards.begin());
    return temp;
}

void Deck::shuffle() {
    srand(time(NULL));

    for (int j = 0; j < 52; j++) { //randomize cards
        for (int i = 0; i < 52; i++) {
            int r = rand() % 52;
            Card temp;
            temp.setVal(cards.at(i).getVal());
            temp.setSuit(cards.at(i).getSuit());
            cards.at(i).setVal(cards.at(r).getVal());
            cards.at(i).setSuit(cards.at(r).getSuit());
            cards.at(r).setVal(temp.getVal());
            cards.at(r).setSuit(temp.getSuit());
        }
    }
}

Card::Card() {
    suit = "";
    val = "";
}

Card::Card(string s, string v) {
    suit = s;
    val = v;
}

void Card::setSuit(string s) {
    suit = s;
}

void Card::setVal(string v) {
    val = v;
}

string Card::getSuit() {
    return suit;
}

string Card::getVal() {
    return val;
}

void Hand::setName(string n) {
    name = n;
}

string Hand::getName() {
    return name;
}

void Hand::addCard(Card card) {
    cards.push_back(card);
}

void Hand::showHand() {
    for (Card card : cards) {
        cout << "-------  ";    
    }
    cout << endl;

    for (Card card : cards) {
        cout << "|" << card.getSuit() << "    |  ";
    }
    cout << endl;

    for (Card card : cards) {
        string val = card.getVal();
        if (val != "10") {
            cout << "|  " << val << "  |  ";
        } else {
            cout << "|  " << val << " |  ";
        }
        
    }
    cout << endl;

    for (Card card : cards) {
        cout << "|    " << card.getSuit() << "|  ";
    }
    cout << endl;

    for (Card card : cards) {
        cout << "-------  ";    
    }
    cout << endl;
}

int total(Hand hand) {
    int index = 0;
    int total = 0;
    int cardVal = 0;
    for (Card card : hand.cards) {
        if ((hand.cards.at(index).getVal() == "J") || (hand.cards.at(index).getVal() == "Q") || (hand.cards.at(index).getVal() == "K")) {
            cardVal = 10;
            total = total + cardVal;
        }
        else if (hand.cards.at(index).getVal() == "A") {
            cardVal = 11;
            total = total + cardVal;
            if (total > 21) {
                total = total - 10;
            } 
        }
        else {
            cardVal = stoi(hand.cards.at(index).getVal());
            total = total + cardVal;
        }
        index++;
    }
    return total;
}

void dealPlayers(Deck* deck, vector<Hand> &players) {
    for (int i = 0; i < 2; i++) {
        for (Hand& player : players) {
            player.addCard(deck->draw());
        }
    }
}

void removePlayers(vector<Hand> &players) {
    
}

void addPlayers(vector<Hand> &players) {
    
}

vector<Hand> createPlayers(Deck* deck, int numPlayer) {
    vector<Hand> playerDecks;
    string name;
    for (int i = 0; i < (numPlayer + 1); i++) {
        Hand player;
        playerDecks.push_back(player);

        if (i == numPlayer) {
            playerDecks.at(i).setName("Dealer");
        }
        else if ((i + 1) == 1) {
            cout << "What is the " << to_string(i + 1) << "'st player's name?" << endl;
            cin >> name;
            playerDecks.at(i).setName(name);
        }
        else if ((i + 1) == 2) {
            cout << "What is the " << to_string(i + 1) << "'nd player's name?" << endl;
            cin >> name;
            playerDecks.at(i).setName(name);
        }
        else if ((i + 1) == 3) {
            cout << "What is the " << to_string(i + 1) << "'rd player's name?" << endl;
            cin >> name;
            playerDecks.at(i).setName(name);
        }
        else {
            cout << "What is the " << to_string(i + 1) << "'th players name?" << endl;
            cin >> name;
            playerDecks.at(i).setName(name);
        }

        playerDecks.at(i).bust = false;
    }

    return playerDecks;
}

vector<Hand> playPlayers(Deck* deck, vector<Hand> playerDecks, int numPlayer) {
    
    char userCont;
    int t;

    for (int i = 0; i < numPlayer; i++) {
        userCont = ' ';
        t = 0;
        while ((userCont != 's') && (userCont != 'S')) {
            cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << playerDecks.at(i).getName() << "'s Cards:" << endl;
            playerDecks.at(i).showHand();
            t = total(playerDecks.at(i));
            cout << "Total: " << to_string(t) << endl;
            if (t > 21) {
                cout << "Bust: Over 21" << endl;
                playerDecks.at(i).bust = true;
                userCont = 's';
            }
            else {
                cout << "Would you like another card? Press H to hit or S to stay:" << endl;
                cin >> userCont;
                while ((userCont != 's') && (userCont != 'S') && (userCont != 'h') && (userCont != 'H')) {
                    cout << "INVALID INPUT" << endl;
                    cout << "Would you like another card? Press H to hit or S to stay:" << endl;
                    cin >> userCont;
                }
                if ((userCont == 'h') || (userCont == 'H')) {
                    playerDecks.at(i).addCard(deck->draw());
                }
            }
        }
    }

    return playerDecks;
}

void playDealer(vector<Hand> playerDecks, Deck* deck, int numPlayer) {
    while (total(playerDecks.at(numPlayer)) < 17) {
        cout << "Dealer Cards" << endl;
        playerDecks.at(numPlayer).showHand();
        playerDecks.at(numPlayer).addCard(deck->draw());
    }

    cout << "Dealer Cards" << endl;
    playerDecks.at(numPlayer).showHand();

    if (total(playerDecks.at(numPlayer)) > 21) {
        cout << "Dealer Bust, All Remaining Players Win" << endl;
    }
    else {
        for (int player = 0; player < numPlayer; player++) {
            if (!(playerDecks.at(player).bust)) {
                cout << "Dealer's Total: " << to_string(total(playerDecks.at(numPlayer))) << endl;
                cout << playerDecks.at(player).getName() << "'s Total: " << to_string(total(playerDecks.at(player))) << endl;
                if (total(playerDecks.at(numPlayer)) > total(playerDecks.at(player))) {
                    cout << "Dealer Wins" << endl;
                }
                else if (total(playerDecks.at(numPlayer)) < total(playerDecks.at(player))) {
                    cout << playerDecks.at(player).getName() << " WINS!!!" << endl;
                }
                else {
                    cout << "PUSH" << endl;
                }
            }
            else {
                cout << playerDecks.at(player).getName() << " busted. Dealer Wins" << endl;
            }
        }
    }
}


