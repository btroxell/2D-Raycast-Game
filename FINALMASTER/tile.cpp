// tile.cpp
// Alex Rutan
// 3/28/15

#include <iostream>
#include "tile.h"

using namespace std;

Tile::Tile()
{
    Tile::ID = -1;
    Tile::tag = -1;
    Xcoord = -1;
    Ycoord = -1;
} //end constructor

Tile::~Tile()
{
  // cout << "goodbye" << endl;
} //end destructor

void Tile::setInfo(int w, int x, int y, int z)
{
    ID = z;//not really used...
    tag = w;
    Xcoord = x;
    Ycoord = y;

    //    cout << "ID: " << ID << endl;
    //    cout << "Tag: " << tag << endl;
    //    cout << "x: " << Xcoord << endl;
    //    cout << "y: " << Ycoord << endl;
    //    cout << " " << endl;
} //end setInfo

int Tile::getX()
{
    return(Xcoord);
} //end getX

int Tile::getY()
{
    return(Ycoord);
} //end getY

int Tile::getTag()
{
    return Tile::tag;
}//end getTag
