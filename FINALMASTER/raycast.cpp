// Phillip Anderson
// raycast.cpp
// 4/10/15
#include "raycast.h"
#include "map.h"
#include "game.h"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

Raycast::Raycast()
{
    tilewidth = 1.0;
    currentx = 0.0;
    currenty = 0.0;
    myTheta = 0.0;
    distance = 0.0;
    side = 0;
}

Raycast::~Raycast()
{
}

void Raycast::distanceCalc(double x, double y, double dist, double direction)//written so it will find the next square once each "game" loop
{//Phillip Anderson
    //Theta needs to be from x clockwise
    double curx = x;//starting x pos
    double cury = y;//starting y pos
    if(direction > 360)
    {
        direction -= 360;
    }
    double theta = direction;//starting direction in degrees
    myTheta = direction;//set my field to direction
    //cout << theta << endl;
    //cout << myTheta << endl;

    side = 0;//side to tell wether exits x or y side

    double sidex = 0.0;//var used to find side of tile to check against
    double sidey = 0.0;

    double toSidex = 0.0;//change in pos after iteration
    double toSidey = 0.0;

    double distance = 0.0;//distance to return

    //double theta = inTheta;//If we change to per pixel instead of degrees, change in theta to double
    int quad = determineQuad(theta);
    theta = theta * (M_PI/180.0);//change theta to radians to use trig functions
    //double mathTheta = atan(theta);//get reference angle
    //cout << theta << endl;
    //cout << mathTheta << endl;
    double checkTheta;

    //int quad = determineQuad(theta);//figure our which quad theta is in
    //cout << quad << endl;

    if(quad == 1)//check against bottom right corner
    {
        sidex = ceil(curx);//gets x side of tile
        if(sidex == curx)//if on side of tile
        {
            toSidex = tilewidth;//increment by tilewidth
        }
        else
        {
            toSidex = sidex - curx;//gets distance between current spot and side of tile
	    //positive
        }
        sidey = ceil(cury);//gets y side of tile
        if(sidey == cury)//if on bottom of tile
        {
            toSidey = tilewidth;//increment by tilewidth
        }
        else
        {
            toSidey = sidey - cury;//gets distance between current spot and top of tile
	    //positive
        }
        checkTheta = atan2(toSidey, toSidex);//theta to corner of tile
        //cout << checkTheta << endl;

        //check if angle is above or below corner
        if(checkTheta >= theta)//right side or bottom right corner
        {
            distance = abs(toSidex / cos(theta));//distance is hypotonuse of triangle
	    //abs of pos / pos
            toSidey = distance * sin(theta);//y is side of triangle that does not reach either side of tile
	    //pos * pos
            side = 1;
        }
        else if(checkTheta < theta)//bottom
        {
            distance = abs(toSidey / sin(theta));
	    //abs of pos / pos
            toSidex = distance * cos(theta);
	    //pos * pos
            side = -1;
        }
    }
    else if(quad == 2)//check against bottom left corner
    {
        sidex = floor(curx);
        if(sidex == curx)
        {
            toSidex = (-tilewidth);
        }
        else
        {
            toSidex = sidex - curx;//gets distance between current spot and side of tile
	    //negative
        }

        sidey = ceil(cury);
        if(sidey == cury)
        {
            toSidey = tilewidth;
        }
        else
        {
            toSidey = sidey - cury;//gets distance between current spot and top of tile
	    //positive
        }
        checkTheta = atan2(toSidey, toSidex);
        //cout << checkTheta << endl;

        if(checkTheta >= theta)//bottom or bottom left corner
        {
            distance = abs(toSidey / sin(theta));
	    //abs of pos / pos
            toSidex = distance * cos(theta);
	    //pos * neg
            side = -1;
        }
        else if(checkTheta < theta)//left side
        {
            distance = abs(toSidex / cos(theta));
	    //abs of neg / neg
            toSidey = distance * sin(theta);
	    //pos * pos
            side = 2;
        }
    }
    else if(quad == 3)//check against top left corner
    {
        sidex = floor(curx);
        if(sidex == curx)
        {
            toSidex = (-tilewidth);
        }
        else
        {
            toSidex = sidex - curx;//gets distance between current spot and side of tile
	    //negative
        }

        sidey = floor(cury);
        if(sidey == cury)
        {
            toSidey = (-tilewidth);
        }
        else
        {
            toSidey = sidey - cury;//gets distance between current spot and top of tile
	    //negative
        }
        checkTheta = atan2(toSidey, toSidex);
        checkTheta += 2 * M_PI;
	//cout << checkTheta << endl;

        if(checkTheta >= theta)//left side or top left corner
        {
            distance = abs(toSidex / cos(theta));
	    //abs of neg / neg
            toSidey = distance * sin(theta);
	    //pos * neg
            side = 2;
        }
        else if(checkTheta < theta)//top
        {
            distance = abs(toSidey / sin(theta));
	    //abs of neg / neg
            toSidex = distance * cos(theta);
	    //pos * neg
            side = -2;
        }
    }
    else if(quad == 4)//check against top right corner
    {
        sidex = ceil(curx);
        if(sidex == curx)
        {
            toSidex = tilewidth;
        }
        else
        {
            toSidex = sidex - curx;//gets distance between current spot and side of tile
	    //pos
        }

        sidey = floor(cury);
        if(sidey == cury)
        {
            toSidey = (-tilewidth);
        }
        else
        {
            toSidey = sidey - cury;//gets distance between current spot and top of tile
	    //neg
        }

        checkTheta = atan2(toSidey, toSidex);
	checkTheta += 2*M_PI;
        //cout << checkTheta << endl;

        if(checkTheta >= theta)//top or top right corner
        {
            distance = abs(toSidey / sin(theta));
	    //abs of neg / neg
            toSidex = distance * cos(theta);
            //pos * pos

	    side = -2;
        }
        else if(checkTheta < theta)//right side
        {
	  distance = abs(toSidex / cos(theta));
            //abs of pos / pos
	    toSidey = distance * sin(theta);
            //pos * neg
	    side = 1;
        }
    }
    else if(quad == -1)//if 90 (pointing down)
    {
        sidey = ceil(cury);
        if(sidey != cury)
        {
            distance = sidey - cury;
            toSidey = sidey - cury;
            toSidex = 0.0;
        }
        else
        {
            distance = tilewidth;
            toSidey = tilewidth;
            toSidex = 0.0;
        }
        side = -1;
    }
    else if(quad == -2)//if 180 (pointing left)
    {
        sidex = floor(curx);
        if(sidex != curx)
        {
            distance = abs(sidex - curx);
            toSidex = (sidex - curx);
            toSidey = 0.0;
        }
        else
        {
            distance = tilewidth;
            toSidex = (-tilewidth);
            toSidey = 0.0;
        }
        side = 1;
    }
    else if(quad == -3)//if 270 (pointing up)
    {
        sidey = floor(cury);
        if(sidey != cury)
        {
            distance = abs(sidey - cury);
            toSidey = sidey - cury;
            toSidex = 0.0;
        }
        else
        {
            distance = tilewidth;
            toSidey = (-tilewidth);
            toSidex = 0.0;
        }
        side = -1;
    }
    else if(quad == 0)//if 0 or 360 (pointing right)
    {
        sidex = ceil(curx);
        if(sidex != curx)
        {
            distance = sidex - curx;
            toSidex = sidex - curx;
            toSidey = 0.0;
        }
        else
        {
            distance = tilewidth;
            toSidex = tilewidth;
            toSidey = 0.0;
        }
        side = 1;
    }

    currentx = curx + toSidex;
    currenty = cury + toSidey;
    Raycast::distance = (distance + dist);//calculated distance + current distance

}//end distanceToObject

