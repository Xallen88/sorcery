#ifndef _RITUAL_H_
#define _RITUAL_H_

#include <vector>
#include <string>
#include "Card.h"

using std::vector;

extern vector<string> ritualList;

class Ritual : public Card {
  int charges;
  int chargeCost;
  void DarkRitual();
  void Standstill(Card* c);
  void AuraOfPower(Card* c);
  void AuraOfSilence(Card* c);
 public:
 	Ritual();
 	Ritual(string name);
 	~Ritual();
 	void incrementCharges(int i);
  int getCharges();
  int getChargeCost();
  void Play() override;
  void Play(Card* c) override;
  //if the charges are 0 then activate does nothing
  void Activate() override;
  void Activate(Card *c) override;
};

#endif
