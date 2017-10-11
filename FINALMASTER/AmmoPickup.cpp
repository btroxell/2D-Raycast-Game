//Phillip Anderson

#include "AmmoPickup.h"

/*
This is where the ammo drops are taken care of
 */

AmmoPickup::AmmoPickup()
{
  myTag = 2;//my tag
  curx = 0;//my x
  cury = 0;//my y
}//end constructor

AmmoPickup::AmmoPickup(double x, double y)
{
  myTag = 2;//my tag
  curx = x;//my x
  cury = y;//my y
}//end constructor

AmmoPickup::~AmmoPickup()
{

}//end deconstructor

void AmmoPickup::act(Gun&g)
{//update selected gun's ammo count
  g.setAmmo(10);
}
