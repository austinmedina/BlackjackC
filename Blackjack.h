#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <list>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Card {
public:
    Card();
    Card(string suit, string value);
    void setSuit(string suit);
    void setVal(string val);
    string getSuit();
    string getVal();
    void show();

private:
    string suit;
    string val;
};

class Deck {
    public:
        Deck();
        Card draw();
        void shuffle();

    private:
        vector< Card > cards;
};

class Hand {
    public:
        void setName(string n);
        string getName();
        void addCard(Card card);
        vector<Card> cards;
        void showHand();
        bool bust = false;
    private:
        string name;

};

void dealPlayers(Deck* deck, vector<Hand> &players);

void removePlayers(vector<Hand> &players);

void addPlayers(vector<Hand> &players);

int total(Hand hand);

vector<Hand> createPlayers(Deck* deck, int numPlayer);

vector<Hand> playPlayers(Deck* deck, vector<Hand> playerDecks, int numPlayer);

void playDealer(vector<Hand> playerDecks, Deck* deck, int numPlayer);

#endif