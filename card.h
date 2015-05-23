#ifndef __card__h
#define __card__h
#include<iostream>

class Card {
  public:
    Card(int n, int s);
    ~Card();
    bool operator>(const Card& c);
    bool operator<(const Card& c);
    int number;
    int suite; //1 clubs, 2 spades, 3 hearts, 4 diamonds
};

std::ostream& operator<<(std::ostream& out, const Card& c);

#endif

