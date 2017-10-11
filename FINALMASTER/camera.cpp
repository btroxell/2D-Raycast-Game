// camera.cpp
// Alex Rutan
// Phil Anderson
// 3/31/15

#include <iostream>
#include <cmath>
#include <vector>
#include "map.h"
#include "raycast.h"
#include "camera.h"

//??#define double stepCap = 40

using namespace std;

/*
Camera constructor is called with parameters for parent position and direction (in this case player's)
Raycount for the number of rays to be cast, the Y resolution of the screen, and a pointer to the map
Initializes all of our vectors for ray draw information
 */
Camera::Camera(double parPosX, double parPosY, double parDir, int rc, int resY, Map* m)
{
    map = m;
    posX = parPosX;
    posY = parPosY;
    dx = 0;
    dy = 0;
    direction = parDir;
    raycount = rc;
    Raycast rays;
    rayDists.resize(rc);
    rayHitX.resize(rc);
    rayHitY.resize(rc);
    currentX.resize(rc);
    currentY.resize(rc);
    xRaysY1.resize(rc);
    xRaysY2.resize(rc);
    yRaysY1.resize(rc);
    yRaysY2.resize(rc);
    solid.resize(rc);
    solidRayDists.resize(rc);
    EnemyY1.resize(rc);
    EnemyY2.resize(rc);
    PickupY1.resize(rc);
    PickupY2.resize(rc);
    GunPickupY1.resize(rc);
    GunPickupY2.resize(rc);
    step = 0;
    startDraw = 0;
    endDraw = 0;
    screenHeight = resY;
    wallHeightTheta = atan2((screenHeight / 2) , 200); // 200 is max dist to wall
} //end constructor

Camera::~Camera()
{
} //end destructor

/*
Grabs the current location of camera
NO LONGER USED
 */
double Camera::getLoc(char axis)
{
    if(axis == 'x')
    {
        return posX;
    } //end if
    if(axis == 'y')
    {
	return posY;
    } //end if
    if(axis == 'z')
    {
	return dx;
    } //end if
    if(axis == 'w')
    {
	return dy;
    } //end if
} //end getLoc

/*
Updates the current direction, location with the parent direction and location
 */
void Camera::update(double parPosX, double parPosY, double parDir)
{
    posX = parPosX;
    posY = parPosY;
    direction = parDir;
} //end update

/*
This is where the camera casts each of the rays, sees what type of object they hit -- if any -- and gives us our distance to the object in question
It then calculates the highest and lowest Y pixel to draw on the screen, these two values are then connected by SDL in the drawing section of our main loop
 */
