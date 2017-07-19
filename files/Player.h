#ifndef PLAYER_H
#define PlAYER_H
#include <string>
#include <vector>
#include "Card.h"
#include "Minion.h"
#include "Ritual.h"

using std::string;
using std::vector;

class Player 
{
 private:
  const string name;
  int life = 20;
  int magic = 3;
  vector<Card*> deck; //deck.back() is top card
  vector<Card*> hand;
  vector<Card*> graveyard;
  Minion *minions[5];
  Ritual *ritual;
 public:
  Player(const string name /*, vector<Card*> deck*/): name(name);
  void incrementMagic(int i = 1);
  bool decrementMagic(int i = 1);
  void incrementLife(int i = 1);
  void decrementLife(int i = 1);
 
  void drawCard();
  //bool isHandFull() const;
  void discardCard(int i);

  string getName() const;
  int getLife() const;
  int getMagic() const;
  Card* getMinion(int m) const;
  Card* getRitual() const;
  int numMinions() const;

  void constructDeck(string deckFile);
  void shuffleDeck();

  void summonMinion(Card* minion);

  void minionAttack(int minion, Player* otherPlayer);
  // direct attack to opponent's life, calls minion's attack function
  void minionAttack(int minion, int otherminion, Player* otherPlayer);
  // gets pointer for attacking and defending minion and then
  // calls minion's attacking function
  void playCard(int i);
  // plays a card, including minions
  void playCard(int i, int targetCard, Player& targetPlayer);
  void useAbility(int minion);
  // uses a minions ability, calls the minions ability function
  void useAbility(int minion, int targetCard, Player& targetPlayer);
}

#endif
