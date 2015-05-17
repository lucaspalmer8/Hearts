#include<iostream>
#include<map>
#include<sstream>
//#include<time.h>
//#include<cstdlib>
#include"card.h"
#include"deck.h"

using namespace std;

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
