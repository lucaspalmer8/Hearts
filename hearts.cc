#include<iostream>
#include<map>
#include<string>
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

void removecard(vector<Card*>& v, int index) {
  for(int i = index; i < v.size()-1; i++) {
    v[i] = v[i+1];
  }
  v.pop_back();
}
  
int countitup(const vector<Card*> v, int suite) {
  int ret = 0;
  for(int i = 0; i < v.size(); i++) {
    if(v[i]->suite == suite) {
      ret++;
    }
  }
  return ret;
}

void playcardspecial(vector<Card*>& hand, vector<Card*>& delt) {
  if(delt.size() == 0) {
    cout << "Your lead man!" << endl;
    cout << "Your hand is:  " << endl;
  }
  else {
    cout << delt.size() << " players have played already." << endl;
    cout << "They played (in following order): " << endl;
    for(int i = 0; i < delt.size(); i++) {
      cout << *delt[i] << "     ";
    }
    cout << endl;
  }
  int c = 0;
  for(vector<Card*>::iterator it = hand.begin(); it != hand.end(); it++) {
    cout << c << ":";
    stringstream ss;
    ss << c;
    char b;
    int countdigits = 0;
    while(ss >> b) {
      countdigits++;
    }
    if(countdigits == 1) {
      cout << "   " << **it << endl;
    }
    else if(countdigits == 2) {
      cout << "  " << **it << endl;
    }
    else {
      cerr << "Wrong number of digits, bad!!!" << endl;
    }
    c++;
  }
  int choice;
  cout << "Pick card number..." << endl;
  while(1) {
    if(!(cin >> choice)) {
      cout << "Please enter an integer." << endl;
      cin.clear();
      cin.ignore();
    } 
    else if(choice < 0 || choice >= hand.size()) {
      cout << "Please enter an interger between " << 0 << " and " << hand.size()-1 << "." << endl;
    }
    else {
      Card* pick = hand[choice];
      cout << "You played:  " << *pick << endl;
      if(delt.size() != 0) {
        if((delt[0]->suite != pick->suite) && (countitup(hand, delt[0]->suite) != 0)) {
          cout << "Must play same suite as first card bud!" << endl;
          cout << "Enter a new number" << endl;
        }
        else {
          removecard(hand, choice);
          delt.push_back(pick);
          break;
        }
      }
      else {
        removecard(hand, choice);
        delt.push_back(pick);
        break;
      }
    }
  }
}
  
void playcard(vector<Card*>& hand, vector<Card*>& delt) {
  if(delt.size() == 0) {
    Card* pick = hand[0];
    removecard(hand, 0);
    delt.push_back(pick);
  }
  else {
    if(countitup(hand, delt[0]->suite) != 0) {
      for(int i = 0; i < hand.size(); i++) {
        if(hand[i]->suite == delt[0]->suite) {
          Card* pick = hand[i];
          removecard(hand, i);
          delt.push_back(pick);
          break;
        }
      }
    }
    else {
      Card* pick = hand[0];
      removecard(hand, 0);
      delt.push_back(pick);
    }
  }
}  

void updatescores(const vector<Card*>& played, vector<int>& scores) {  
  int theone = played[0]->suite;
  int thenumber = played[0]->number;
  int theloser = 0;
  for(int i = 1; i < 4; i++) {
    if((played[i]->suite == theone) && (played[i]->number > thenumber)) {
      thenumber = played[i]->number;
      theloser = i;
    }
  }
  int points;
  for(int i = 0; i < 4; i++) {
    if(played[i]->suite == 3) {
      points += 1;
    }
    if((played[i]->suite == 2) && (played[i]->number == 12)) {
      points += 13;
    }
  }
  scores[theloser] += points;
}
  
void printscores(const vector<string> names, const vector<int> scores) {
  cout << endl << endl << "The scores are... " << endl;
  for(int i = 0; i < 4; i++) {
    cout << names[i] << "   " << scores[i] << endl;
  }
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
  Sid = mergesort(Sid);
  Jim = mergesort(Jim);
  Sal = mergesort(Sal);
  Player = mergesort(Player);
  int spot;
  vector<vector<Card*> > gametime;
  vector<string> names;
  if(hastwoofclubs(Sid)) {
    gametime.push_back(Sid);     names.push_back("Sid"); 
    gametime.push_back(Jim);     names.push_back("Jim");
    gametime.push_back(Sal);     names.push_back("Sal");
    gametime.push_back(Player);  names.push_back(name);
    spot = 3;
  }
  else if(hastwoofclubs(Jim)) {
    gametime.push_back(Jim);     names.push_back("Jim");
    gametime.push_back(Sal);     names.push_back("Sal");
    gametime.push_back(Player);  names.push_back(name);
    gametime.push_back(Sid);     names.push_back("Sid");
    spot = 2;
  }
  else if(hastwoofclubs(Sal)) {
    gametime.push_back(Sal);     names.push_back("Sal");
    gametime.push_back(Player);  names.push_back(name);
    gametime.push_back(Sid);     names.push_back("Sid");
    gametime.push_back(Jim);     names.push_back("Jim");
    spot = 1;
  }
  else if(hastwoofclubs(Player)) {
    gametime.push_back(Player);  names.push_back(name);
    gametime.push_back(Sid);     names.push_back("Sid");
    gametime.push_back(Jim);     names.push_back("Jim");
    gametime.push_back(Sal);     names.push_back("Sal");
    spot = 0;
  }
  else {
    cerr << "Bad, nobody has two of clubs" << endl;
  }
  vector<int> scores;
  scores.push_back(0); scores.push_back(0); scores.push_back(0); scores.push_back(0);
  for(int i = 0; i < 13; i++) {
    vector<Card*> played;
    for(int j = 0; j < 4; j++) {
      if(j == spot) {
        playcardspecial(gametime[j], played);
      }
      else {
        playcard(gametime[j], played);
      }
    }
    updatescores(played, scores);
    printscores(names, scores);
  }      
}
