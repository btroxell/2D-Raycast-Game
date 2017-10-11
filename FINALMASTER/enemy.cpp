//Phillip Anderson

#include "enemy.h"
#include <iostream>

using namespace std;

/*
  This is the enemy class. it has a map and a player.
  it needs the map to tell where to update the tags.
  needs the player so it can attack and move towards the player.
 */

Enemy::Enemy()
{
  HP = 50;//hit points
  AP = 10;//attack points
  dead = false;//am i dead?
  myTag = 4;//i am a 4 in map
  speed = 2;
  score = 50;//points given when slain
  posX = 0;//where am i
  posY = 0;
  tileX = posX /25;
  oldTX = 0;
  oldTY = 0;
  tileY = posY /25;
  caster = Raycast();
  distance = 0;
  currentX = posX;
  currentY = posY;
  ppx = 0;//where is player
  ppy = 0;
  ptx = 0;
  pty = 0;
  cooldown = 15;//cooldown after attack
  countdown = 0;
}//end constructor

Enemy::Enemy(double x, double y)
{
  HP = 50;
  AP = 10;
  dead = false;
  myTag = 4;
  speed = 2;
  score = 50;
  posX = x;
  posY = y;
  tileX = posX/25;
  tileY = posY/25;
  oldTX = 0;
  oldTY = 0;
  caster = Raycast();
  distance = 0;
  currentX = posX;
  currentY = posY;
  ppx = 0;
  ppy = 0;
  ptx = 0;
  pty = 0;
  cooldown = 500;
  countdown = 0;
}//end constructor

Enemy::~Enemy()
{
}//end destructor

void Enemy::updateDest()//always has ray to player
{
  ppx = player->getPosX();
  ppy = player->getPosY();
  ptx = player->getTileX();
  pty = player->getTileY();
}//end updateDest

void Enemy::takeDamage(int damage)//reduces hp by damage amount
{
  cout << "SQUEAK!" << endl;
  HP = HP - damage;
  cout << HP << endl;
  if(HP <= 0)
    {
      whenDead();
    }
}//end takeDamage

void Enemy::attack()//attack player
{
  player->takeDamage(AP);
  countdown = cooldown;
}//end attack

bool Enemy::atDest()
{//checks if i have reached my destination
  bool atDest = false;

  //cout << posX << " myPos  " << posY << endl;
  //cout << ppx << " PlayerPos " << ppy << endl;

  if(posX + 25 >= ppx && posX - 25 <= ppx)//allows a tilewidth is any direction
    {
      //cout << "x good" << endl;
      //cout << posX << "  " << ptx << endl;
      if(posY + 25 >= ppy && posY - 25 <= ppy)
	{
	  atDest = true;
	  //cout << "at Dest" << endl;
	}
    }

  return atDest;
}//end atDest

void Enemy::move()//how i move
{
  //cout << "move" << endl;
  double rise = posY - ppy;//x change to player
  double run = posX - ppx;//y change to player

  //cout << posX << "  " << posY << endl;
  //cout << ptx << "  " << pty << endl;

  double dir = atan2(rise, run);// angle to player
  dir = dir * 180/M_PI;
  if(dir < 0)
    {
      dir += 360;
    }
  if(dir > 0)
    {
      dir -= 360;
    }
  dir = dir * M_PI/180;
  
  //cout << dir << endl;
  if(!dead)// if im not dead
    {
      if(!blocked(posX, posY, ppx, ppy))//if my path is not blocked
	{
	  //cout << "not blocked" << endl;
	  if(!atDest())//if i am not at my destination
	    { 
	      double dx = speed * cos(dir);//how much to move in the x dir
	      double dy = speed * sin(dir);//how much to move in the y dir

	      //cout << tileX << " before " << tileY << endl;
	      oldTX = tileX;//previous tile
	      oldTY = tileY;
  
	      posX = posX - dx;//change position
	      posY = posY - dy;

	      tileX = posX / 25;//update tile
	      tileY = posY / 25;
	  
	      //cout << oldTX << " old " << oldTY << endl;
	      //cout << tileX << " new " << tileY << endl;
	      m->setTileTag(tileX, tileY, 4);//set new tile to my tag
	      if(tileX != oldTX || tileY != oldTY)
		{
		  m->setTileTag(oldTX, oldTY, 0);//reset old tile tag
		}
	    }//end if
	  else //if i am at my destination
	    {
	      //cout << "attack" << endl;
	      attack();
	    }//end at dest check
	}//end blocked check
    }//end dead check
  //cout << posX << "  " << posY << endl;
}//end move

bool Enemy::blocked(double curx, double cury, double destx, double desty)
{//checks if my path to the player is blocked
    bool blocked = false;

    //get angle to destination
    double run = destx - curx;
    double rise = desty - cury;
    double theta = atan2(rise, run);
    theta = theta * (180/M_PI);

    if(theta < 360)
      {
	theta += 360;
      }
    if(theta > 360)
      {
	theta -= 360;
      }
    //cout << theta << endl;

    for(int i = 1; i < 10; i++)//allow view of 10 steps
    {
      if(!blocked)// if we have been blocked, stop casting
	{
	  caster.distanceCalc(currentX, currentY, distance, theta);//get distance to first tile

	  distance = caster.getCurrentDistance();

	  double checkx = caster.getCurrentX();//distance in x direction
	  double checky = caster.getCurrentY();//distance in y direction

	  currentX = checkx;
	  currentY = checky;
	
	  //cout << currentX << " curxy  " << currentY << endl;
	  int tilex = m->getTileX(int(currentX));
	  int tiley = m->getTileY(int(currentY));
	  //cout << tilex << " checked tile " << tiley << endl;

	  if(m->getTileTag(tilex, tiley) == 1)//if ray has hit a wall
	    {
	      //cout << "blocked" << endl;
	      blocked = true;
	    }//end wall check
	}//end blocked check
    }//end for
    currentX = posX;//reset starting point for checker
    currentY = posY;
    return blocked;
}//end blocked

int Enemy::getScore()
{//returns how many points i am worth
  return score;
}

int Enemy::getTileX()
{//return info about my tile
  return tileX;
}

int Enemy::getTileY()
{//returns info about my tile
  return tileY;
}

double Enemy::getPosX()
{//returns my position
  return posX;
}

double Enemy::getPosY()
{//returns my position
  return posY;
}

void Enemy::setMap(Map * map)
{//set map to avoid circular dependancy of map needing to know where enemies are
  m = map;
}

void Enemy::whenDead()
{//upon death, do this stuff
  //My Will
  dead = true;
  m->setTileTag(tileX, tileY, 0);
  m->setTileTag(tileX, tileY, 2);
  posX = -500;
  posY = -500;
  player->updateScore(score);
  cout << "Score: " << player->getScore() << endl;
  //Undersigned, Squeakers the Rat
}

void Enemy::setPlayer(Player * p)
{//sets the person i will be attacking
  player = p;
}

double Enemy::getDistToPlayer()
{//calculates distance to player
  //cout << distance << endl;
  double rise = player->getPosX() - posX;
  double run = player->getPosY() - posY;
  distance = sqrt((rise * rise) + (run * run));
  return distance;
}

bool Enemy::isDead()
{//am i dead yet?
  return dead;
}
