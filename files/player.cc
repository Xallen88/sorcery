#include <string>
#include "player.h"

using std::string;

class Player { 

const string name;
int life;
int magic;

void Player::incrementMagic(int i)
{
 magic += i;
}

bool Player::decrementMagic(int i)
{
 if (magic < i) 
  return false;
 magic -= i;
 return true;
}

void Player::incrementLife(int i)
{
 life += i;
}

void Player::decrementMagic(int i)
{
 if (life > i)
  life -= i;
 else{
  end(getOtherPlayer(this));
 }
}
