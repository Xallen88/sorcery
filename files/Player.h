#ifndef _PLAYER_H_
#define _PlAYER_H_
#include <string>
#include <vector>
#include "Card.h"
#include "Minion.h"
#include "Enchantments.h"
#include "Ritual.h"
#include "Spell.h"

class Player 
{
 private:
  const string name;
  int life = 20;
  int magic = 3;
  vector<Card*> deck; //deck.back() is top card
  vector<Card*> hand;
  vector<Card*> graveyard;
  vector<Minion*> minions;
  Ritual *ritual;
 public:
  Player(const string name);
  void incrementMagic(int i = 1);
  bool decrementMagic(int i = 1);
  void incrementLife(int i = 1);
  void decrementLife(int i = 1);
 
  void drawCard();
  //bool isHandFull() const;
  void discardCard(unsigned int i);

  string getName() const;
  int getLife() const;
  int getMagic() const;
  Minion* getMinion(int m) const;
  Ritual* getRitual() const;
  int numMinions() const;

  void constructDeck(string deckFile);
  void shuffleDeck();

  void summonMinion(Minion* minion);
  void setRitual(Ritual* r);

  void minionAttack(int minion, Player* otherPlayer);
  // direct attack to opponent's life, calls minion's attack function
  void minionAttack(int minion, int otherminion, Player* otherPlayer);
  // gets pointer for attacking and defending minion and then
  // calls minion's attacking function
  void playCard(unsigned int i);
  // plays a card, including minions
  void playCard(unsigned int i, int targetCard, Player& targetPlayer);
  void useAbility(int minion);
  // uses a minions ability, calls the minions ability function
  void useAbility(int minion, int targetCard, Player& targetPlayer);
};

#endif
