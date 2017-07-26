#include <string>
#include "Minion.h"
#include "Enchantments.h"
#include "Player.h"
#include "Sorcery.h"
#include "Card.h"
#include "Sorcery.h"
#include <sstream>
#include <fstream>

using namespace std;

vector<string> minionList={"Air Elemental", "Earth Elemental", "Fire Elemental", "Potion Seller", "Novice Pyromancer", "Apprentice Summoner", "Master Summoner", "Wild Pyromancer"};

Minion::Minion(){}
Minion::Minion(string name) : Card (name){
  type = "Minion";
  numEnch=0;
  stringstream ss;
  string line;
  string fileName = name;
  actions = 1;
  silenced = false;
  activeEnch=nullptr;

  int len = fileName.length();
  for (int i = 0; i < len; ++i) {
    if (fileName[i] == ' ') {
      fileName.erase(fileName.begin()+i);
      --i;
      --len;
    }
  }

  if(activePlayer==&playerOne){
    owner=1;
  }else{
    owner=2;
  }

  fileName = "minions/" + fileName + ".info";
  ifstream infoFile (fileName);
  getline(infoFile, line);
  ss.str(line);
  //Adding cost, atk, hp
  ss >> cost;
  ss >> curAtk;
  ss >> curHp;
  maxHp = curHp;
  maxAtk = curAtk;
  //Determining if any active/triggered ability
  ss >> trigger;
  triggerType = trigger;
  //5 signifying a activateable ability reads the cost of activation
  if (trigger == 5) { 
    ss >> aCost;  
  }
  //if (trigger == 0) return;//no trigger thus no desc
  getline(ss, description);	
  infoFile.close();
  // feed remaining line into description
}
Minion::~Minion(){
  for(unsigned int i = 0; i < enchantments.size(); ++i){
    delete enchantments[i];
  }
}

void Minion::applyChange(char op, char c, int val) {
  if (c == 'a') {
    //doing attack stats
    if (op == '*') {
      maxAtk *= val;
      curAtk *= val;
    } else if (op == '+') {
      maxAtk += val;
      curAtk += val;
    } else if (op == '-') {
      maxAtk -= val;
      curAtk -= val;
    } else if (op == '/') {
      maxAtk /= val;
      curAtk /= val;
    }
  } else {//c is equal to h
    //doing defence stats
    if (op == '*') {
      maxHp *= val;
      curHp *= val;
    } else if (op == '+') {
      maxHp += val;
      curHp += val;
    } else if (op == '-') {
      maxHp -= val;
      curHp -= val;
    } else if (op == '/') {
      maxHp /= val;
      curHp /= val;
    }
  }
}
void Minion::Attack(Player *p) {
  if (hasActionLeft()) {
    useAction();
    p->decrementLife(curAtk);
  } else printError("Minion has already used an action for this turn");
}
void Minion::Attack(Minion *m) {
  if (hasActionLeft()) {
    useAction();
    m->decrementLife(curAtk); 
    decrementLife(m->getAtk());
  } else printError("Minion has already used an action for this turn");
}
void Minion::incrementAtk(int i) {
  curAtk += i;
  maxAtk += i;
}

void Minion::decrementAtk(int i) {
  curAtk -= i;
  maxAtk -= i;
}
void Minion::decrementLife(int i) { 
  curHp -= i;
  if (isDead()) {
    clearAllEnchants();
    //Check who the minion belongs to and send to respective graveyard
    if (owner == 1) {
      playerOne.unsummonMinion(this);
      playerOne.toGraveyard(this);
    } else {//Player2
      playerTwo.unsummonMinion(this);
      playerTwo.toGraveyard(this);
    }
  }	
}
void Minion::incrementLife(int i) {
 applyChange('+', 'h', i);
}
bool Minion::isDead() {
 return curHp <= 0;
}
void Minion::addEnchant(Enchantment *e) {//Supports * and + on attack and *, +, - on hp
  //remove from vector
  enchantments.emplace_back(e);
  numEnch++;
  if(e->getEnchType()==3){
    activeEnch=e;
    return;
  }else if(e->getEnchType()==2){
    Silence();
  }else{
    //Add the stats in from enchantments
    applyChange(e->getAOp(), 'a', e->getAVal());
    applyChange(e->getHOp(), 'h', e->getHVal());
  }
  
}
void Minion::removeTopEnch() {
  Enchantment *e = enchantments.back();
  numEnch -= 1;

  if(e->getEnchType()==3){ //activated abilities
    activeEnch = nullptr;
    return;
  }else if(e->getEnchType()==2){ //silence
    UnSilence();
    for (int k = 0; k < numEnch; k++) {
      Card *crd = (Card *) enchantments[k];
      if (crd->getName() == "Silence") Silence();
    }
  }
  else{
    //Take away stats from enchantment
    // for atk stats
    int aOp = e->getAOp();
    int hOp = e->getHOp();
    if (aOp == '*') {
      applyChange('/', 'a', e->getAVal());
    } else if (aOp == '/') {
      applyChange('*', 'a', e->getAVal());
    } else if (aOp == '+') {
      applyChange('-', 'a', e->getAVal());
    } else {//the subtract case
      applyChange('+', 'a', e->getAVal());
    }
    //For hp stats
    if (hOp == '*') {
      applyChange('/', 'h', e->getHVal());
    } else if (hOp == '/') {
      applyChange('*', 'h', e->getHVal());
    } else if (hOp == '+') {
      applyChange('-', 'h', e->getHVal());
    } else {//the subtract case
      applyChange('+', 'h', e->getHVal());
    }
  }
  if(e->getOwner()==1) playerOne.toGraveyard(e);
  else playerTwo.toGraveyard(e);
  enchantments.pop_back();
}
bool Minion::hasActiveEnch(){
  if(activeEnch){
    return true;
  }return false;
}
void Minion::clearAllEnchants() {
 //popping enchantment
  for (int k = numEnch; k > 0; --k){
    removeTopEnch();
  }
}