void Camera::castRay()
{
    int i;
    //Direction is the way we're facing, we want to start our casting at the furthest left ray
    int castDir = direction - 45;

    //Make sure our direction stays within the 360 degree range
    if(castDir < 0)
    {
	castDir += 360;
    } //end if
    //cout << direction << endl;
    
    if(castDir > 360)
    {
	castDir -= 360;
    } //end if

    //Only go out 200 steps, each step jumps from one edge of a tile to the next
    if(step == 200)
    {
	step = 0;
    } //end if
    
    //cout << castDir << endl;

    //Do this 90 times, one for each ray
    for(i = 0; i < raycount; i++)
    {
      //cout << "start of for" << endl;
        //If we're on our first step, everything should start at the location of camera, and nothing should be hit
	if(step == 0)
	{
	    rayDists[i] = 0;
	    currentX[i] = posX;
	    currentY[i] = posY;
	    rayHitX[i] = false;
	    rayHitY[i] = false;
	    solid[i] = 0;
	    solidRayDists[i] = 0;
	} //end if
	else{

	    //if a ray has not hit a solid wall on either axis, jump to the next side and record it's current distance and location 
	    if(!(rayHitX[i] || rayHitY[i]))
	    {
	        rays.distanceCalc(currentX[i], currentY[i], rayDists[i], castDir + i); //turn back into x and y?
		rayDists[i] = rays.getCurrentDistance();
		currentX[i] = rays.getCurrentX();
		currentY[i] = rays.getCurrentY();
	    } //end if

	} //end else
	
        int side = rays.xOrYSide();//returns whats side of the tile was hit
	if(side == 0)// if no tile was hit
	    {
		rayHitX[i] = false;
		rayHitY[i] = false;
	    } //end if
	    else if(side == 1)//hit left side
	    {
	      if(map->isWall(currentX[i], currentY[i]))// if we hit a wall on the x side
		{
		  rayHitX[i] = true;//update that x was hit
		}
	      else if(map->isSolid(currentX[i], currentY[i]))//if we hit something other than a wall
		{//these aren't really dependent on what side of the tile they got hit from,
		  //but it does need to be coupled with the wall check
		  solid[i] = map->getTileTag(currentX[i] / 25, currentY[i] / 25);
		  solidRayDists[i] = rays.getCurrentDistance();
		}
	    } //end elseif
	    else if(side == 2)//hit right side
	    {
	      if(map->isWall(currentX[i] - 1, currentY[i]))//the other x side
		{
		  rayHitX[i] = true;
		}
	      else if(map->isSolid(currentX[i], currentY[i]))
		{
		    //cout << currentX[i] << "  " << currentY[i] << endl;
		  solid[i] = map->getTileTag(currentX[i] / 25, currentY[i] / 25);
		  solidRayDists[i] = rays.getCurrentDistance();
		}
	    } //end elseif
	    else if(side == -1)//hit bottom
	      {
		if(map->isWall(currentX[i], currentY[i]))// hit y side
		  {
		    rayHitY[i] = true;//update that y has been hit
		  }
		else if(map->isSolid(currentX[i], currentY[i]))
		{
		  solid[i] = map->getTileTag(currentX[i] / 25, currentY[i] / 25);
		  solidRayDists[i] = rays.getCurrentDistance();
		}
	      }
	    else if(side == -2)// hit top
	    {
	      if(map->isWall(currentX[i], currentY[i] - 1))// another y check
		{
		      rayHitY[i] = true;
		}
		else if(map->isSolid(currentX[i], currentY[i]))
		{
		    solid[i] = map->getTileTag(currentX[i] / 25, currentY[i] / 25);
		    solidRayDists[i] = rays.getCurrentDistance();
		}
	    }
	    //cout << solid[i] << endl;
    } //end for
    for(i = 0; i < raycount; i++)
    {
      //cout << solid[i] << endl;
      //cout << "i in next for " << i << endl;
        if(rayHitX[i])//if an x wall was hit
	{
	    xRaysY1[i] = 120 - ((200 - rayDists[i]) * tan(wallHeightTheta)); //top half of screen - height to make y
	    xRaysY2[i] = screenHeight - xRaysY1[i];
	} //end if
        else if(rayHitY[i])//if a y wall was hit
	{
	    yRaysY1[i] = 120 - ((200 - rayDists[i]) * tan(wallHeightTheta));
	    //cout << rayDists[i]<< endl;
	    yRaysY2[i] = screenHeight - yRaysY1[i];
	} //end elseif
	else if(solid[i] == 2)//if an ammo Pickup was hit
	{
	      //cout << "before" << endl;
	      PickupY1[i] = 120 - ((solidRayDists[i]) * tan(wallHeightTheta));
	      PickupY2[i] = screenHeight - PickupY1[i];
	      //PickupY1[i] = 100 - solidRayDists[i]//reusing pickupy1 for distance
	      //cout << "pickup seen" << endl;
	}
	else if(solid[i] == 3)//extra, for another pickup. would need new tag
	{
	      GunPickupY1[i] = 120 - ((200 - solidRayDists[i]) * tan(wallHeightTheta));
	      GunPickupY2[i] = screenHeight - GunPickupY1[i];
	}
	else if(solid[i] == 4)//if an enemy was hit
	{
	  //cout << "found Enemy" << endl;
	  for(int n = 0; n < map->enemies.size(); n++)
	    {
	      //figure out which enemy was hit
	      if(map->enemies[n].getTileX() == int(currentX[i]/25) && map->enemies[n].getTileY() == int(currentY[i]/25))
		{
		  //cout << "correct Enemy" << endl;
		  EnemyY1[i] = 120 - (map->enemies[n].getDistToPlayer() * tan(wallHeightTheta));
		  EnemyY2[i] = screenHeight - EnemyY1[i];
		  //cout << "enemy " << endl;
		}//end if
	    }//end for
	}
        else{
	  //set everything to not be drawn
	    xRaysY1[i] = 0;
	    xRaysY2[i] = 0;
	    yRaysY1[i] = 0;
	    yRaysY2[i] = 0;
	    PickupY1[i] = 0;
	    PickupY2[i] = 0;
	    GunPickupY1[i] = 0;
	    GunPickupY2[i] = 0;
	    EnemyY1[i] = 0;
	    EnemyY2[i] = 0;
	} //end else
    } //end for
} //end castRay
