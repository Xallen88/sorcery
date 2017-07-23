#include <string>
#include "Minion.h"
#include "Enchantments.h"
#include "Player.h"
#include "Sorcery.h"
#include "Card.h"
#include "Sorcery.h"

Minion::Minion(){}
Minion::Minion(string name): {
  type = "Minion";
  stringstream ss;
  string line;
  string fileName = name;
  actions = 1;

  int len = fileName.length();
  for (int i = 0; i < len; ++i) {
    if (fileName[i] == ' ') {
      fileName.erase(i);
      --i;
      --len;
    }
  }

  fileName = "minions/" + fileName + ".info";
  ifstream infoFile (fileName);
  getline(infoFile, line);
  //Adding cost, atk, hp
  ss >> cost;
  ss >> curAtk;
  ss >> curHp;
  maxHp = curHp;
  maxAtk = curAtk;
  //Determining if any active/triggered ability
  ss >> trigger;
  //5 signifying a activateable ability reads the cost of activation
  if (trigger == 5) { 
    ss >> tCost;  
  }
  if (trigger == 0) return;//no trigger thus no desc
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
void Minion::incrementAtk(int i) {
  curAtk += i;
  maxAtk += i;
}

void Minion::decrementAtk(int i) {
  curAtk -= i;
  maxAtk -= i;
}
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

void Minion::Play(){ activePlayer->summonMinion(this); }

void Minion::Play(Card* c){
 //Nothing
}
void Minion::resetActions() { actions = 1; }
bool hasActionLeft() { return actions == 1; }
void useAction() { actions--; }

void Minion::FireElemental(Card *c) {
	if(c->getOwner() != owner){
        	Minion* minionPtr = (Minion*) c;
		minionPtr->decrementLife(1);
	}
}
void Minion::PotionSeller() {
  int m = activePlayer->numMinions();
  for (int k = 1; k <= m; k++) {
    Minion *m = activePlayer->getMinion(k);
    m->applyChange('+', h, 1);
  }
}
void Minion::NovicePyromancer(Card *c) {
  if (c->getType() != "Minion") return;
  Minion *m = c;
  m->decrementLife(1);
}
void Minion::ApprenticeSummoner() {
  int num = activePlayer->numMinions();
  if (num == 5) return;
  Minion *m = new Minion("AirElemental");
  activePlayer->summonMinion(m);
}
void Minion::MasterSummoner() {
  int num = activePlayer->numMinions();
  if (num < 5) {
    for (int k = 0; k < 5-num; k++) {
      Minion *m = new Minion("AirElemental");
      activePlayer->summonMinion(m);
    }
  }
}
void Minion::Activate(){
  if (name == "Potion Seller") PotionSeller();
  else if (name == "Apprentice Summoner") ApprenticeSummoner();
  else if (name == "Master Summoner") MasterSummoner();
}

void Minion::Activate(Card* c){
  if (name == "Novice Pyromancer") NovicePyromancer(c);
  else if (name == "Fire Elemental") FireElemental(c);
}
