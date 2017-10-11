#ifndef PLAYER_H
#define PLAYER_H

#include "Gun.h"
#include "map.h"
#include "raycast.h"
#include "AmmoPickup.h"

class Map;
class Player
{
  private:
    int HP;
    bool dead;
    double posX;
    double posY;
    double newPosX;
    double newPosY;
    double dx;
    double dy;
    double direction;
    int cooldown;
    int count;
    int speed;
    int score;
    std::vector<double>currentX;
    std::vector<double>currentY;
    bool haveGun[6];
    Gun equiped;
    Gun guns[6];
    Map * m;

  public:
    Player();
    Player(Map*);
    ~Player();
    double getPosX();
    double getPosY();
    double getDir();
    int getScore();
    void move(int);
    void rotate(double);
    void updateScore(int);
    void shoot();
    void takeDamage(int);
    void swapGun(int);
    void update();
    bool isDead();
    int getTileX();
    int getTileY();
};

#endif
