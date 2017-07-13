 #include "Minion.h"
using namespace std;

Minion::Minion(int a, int d): atk{a}, def{d}{}
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
