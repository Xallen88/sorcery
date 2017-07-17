#include "Minion.h"
#include "Enchantments.h"
using namespace std;

Minion::Minion(string name, int a, int h): Card{name}, curAtk{a}, curHp{h},
                                                       maxAtk{a}, maxHp{h},
                                                       base_atk{a}, base_hp{h}{}
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
void Minion::Attack(Player *p) { /*Check if can attack then */ p->decrementLife(atk); }
void Minion::Attack(Minion *m) { /*Check if can attack then */ m->decrementLife(atk); }
void Minion::decrementLife(int i) { 
 hp -= i;
 if (hp < 0) hp = 0;
}
void Minion::incrementLife(int i) {
 hp += i;
 if (hp > maxHp) hp = maxHp;
}
bool Minion::isDead {
 return hp <= 0;
}
void Minion::addEnchant(Enchantments *e) {//Supports * and + on attack and *, +, - on hp
  //remove from vector
  enchantments.emplace_back(e);
  numEnch++;
  //Add the stats in from enchantments
  applyChange(e->getAOp(), 'a', e->getAVal());
  applyChange(e->getHOp(), 'h', e->getHVal());
  
}
void Minion::clearAllEnchants() {
 int aOp = enchantment[v.size() - 1]->getAOp();
 int hOp = enchantment[v.size() - 1]->getHOp();
 
 //Take away stats from enchantment
 // for atk stats
 if (aOp == '*') {
   applyChange('/', 'a', e->getAVal());
 } else if (aOp = '/') {
   applyChange('*', 'a', e->getAVal());
 } else if (aOp = '+') {
   applyChange('-', 'a', e->getAVal());
 } else {//the subtract case
   applyChange('+', 'a', e->getAVal());
 }
 //For hp stats
 if (hOp == '*') {
   applyChange('/', 'h', e->getHVal());
 } else if (hOp = '/') {
   applyChange('*', 'h', e->getHVal());
 } else if (hOp = '+') {
   applyChange('-', 'h', e->getHVal());
 } else {//the subtract case
   applyChange('+', 'h', e->getHVal());
 }
 //popping enchantment
  for (int k = 0; k < numEnch; k++) 
    enchantments.popback()
  }
  numEnch = 0;
}

int Minion::getHp() { return curHp; }
int Minion::getAtk() { return curAtk; }
