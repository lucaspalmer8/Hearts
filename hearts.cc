#include<iostream>
#include<vector>
#include<map>
#include<sstream>
#include<time.h>
#include<cstdlib>

using namespace std;

class Card {
  public:
    Card(int n, int s): number(n), suite(s) {}
    ~Card() {} 
    int number;
    int suite; //1 clubs, 2 spades, 3 hearts, 4 diamonds
};

class Deck {
public:
  static int instance;
  static int isDeck() {
    return instance;
  }
  Deck() {
    for(int i = 1; i < 14; i++) {
      for(int j = 1; j < 5; j++) {
        Card* card = new Card(i, j);
        deckofcards.push_back(card);
      }
    }
    addinstance();
  }
  ~Deck() {
    for(int i = 0; i < 52; i++) {
      delete deckofcards[i];
    }
    subinstance();
  }
  void Shuffle() {
    srand (time(NULL));
    for(int i = 0; i < 100; i++) {
      int n = rand() % 52;
      int m = rand() % 52;
      Card* temp = deckofcards[n];
      deckofcards[n] = deckofcards[m];
      deckofcards[m] = temp;
    }
  }
  static void addinstance() {
    instance = 1;
  }
  static void subinstance() {
    instance = 0;
  }   
  vector<Card*> deckofcards;
};

int Deck::instance = 0;

void output(Deck* d) {
  for(int i = 0; i < 52; i++) {
    cout << d->deckofcards[i]->number << "  " << d->deckofcards[i]->suite << endl;
  }
}

int main() {
  Deck* deal = new Deck();
  deal->Shuffle();
  output(deal);
}