int Minion::getHp() { return curHp; }
int Minion::getAtk() { return curAtk; }
int Minion::getACost() { return aCost; }
int Minion::getEnchNum() { return numEnch; }
Enchantment* Minion::getEnch(int n) {
  if (n > numEnch-1) return nullptr;
  return enchantments[n];
}
void Minion::Play(){ activePlayer->summonMinion(this); }

void Minion::Play(Card* c){
 //Nothing
}

void Minion::resetActions() { actions = 1; }
bool Minion::hasActionLeft() { return actions == 1; }
void Minion::useAction() { actions--; }
void Minion::FireElemental(Card *c) {
	if(c->getOwner() != owner){
        	Minion* minionPtr = (Minion*) c;
		minionPtr->decrementLife(1);
	}
}
void Minion::PotionSeller() {
  if((activePlayer == &playerOne && owner == 1) || (activePlayer == &playerTwo && owner == 2)){
    int m = activePlayer->numMinions();
    for (int k = 1; k <= m; k++) {
      Minion *m = activePlayer->getMinion(k);
      m->applyChange('+', 'h', 1);
    }
  }
}
void Minion::NovicePyromancer(Card *c) {
  if (c->getType() != "Minion") return;
  Minion *m = (Minion*) c;
  m->decrementLife(1);
}
void Minion::ApprenticeSummoner() {
  int num = activePlayer->numMinions();
  if (num == 5) return;
  Minion *m = new Minion("Air Elemental");
  activePlayer->summonMinion(m);
}
void Minion::MasterSummoner() {
  int num = activePlayer->numMinions();
  if (num < 5) {
    for (int k = num; k < num+3 && k < 5; k++) {
      Minion *m = new Minion("Air Elemental");
      activePlayer->summonMinion(m);
    }
  }
}
void Minion::WildPyromancer(){
  activePlayer->damageAllMinions(1);
  nonActivePlayer->damageAllMinions(1);
}
void Minion::Silence() { silenced = true; }
void Minion::UnSilence() { silenced = false; }
void Minion::Activate(){
  if (silenced) {
    printError("Minion is silenced, cannot use ability");
    return;
  }
  if(!triggerCard){
    if (!hasActionLeft()) {
        printError("Minion has already used an action for this turn");
        return;
    }
    if(activeEnch){
      if(!activeEnch->requiresTarget()) {
        activeEnch->Activate();
        useAction();
      }
      else printError("This ability requires a target");
      return;
    }

    if(name=="Apprentice Summoner"||name=="Master Summoner"){
      //Check if active player has enough to activate
      if (!activePlayer->decrementMagic(aCost)) {
        printError("Insufficient magic to cast ability");
        return;
      }    
      //Now charge for activation
      useAction();
    }
  }
  if (name == "Potion Seller") PotionSeller();
  else if (name == "Apprentice Summoner") ApprenticeSummoner();
  else if (name == "Master Summoner") MasterSummoner();
  else return;  
}

void Minion::Activate(Card* c){
  if (silenced) {
    printError("Minion is silenced, cannot use ability");
    return;
  }

  if(!triggerCard){
    if (!hasActionLeft()) {
        printError("Minion has already used an action for this turn");
        return;
    }
    if(activeEnch){
      if(activeEnch->requiresTarget()) {
        activeEnch->Activate();
        useAction();
      }
      else printError("This ability does not require a target");
      return;
    }

    if(name=="Novice Pyromancer"){
      //Check if active player has enough to activate (if non-trigger ability)
      if (!activePlayer->decrementMagic()) {
        printError("Insufficient magic to cast ability");
        return;
      }    
      //Now charge for activation
      useAction();
    }  
  }

  if (name == "Novice Pyromancer") NovicePyromancer(c);
  else if (name == "Fire Elemental") FireElemental(c);
  else if (name == "Wild Pyromancer") WildPyromancer();
  else return;  
}

