#ifndef _RITUAL_H_
#define _RITUAL_H_
#include "Card.h"
class Ritual: public Card {
  int charges;
  //bunch of different Ritual functions
 public:
  void Play() override;
  //if the charges are 0 then activate does nothing
  void Activate() override;
  void Activate(Card *c) override;
};

#endif
