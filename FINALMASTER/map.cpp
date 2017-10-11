// map.cpp
// Alex Rutan
// 3/26/15

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "map.h"
#include "tile.h"

using namespace std;

/*
  Used by and used for just about everything!
  Most/all tile info comes from here including tags.
     ^^^very important for finding walls, enemies, items, etc.
  
 */

Map::Map()
{
    Map::gridX = 25;//x dist
    Map::gridY = 25;//y dist
    Map::tileX[625];//stores x info for every tile
    Map::tileY[625];//stores y info for every tile
    Map::tileTag[625];//stores tag info for every tile
    this->loadMap();//loads map
    for(int i = 0; i < enemies.size(); i++)//sets map for entities
      {
	enemies[i].setMap(this);
      }
} //end constructor

Map::~Map()
{
} //end destructor


void Map::loadMap()
{
    int count = 0;//counts thru arrays
    vector<int>mapData(gridX*gridY);//holds all tile tags
    vector<Tile>tile(gridX*gridY);//holds all tiles
    ifstream inFile;//file stream for reading
    stringstream ss;//string stream for parseing chars to ints
    inFile.open("game.map");//reads map in file
    int fileCounter = 0;//indexer for reading file
    while(!inFile.eof())
      {
	string data;//string to hold numbers
	getline(inFile, data, ',');//read each tag
	int tag;//int to become tags
	//convert to int
	ss << data;
	//cout << data << endl; 
	ss >> tag;
	//cout << tag << endl;
	//resets stringstream
	ss.clear();
	ss.str("");
	mapData[fileCounter] = tag;//set tag in mapdata
	fileCounter++;
	//cout << tag << endl;
      }

    //prints initial map in proper format
    for(int y = 0; y < 25; y++)
      {
	for(int x = 0; x < 25; x++)
	  {
	    cout << mapData[25*y + x];
	  }
	cout <<endl;
      }
    //TODO: mapFile should be read from an external .map file.
    /*int mapFile[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		     1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		     1, 0, 0, 0, 2, 0, 0, 4, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		     1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
		     1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1,
		     1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1,
		     1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1,
		     1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
		     1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		     1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		     1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		     1, 0, 0, 0, 2, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1,
		     1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
		     1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1,
		     1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
		     1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
		     1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
		     1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
		     1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		     1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1,
		     1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		     1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 1,
		     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    */
    for (int i = 0; i < gridY; i++)
    {
      for (int j = 0; j < gridX; j++)
	{//sets all info for each tile
	    tile[count].setInfo(mapData[count], i, i, count);//<== weird!! takes both i and works fine. if either are j, the j dimension only gets 1 pixel width.
	    //^^^ size of grid determines size of tiles??? made with the intent to allow different map sizes,
	    //but upon realizing this dependancy, we started hard coding 25 in other classes.
      	    tileX[count] = tile[count].getX();
	    tileY[count] = tile[count].getY();
    	    tileTag[count] = tile[count].getTag();
	    if(tileTag[count] == 4)//finds enemies
	      {
		//cout << tileX[count] << "  " << tileY[count] << endl;
		enemies.push_back(Enemy(j*25 + .5, i*25 + .5));
	      }
	    if(tileTag[count] == 3)//finds spawn point
	      {
		initPlayerX = j*25 + .5;//sets player poition
		initPlayerY = i*25 + .5;//sets plater position
	      }
    	    count++;
      } //end for
    } //end for
} //end loadMap

int Map::getTileX(int x)
{//returns x coord of index given
    return(tileX[x]);
} //end getTileX

int Map::getTileY(int y)
{//returns y coord of index given
    return(tileY[y]);
} //end getTileY

int Map::getTileTag(int x, int y)//gets tile tag at x,y coords
{//Phillip Anderson. added 4/14/15
    int myTag = -1;
    int i = gridX*y+x;
    
    //cout << x << "  " << y << endl;

    myTag = tileTag[i];//get tag of tile
    
    return myTag;//return tag
}//end getTileTag

void Map::setTileTag(int x, int y, int tag)
{//sets given tile's tag to tag
    int i = gridX*y+x;
    tileTag[i] = tag;
}

bool Map::isWall(double checkx, double checky)//checks given coords are a wall
{//Phillip Anderson
    //usually used with Raycast
    //find tile that contains x and y coords
    int x = floor(checkx);
    int y = floor(checky);

    bool wall = false;
    //get tile with x and y coords
    int tilex = getTileX(x);
    int tiley = getTileY(y);

    if(getTileTag(tilex, tiley) == 1)//if it's a wall...
    {
        wall = true;//...it's a wall.
    }

    return wall;
}

bool Map::isSolid(double checkx, double checky)//checks if tile is solid
{//Phillip Anderson
    //find tile of x and y
    int x = floor(checkx);
    int y = floor(checky);

    bool solid = false;

    //get tile
    int tilex = getTileX(x);
    int tiley = getTileY(y);

    //cout << tilex << "  " << tiley << endl;

    if(getTileTag(tilex, tiley) == 2)//TODO: make array of objects to be sprite-ed
      {//ammoPickup
        solid = true;
    }
    if(getTileTag(tilex, tiley) == 4)
      {//enemy
	solid = true;
      }

    return solid;
} //end isSolid

void Map::setEnemyMap(Map * map)
{//sets all enemy maps
  //using this after map has been read allows for different number of enemies
  for(int i = 0; i < enemies.size(); i++)
    {
      enemies[i].setMap(map);
    }
}

double Map::getInitPlayerX()
{//used to spawn player
  return initPlayerX;
}

double Map::getInitPlayerY()
{//used to spawn player
  return initPlayerY;
}
