#include"deck.h"
#include<time.h>
#include<cstdlib>

using namespace std;

int Deck::isDeck() {
  return instance;
}

Deck::Deck() {
  for(int i = 1; i < 14; i++) {
    for(int j = 1; j < 5; j++) {
      Card* card = new Card(i, j);
      deckofcards.push_back(card);
    }
  }
  addinstance();
}

Deck::~Deck() {
  for(int i = 0; i < 52; i++) {
    delete deckofcards[i];
  }
  subinstance();
}

void Deck::Shuffle() {
  srand (time(NULL));
  for(int i = 0; i < 200; i++) {
    int n = rand() % 52;
    int m = rand() % 52;
    Card* temp = deckofcards[n];
    deckofcards[n] = deckofcards[m];
    deckofcards[m] = temp;
  }
}

void Deck::addinstance() {
  instance = 1;
}

void Deck::subinstance() {
  instance = 0;
}

int Deck::instance = 0;
