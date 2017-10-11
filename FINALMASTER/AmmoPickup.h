#ifndef AMMOPICK_H
#define AMMOPICK_H

#include "Gun.h"

class AmmoPickup//: public Pickup
{
  private:
    int myTag;
    double curx;
    double cury;
  public:
    AmmoPickup();
    AmmoPickup(double, double);
    ~AmmoPickup();
    static void act(Gun&);
};

#endif
