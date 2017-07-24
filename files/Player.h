#ifndef _PLAYER_H_
#define _PlAYER_H_
#include <string>
#include <vector>

using std::vector;
using std::string;

class Card;
class Ritual;
class Minion;
class Enchantment;

class Player 
{
 private:
  string name;
  int life = 20;
  int magic = 3;
  vector<Card*> deck; //deck.back() is top card
  vector<Card*> hand;
  vector<Card*> graveyard;
  vector<Minion*> minions;
  Ritual *ritual=nullptr;
 public:
  Player();
  Player(const string name);
  ~Player();
  void incrementMagic(int i = 1);
  bool decrementMagic(int i = 1);
  void incrementLife(int i = 1);
  void decrementLife(int i = 1);
 
  void drawCard();
  void discardCard(unsigned int i);
  void printHand();

  string getName() const;
  int getLife() const;
  int getMagic() const;
  Minion* getMinion(int m) const;
  Ritual* getRitual() const;
  int numMinions() const;

  void setName(string name);

  void constructDeck(string deckFile);
  void shuffleDeck();
  int handSize();
  Card* topDeck();

  void summonMinion(Minion* minion);
  void unsummonMinion(Minion* minion);
  void setRitual(Ritual* r);
  void toGraveyard(Card* c);
  void toBottomDeck(Card* c);
  bool summonFromGraveyard();
  void damageAllMinions(int i);

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
