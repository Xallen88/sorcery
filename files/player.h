#ifndef PLAYER_H
#define PlAYER_H
#include <string>

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
  //adds a card to hand if deck is nonempty and hand is not full
  bool isHandFull();
  void discardCard(int i);
  bool playCard();

  string getName() const;
  int getLife();
  int getMagic();
  //(Minion*)* getMinions()
  //Ritual* getRitual()
}

#endif
