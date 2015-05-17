#include<iostream>
#include<map>
#include<sstream>
#include"card.h"
#include"deck.h"

using namespace std;

void outputdeck(Deck* d) {
  for(int i = 0; i < 52; i++) {
    cout << d->deckofcards[i]->number << "  " << d->deckofcards[i]->suite << endl;
  }
}

void outputhand(const vector<Card*>& v) {
  for(int i = 0; i < v.size(); i++) {
    cout << v[i]->number;
    int n = v[i]->number;
    stringstream ss;
    ss << n;
    char c;
    int count = 0;
    while(ss >> c) {
      count++;
    }
    if(count == 1) {
      cout << "   ";
    }
    else if(count == 2) {
      cout << "  ";
    }
    else {
      cerr << "Wrong number of digits in the number of a card." << endl;
    }
    if(v[i]->suite == 1) {
      cout << "♣ " << endl;
    }
    else if(v[i]->suite == 2) {
      cout << "♠ " << endl;
    }
    else if(v[i]->suite == 3) {
       cout << "❤ " << endl;
    }
    else if(v[i]->suite == 4) {
      cout << "♦" << endl;
    }
    else {
      cerr << "Bad suite number, must be 1-4" << endl;
    }
  }
}

void deal(const Deck* const d, vector<Card*>& p1, vector<Card*>& p2, vector<Card*>& p3, vector<Card*>& p) {
  for(int i = 0; i < 52; i++) {
    p1.push_back(d->deckofcards[i]); i++;
    p2.push_back(d->deckofcards[i]); i++;
    p3.push_back(d->deckofcards[i]); i++;
    p.push_back(d->deckofcards[i]);
  }
} 

int main() {
  Deck* carddeck = new Deck();
  carddeck->Shuffle();
  cout << "You are playing hearts today!" << endl;
  cout << "You will play against 3 other players, Sid, Jim, and Sal!" << endl;
  cout << "Enter name please: ";
  string name;
  cin >> name;
  vector<Card*> Sid;
  vector<Card*> Jim;
  vector<Card*> Sal;
  vector<Card*> player;
  deal(carddeck, Sid, Jim, Sal, player);
  outputhand(player);
}






