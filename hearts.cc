#include<iostream>
#include<map>
#include<sstream>
#include"card.h"
#include"deck.h"

using namespace std;

void deal(const Deck* const d, vector<Card*>& p1, vector<Card*>& p2, vector<Card*>& p3, vector<Card*>& p) {
  for(int i = 0; i < 52; i++) {
    p1.push_back(d->deckofcards[i]); i++;
    p2.push_back(d->deckofcards[i]); i++;
    p3.push_back(d->deckofcards[i]); i++;
    p.push_back(d->deckofcards[i]);
  }
} 

vector<Card*> merge(const vector<Card*>& v1, const vector<Card*>& v2) {  //merge function for mergesort
  vector<Card*> v;
  int i = 0;
  int j = 0;
  while(i < v1.size() && j < v2.size()) {
    if(*v1[i] < *v2[j]) {    //Note use of overloaded operators < for class Card
      v.push_back(v1[i]);
      i++;
    }
    else {
      v.push_back(v2[j]);
      j++;
    }
  }
  if(i < v1.size()) {
    while(i < v1.size()) {
      v.push_back(v1[i]);
      i++;
    }
  }
  else {
    while(j < v2.size()) {
      v.push_back(v2[j]);
      j++;
    }
  }
  return v;
}     

vector<Card*> firsthalf(const vector<Card*>& v) { //takes first half (for mergesort)
  int n = v.size()/2;
  vector<Card*> retval;
  for(int i = 0; i < n; i++) {
    retval.push_back(v[i]);
  }
  return retval;
}

vector<Card*> secondhalf(const vector<Card*>& v) { //takes second half (for mergesort)
  int n = v.size()/2;
  vector<Card*> retval;
  for(int i = n; i < v.size(); i++) {
    retval.push_back(v[i]);
  }
  return retval;
}

vector<Card*> mergesort(vector<Card*> v) {     //sorts a hand of cards
  if(v.size() == 1) {
    return v;
  }
  vector<Card*> v1 = mergesort(firsthalf(v));
  vector<Card*> v2 = mergesort(secondhalf(v));
  return merge(v1, v2);
}
    
bool hastwoofclubs(const vector<Card*>& v) {  //check to see who goes first
  for(int i = 0; i < v.size(); i++) {
    if(v[i]->number == 2 && v[i]->suite == 1) {
      return true;
    }
  }
  return false;
}

ostream& operator<<(ostream& out, vector<Card*> v) {
  for(int i = 0; i < v.size(); i++) {
    out << *v[i];
  }
  return out;
}

int main() {
  Deck* carddeck = new Deck();
  carddeck->Shuffle();
  //cout << *carddeck;
  cout << "You are playing hearts today!" << endl;
  cout << "You will play against 3 other players, Sid, Jim, and Sal!" << endl;
  cout << "Enter name please: ";
  string name;
  cin >> name;
  vector<Card*> Sid;
  vector<Card*> Jim;
  vector<Card*> Sal;
  vector<Card*> Player;
  deal(carddeck, Sid, Jim, Sal, Player);
  cout << mergesort(Player);
  if(hastwoofclubs(Sid)) {
    vector<Card*> gametime[4] = {Sid, Jim, Sal, Player};
  }
  else if(hastwoofclubs(Jim)) {
    vector<Card*> gametime[4] = {Jim, Sal, Player, Sid};
  }
  else if(hastwoofclubs(Sal)) {
    vector<Card*> gametime[4] = {Sal, Player, Sid, Jim};
  }
  else if(hastwoofclubs(Player)) {
    vector<Card*> gametime[4] = {Player, Sid, Jim, Sal};
  }
  else {
    cerr << "Bad, nobody has two of clubs" << endl;
  }   
}






