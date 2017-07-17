#ifndef _SPELL_H_
#define _SPELL_H_

#include "Card.h"

class Spell : public Card {
  //Bunch of private functions that activate based on spell
 public:
  Spell();
  ~Spell();
  void Activate(Card *c) override;
  void Activate() override;
  void Play() override;
};
#endif
