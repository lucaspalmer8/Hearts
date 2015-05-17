#ifndef __deck__h
#define __deck__h
#include<vector>
#include"card.h"

class Deck {
public:
  static int instance;
  static int isDeck();
  Deck();
  ~Deck();
  void Shuffle();
  static void addinstance();
  static void subinstance();
  std::vector<Card*> deckofcards;
};

#endif
