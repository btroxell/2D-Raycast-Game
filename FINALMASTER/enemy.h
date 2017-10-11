#ifndef ENEMY_H
#define ENEMY_H

#include "raycast.h"
#include "map.h"
#include "Player.h"
#include <cmath>

class Map;
class Player;
class Enemy
{
  private:
    int HP;
    int AP;
    bool dead;
    int myTag;
    int score;
    int speed;
    double posX;
    double posY;
    //int playerTile;
    Map* m;
    Player* player;
    double distance;
    double currentX;
    double currentY;
    int tileX;
    int tileY;
    int oldTX;
    int oldTY;
    double ppx;
    double ppy;
    int ptx;
    int pty;
    double dx;
    double dy;
    int cooldown;
    int countdown;
    Raycast caster;
  public:
    Enemy();
    Enemy(double, double);
    ~Enemy();
    void updateDest();
    void takeDamage(int);
    void attack();
    bool blocked(double, double, double, double);
    void move();
    bool atDest();
    int getScore();
    int getTileX();
    int getTileY();
    double getPosX();
    double getPosY();
    void setMap(Map*);
    void whenDead();
    void setPlayer(Player*);
    double getDistToPlayer();
    bool isDead();
};

#endif
