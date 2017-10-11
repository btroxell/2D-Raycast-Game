//Phillip Anderson
//Alex Rutan

#include "Player.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

Player::Player()
{
  HP = 100;
  posX = 50.5;
  posY = 50.5;
  newPosX = 50.5;
  newPosY = 50.5;
  dx = 0;
  dy = 0;
  direction = 0;
  speed = 2;
  cooldown = 10;
  count = 0;
  score = 0;
  dead = false;
  haveGun[0] = true;
  for(int i = 1; i < 6; i++)
  {
      haveGun[i] = false;
  }
  guns[0] = Gun(500);
  equiped = guns[0];
  currentX.resize(25);
  currentY.resize(25);
}

Player::Player(Map * m)
{
    HP = 100;
    Player::m = m;
    posX = m->getInitPlayerX();
    posY = m->getInitPlayerY();
    newPosX = posX;
    newPosY = posY;
    direction = 0;
    speed = 2;
    cooldown = 10;
    count = 0;
    score = 0;
    dead = false;
    haveGun[0] = true;
    for(int i = 1; i < 6; i++)
    {
        haveGun[i] = false;
    }
    guns[0] = Gun(500);
    equiped = guns[0];

    currentX.resize(25);
    currentY.resize(25);
}

Player::~Player()
{
}

void Player::move(int fb) //moves forward in direction
{
    if(fb == 0)
    {
	newPosX = posX - dx*speed;
	newPosY = posY - dy*speed;
	if(!m->isWall(newPosX, newPosY))
	  {
	    posX = newPosX;
	    posY = newPosY;
	  }
    } //end if
    if(fb == 1)
    {
	newPosX = posX + dx*speed;
	newPosY = posY + dy*speed;
	if(!m->isWall(newPosX, newPosY))
	  {
	    posX = newPosX;
	    posY = newPosY;
	  }
    } //end if
} //end move

void Player::rotate(double r)//rotates player
{
    direction = direction + r;

    if(direction > 360)//if angle is too big
    {
	direction = 0;
    } //end if
    if(direction < 0)
    {
	direction = 360;
    } //end if
    dy = sin(M_PI/180 * direction)*1;
    dx = cos(M_PI/180 * direction)*1;
} //end rotate

double Player::getPosX()
{
  return posX;
}

double Player::getPosY()
{
  return posY;
}

double Player::getDir()
{
  return direction;
}

int Player::getScore()
{
  return score;
}

void Player::updateScore(int points)
{
  score += points;
}

void Player::shoot()//shoots gun
{
  if(count == 0)//if cooldown is ready
  {
      cout << "shoot" << endl;//so you know u shot
      bool shot = false;//if you shot an enemy
      int shotEnemy = -1;//index in array of enemies in map
      count = cooldown;//set cooldown again
      equiped.shoot();//decrements ammo of gun
      Raycast caster;

      double dist = 0;
  
      currentX[0] = posX;
      currentY[0] = posY;
      for(int i = 0; i < 100; i++)//cast ray of bullet
      {
          if(m->getTileTag(currentX[0]/25, currentY[0]/25) == 0 && m->getTileTag(currentX[0]/25, currentY[0]/25) != 1)
	  {//if empty and not a wall
	      caster.distanceCalc(currentX[0], currentY[0], dist, direction);
	      currentX[0] = caster.getCurrentX();
	      currentY[0] = caster.getCurrentY();
	      //cout << m->getTileTag(currentX[0]/25, currentY[0]/25) << endl;
	  }
          if(m->getTileTag(currentX[0]/25, currentY[0]/25) == 4)//if hit an enemy
	  {
	      for(int n = 0; n < m->enemies.size(); n++)//figure out which enemy
	      {
		if(m->enemies[n].getTileX() == int(currentX[0]/25) && m->enemies[n].getTileY() == int(currentY[0]/25))//if enemy has been shot
		  {
		    shot = true;
		    shotEnemy = n;
		  }//end if
	      }//end for
	  }//end if
      }//end for

      if(shot)
	{
	  m->enemies[shotEnemy].takeDamage(equiped.getDamage());//damage shot enemy
	}
    } //end if
  }//end shoot

void Player::swapGun(int i)//actual number on key
{
  equiped = guns[i - 1];//not used, but easily implemented
}

void Player::takeDamage(int damage)
{
  HP = HP - damage;
  cout << HP << endl;
  if(HP <= 0)
    {
      dead = true;
    }
}

void Player::update ()
{
    if(count != 0)
    {
        count--;//decrement cooldown
    } //end if
    if(m->getTileTag(posX/25, posY/25) == 2)//if on pickup
    {
        AmmoPickup::act(equiped);//add ammo to clip
	score += 10;
	cout << "Score: " << score << endl;
	m->setTileTag(posX/25, posY/25, 0);//clear tile of pickup
    }
} //end pickUp

bool Player::isDead()//return whether the player is dead or not
{
  return dead;
}

int Player::getTileX()//returns the tile player is on
{
  return posX/25;
}

int Player::getTileY()//returns the tile player is on
{
  return posY/25;
}
