//NO LONGER USED
//MOVE ALONG, NOTHING TO SEE HERE
//Phillip Anderson

#include "MovementEngine.h"

using namespace std;

MovementEngine::MovementEngine()
{
    blockedx = 0.0;
    blockedy = 0.0;
    direction = 0.0;
    aix.resize(10);
    aiy.resize(10);
    path.resize(10);
    oldWall = 0;
}//end const

MovementEngine::MovementEngine(Map & m)
{
    blockedx = 0.0;
    blockedy = 0.0;
    direction = 0.0;
    aix.resize(10);
    aiy.resize(10);
    path.resize(10);
    oldWall = 0;
    MovementEngine::m = m;
}//end const

MovementEngine::~MovementEngine()
{
}//end dest

bool MovementEngine::atDest(double destx, double desty, double curx, double cury)//checks if at destination
{
    bool movePls = true;
    if(curx == destx && cury == desty)
    {
        movePls = false;
    }

    return movePls;
}//end needMove

/*bool moveable(double x, double y)
{
    bool fairMove = true;
    Tile tile;
    tile = getTile(x, y);

    int i;
    for(i = 0; i < noWalkSpace.size() - 1, i++)
    {
        if(tile.tag == noWalkSpace[i])
        {
            fairMove = false;
        }
    }
    return fairMove;
}//end moveable*/

bool MovementEngine::blocked(double curx, double cury, double destx, double desty)
{//checks if blocked by impassable object
    Raycast caster;

    bool blocked = false;
    double checkx = curx;
    double checky = cury;
    double distance = 0.0;

    //get angle to destination
    double run = destx - curx;
    double rise = desty - cury;
    double theta = atan2(rise/run);
    double mathTheta = atan(rise/run);
    theta = theta * (180/M_PI);

    for(int i = 1; i < 10; i++)
    {
        caster.distanceCalc(curx, cury, theta);//get distance to first tile

        distance = caster.getCurrentDistance();

        checkx = (distance * cos(mathTheta));//distance in x direction
        checky = (distance * sin(mathTheta));//distance in y direction

        int tilex = m.getTileX(int(checkx));
        int tiley = m.getTileY(int(checky));

        if(m.getTileTag(tilex, tiley) == 1)//TODO: make array of impassable objects
        {
            blocked = true;
            blockedx = checkx;
            blockedy = checky;
        }
    }
    return blocked;
}//end blocked(4 param)

/*   A* pathing!!! to be implemented if time!!!! change to recursive
bool blocked(double x, double y, int wall, double dir)
{//checks along path while same wall is hit
    Raycast caster;

    bool blocked = false;
    double checkx = x;
    double checky = y;
    double distance = 0.0;
    caster.setCurrentx(checkx);
    caster.setCurrenty(checky);


}

void MovementEngine::aiPath(double destx, double desty, double curx, double cury, double speed)//to be used once per game loop
{
    int step = 0;

    Raycast pather;
    pather.setCurrentx(curx);
    pather.setCurrenty(cury);

    double distx = destx - curx;//distance needed in x direction to get to destination
    double disty = desty - cury;//distance needed in y direction to get to destination

    double direction = atan2(movey, movex);

    this.setDirection(direction);

    pather.setCurrentTheta(direction);

    bool keepGoing = true;
    while(keepGoing)
    {
        if(!blocked(curx, cury, destx, desty))
        {
            if(!atDest(destx, desty, curx, cury))//if loop so can be updated once per loop
            {
                double movex = destx - curx;//distance needed in x direction to get to destination
                double movey = desty - cury;//distance needed in y direction to get to destination

                double direction = atan2(movey, movex);

                //updates x and y for next draw
                //curx += cos(direction) * speed;
                //cury += sin(direction) * speed;
                aix[step] = cos(direction);
                aiy[step] = sin(direction);
                direction = direction * (180 / M_PI);//turn direction into degrees for transfer to distanceClac

                path[step] = pather.distanceCalc(aix[step], aiy[step], direction);
                step++;
            }
            else//at dest
            {
                keepGoing = false;
            }
        }
        else//blocked
        {
            double leftRay = pather.distanceCalc(aix[step], aiy[step], direction - 90);
            double leftTheta = pather.getCurrentTheta();
            double rightRay = pather.distanceCalc(aix[step], aiy[step], direction + 90);
            double rightTheta = pather.getCurrentTheta();


        }
    }//end while
}//end act
*/

void aiPath(double destx, double desty, double curx, double cury, double speed)
{
    double movex = destx - curx;//distance needed in x direction to get to destination
    double movey = desty - cury;//distance needed in y direction to get to destination

    double direction = atan2(movey, movex);

    if(!blocked(destx, desty, curx, cury))// if can get to dest
    {
        //updates x and y for next draw
        curx += cos(direction) * speed;
        cury += sin(direction) * speed;
    }

    else//move in direction that is less blocked
    {
        if(blockedx > blockedy)
        {
            curx += cos(direction) * speed;
        }
        else if(blockedx < blockedy)
        {
            cury += sin(direction) * speed;
        }
    }
}//end ai path

double MovementEngine::getBlockedX(double curx, double cury, double destx, double desty)
{
    if(blocked(curx, cury, destx, desty))
    {
        return blockedx;
    }
}//end getBlockedX

double MovementEngine::getBlockedY(double curx, double cury, double destx, double desty)
{
    if(blocked(curx, cury, destx, desty))
    {
        return blockedy;
    }
}//end getBlockedY

void MovementEngine::setDirection(double theta)
{
    MovementEngine::direction = theta;
}

