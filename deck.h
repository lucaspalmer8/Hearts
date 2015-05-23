#ifndef __deck__h
#define __deck__h
#include<vector>
#include"card.h"
#include<iostream>

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

std::ostream& operator<<(std::ostream& out, const Deck& d);

#endif
