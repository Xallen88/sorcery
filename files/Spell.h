#ifndef _SPELL_H_
#define _SPELL_H_

#include <string>
#include <vector>
#include "Card.h"

using std::vector;

extern vector<string> spellList;

class Spell : public Card {
  bool destroyed;
  void Recharge();
  void RaiseDead();
  void Blizzard();
  void FindMinions();
  void Banish(Card *c);
  void Unsummon(Card *c);
  void Disenchant(Card *c);
 public:
  Spell();
  Spell(string name);
  ~Spell() override;
  void Activate(Card *c) override;
  void Activate() override;
  void Play() override;
  void Play(Card* c) override;
  bool isDestroyed();
  void Destroy();
};
#endif
