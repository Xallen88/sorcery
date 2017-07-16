 #include "Minion.h"
using namespace std;

Minion::Minion(string name, int a, int h): Card{name}, curAtk{a}, curHp{h},
                                                       maxAtk{a}, maxHp{h}{}
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
void Minion::addEnchant(Enchantments *e) {
  enchantments.emplace_back(e);
  numEnch++;
  //Add the stats in from enchantments
}
void Minion::clearAllEnchants() {
  for (int k = 0; k < numEnch; k++) 
    enchantments.popback()
  }
  numEnch = 0;
  //Take away stats from echantments
}
