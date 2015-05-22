#include"card.h"

using namespace std;

Card::Card(int n, int s): number(n), suite(s) {}

Card::~Card() {}

bool Card::operator>(const Card& c) {
  if (this->suite > c.suite) {
    return true;
  }
  else if (this->suite < c.suite) {
    return false;
  }
  else {
    if (this->number > c.number) {
      return true;
    }
    else {
      return false;
    }
  }
}
  
    
bool Card::operator<(const Card& c) {
  if (this->suite < c.suite) {
    return true;
  }
  else if (this->suite > c.suite) {
    return false;
  }
  else {
    if (this->number < c.number) {
      return true;
    }
    else {
      return false;
    }
  }
}


