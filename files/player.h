#ifndef PLAYER_H
#define PlAYER_H
#include <string>
#include "card.h"

using std::string;

class Player 
{
 private:
  const string name;
  int life = 20;
  int magic = 3;
  //vector<Card*> deck
  //vector<Card*> hand
  //Minion *minions[5]
  //vector<Card*> graveyard
  //Ritual ritual
 public:
  Player(const string name /*, vector<Card*> deck*/): name(name);
  void incrementMagic(int i = 1);
  bool decrementMagic(int i = 1);
  void incrementLife(int i = 1);
  void decrementLife(int i = 1);
  void drawCard();
  // adds a card to hand if deck is nonempty and hand is not full
  bool isHandFull() const;
  void discardCard(int i);

  string getName() const;
  int getLife() const;
  int getMagic() const;
  Card* getMinion(int m) const;
  Card* getRitual() const;

  void minionAttack(int minion, Player* otherPlayer);
  // direct attack to opponent's life, calls minion's attack function
  void minionAttack(int minion, int otherminion, Player* otherPlayer);
  // gets pointer for attacking and defending minion and then
  // calls minion's attacking function
  void playCard(int card);
  // plays a card, including minions
  void playCard(int card, int targetPlayer, int targetCard);
  void useAbility(int minion);
  // uses a minions ability, calls the minions ability function
  void useAbility(int minion, int targetPlayer, int targetCard);
}

#endif
