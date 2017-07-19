#ifndef _RITUAL_H_
#define _RITUAL_H_

#include "Card.h"

class Ritual: public Card {
  int charges;
  int chargeCost;
  void DarkRitual();
  void Standstill();
  void AuraOfPower();
  void AuraOfSilence();
 public:
 	Ritual();
 	Ritual(string name);
 	~Ritual();
 	void incrementCharges(int i);
  void Play() override;
  void Play(Card* c) override;
  //if the charges are 0 then activate does nothing
  void Activate() override;
  void Activate(Card *c) override;
};

#endif
