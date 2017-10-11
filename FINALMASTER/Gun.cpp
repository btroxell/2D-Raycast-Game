//Phillip Anderson

#include "Gun.h"

using namespace std;

/*
  Easily overwriteable!
  handles damage and ammo stuff for player.
  doing it like this allows for different guns realatively easily
 */

Gun::Gun()
{
  ammo = 10;
  cooldown = 0;
  damage = 25;
  count = 0;
}//end constructor

Gun::Gun(int cooldown)
{
  ammo = 10;
  Gun::cooldown = cooldown;
  damage = 25;
  count = 0;
}//end constructor

Gun::~Gun()
{

}//end destructor

void Gun::setAmmo(int ammo)
{//updates gun ammo by amount given
  Gun::ammo += ammo;
}

int Gun::getCount()
{//gets current count of cooldown
  return count;
}

void Gun::decCount()
{//reduces count
  count--;
}

void Gun::shoot()
{//decrements ammo and sets cooldown
  ammo--;
  count = cooldown;
}

int Gun::getDamage()
{//sees how much damage the gun does
  return damage;
}
