#ifndef GUN_H
#define GUN_H

class Gun
{
  private:
    int ammo;
    int cooldown;
    int damage;
    int count;
 public:
    Gun();
    Gun(int);
    ~Gun();
    void setAmmo(int);
    void decCount();
    void shoot();
    int getDamage();
    int getCount();
};

#endif
