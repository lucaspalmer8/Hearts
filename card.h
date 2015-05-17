#ifndef __card__h
#define __card__h

class Card {
  public:
    Card(int n, int s);
    ~Card();
    int number;
    int suite; //1 clubs, 2 spades, 3 hearts, 4 diamonds
};

#endif

