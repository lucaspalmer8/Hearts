#include"card.h"
#include<iostream>
#include<sstream>

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

ostream& operator<<(ostream& out, const Card& c) { //outputs a card
  out << c.number;
  stringstream ss;
  ss << c.number;
  char cc;
  int count = 0;
  while(ss >> cc) {
    count++;
  }
  if(count == 1) {
    out << "   ";
  }
  else if(count == 2) {
    out << "  ";
  }
  else {
    cerr << "Wrong number of digits in the number of a card." << endl;
  }
  if(c.suite == 1) {
    out << "♣ ";
  }
  else if(c.suite == 2) {
    out << "♠ ";
  }
  else if(c.suite == 3) {
    out << "❤ ";
  }
  else if(c.suite == 4) {
    out << "♦";
  }
  else {
    cerr << "Not a valid suite number" << endl;
  }
  return out;
}  
 
  