int Raycast::determineQuad(double theta)//determines quadrent of angle. EXTRENIOUS??
{//Phillip Anderson
    //cout << theta << endl;
    //theta = theta * (180 / M_PI);
    //cout << theta << endl;
    if(theta == 0)
    {
        return 0;
    }
    else if(theta == 90)
    {
        return -1;
    }
    else if(theta == 180)
    {
        return -2;
    }
    else if(theta == 270)
    {
        return -3;
    }
    else if(theta == 360)
    {
        return 0;
    }
    else if(theta > 360)
    {
        theta -= 360;
        determineQuad(theta);
    }
    if(theta < 90)
    {
        return 1;
    }
    else if(theta < 180)
    {
        return 2;
    }
    else if(theta < 270)
    {
        return 3;
    }
    else if(theta < 360)
    {
        return 4;
    }
    else if(theta < 0)
    {
        theta += 360;
        determineQuad(theta);
    }
}//end determine quad

int Raycast::xOrYSide()//checks which side of tile the ray has hit
{//Phillip Anderson. to be used in conjunction with distcalc.
    //returns 1 if hits left or right side.
    //returns -1 if hits top or bottom side.
    //returns 0 if no wall hit

  // cout << side << endl;
    return side;

}//end xoryside checker

void Raycast::setCurrentX(double x)
{
    currentx = x;
}

void Raycast::setCurrentY(double y)
{
    currenty = y;
}

void Raycast::setCurrentTheta(double theta)
{//my theta in dist calc is in degrees
    myTheta = theta;
}

double Raycast::getCurrentX()
{
    return currentx;
}

double Raycast::getCurrentY()
{
    return currenty;
}

double Raycast::getCurrentTheta()
{//in degrees
    return myTheta;
}

double Raycast::getCurrentDistance()
{
  return distance;
}
