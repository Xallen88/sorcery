 #include "Minion.h"
using namespace std;

Minion::Minion(int a, int d): atk{a}, def{d}{}
void Minion::Attack(Player *p) { /*Check if can attack then */ p->decrementLife(atk); }
