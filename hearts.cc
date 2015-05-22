#include<iostream>
#include<map>
#include<sstream>
#include"card.h"
#include"deck.h"

using namespace std;

void outputdeck(Deck* d) {
  for(int i = 0; i < 52; i++) {
    cout << d->deckofcards[i]->number << "  " << d->deckofcards[i]->suite << endl;
  }
}

void outputhand(const vector<Card*>& v) {
  for(int i = 0; i < v.size(); i++) {
    cout << v[i]->number;
    int n = v[i]->number;
    stringstream ss;
    ss << n;
    char c;
    int count = 0;
    while(ss >> c) {
      count++;
    }
    if(count == 1) {
      cout << "   ";
    }
    else if(count == 2) {
      cout << "  ";
    }
    else {
      cerr << "Wrong number of digits in the number of a card." << endl;
    }
    if(v[i]->suite == 1) {
      cout << "♣ " << endl;
    }
    else if(v[i]->suite == 2) {
      cout << "♠ " << endl;
    }
    else if(v[i]->suite == 3) {
       cout << "❤ " << endl;
    }
    else if(v[i]->suite == 4) {
      cout << "♦" << endl;
    }
    else {
      cerr << "Bad suite number, must be 1-4" << endl;
    }
  }
}

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
    

int main() {
  Deck* carddeck = new Deck();
  carddeck->Shuffle();
  cout << "You are playing hearts today!" << endl;
  cout << "You will play against 3 other players, Sid, Jim, and Sal!" << endl;
  cout << "Enter name please: ";
  string name;
  cin >> name;
  vector<Card*> Sid;
  vector<Card*> Jim;
  vector<Card*> Sal;
  vector<Card*> player;
  deal(carddeck, Sid, Jim, Sal, player);
  outputhand(mergesort(player));
}






