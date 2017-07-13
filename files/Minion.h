#ifndef MINION_H
#define MINION_H


Class Minion {
  int atk;
  int def;
 public:
  Minion(int a, int d);
  ~Minion() override;
  void Play() override;
  void Activate() override;
  void Activate(Card *target) override;
};



#endif
