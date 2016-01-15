#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include<cstdlib>
#include<time.h>
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

ostream& operator<<(ostream& out, vector<Card*> v) {  //output operator for a hand of cards
  for(int i = 0; i < v.size(); i++) {
    out << *v[i];
  }
  return out;
}

void removecard(vector<Card*>& v, int index) {  //remove the played card from the hand of cards
  for(int i = index; i < v.size()-1; i++) {
    v[i] = v[i+1];
  }
  v.pop_back();
}
  
int countitup(const vector<Card*> v, int suite) { //counts the number of specific suite in a hand
  int ret = 0;
  for(int i = 0; i < v.size(); i++) {
    if(v[i]->suite == suite) {
      ret++;
    }
  }
  return ret;
}

void playcardspecial(vector<Card*>& hand, vector<Card*>& delt, int i, int j, string name) { //player must play a card
  if(delt.size() == 0) {
    cout << "Your lead " << name << "!" << endl;
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
  cout << name << ", pick the card number that you want to play..." << endl;
  string temp;
  while(1) {
    getline(cin, temp);
    stringstream sss(temp);
    if(!(sss >> choice)) {
      cout << name << ", please enter an integer." << endl;
    } 
    else if(sss >> temp) {
      cout << name << ", please enter a single value." << endl;
    }
    else if(choice < 0 || choice >= hand.size()) {
      cout << name << ", please enter an interger between " << 0 << " and " << hand.size()-1 << "." << endl;
    }
    else {
      Card* pick = hand[choice];
      cout << "You played:  " << *pick << endl;
      if(delt.size() != 0) {
        if((delt[0]->suite != pick->suite) && (countitup(hand, delt[0]->suite) != 0)) {
          cout << "Must play same suite as first card bud!" << endl;
          cout << "Enter a new number." << endl;
        }
        else {
          removecard(hand, choice);
          delt.push_back(pick);
          break;
        }
      }
      else {
        //"This is j: " << j << "  This is i: " << i << " This is suite: " << pick->suite << " This is number: " << pick->number << endl;
	if(j == 0 && i == 0 && (pick->suite != 1 || pick->number != 2)) {
          cout << "Must lead with the two of clubs, " << name << "." << endl;
          cout << "Enter a new number." << endl;
        }
        else {
          removecard(hand, choice);
          delt.push_back(pick);
          break;
        }
      }
    }
  }
}
  
void playcardeasy(vector<Card*>& hand, vector<Card*>& delt, int i, int j) { //computer must play a card
  srand (time(NULL));
  if(delt.size() == 0) {
    int play = rand() % hand.size();
    Card* pick;
    if(i == 0 && j == 0) {
      if(hand[0]->number == 2) {
        pick = hand[0];
      } 
      else {
        pick = hand[1];
      }
    }
    else {
      pick = hand[play];
    }
    removecard(hand, play);
    delt.push_back(pick);
  }
  else {
    int counter = countitup(hand, delt[0]->suite);
    if(counter != 0) {
      for(int i = 0; i < hand.size(); i++) {
        if(hand[i]->suite == delt[0]->suite) {
          int play = rand() % counter;
          Card* pick = hand[i+play];
          removecard(hand, i+play);
          delt.push_back(pick);
          break;
        }
      }
    }
    else {
      int play = rand() % hand.size();
      Card* pick = hand[play];
      removecard(hand, play);
      delt.push_back(pick);
    }
  }
}  

void playcardhard(vector<Card*>& hand, vector<Card*>& delt, int i, int j) {
  srand (time(NULL));
  if(delt.size() == 0) {
    int play = rand() % hand.size();
    Card* pick;
    if(i == 0 && j == 0) {
      if(hand[0]->number == 2) {
        pick = hand[0];
      }
      else {
        pick = hand[1];
      }
    }
    else {
      pick = hand[play];
    }
    removecard(hand, play);
    delt.push_back(pick);
  }
  else {
    int counter = countitup(hand, delt[0]->suite);
    if(counter != 0) {
      for(int i = 0; i < hand.size(); i++) {
        if(hand[i]->suite == delt[0]->suite) {
		  Card* pick = hand[i];
		  int play = i;
		  for(int j = 0; j < counter; j++) {
			int cardnumber = hand[i+j]->number;
			if(cardnumber < delt[0]->number || (delt.size() > 1 && cardnumber < delt[1]->number) 
				|| (delt.size() > 2 && cardnumber < delt[2]->number)) {
			  play = i+j;
			  pick = hand[i+j];
			}
		  }
          removecard(hand, i);
          delt.push_back(pick);
          break;
        }
      }
    }
    else {
	  //get rid of a bad card!
	  int play = -1;	  //the index of the card you want to play
	  Card* pick = 0;     //the card you want to play
	  for(int i = 0; i < hand.size(); i++) {
	    if(hand[i]->suite == 2 && hand[i]->number == 12) {
		  //queen of spades
		  play = i;
		  pick = hand[i];
		  
		} 
	  }
	  if(!pick) {
	    for(int i = 0; i < hand.size(); i++) {
		  if(hand[i]->suite == 3) {
			//a heart
			if(!pick || pick->number < hand[i]->number) {
			  play = i;
		      pick = hand[i];
			}
		  }
		}
	  }
	  if(!pick) {
	    play = rand() % hand.size();
      	pick = hand[play];
	  }
      removecard(hand, play);
      delt.push_back(pick);
    }
  }
}

void updatescores(const vector<Card*>& played, vector<int>& scores, int& next) {  
  int theone = played[0]->suite;
  int thenumber = played[0]->number;
  int theloser = next;
  for(int i = 1; i < 4; i++) {
    int atcard = (next + i) % 4;
    if((played[i]->suite == theone) && (played[i]->number > thenumber)) {
      thenumber = played[i]->number;
      theloser = atcard;
    }
  }
  next = theloser;  
  int points = 0;
  for(int i = 0; i < 4; i++) {
    if(played[i]->suite == 3) {
      points += 1;
    }
    if((played[i]->suite == 2) && (played[i]->number == 12)) {
      points += 13;
    }
  }
  if(points == 26) {
    for(int i = 0; i < 4; i++) {
      if(i != theloser) {
        scores[theloser] += 26;
      }
    }
  } 
  else {
    scores[theloser] += points;
  }
}
  
void printscores(const vector<string> names, const vector<int> scores) {
  cout << endl << endl << endl << endl << endl << endl << "The scores are... " << endl;
  for(int i = 0; i < 4; i++) {
    cout << names[i] << "   " << scores[i] << endl;
  }
}

void playhearts(string& level) {
  cout << endl << endl << endl << endl << endl << endl;
  Deck* carddeck = new Deck();
  carddeck->Shuffle();
  //cout << *carddeck;
  cout << "Welcome to the game of hearts!"  << endl;
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
  int spot = 3;  //holds the spot of the player
  int next;  //holds the spot of the next player to go
  vector<vector<Card*> > gametime;
  vector<string> names;
  gametime.push_back(Sid);     names.push_back("Sid"); 
  gametime.push_back(Jim);     names.push_back("Jim");
  gametime.push_back(Sal);     names.push_back("Sal");
  gametime.push_back(Player);  names.push_back(name);
  if(hastwoofclubs(Sid)) {
    next = 0;
  }
  else if(hastwoofclubs(Jim)) {
    next = 1;
  }
  else if(hastwoofclubs(Sal)) {
    next = 2;
  }
  else if(hastwoofclubs(Player)) {
    next = 3;
  }
  else {
    cerr << "Bad, nobody has two of clubs" << endl;
  }
  vector<int> scores;
  scores.push_back(0); scores.push_back(0); scores.push_back(0); scores.push_back(0);
  for(int i = 0; i < 13; i++) {
    cout << endl << endl << endl << endl << endl << endl << endl;
    vector<Card*> played;
    for(int j = 0; j < 4; j++) {
      int togo = (next + j) % 4;
      if(togo == spot) {
        playcardspecial(gametime[togo], played, i, j, name);
      }
      else {
        if(level == "easy") playcardeasy(gametime[togo], played, i, j);
        if(level == "hard") playcardhard(gametime[togo], played, i, j);
      }
    }
    updatescores(played, scores, next);
  }
  printscores(names, scores);
  delete carddeck;      
}

void asklevel(string& level) {  //asks about the preferred level of difficulty
  string answer;
  while(1) {
    cout << endl << endl << endl << endl << endl << endl;
    cout << "What level do you want to play?! (easy/hard)" << endl;
    getline(cin,answer);
    stringstream sss(answer);
    sss >> answer;
    if(answer == "easy" && !(sss >> answer)) {
      level = "easy";
      break;
    }
    else if(answer == "hard" && !(sss >> answer)) {
      level = "hard";
      break;
    }
    else {
      cout << "Please enter easy or hard!" << endl;
    }
  }
}

int ask(string& level) {   //asks if you want to play hearts
  int val = 1;
  string answer;
  while(1) {
    cout << endl << endl << endl << endl << endl << endl;
    cout << "Would you like to play hearts?! (yes/no)" << endl;
    getline(cin,answer);
    stringstream sss(answer);
    sss >> answer;
    if(answer == "yes" && !(sss >> answer)) {
      asklevel(level);
      break;
    }
    else if(answer == "no" && !(sss >> answer)) {
      cout << "OK, bye!" << endl;
      val = 0;
      break;
    }
    else {
      cout << "Please enter yes or no!" << endl;
    }
  }
  return val;
}


int main() {
  string level;
  while(1) {
    if(ask(level)) {
      playhearts(level);
    }
    else {
      break;
    }
  }
}
    
















