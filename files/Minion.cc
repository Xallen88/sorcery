#include <string>
#include "Minion.h"
#include "Enchantments.h"
#include "Player.h"
#include "Sorcery.h"
#include "Card.h"

Minion::Minion(){}
Minion::Minion(string name): {
  type="Minion";
  stringstream ss;
  string line;
  string fileName = name;

	int len = fileName.length();
	for (int i = 0; i < len; ++i) {
		if (fileName[i] == ' ') {
			fileName.erase(i);
			--i;
			--len;
		}
	}

  fileName="minions/"+fileName+".info";
  ifstream infoFile (fileName);
  getline(infoFile, line);
 
  ss >> cost;
  ss >> charges;
  ss >> chargeCost;
  ss >> trigger;
  // take ints from file

  getline(ss, description);	
  // feed remaining line into description
}
Minion::~Minion(){}

void Minion::applyChange(char op, char c, int val) {
  if (c == 'a') {
    //doing attack stats
    if (op == '*') {
      maxAtk *= val;
      curAtk *= val;
    } else if (op == '+') {
      maxAtk += val;
      curAtk += val;
    } else if (op == '-') {
      maxAtk -= val;
      curAtk -= val;
    } else if (op == '/') {
      maxAtk /= val;
      curAtk /= val;
    }
  } else {//c is equal to h
    //doing defence stats
    if (op == '*') {
      maxHp *= val;
      curHp *= val;
    } else if (op == '+') {
      maxHp += val;
      curHp += val;
    } else if (op == '-') {
      maxHp -= val;
      curHp -= val;
    } else if (op == '/') {
      maxHp /= val;
      curHp /= val;
    }
  }
}
void Minion::Attack(Player *p) { /*Check if can attack then */ p->decrementLife(curAtk); }
void Minion::Attack(Minion *m) { /*Check if can attack then */ m->decrementLife(curAtk); }
void Minion::decrementLife(int i) { 
 curHp -= i;
 if (curHp < 0) curHp = 0;
}
void Minion::incrementLife(int i) {
 curHp += i;
 if (curHp > maxHp) curHp = maxHp;
}
bool Minion::isDead() {
 return curHp <= 0;
}
void Minion::addEnchant(Enchantment *e) {//Supports * and + on attack and *, +, - on hp
  //remove from vector
  enchantments.emplace_back(e);
  numEnch++;
  //Add the stats in from enchantments
  applyChange(e->getAOp(), 'a', e->getAVal());
  applyChange(e->getHOp(), 'h', e->getHVal());
  
}
void Minion::clearAllEnchants() {
 int aOp = enchantments.back()->getAOp();
 int hOp = enchantments.back()->getHOp();
 Enchantment *e = enchantments.back();
 
 //Take away stats from enchantment
 // for atk stats
 if (aOp == '*') {
   applyChange('/', 'a', e->getAVal());
 } else if (aOp == '/') {
   applyChange('*', 'a', e->getAVal());
 } else if (aOp == '+') {
   applyChange('-', 'a', e->getAVal());
 } else {//the subtract case
   applyChange('+', 'a', e->getAVal());
 }
 //For hp stats
 if (hOp == '*') {
   applyChange('/', 'h', e->getHVal());
 } else if (hOp == '/') {
   applyChange('*', 'h', e->getHVal());
 } else if (hOp == '+') {
   applyChange('-', 'h', e->getHVal());
 } else {//the subtract case
   applyChange('+', 'h', e->getHVal());
 }
 //popping enchantment
  for (int k = 0; k < numEnch; ++k){
    enchantments.pop_back();
  }
  numEnch = 0;
}

int Minion::getHp() { return curHp; }
int Minion::getAtk() { return curAtk; }

void Minion::Play(){
  Card* ritualPtr = activePlayer->getRitual();
  if (ritualPtr) {
    //graveyard.push_back(ritualPtr);
  }
  activePlayer->setRitual(this);
}

void Minion::Play(Card* c){

}

void Minion::Activate(){

}

void Minion::Activate(Card* c){

}
